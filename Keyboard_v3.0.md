#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>


int main(int argc, char **argv)
{
ros::init(argc, argv, "move_pub");
ros::NodeHandle n;
ros::Publisher cmd_vel_pub_ = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1); 
ros::Rate rate(10);

while (ros::ok())
 {
    std::cout << "Type a command and then press enter.  "
      "Use 'w' to move forward, 's' to move backward, 'q' to turn forward-left, "
      "'e' to turn forward-right, 'd' to move backwards-left, 'a' to move backwards-right, '.' to exit.\n";

    //we will be sending commands of type "twist"
    geometry_msgs::Twist base_cmd;

    char cmd[50];
    while(ros::ok()){

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

  }
return 0;

}


