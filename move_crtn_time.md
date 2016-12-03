#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
ros::init(argc, argv, "move_pub");
ros::NodeHandle n;
ros::Publisher movement_pub = n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",100); 
ros::Rate rate(10);

double linspeed;
double angspeed;
std::cout << "This code will make the robot move at a certain speed for a certain time, the combinations that you enter speed-wise will define whether it goes forward/backward, to the sides, etc." << std::endl;

std::cout << "Enter desired linear speed between 0.1 and 1.5, to go forward; between -0.1 and -1.5 to go backward: " << std::endl;
std::cin >> linspeed;
std::cout << "Enter desired angular speed between 0.1 and 13.9 to go to the left; between -0.1 and -13.9 to go the right : " << std::endl;
std::cin >> angspeed;

double usrtime;
std::cout << "Enter the desired time of travel in seconds" << std::endl;
std::cin >> usrtime;

ros::Time start = ros::Time::now();
while (ros::Time::now() - start < ros::Duration(usrtime)) 
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
