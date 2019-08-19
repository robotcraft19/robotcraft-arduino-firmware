#include "Header.h"

void update() // update service routine
{
  encUpdate(&oldEncoderLeft, &oldEncoderRight);
  poseUpdate();
  pidControl(realSpeed, desiredSpeed);
  readSensorsIR(&distanceIR_L, &distanceIR_F, &distanceIR_R);
}

void setup()
{ 
  // Setup pins
  pinMode(LEFT_ENCODER_A, INPUT);
  pinMode(LEFT_ENCODER_B, INPUT);
  pinMode(RIGHT_ENCODER_A, INPUT);
  pinMode(RIGHT_ENCODER_B, INPUT);

  // Initialize oldEncoder values
  encUpdate(&oldEncoderLeft, &oldEncoderRight);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(25);

  // Setup ROS
  setupROS();
 

  desiredSpeed = cmd_vel(0.00, 0.0); // pass desired linear velocity (m/s) and angular velocitiy (rad/s)

  // Start motors
  digitalWrite(RIGHT_MOTOR_DIR, FORWARD);
  analogWrite(RIGHT_MOTOR_PWM, 0);

  digitalWrite(LEFT_MOTOR_DIR, FORWARD);
  analogWrite(LEFT_MOTOR_PWM, 0);

  // Initialize timestamp
  timestamp = millis();
}

void loop()
{

  // Polling version of the code
  if ((millis() - timestamp) >= 1000 / UPDATE_FREQUENCY)
  {
    update();  // update robot
    publish(); // Publish all ROS messages
    nh.spinOnce(); // Receive messages
    timestamp = millis();
  }
}
