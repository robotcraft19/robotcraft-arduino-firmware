#include <Encoder.h>
#include "Header.h"

void update() // update service routine
{
  encUpdate(&oldEncoderLeft, &oldEncoderRight);
  poseUpdate();
  pidControl(realSpeed, desiredSpeed);

  Serial.println(realSpeed.ang_vel);

  float x = robotPosition.x;
  float theta = radToDeg(robotPosition.theta);
  /*
  if (theta >= 90)
  {
    analogWrite(RIGHT_MOTOR_PWM, 0);
    analogWrite(LEFT_MOTOR_PWM, 0);
  }
  */
  
  //printRobotPosition();
  //printSensorsIR();
}

void setup()
{
  // Setup pins
  pinMode(LEFT_ENCODER_A, INPUT);
  pinMode(LEFT_ENCODER_B, INPUT);
  pinMode(RIGHT_ENCODER_A, INPUT);
  pinMode(RIGHT_ENCODER_B, INPUT);

  // Initialize oldEncoder values
  oldEncoderRight = myEncRight.read();
  oldEncoderLeft = myEncLeft.read();

  Serial.begin(9600);

  //speed = cmd_vel(); // get desired speed
  desiredSpeed.lin_vel = 0.0; // cm/s
  desiredSpeed.ang_vel = 0.0;

  // Convert the linear and angular velocities to the wheels' angular velocity
  cmd_vel2wheels(&desiredSpeed);

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
