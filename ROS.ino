#include "Header.h"

void setupROS()
{ 
  // Set LED color to yellow to indicate connection establishment  
  leds[0] = CRGB(100, 100, 0);
  leds[1] = CRGB(100, 100, 0);
  FastLED.show();
  
  // Initialize NodeHandle
  nh.initNode();
  nh.getHardware()->setBaud(115200);

  // Setup publishers
  nh.advertise(left_dist_pub);
  nh.advertise(front_dist_pub);
  nh.advertise(right_dist_pub);
  nh.advertise(pose_pub);

  // Setup subscribers
  nh.subscribe(cmd_vel_sub);
  nh.subscribe(rgb_leds_sub);
  nh.subscribe(set_pose_sub);

  // Wait until you are actually connected
  while (!nh.connected())
  {
    nh.spinOnce();
  }

  // Set LED color to green to indicate succesful connection with ROS
  leds[0] = CRGB(50, 100, 0);
  leds[1] = CRGB(50, 100, 0);
  FastLED.show();
}

void publishSensorData() {
  
  // Set message data and publish message
  int left_ir, front_ir, right_ir;
  readSensorsIR(&left_ir, &front_ir, &right_ir);
  
  dist_msg.data = left_ir;
  left_dist_pub.publish(&dist_msg);

  dist_msg.data = front_ir;
  front_dist_pub.publish(&dist_msg);

  dist_msg.data = right_ir;
  right_dist_pub.publish(&dist_msg);
  
}

void publish()
{
    publishPose();
    publishSensorData();
}

void publishPose() {
  // Publish robot pose
  pose_msg.x = robotPosition.x;
  pose_msg.y = robotPosition.y;
  pose_msg.theta = robotPosition.theta;
  pose_pub.publish(&pose_msg);
}


void readCmdVel(const geometry_msgs::Twist& msg) {
  // Receive cmd_vel message and process
  float linear = msg.linear.x;
  float angular = msg.angular.z;
  desiredSpeed = cmd_vel(linear, angular); // pass desired linear velocity (m/s) and angular velocitiy (rad/s)
  
}

void setPose(const geometry_msgs::Pose2D& msg) {
  // Receive pose and set robot position
  robotPosition.x = msg.x;
  robotPosition.y = msg.y;
  robotPosition.theta = msg.theta;
}

void setLED(const std_msgs::UInt8MultiArray& msg) {
  // Set RGB LEDs
  leds[0] = CRGB(msg.data[0], msg.data[1], msg.data[2]);
  leds[1] = CRGB(msg.data[3], msg.data[4], msg.data[5]);
  FastLED.show();
}
