#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

using namespace std;

int argc 
char **argv

ros::init(argc, argv, "move_pub");
ros::NodeHandle n;
ros::Publisher cmd_vel_pub_ = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1); 
ros::Rate rate(10);
while(ros::ok()){
    //we will be sending commands of type "twist"
          geometry_msgs::Twist base_cmd;

      char cmd;
      cin >> cmd;
      if(cmd!='w' && cmd!='s' && cmd!='a' && cmd!='d' && cmd!='q' && cmd!='e' && cmd!='.')
      {
        cout << "unknown command:" << cmd << "\n";
        continue;
      }
   
      base_cmd.linear.x = base_cmd.linear.y = base_cmd.angular.z = 0;

void move (char letter, int x, int z){
//move in different directions: forward, forward left and right, backwards, backwards left and right
if(cmd== letter){
      base_cmd.linear.x = x;
      base_cmd.angular.z = z;
   }
}


int main(int argc, char **argv){
while (ros::ok())
 {
    cout << "Type a command and then press enter.  "
      "Use 'w' to move forward, 's' to move backward, 'q' to turn forward-left, "
      "'e' to turn forward-right, 'd' to move backwards-left, 'a' to move backwards-right, '.' to exit.\n";

    while(ros::ok()){
      move('w', 1.5, 0);
      
/*
      //move backward
      else if(cmd=='s'){
        base_cmd.linear.x = -1.5;
      } 

      //turn forward-left (yaw) and drive forward at the same time
      else if(cmd=='q'){
        base_cmd.angular.z = 5;
        base_cmd.linear.x = 1;
      } 
      //turn forward-right (yaw) and drive forward at the same time
      else if(cmd=='e'){
        base_cmd.angular.z = -5;
        base_cmd.linear.x = 1;
      }
      //turn backward-left (yaw) and drive forward at the same time
      else if(cmd=='d'){
        base_cmd.angular.z = 5;
        base_cmd.linear.x = -1;
      }
 
      //turn backward-right (yaw) and drive forward at the same time
      else if(cmd=='a'){
        base_cmd.angular.z = -5;
        base_cmd.linear.x = -1;
      }

      //quit
      else if(cmd=='.'){
        break;
      }
*/

      //publish the assembled command
      cmd_vel_pub_.publish(base_cmd);

      ros::spinOnce();
      rate.sleep();
    }
  }
return 0;
}



