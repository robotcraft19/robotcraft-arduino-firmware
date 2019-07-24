#ifndef HEADER_H
#define HEADER_H

// Define pins
#define LEFT_ENCODER_A 18
#define LEFT_ENCODER_B 19

#define RIGHT_ENCODER_A 3
#define RIGHT_ENCODER_B 2

#define RIGHT_MOTOR_PWM 4
#define LEFT_MOTOR_PWM 9

#define RIGHT_MOTOR_DIR 5
#define LEFT_MOTOR_DIR 6

#define IR_LEFT A2
#define IR_FRONT A3
#define IR_RIGHT A4

// Define other constants
#define UPDATE_FREQUENCY 10.0
#define IR_SAMPLE_SIZE 25
#define ENCODER_RES 8200.0
#define WHEEL_TO_WHEEL 9.9 //in centimer
#define WHEEL_RADIUS 1.5

// Structures
typedef struct
{
  float x;
  float y;
  float theta;
} Position;

typedef struct
{
  float left;
  float right; //Encoder difference on left and right wheel since last readout
} EncoderDifference;

typedef struct
{
  float lin_vel;
  float ang_vel;
  float wheel_left; //angular velocities of wheels
  float wheel_right;
} Speed;


// Global Variables
Position robotPosition = {0.0, 0.0, 0.0};

long oldEncoderRight = 0;
long oldEncoderLeft = 0;
EncoderDifference encDiff = {0.0, 0.0};
unsigned long timestamp;

Speed desiredSpeed;
Speed realSpeed;

// Encoder definition
Encoder myEncLeft(LEFT_ENCODER_A, LEFT_ENCODER_B);
Encoder myEncRight(RIGHT_ENCODER_A, RIGHT_ENCODER_B);

#endif
