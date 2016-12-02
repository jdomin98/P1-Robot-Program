#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
ros::init(argc, argv, "move_pub");
ros::NodeHandle n;
ros::Publisher movement_pub = n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",1); 
ros::Rate rate(10);

double linspeed;
double angspeed;
std::cout << "This code will make the robot move at your chosen speed...forever! Here are the combinations that you have to type for it to move in different directions, if you just want to move forward/backward enter a linear speed but no angular; if you want to spin in its place, enter an angular speed but no linear; if you wanna advance and turn here are the sign combinations: + l.speed and + a.speed to go forward left; + l.speed and - a.speed to go forward right; - l.speed and + a.speed to go backward left; - l.speed and - a.speed to go backward right" << std::endl;

std::cout << "Enter desired linear speed between 0.1 and 1.5, to go forward; between -0.1 and -1.5 to go backward: " << std::endl;
std::cin >> linspeed;
std::cout << "Enter desired angular speed between 0.1 and 5 to go to the left; between -0.1 and -5 to go the right: " << std::endl;
std::cin >> angspeed;


while (ros::ok()) 
{
    geometry_msgs::Twist move;
    //velocity controls
    move.linear.x = linspeed; //linear speed value m/s
    move.angular.z = angspeed; //angular speed value m/s
    movement_pub.publish(move);

    ros::spinOnce();
    rate.sleep();
}
return 0;
}
