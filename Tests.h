#include "Arduino.h"

void print_sensors(int S0, int S1, int S2, int S3, int S4, int S5)
{
  Serial.print("S0: ");
  Serial.print(S0);
  Serial.print("\n"); 
  
  Serial.print("S1: ");
  Serial.print(S1);
  Serial.print("\n");
  
  Serial.print("S2: ");
  Serial.print(S2);
  Serial.print("\n");
  
  Serial.print("S3: ");
  Serial.print(S3);
  Serial.print("\n");
  
  Serial.print("S4: ");
  Serial.print(S4);
  Serial.print("\n");
  
  Serial.print("S5: ");
  Serial.print(S5);
  Serial.print("\n");
}

void print_error_correction(double error)
{
  Serial.print("Error_Correction: ");
  Serial.print(error);
  Serial.print("\n"); 
}

void print_motors(int M1a, int M1b, int M2a, int M2b, int EN1, int EN2)
{
  Serial.print("M1: ");
  Serial.print(error);
  Serial.print("\n"); 
}
