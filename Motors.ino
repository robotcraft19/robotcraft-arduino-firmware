#include "Header.h"

void encUpdate(long *oldEncoderLeft, long *oldEncoderRight) {
   *oldEncoderRight = encoderRight();
   *oldEncoderLeft = encoderLeft();
}

long encoderRight()
{
  long encoderRight = myEncRight.read();
  long rightRotation = encoderRight - oldEncoderRight;
  encDiff.right = rightRotation;
  
  if (rightRotation > 1)
  {
    //Serial.println("Right is going FORWARD");
  }
  else if (rightRotation < -1)
  {
    //Serial.println("Right is going BACKWARDS");
  }
  else if ((rightRotation <= 1) || (rightRotation >= -1))
  {
    //Serial.println("Right is stationary");
  }
  //Serial.println(rightRotation);
  return encoderRight;
}

long encoderLeft()
{
  long encoderLeft = myEncLeft.read();
  long leftRotation = encoderLeft - oldEncoderLeft;
  encDiff.left = leftRotation;
  
  if (leftRotation > 1)
  {
    //Serial.println("Left is going FORWARD");
  }
  else if (leftRotation < -1)
  {
    //Serial.println("Left is going BACKWARDS");
  }
  else if ((leftRotation <= 1) || (leftRotation >= -1))
  {
    //Serial.println("Left is stationary");
  }
  //Serial.println(leftRotation);
  return encoderLeft;
}
