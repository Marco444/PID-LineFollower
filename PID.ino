#include <iostream>

using namespace std;

int target_val = 0;
int last_P;
boolean bools = true;

// Constants that if they are lower, the importance of the term is lower in regards to error_correction.
int PK = 1/2;
int IK = 1/10000;
int DK = 3/2;

void calibrate()
{

  //Code goes here.
}

void PID(int S0, int S1, int S2, int S3, int S4, int S5, int M1_left, int M1_right,
         int M2_left, int M2_right, int EN1, int EN2)
{

    //Initialise all variables outside of the loop for better efficiency.
    int positions, P, D, I;
    double PK, IK, DK, error_correction; //K for Constants

    // Define the weights of each sensor
    static int W0 = -2000;
    static int W1 = -1000;
    static int W2 = 3000;
    static int W3 = 3000;
    static int W4 = 1000;
    static int W5 = 2000;

    positions = (S0*W0) + (S1*W1) + (S2*W2) + (S3*W3) + (S4*W4) + (S5*W5);

    P = positions; // - (SRO+SR1+SR2+SR3+SR4+SR5) => - white line value; // P, for proportional.
    D = P - last_P; // D, for Derivative.
    I += P; // I, for Integral.

    last_P = P;
    error_correction = (P*PK) + (I*IK) + (D*DK);

    // Once I have the error, I want to correct it; this indefinetely until the switch is turned off.
    solve_error(error_correction,M1_left,M1_right,M2_left,M2_right,EN1,EN2);

}

void solve_error(int error,int M1_left, int M1_right, int M2_left, int M2_right, int EN1, int EN2)
{
    //if(W2 < error < W4){
    //    analogWrite(M1_left, error )
    //}
    analogWrite(M1_left, error );
}

int S0 = A0 , S1 = 24 , S2 = 25, S3 = 26, S4 = 27, S5 = 28;
int M1a = 11, M1b = 16, EN1 = 6;
int M2a = 5, M2b = 15, EN2 = 14;


void setup() {

  //Set Sensors:
  pinMode(S0, INPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  //Set Motor 1:
  pinMode(M1a, OUTPUT);
  pinMode(M1b, OUTPUT);
  pinMode(EN1, OUTPUT);

  //Set Motor 2:
  pinMode(M2a, OUTPUT);
  pinMode(M2b, OUTPUT);
  pinMode(EN2, OUTPUT);

  //Set Other Unused Pins:
    // Not as it is also RESET pinmode(1, OUTPUT)
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(13, OUTPUT);
  
  
  //Set higher resolutions for improved acuraccy:
  //analogReadResolution(16);
  //analogWriteResolution(12); //Error ¿?
  //int last_P = AnalogRead();

  Serial.begin(9600);
}

void loop() {

 while(bools){
  //Read analog values from sensors:
  analogRead(S0);
  analogRead(S1);
  analogRead(S2);
  analogRead(S3);
  analogRead(S4);
  analogRead(S5);
    Serial.print("S0: ");
    Serial.println(analogRead(S0));
  
    delay(1000);
 }
  PID(S0, S1, S2, S3, S4, S5, M1a, M1b, M2a, M2b, EN1, EN2);
  
}

ISR (INT0_vect)
{
    /* interrupt code here */
}
