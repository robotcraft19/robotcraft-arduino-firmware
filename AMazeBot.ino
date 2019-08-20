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
  
  // Motors
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
 

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
    
    if(rosOK() == true) {
        publish(); // Publish all ROS messages
        nh.spinOnce(); // Receive messages
    } 
    else {
        desiredSpeed = cmd_vel(0.00, 0.0); // Stop locally because message not getting through anymore
    }
    
    if (cmd_vel_timeout >= 5)
    {
        desiredSpeed = cmd_vel(0.00, 0.0);
        cmd_vel_pub.publish(&stop_msg); // Stop robot after timeout when not receiving any new messages
    }

    cmd_vel_timeout++;
    timestamp = millis();
  }
}
