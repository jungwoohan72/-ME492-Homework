#include "ros/ros.h"
#include "hw3/hw3_msg.h"

std::string oddeven; //String type storage "oddeven" to store whether the subscribed number from "Node1" is even or odd.
int data; //Int type storage "data" to store the subscribed number from "Node1".

class PublishandSubscribe //"Node2" will work as both publisher and subscriber. Class definition for this kind of specific node.
{
public:
  PublishandSubscribe() 
  {
    hw3_node2_publisher = nh.advertise<hw3::hw3_msg>("number_oddeven", 100); //Declare "Node2" as a publisher that publishes to "number_oddeven" topic.
    hw3_node2_subscriber = nh.subscribe("number", 100, &PublishandSubscribe::msgCallback, this); //Declare "Node2" as a subscriber that subscribes a message from "number" topic.
  }

  void msgCallback(const hw3::hw3_msg::ConstPtr& node1_msg) //Defining a callback function that will be run if the subscriber receives a message.
  {
    hw3::hw3_msg node2_msg; //Create "node2_msg" message that will be published to "number_oddeven" topic.

    node2_msg.data = node1_msg -> data; //Set "data" attribute in node2_msg as the number subscribed from "number" topic.

    if (node2_msg.data % 2)
    {
      ROS_INFO("ODD");
      node2_msg.oddeven = "ODD"; //If the number subscribed from "number" topic is odd, declare "oddeven" attribute in node2_msg as a string, "ODD".
    }
    else
    {
      ROS_INFO("EVEN");
      node2_msg.oddeven = "EVEN"; //If the number subscribed from "number" topic is even, declare "oddeven" attribute in node2_msg as a string, "EVEN".
    }

    hw3_node2_publisher.publish(node2_msg); //Publishes the node2_msg to "number_oddeven" topic.
  }

private:
  ros::Publisher hw3_node2_publisher;
  ros::Subscriber hw3_node2_subscriber;
  ros::NodeHandle nh;

};

int main(int argc, char **argv)
{
  ros::init(argc,argv,"Node2"); //Initialize "Node2".

  PublishandSubscribe hw3_Node2; //Set "Node2" as both publisher and subscriber by using the defined class, "PublishandSubscribe".
  ros::spin(); //Keep subscribing message.

  return 0;
}


