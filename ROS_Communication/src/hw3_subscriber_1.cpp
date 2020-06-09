#include "ros/ros.h"
#include "hw3/hw3_msg.h"

void msgCallback(const hw3::hw3_msg::ConstPtr& node2_msg) //Defining a callback function that will be run as a subscriber receives a message.
{
  ROS_INFO("%d is %s", node2_msg -> data, node2_msg -> oddeven.c_str()); //Display the message.
}

int main(int argc, char **argv)
{
  ros::init(argc, argv,"Node3"); //Initialize "Node3".
  ros::NodeHandle nh;

  ros::Subscriber hw3_subscriber = nh.subscribe("number_oddeven",100,msgCallback); //Declare "Node3" as a subscriber that subscribes to the "number_oddeven" topic. "msgCallback" function defined above will be executed as the subscriber receives message.

  ros::spin();
  
  return 0;
}
