#include "Header.h"

float getDistance(int ir_pin)
{
  /*
   * int ir_pin: Analog pin number of IR sensor
   * Returns distance in m (and cuts off at 0.1m and 0.8m because range of sensor is 10-80cm)
   */

  int ir_val[IR_SAMPLE_SIZE];

  // Collect samples from IR sensor
  for (int i = 0; i < IR_SAMPLE_SIZE; i++)
  {
    // Read analog value
    ir_val[i] = analogRead(ir_pin);
  }

  // Sort array of sensor values
  sortArray(ir_val, IR_SAMPLE_SIZE);

  // Use median value for further caluclations -> ir_val[SAMPLE_SIZE/2]
  float distance_cm = 4800.0 / (ir_val[IR_SAMPLE_SIZE / 2] - 20.0);

  // Alternative formulas found in experiments
  //5177 / (ir_val[SAMPLE_SIZE/2] -19.54) - 1.28;
  //4213 / (ir_val[SAMPLE_SIZE/2] -41.64);
  //rangeIR[0] = ( (364.0 * exp(-0.02714 * analog_temp0)) + (62.85 * exp(-0.004412 * analog_temp0)) ) * 0.01;


  // Check if distance inside range that can be measured by sensor (10-80cm), otherwise cut value off
  if (distance_cm > 80.0 || distance_cm < 0.0)
    return 0.81;
  else if (distance_cm < 10.0)
    return 0.09;
  return (float)(distance_cm / 100.0); // return in m
}

// Get IR Sensor values
float sensL()
{
  float distance = getDistance(IR_LEFT);
  return distance;
}
float sensF()
{
  float distance = getDistance(IR_FRONT);
  return distance;
}
float sensR()
{
  float distance = getDistance(IR_RIGHT);
  return distance;
}

void readSensorsIR(float *irLeft, float *irFront, float *irRight) {
  *irLeft = sensL();
  *irFront = sensF();
  *irRight = sensR();
}

// Helper function to sort array
void sortArray(int a[], int size)
{
  for (int i = 0; i < (size - 1); i++)
  {
    bool flag = true;
    for (int o = 0; o < (size - (i + 1)); o++)
    {
      if (a[o] > a[o + 1])
      {
        int t = a[o];
        a[o] = a[o + 1];
        a[o + 1] = t;
        flag = false;
      }
    }
    if (flag)
      break;
  }
}
