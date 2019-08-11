#include <Encoder.h>
#include "Header.h"

void update() // update service routine
{
  encUpdate(&oldEncoderLeft, &oldEncoderRight);
  poseUpdate();
  pidControl(realSpeed, desiredSpeed);
  readSensorsIR(&distanceIR_L, &distanceIR_F, &distanceIR_R);

  /*
  Serial.println(realSpeed.lin_vel);

  float x = robotPosition.x;
  float theta = radToDeg(robotPosition.theta);
  
  if (x >= 0.2)
  {
    analogWrite(RIGHT_MOTOR_PWM, 0);
    analogWrite(LEFT_MOTOR_PWM, 0);
    desiredSpeed.lin_vel = 0.0;
    desiredSpeed.ang_vel = 0.0;
  }
  
  printRobotPosition();
  printSensorsIR();
  */
}

void setup()
{
  // Setup serial
  Serial.begin(9600);
  
  // Setup pins
  pinMode(LEFT_ENCODER_A, INPUT);
  pinMode(LEFT_ENCODER_B, INPUT);
  pinMode(RIGHT_ENCODER_A, INPUT);
  pinMode(RIGHT_ENCODER_B, INPUT);

  // Initialize oldEncoder values
  encUpdate(&oldEncoderLeft, &oldEncoderRight);

  desiredSpeed = cmd_vel(0.05, 0.0); // pass desired linear velocity (m/s) and angular velocitiy (rad/s)

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
    update();
    timestamp = millis();


    
  }
}
