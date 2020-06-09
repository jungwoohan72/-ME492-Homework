#include <ros/ros.h>
#include "string.h"
#include <cmath>
#include <sensor_msgs/LaserScan.h>
#include <vector>
#include <algorithm>

#include <fstream>
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/extract_indices.h>

using namespace std;

// Global variable
pcl::PointCloud<pcl::PointXYZ>::Ptr prev_cloud (new::pcl::PointCloud<pcl::PointXYZ>); //Point cloud 변수 선언
Eigen::Matrix4f transMtx_now; // 현재 위치 정보를 저장하기 위한 4 x 4 매트릭스 선언
Eigen::Matrix4f transMtx_prev; // 직전 위치 정보를 저장하기 위한 4 x 4 매트릭스 선언
Eigen::Matrix4f transMtx_delta; // transMtx_now와 transMtx_prev간의 transformation matrix 정보를 저장하기 위한 매트릭스 선언

double pos[3]; // 현재 로봇의 x, y, theta 값을 저장하기 위한 Array 선언

void lidar_cb(sensor_msgs::LaserScan msg){

    // angle in radian
    float angle_min = msg.angle_min; // 라이다 센서 시작 각도
    float angle_max = msg.angle_max; // 라이다 센서 종료 각도
    float angle_increment = msg.angle_increment; // 시작 각도와 종료 각도 사이의 각도 증가 step
    std::vector<float> range = msg.ranges; // 각 각도 값에 위치해 있는 장애물의 거리 정보 저장. 여기선 angle_min이 0도이고, angle_max가 360도, 그리고 angle_increment가 1도이므로 총 360개의 거리 정보가 저장

    // size of range vector
    int len = range.size();
    float angle_now;

    /// 1. LaserScan msg to PCL::PointXYZ

    // initializae pointcloud
    pcl::PointCloud<pcl::PointXYZ>::Ptr new_cloud (new::pcl::PointCloud<pcl::PointXYZ>); // 로봇이 움직임에 따른 변화된 point cloud를 저장하기 위한 변수 선언
    pcl::ExtractIndices<pcl::PointXYZ> extract; // new_cloud에서 inf_points를 제거한 point cloud를 저장하기 위한 변수 선언
    pcl::PointIndices::Ptr inf_points(new pcl::PointIndices()); // range 값에 inf가 찍히는 point data를 저장

    new_cloud->is_dense = false;
    new_cloud->width = len;
    new_cloud->height = 1;
    new_cloud->points.resize(len);

    // fill the pointcloud
    for(int i = 0; i < len; i++){

        // TO DO START

        angle_now = angle_min + i*angle_increment;

        // TO DO END

        if (std::isinf(range[i])==false){

            // TO DO START

            new_cloud -> points[i].x = range[i]*cos(angle_now);
            new_cloud -> points[i].y = range[i]*sin(angle_now);
            new_cloud -> points[i].z = 0;

            // TO DO END

        }
        else{
            // indices of infinite distance points
            inf_points->indices.push_back(i);

        }
    }

    // Remove infinite distance points from new_cloud
    extract.setInputCloud(new_cloud);
    extract.setIndices(inf_points);
    extract.setNegative(true);
    extract.filter(*new_cloud);

    // 2. Get transformation between previous pointcloud and current pointcloud

    // transMtx_prev : transformation matrix at time (t-1)
    // transMtx_now : transformation matrix at time (t)
    // 4X4 transformation matrix (3X3: rotation matrix, 3X1: translation vector)

    if(prev_cloud->width == 0){

        // initialize transformation matrix. initial posiiton: x = 0, y = 0, theta = 0;
        transMtx_prev << cos(0), -sin(0), 0, 0,
                        sin(0), cos(0), 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1;
        pos[2] = 0;
    }

    else{

        // ICP algorithm
        // http://pointclouds.org/documentation/tutorials/iterative_closest_point.php
        // http://pointclouds.org/documentation/tutorials/interactive_icp.php#interactive-icp
        pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
        icp.setInputSource(prev_cloud);
        icp.setInputTarget(new_cloud);
        pcl::PointCloud<pcl::PointXYZ> Final;
        icp.align(Final);
        std::cout << "has converged:" << icp.hasConverged() << " score: " <<
        icp.getFitnessScore() << std::endl;
        std::cout << icp.getFinalTransformation() << std::endl;

        transMtx_delta = icp.getFinalTransformation();

    // 3. Get current transformation matrix using previous transformation and ICP result
    //  (Odometry calculation)

        // TO DO START

        transMtx_now = transMtx_prev*transMtx_delta;

        // TO DO END

    // 4. Get current position from transformation matrix

        // TO DO START

        pos[0] = transMtx_now(0,3);
        pos[1] = transMtx_now(1,3);
        pos[2] = pos[2] + asin(transMtx_delta(1,0));

        // TO DO END

        transMtx_prev = transMtx_now; // Save current transformation matrix in transMtx_prev

    }
    // 5. Save new_cloud in prev_cloud

    prev_cloud = new_cloud;

}

int main(int argc, char **argv){

    ros::init(argc, argv, "lidar_homework_node");
    ros::NodeHandle nh;

    ros::Subscriber sub_lidar = nh.subscribe("/scan", 1, lidar_cb);

    ros::Rate loop_rate(5);

    // initialize prev_cloud
    prev_cloud->width = 0;

    // File write

    // TO DO START
    string filePath = "/home/me492/catkin_ws/src/lidar_homework/hw4_result.txt"; //<- Change to your own directory
    // TO DO END

    ofstream txtFile(filePath);

    while(ros::ok()){
        ros::spinOnce();

        ROS_INFO("pos : x = %f | y = %f | theta = %f", pos[0], pos[1], pos[2]);
        txtFile << pos[0] << "\t" << pos[1] << "\t" << pos[2] << endl;

        loop_rate.sleep();
    }

    txtFile.close();
    return 0;
}
