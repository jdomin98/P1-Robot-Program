#include "ros/ros.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"

void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)

{
ROS_INFO("I received odom: [%f,%f,%f]", odom->twist.twist.linear.x, odom->pose.pose.position.y,odom->pose.pose.position.z); //store x,y,z position values
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle nh;
  ros::Subscriber sub_odom = nh.subscribe("odom", 1000, odomCallback);

double x_pos = odom.pose.pose.position.x;
double y_pos = odom.pose.pose.position.y;
double z_pos = odom.pose.pose.position.z;

  double x_epos = 0.2; //desired end position

while (x_pos < x_epos && ros::ok()) //while robot is not at the end position

{
//move the robot towards the end position
    ros::Publisher movement_pub = nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 10);
    geometry_msgs::Twist vel;
    vel.linear.x = 2.0;
    vel.angular.z = 0.0;

   movement_pub.publish(vel);

}

  ros::spin();
  return 0;
}
