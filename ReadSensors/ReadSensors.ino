#include <ros.h>
#include <Arduino.h>
#include <sensor_msgs/Range.h>
#include <std_msgs/Bool.h>

//add ultrasonic pin config
const int TRIG_PIN_FWD = 22;
const int ECHO_PIN_FWD = 23;
const int TRIG_PIN_BACK = 24;
const int ECHO_PIN_BACK = 25;
//add ultrasonic freq
const int SONAR_FREQ = 40;
// Add electromagnet control pin
const int ELECTROMAGNET_PIN = 8;


// ROS node handle
ros::NodeHandle nh;

// Function prototypes
float readUltrasonicSensor(int trigPin, int echoPin);
// Callback function for electromagnet control
void electromagnetControlCallback(const std_msgs::Bool& msg);

// ROS subscriber and publishers
//add range publishers
sensor_msgs::Range range_msg_fwd;
sensor_msgs::Range range_msg_back;
ros::Publisher sensor_pub_fwd("range_data_fwd", &range_msg_fwd);
ros::Publisher sensor_pub_back("range_data_back", &range_msg_back);
// Add subscriber for electromagnet control
ros::Subscriber<std_msgs::Bool> electromagnet_sub("electromagnet_cmd", &electromagnetControlCallback);

void setup() {
  //ros node initalise
  nh.initNode();
  //ros publishers
  nh.advertise(sensor_pub_fwd);
  nh.advertise(sensor_pub_back);
  // ros subscriber
  nh.subscribe(electromagnet_sub);
  //ultrasonic pin config
  pinMode(TRIG_PIN_FWD, OUTPUT);
  pinMode(ECHO_PIN_FWD, INPUT);
  pinMode(TRIG_PIN_BACK, OUTPUT);
  pinMode(ECHO_PIN_BACK, INPUT);
  // electromagnet pin config
  pinMode(ELECTROMAGNET_PIN, OUTPUT);



//Ros message info
  range_msg_fwd.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg_fwd.field_of_view = 1.0;  // Approximate, adjust to your sensor
  range_msg_fwd.min_range = 0.02;  // HC-SR04 specs
  range_msg_fwd.max_range = 4.0;  // HC-SR04 specs

  range_msg_back.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg_back.field_of_view = 1.0;  // Approximate, adjust to your sensor
  range_msg_back.min_range = 0.02;  // HC-SR04 specs
  range_msg_back.max_range = 4.0;  // HC-SR04 specs
}

void loop() {
  nh.spinOnce();

  range_msg_fwd.range = readUltrasonicSensor(TRIG_PIN_FWD, ECHO_PIN_FWD);
  range_msg_fwd.header.stamp = nh.now();
  sensor_pub_fwd.publish(&range_msg_fwd);

  range_msg_back.range = readUltrasonicSensor(TRIG_PIN_BACK, ECHO_PIN_BACK);
  range_msg_back.header.stamp = nh.now();
  sensor_pub_back.publish(&range_msg_back);
 
  delay(1000 / SONAR_FREQ); // Adjust to sensor's maximum frequency

}


float readUltrasonicSensor(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration 
  * 0.00034 / 2; //metres

    // Check if measurement is within the sensor range
  if (distance < 0.02 || distance > 4.0) {
    return NAN;
  }
  
  return distance;
}

// Function to control electromagnet
void electromagnetControlCallback(const std_msgs::Bool& msg) {
  digitalWrite(ELECTROMAGNET_PIN, msg.data ? HIGH : LOW);
}
