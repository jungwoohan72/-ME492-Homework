#include "ros/ros.h"
#include "hw3/hw3_msg.h" // Header file automatically generated from the created message file, "hw3_msg.msg".

int main(int argc, char **argv) 
{
  //Initialize "Node1".
  ros::init(argc, argv, "Node1");

  //Required to deal with the initialized node.
  ros::NodeHandle nh; 
  
  //Declare a publisher that publishes to topic named "number".
  ros::Publisher hw3_node1 = nh.advertise<hw3::hw3_msg>("number", 100);

  //Set "loop_rate" variable with 1Hz (it will be used to publish one message for every second).
  ros::Rate loop_rate(1);
  
  //Declare "node1_msg" variable that will be published to the topic.
  hw3::hw3_msg node1_msg;

  int count = 0;

  while (ros::ok())
  {
    node1_msg.data = count; //Set "data" attribute in node1_msg as "count".
    
    ROS_INFO("send msg = %d", node1_msg.data); //Show current value for "count".

    hw3_node1.publish(node1_msg); //"Node1" publishes "node1_msg" to the topic.

    loop_rate.sleep(); //Loop will be executed once for every second.

    ++count; //Increase "count" by 1 for every loop.
  }
  
  return 0;
}


    


