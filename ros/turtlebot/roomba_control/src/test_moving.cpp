#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test_moving");
  ros::NodeHandle n;
  ros::Publisher velocity_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  ros::Rate rate(1);

  geometry_msgs::Twist msg;

  if (ros::ok())
  {
    msg.linear.x = 1.0; 
    msg.angular.z = 0;
    velocity_pub.publish(msg);
    ROS_INFO("%s", "Starting");
    ros::spinOnce();
    rate.sleep();
  }

  if (ros::ok())
  {
    msg.linear.x = 0.2; 
    msg.angular.z = 0;
    velocity_pub.publish(msg);
    ROS_INFO("%s", "Forward");
    ros::spinOnce();
    rate.sleep();
  }

  if (ros::ok())
  {
    msg.linear.x = -0.2; 
    msg.angular.z = 0;
    velocity_pub.publish(msg);
    ROS_INFO("%s", "Backward");
    ros::spinOnce();
    rate.sleep();
  }

  if (ros::ok())
  {
    msg.linear.x = 0; 
    msg.angular.z = 1.0;
    velocity_pub.publish(msg);
    ROS_INFO("%s", "Left");
    ros::spinOnce();
    rate.sleep();
  }
  if (ros::ok())
  {
    msg.linear.x = 0; 
    msg.angular.z = -1.0;
    velocity_pub.publish(msg);
    ROS_INFO("%s", "Right");
    ros::spinOnce();
    rate.sleep();
  }
  if (ros::ok())
  {
    msg.linear.x = 0; 
    msg.angular.z = 0;
    velocity_pub.publish(msg);
    ROS_INFO("%s", "Stop");
    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}

