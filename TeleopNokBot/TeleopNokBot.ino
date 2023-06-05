#include <ros.h>
#include <geometry_msgs/Twist.h>
#include "4_Wheel_Vehicle.h"
#include <Arduino.h>

const int STEP_SIZE = 100;

ros::NodeHandle nh;

void cmdVelCallback(const geometry_msgs::Twist& cmd_vel);

ros::Subscriber<geometry_msgs::Twist> cmd_vel_sub("cmd_vel", cmdVelCallback);

four_wheel_vehicle nokbot = four_wheel_vehicle(); 

void setup() {
  nh.initNode();
  nh.subscribe(cmd_vel_sub);
}

void loop() {
  nh.spinOnce();
}

void cmdVelCallback(const geometry_msgs::Twist& cmd_vel) {
  if (cmd_vel.linear.x > 0 && cmd_vel.linear.y == 0 && cmd_vel.angular.z == 0) {
    nokbot.run_forward(STEP_SIZE);
  }
  else if (cmd_vel.linear.x < 0 && cmd_vel.linear.y == 0 && cmd_vel.angular.z == 0) {
    nokbot.run_backward(STEP_SIZE);
  }
  else if (cmd_vel.linear.x == 0 && cmd_vel.linear.y > 0 && cmd_vel.angular.z == 0) {
    nokbot.run_right(STEP_SIZE);
  }
  else if (cmd_vel.linear.x == 0 && cmd_vel.linear.y < 0 && cmd_vel.angular.z == 0) {
    nokbot.run_left(STEP_SIZE);
  }
  else if (cmd_vel.linear.x > 0 && cmd_vel.linear.y > 0 && cmd_vel.angular.z == 0) {
    nokbot.run_forward_right(STEP_SIZE);
  }
  else if (cmd_vel.linear.x > 0 && cmd_vel.linear.y < 0 && cmd_vel.angular.z == 0) {
    nokbot.run_forward_left(STEP_SIZE);
  }
  else if (cmd_vel.linear.x < 0 && cmd_vel.linear.y > 0 && cmd_vel.angular.z == 0) {
    nokbot.run_backward_right(STEP_SIZE);
  }
  else if (cmd_vel.linear.x < 0 && cmd_vel.linear.y < 0 && cmd_vel.angular.z == 0) {
    nokbot.run_backward_left(STEP_SIZE);
  }
  else if (cmd_vel.linear.x == 0 && cmd_vel.linear.y == 0 && cmd_vel.angular.z > 0) {
    nokbot.rotate_cw(STEP_SIZE);
  }
  else if (cmd_vel.linear.x == 0 && cmd_vel.linear.y == 0 && cmd_vel.angular.z < 0) {
    nokbot.rotate_ccw(STEP_SIZE);
  }
  else {
    //digitalWrite(8, HIGH);
    // No valid movement state or do nothing
  }
}
