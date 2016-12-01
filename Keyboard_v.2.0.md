#include <iostream>
#include <cstdlib>
//#include <time.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

class RobotDriver
{
private:
  //! The node handle we'll be using
  ros::NodeHandle nh_;
  //! We will be publishing to the "/base_controller/command" topic to issue commands
  ros::Publisher cmd_vel_pub_;

public:
  //! ROS node initialization
  RobotDriver(ros::NodeHandle &nh)
  {
    nh_ = nh;
    //set up the publisher for the cmd_vel_mux/input/teleop topic
    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
  }

  //! Loop forever while sending drive commands based on keyboard input
  bool driveKeyboard()
  {
    std::cout << "Type a command and then press enter.  "
      "Use 'w' to move forward, 's' to move backward, 'q' to turn forward-left, "
      "'e' to turn forward-right, 'd' to move backwards-left, 'a' to move backwards-right, '.' to exit.\n";

    //we will be sending commands of type "twist"
    geometry_msgs::Twist base_cmd;

    char cmd[50];
    while(nh_.ok()){

      std::cin.getline(cmd, 50);
      if(cmd[0]!='w' && cmd[0]!='s' && cmd[0]!='a' && cmd[0]!='d' && cmd[0]!='q' && cmd[0]!='e' && cmd[0]!='.')
      {
        std::cout << "unknown command:" << cmd << "\n";
        continue;
      }

      base_cmd.linear.x = base_cmd.linear.y = base_cmd.angular.z = 0;   
      //move forward
      if(cmd[0]=='w'){
        base_cmd.linear.x = 1.5;
      }
      
      //move backward
      if(cmd[0]=='s'){
        base_cmd.linear.x = -1.5;
      } 

      //turn forward-left (yaw) and drive forward at the same time
      else if(cmd[0]=='q'){
        base_cmd.angular.z = 5;
        base_cmd.linear.x = 1;
      } 
      //turn forward-right (yaw) and drive forward at the same time
      else if(cmd[0]=='e'){
        base_cmd.angular.z = -5;
        base_cmd.linear.x = 1;
      }
      //turn backward-left (yaw) and drive forward at the same time
      else if(cmd[0]=='d'){
        base_cmd.angular.z = 5;
        base_cmd.linear.x = -1;
      }
 
      //turn backward-right (yaw) and drive forward at the same time
      else if(cmd[0]=='a'){
        base_cmd.angular.z = -5;
        base_cmd.linear.x = -1;
      }

      //quit
      else if(cmd[0]=='.'){
        break;
      }

      //publish the assembled command
      cmd_vel_pub_.publish(base_cmd);
    }
    return true;
  }

};

int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "robot_driver");
  ros::NodeHandle nh;

  RobotDriver driver(nh);
  driver.driveKeyboard();
}
