
void PID(int S0, int S1, int S2, int S3, int S4, int S5, int M1_left, int M1_right,
         int M2_left, int M2_right, int EN1, int EN2)
{

    //Initialise all variables outside of the loop for better efficiency.
    int P, I, D, last_P;
    int position;
    double PK, IK, DK, error_correction; //K for Constants

    // Define the weights of each sensor
    static int W0 = -3000;
    static int W1 = -2000;
    static int W2 = -1000;
    static int W3 = 0;
    static int W4 = 1000;
    static int W5 = 2000;
    static int W6 = 3000;

    // Constants that if they are lower, the importance of the term is lower in regards to error_correction.
    PK = 1/2;
    IK = 1/10000;
    DK = 3/2;

    position = (S0*WO) (S1*W1) + (S2*W2) + (S3*W3) + (S4*W4) + (S5*W5) + (S6*W6)

    P = position - (SRO+SR1+SR2+SR3+SR4+SR5+SR6); // P, for proportional.
    D = P - last_P; // D, for Derivative.
    I += P; // I, for Integral.

    last_P = P;
    error_correction = (P*PK) + (I*IK) + (D*DK);

    // Once I have the error, I want to correct it; this indefinetely until the switch is turned off.
    solve_error(error_correction,int M1_left, int M1_right, int M2_left, int M2_right, int EN1, int EN2);

}

void solve_error(int error,int M1_left, int M1_right, int M2_left, int M2_right, int EN1, int EN2)
{
    //if(W2 < error < W4){
    //    analogWrite(M1_left, error )
    //}
    analogWrite(M1_left, error )
}
