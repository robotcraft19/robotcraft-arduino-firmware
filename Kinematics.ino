#include "Header.h"

// Receive desired linear and angular velocities as input
Speed cmd_vel(float lin_vel, float ang_vel)
{
  Speed robot;
  robot.lin_vel = lin_vel;
  robot.ang_vel = ang_vel;
  cmd_vel2wheels(&robot); // Convert the linear and angular velocities to the wheels' angular velocity

  return robot;
}

// Convert the linear and angular velocities to the wheels' angular velocity
void cmd_vel2wheels(Speed *speed)
{
  speed->wheel_left = (speed->lin_vel - WHEEL_TO_WHEEL / 2 * speed->ang_vel) / WHEEL_RADIUS;
  speed->wheel_right = (speed->lin_vel + WHEEL_TO_WHEEL / 2 * speed->ang_vel) / WHEEL_RADIUS;
}

/* Update position based on input linear and angular velocity + elapsed time since last iteration */
void poseUpdate()
{
  Position oldPosition = robotPosition;
  
  float timeDiff = (float)(millis() - timestamp) / 1000.0;// convert to seconds

  /* calculate and update real linear and angular speeds of robot */
  realSpeed.lin_vel = 2 * M_PI * WHEEL_RADIUS / ENCODER_RES * (encDiff.right + encDiff.left) / 2.0 / timeDiff;
  realSpeed.ang_vel = 2 * M_PI * WHEEL_RADIUS / ENCODER_RES * (encDiff.right - encDiff.left) / WHEEL_TO_WHEEL / timeDiff;

  /* update angular wheel speeds */
  cmd_vel2wheels(&realSpeed);

  /* calculate new position and angular orientation of robot */
  Position newPosition;
  newPosition.theta = atan2(sin(oldPosition.theta + realSpeed.ang_vel * timeDiff), cos(oldPosition.theta + realSpeed.ang_vel * timeDiff));
  newPosition.x = oldPosition.x + realSpeed.lin_vel * timeDiff * cos(newPosition.theta);
  newPosition.y = oldPosition.y + realSpeed.lin_vel * timeDiff * sin(newPosition.theta);

  /* Update RobotPosition */
  robotPosition.x = newPosition.x;
  robotPosition.y = newPosition.y;
  robotPosition.theta = newPosition.theta;
}


void printRobotPosition()
{
  Serial.print("x: "); Serial.println(robotPosition.x);
  Serial.print("y: "); Serial.println(robotPosition.y);
  Serial.print("theta: "); Serial.println(robotPosition.theta);
  Serial.println();
}


// Helper functions to convert radians <--> degrees
float radToDeg(float rad)
{
  return (rad * 180 / M_PI);
}

float degToRad(float deg)
{
  return (deg / 180 * M_PI);
}
