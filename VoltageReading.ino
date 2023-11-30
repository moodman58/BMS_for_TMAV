// pls run it on Linux
#include <Arduino.h>
#include <ros.h>
#include <std_msgs/Float32.h>

const int BATTERY_PIN = A0; //choose the pin
const float MAX_VOLTAGE = 9.0; // choose the max voltage

ros::NodeHandle nh;
std_msgs::Float32 battery_msg;
ros::Publisher battery_pub("battery_voltage", &battery_msg);

void setup() {
  nh.initNode();
  nh.advertise(battery_pub);
  Serial.begin(57600);
}

void loop() {
  int rawValue = analogRead(BATTERY_PIN);
  
  // Convert the raw analog value to voltage
  float voltage = (rawValue * MAX_VOLTAGE) / 1023.0;

  // Calculate the state of charge (SOC) based on your battery characteristics
  float soc = (voltage / MAX_VOLTAGE) * 100.0;
  soc = constrain(soc, 0, 100);  // Ensure SOC is within 0-100%

  // Publish the battery voltage to ROS
  battery_msg.data = voltage;
  battery_pub.publish(&battery_msg);

  // You can also publish the state of charge if needed
  // ROS uses the publish() function to send messages to a topic
  // For example: battery_state_of_charge_pub.publish(&battery_state_of_charge_msg);

  nh.spinOnce();

  delay(1000);  // Adjust the delay based on your requirements
}
