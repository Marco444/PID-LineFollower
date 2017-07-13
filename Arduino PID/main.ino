#include "PID.ino"

int S0 = 23 , S1 = 24 , S2 = 25, S3 = 26, S4 = 27, S5 = 28;
int M1a = 11, M1b = 16, EN1 = 6;
int M2a = 5, M2b = 15, EN2 = 14;


void setup() {

  //Set Sensors:
  pinmode(S0, INPUT);
  pinmode(S1, INPUT);
  pinmode(S2, INPUT);
  pinmode(S3, INPUT);
  pinmode(S4, INPUT);
  pinmode(S5, INPUT);

  //Set Motor 1:
  pinmode(M1a, OUTPUT);
  pinmode(M1b, OUTPUT);
  pinmode(EN1, OUTPUT);

  //Set Motor 2:
  pinmode(M2a, OUTPUT);
  pinmode(M2b, OUTPUT);
  pinmode(EN2, OUTPUT);

  //Set Other Unused Pins:
    // Not as it is also RESET pinmode(1, OUTPUT)
  pinmode(3, OUTPUT);
  pinmode(4, OUTPUT);
  pinmode(13, OUTPUT);

}

void loop() {

  //Set higher resolutions for improved acuraccy:
  analogReadResolution(16);
  analogWriteResolution(12); //Error ¿?

  //Read analog values from sensors:
  analogRead(S0);
  analogRead(S1);
  analogRead(S2);
  analogRead(S3);
  analogRead(S4);
  analogRead(S5);

  PID(S0, S1, S2, S3, S4, S5, M1a, M1b, M2a, M2b, EN1, EN2);
}
