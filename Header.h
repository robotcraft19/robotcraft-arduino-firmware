#ifndef HEADER_H
#define HEADER_H

// PINS
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

// OTHER CONSTANTS
#define UPDATE_FREQUENCY 10.0
#define IR_SAMPLE_SIZE 25
#define ENCODER_RES 8344.0 // 298 x 28
#define WHEEL_TO_WHEEL 0.097 //in centimer
#define WHEEL_RADIUS 0.016

#define KP 10
#define KI 0.3
#define KD 0

#define FORWARD 0
#define BACKWARD 1

// STRUCTURES KINEMATICS
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


// STRUCTURES PID
typedef struct {
    float AngVelLeft = 0;
    float AngVelRight = 0;
} ProportionalError;

typedef struct {
    float Left = 0;
    float Right = 0;
} DerivativeError;

typedef struct {
    float Left = 0;
    float Right = 0;
} IntegralError;



// GENERAL GLOBAL VARIABLES
Position robotPosition = {0.0, 0.0, 0.0};
unsigned long timestamp;

// SENSOR GLOBAL VARIABLES
int distanceIR_L, distanceIR_F, distanceIR_R;

// KINEMATICS GLOBAL VARIABLES
Speed desiredSpeed;
Speed realSpeed;

long oldEncoderRight = 0;
long oldEncoderLeft = 0;
EncoderDifference encDiff = {0.0, 0.0};


// PID GLOBAL VARIABLES
ProportionalError PropErr;
DerivativeError DerivErr;
IntegralError IntegErr;

float gainLeft;
float gainRight;


// ENCODER DEFINITIONS
Encoder myEncLeft(LEFT_ENCODER_A, LEFT_ENCODER_B);
Encoder myEncRight(RIGHT_ENCODER_A, RIGHT_ENCODER_B);

#endif
