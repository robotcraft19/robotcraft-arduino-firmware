#include "Header.h"

int getDistance(int ir_pin)
{
  /*
   * int ir_pin: Analog pin number of IR sensor
   * Returns distance in mm (and cuts off at 100mm and 800mm because range of sensor is 10-80cm)
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

  // Check if distance inside range that can be measured by sensor (10-80cm), otherwise cut value off
  if (distance_cm > 80.0)
    distance_cm = 80.0;
  else if (distance_cm < 10.0)
    distance_cm = 10.0;
  return (int)(distance_cm * 10.0); // return in mm
}

// Get IR Sensor values
int sensL()
{
  int distance = getDistance(IR_LEFT);
  return distance;
}
int sensF()
{
  int distance = getDistance(IR_FRONT);
  return distance;
}
int sensR()
{
  int distance = getDistance(IR_RIGHT);
  return distance;
}

void readSensorsIR(int *irLeft, int *irFront, int *irRight) {
  *irLeft = sensL();
  *irFront = sensF();
  *irRight = sensR();
}

void printSensorsIR()
{
  int rangeLeft = sensL();
  int rangeFront = sensF();
  int rangeRight = sensR();
  Serial.print("Sensor Left: ");
  Serial.println(rangeLeft);
  Serial.print("Sensor Front: ");
  Serial.println(rangeFront);
  Serial.print("Sensor Right: ");
  Serial.println(rangeRight);
  Serial.println("\n");
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
