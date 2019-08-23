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
  
  return encoderRight;
}

long encoderLeft()
{
  long encoderLeft = myEncLeft.read();
  long leftRotation = encoderLeft - oldEncoderLeft;
  encDiff.left = leftRotation;
  
  return encoderLeft;
}
