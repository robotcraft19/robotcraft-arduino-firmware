#include "Header.h"

float gainPID = 0;

void pidControl(Speed realSpeed, Speed desiredSpeed) {
    float newPropLeft = desiredSpeed.wheel_left - realSpeed.wheel_left;
    float newPropRight = desiredSpeed.wheel_right - realSpeed.wheel_right;

    float newDerivLeft = newPropLeft - PropErr.AngVelLeft;
    float newDerivRight = newPropRight - PropErr.AngVelRight;

    float newIntegLeft = IntegErr.Left + newPropLeft;
    float newIntegRight = IntegErr.Right + newPropRight;

    gainLeft = KP*newPropLeft + KI*newIntegLeft*(1000/UPDATE_FREQUENCY) + KD*newDerivLeft/(1000/UPDATE_FREQUENCY);
    gainRight = KP*newPropRight + KI*newIntegRight*(1000/UPDATE_FREQUENCY) + KD*newDerivRight/(1000/UPDATE_FREQUENCY);
    
    PropErr.AngVelLeft = newPropLeft;
    PropErr.AngVelRight = newPropRight;
    DerivErr.Left = newDerivLeft;
    DerivErr.Right = newDerivRight;
    IntegErr.Left = newIntegLeft;
    IntegErr.Right = newIntegRight;

    if (gainLeft >= 0) {
      digitalWrite(LEFT_MOTOR_DIR, FORWARD);
    } else {
      digitalWrite(LEFT_MOTOR_DIR, BACKWARD);
    }

    if (gainRight >= 0) {
      digitalWrite(RIGHT_MOTOR_DIR, FORWARD);
    } else {
      digitalWrite(RIGHT_MOTOR_DIR, BACKWARD);
    }

    gainLeft = abs(gainLeft);
    gainRight = abs(gainRight);


    if (gainLeft >= 255) gainLeft = 255;
    if (gainRight >= 255) gainRight = 255;
    

    //analogWrite to PWM pin => gain !
    analogWrite(LEFT_MOTOR_PWM, gainLeft);
    analogWrite(RIGHT_MOTOR_PWM, gainRight);
}
