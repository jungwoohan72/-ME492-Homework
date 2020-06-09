#include <ros/ros.h>
#include "string.h"
#include <cmath>
#include <sensor_msgs/PointCloud2.h>
//#include <pcl_conversions/pcl_conversions.h>
#include <vector>
#include <algorithm>
#include <opencv2/highgui.hpp>
#include <opencv2/plot.hpp>

#include <iostream>
//#include <pcl/io/pcd_io.h>
//#include <pcl/point_types.h>
//#include <pcl/point_cloud.h>

#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

Mat frame;
Mat gray;
Mat flip_img;

void Image_callback(const sensor_msgs::ImageConstPtr &msg){

	try{
	    frame = cv_bridge::toCvShare(msg, "bgr8")->image;
	    cvtColor(frame, gray, COLOR_BGR2GRAY);
            cv::flip(frame, flip_img, 1);
 
	}

	catch (cv_bridge::Exception& e){
		ROS_ERROR("Could not convert from '%s' to 'grayscale'.", msg->encoding.c_str());
	}

}

int main(int argc, char **argv){

    ros::init(argc, argv, "img_node");
    ros::NodeHandle nh;

    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub_gray = it.advertise("/grayscale/image" , 1);
    image_transport::Publisher pub_flipped = it.advertise("/flipped/image", 1);
    image_transport::Subscriber sub = it.subscribe("/camera/rgb/image_raw", 1, Image_callback);

    sensor_msgs::ImagePtr msg_gray;
    sensor_msgs::ImagePtr msg_flip;

    ros::Rate loop_rate(30);

    while(ros::ok()){
        msg_gray = cv_bridge::CvImage(std_msgs::Header(), "mono8", gray).toImageMsg();
        msg_flip = cv_bridge::CvImage(std_msgs::Header(), "bgr8", flip_img).toImageMsg();

        pub_gray.publish(msg_gray);
        pub_flipped.publish(msg_flip);
        ROS_INFO("ImageMsg Send.");

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
