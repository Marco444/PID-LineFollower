int target_val = 3500; //Value of the Line, which is given more acurately by calibrate().
int last_P;
boolean bools = true;

//Declare Pins
int S0_pin = A0 , S1_pin = A1 , S2_pin = 25, S3_pin = 26, S4_pin = 27, S5_pin = 28;
int M1_left = 11, M1_right = 16, EN1 = 6;
int M2_left = 5, M2_right = 15, EN2 = 14;

// Constants of PID. That if they are lower, the importance of the term is lower in regards to error_correction.
double PK = 1/2;
double IK = 1/10000;
double DK = 3/2;

//Sensors, whose weight is given by calibrate:
int W0 = 1000;
int W1 = 2000;
int W2 = 3000;
int W3 = 4000;
int W4 = 5000;
int W5 = 6000;

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
  Serial.print("Error Correction: ");
  Serial.print(error);
  Serial.print("\n");
}
//void print_error_correction(double error)
void calibrate()
{
  //Code goes here.
}

void PID(int S0, int S1, int S2, int S3, int S4, int S5)
{

    //Initialise all variables outside of the loop for better efficiency.
    int positions, P, D, I;
    double error_correction;

    positions = (S0*W0) + (S1*W1) + (S2*W2) + (S3*W3) + (S4*W4) + (S5*W5);

    P = positions / 6 - target_val; // P, for proportional.// If error is 3500, then we are on the line. 
    D = P - last_P; // D, for Derivative.
    I += P; // I, for Integral.

    last_P = P;
    error_correction = (P*PK) + (I*IK) + (D*DK);
    
    print_error_correction(error_correction);
    // Once I have the error, I want to correct it; this indefinetely until the switch is turned off.
    solve_error(error_correction);

}

void solve_error(int error)
{
    //If error is negative, it means lhs sensors are sensing the line. Hence, turn right
    //If error is positive, then the rhs sensors are sensing the line. Thus, turn left.
    //Else do nothing, we are on the line ! => Could be modifiable for perfomance, very few instances of this being true
    
    if(error < 0){
      digitalWrite(EN1, HIGH);
      analogWrite(M1_left, 0);
      analogWrite(M1_right, abs(error) / 4);
      digitalWrite(EN1, LOW);
      
      digitalWrite(EN2, HIGH);
      analogWrite(M2_right, abs(error) / 4);
      analogWrite(M2_right, 0);
      digitalWrite(EN2, LOW);
      
    } else if(error > 0){
      digitalWrite(EN1, HIGH);
      analogWrite(M1_left, error / 4);
      analogWrite(M1_right, 0);
      digitalWrite(EN1, LOW);
      
      digitalWrite(EN2, HIGH);
      analogWrite(M2_right, error / 4);
      analogWrite(M2_right, 0);
      digitalWrite(EN2, LOW);
      
    } else {
    ;
    }
}




void setup() {

  //Set Sensors:
  pinMode(S0_pin, INPUT);
  pinMode(S1_pin, INPUT);
  pinMode(S2_pin, INPUT);
  pinMode(S3_pin, INPUT);
  pinMode(S4_pin, INPUT);
  pinMode(S5_pin, INPUT);

  //Set Motor 1:
  pinMode(M1_left, OUTPUT);
  pinMode(M1_right, OUTPUT);
  pinMode(EN1, OUTPUT);

  //Set Motor 2:
  pinMode(M2_left, OUTPUT);
  pinMode(M2_right, OUTPUT);
  pinMode(EN2, OUTPUT);

  //Set Other Unused Pins:
    // Not as it is also RESET pinmode(1, OUTPUT)
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(13, OUTPUT);


  Serial.begin(9600);
  calibrate();
}

int read_sensor(int sensorN)
{
 return analogRead(sensorN); 
}

void debugSensors(){
  for(int i = 0;i < 6;i++){
    int sum = 0;
    
    for(int ii = 0;ii < 10;ii++){ 
      sum += read_sensor(14 +i);    Serial.print("Sensor ");Serial.print(i);Serial.print("=");    Serial.println(analogRead(14 + i));


    }
    Serial.print("Sensor ");Serial.print(i);Serial.print("=");
    Serial.println(sum / 10);
    delay(1000);
  }
}

void loop() { //while(bools){


  //Read analog values from sensors:
  
  
  //print_sensors(S0, S1, S2, S3, S4, S5);
  debugSensors();
  delay(1000);
  
 // PID(S0, S1, S2, S3, S4, S5);
  
  //print_motors(M1a, M1b, M2a, M2b, EN1, EN2);

 //}
}

