#include <ros.h>
#include <geometry_msgs/Twist.h>
#include "4_Wheel_Vehicle.h"
#include <Arduino.h>
//#include <sensor_msgs/Range.h>

//const int TRIG_PIN_FWD = 22;
//const int ECHO_PIN_FWD = 23;
//const int TRIG_PIN_BACK = 24;
//const int ECHO_PIN_BACK = 25;
//const int SONAR_FREQ = 40;
const int STEP_SIZE = 100;

// ROS node handle
ros::NodeHandle nh;

// Function prototypes
void cmdVelCallback(const geometry_msgs::Twist& cmd_vel);
//void updateMotors(double cmd_vel.linear.x, double cmd_vel.linear.y, double cmd_vel.angular.z);
//float readUltrasonicSensor(int trigPin, int echoPin);

// ROS subscriber and publishers
ros::Subscriber<geometry_msgs::Twist> cmd_vel_sub("cmd_vel", cmdVelCallback);
//sensor_msgs::Range range_msg_fwd;
//sensor_msgs::Range range_msg_back;
//ros::Publisher sensor_pub_fwd("range_data_fwd", &range_msg_fwd);
//ros::Publisher sensor_pub_back("range_data_back", &range_msg_back);


four_wheel_vehicle nokbot = four_wheel_vehicle(); 

void setup() {
  nh.initNode();
  nh.subscribe(cmd_vel_sub);
//  nh.advertise(sensor_pub_fwd);
//  nh.advertise(sensor_pub_back);
//  pinMode(TRIG_PIN_FWD, OUTPUT);
//  pinMode(ECHO_PIN_FWD, INPUT);
//  pinMode(TRIG_PIN_BACK, OUTPUT);
//  pinMode(ECHO_PIN_BACK, INPUT);

//  range_msg_fwd.radiation_type = sensor_msgs::Range::ULTRASOUND;
//  range_msg_fwd.field_of_view = 1.0;  // Approximate, adjust to your sensor
//  range_msg_fwd.min_range = 0.02;  // HC-SR04 specs
//  range_msg_fwd.max_range = 4.0;  // HC-SR04 specs
//
//  range_msg_back.radiation_type = sensor_msgs::Range::ULTRASOUND;
//  range_msg_back.field_of_view = 1.0;  // Approximate, adjust to your sensor
//  range_msg_back.min_range = 0.02;  // HC-SR04 specs
//  range_msg_back.max_range = 4.0;  // HC-SR04 specs
}

void loop() {
  nh.spinOnce();

//  range_msg_fwd.range = readUltrasonicSensor(TRIG_PIN_FWD, ECHO_PIN_FWD);
//  range_msg_fwd.header.stamp = nh.now();
//  sensor_pub_fwd.publish(&range_msg_fwd);
//
//  range_msg_back.range = readUltrasonicSensor(TRIG_PIN_BACK, ECHO_PIN_BACK);
//  range_msg_back.header.stamp = nh.now();
//  sensor_pub_back.publish(&range_msg_back);
 
//  delay(1000 / SONAR_FREQ); // Adjust to sensor's maximum frequency
//delay(100);
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
    digitalWrite(8, HIGH);
    // No valid movement state or do nothing
  }

//if(cmd_vel.linear.x > 0)
//nokbot.run_forward(100);


}
//
//float readUltrasonicSensor(int trigPin, int echoPin) {
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  long duration = pulseIn(echoPin, HIGH);
//  float distance = duration 
//  * 0.00034 / 2; //metres
//
//    // Check if measurement is within the sensor range
//  if (distance < 0.02 || distance > 4.0) {
//    return NAN;
//  }
//  
//  return distance;
//}
