#include <Encoder.h>
#include "Header.h"

void update() // update service routine
{
  oldEncoderRight = encoderRight();
  oldEncoderLeft = encoderLeft();

  // Update position based on input linear and angular velocity + elapsed time since last iteration
  poseUpdate();

  float x = robotPosition.x;
  float theta = radToDeg(robotPosition.theta);

  if (x >= 20)
  {
    analogWrite(RIGHT_MOTOR_PWM, 0);
    analogWrite(LEFT_MOTOR_PWM, 0);
  }

  printRobotPosition();
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
  desiredSpeed.lin_vel = 5.0;
  desiredSpeed.ang_vel = 0.0;

  // Convert the linear and angular velocities to the wheels' angular velocity
  cmd_vel2wheels(&desiredSpeed);

  // Start motors
  digitalWrite(RIGHT_MOTOR_DIR, 0);
  analogWrite(RIGHT_MOTOR_PWM, map(desiredSpeed.lin_vel, 0, 10, 0, 255));

  digitalWrite(LEFT_MOTOR_DIR, 0);
  analogWrite(LEFT_MOTOR_PWM, map(desiredSpeed.lin_vel, 0, 10, 0, 255));

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
