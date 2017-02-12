#include <AccelStepper.h>
#include <MultiStepper.h>
//------------------------------------------------------------------------------------------------
//Circluar Movement Parameters
//float Xc=0,Yc=0,Zc=0;             //X,Y,Z co-ordinates according to circle equation
float Raduis = 70;                //Circle Raduis
//------------------------------------------------------------------------------------------------
// Delta robot parameters
float  sb = 420;
float  sp = 94 ;
float  l = 363.14 ;
//-------------------------------------------------------------------------------------------------

//Inverse kinematics Variables
float  x = 0, y = 0, z = 0;            // required co-ordinate
float  a, b, c, c1, c2, c3;          // calculation variable
float  L11, L12, L21, L22, L31, L32;   // all avaible solution for input
float  L1, L2, L3 ;                  // knee down solution
float  Lp1 , Lp2 , Lp3 ;               // Latest previous L1,L2,L3
float  Ln1 = 0 , Ln2 = 0 , Ln3 = 0 ; // Distance to move from current point
long  S1 = 0 , S2 = 0, S3 = 0 ;        // number of steps for each stepper motor
//--------------------------------------------------------------------------------------------------

//Inverse Jacobian Variables
float  Xv = 0, Yv = 0, Zv = 0 ;              //End effector velocities in x,y,z direction
float  Lv1 = 0, Lv2 = 0, Lv3 = 0;            //Carriages velocities in mm/s
int speeda = 0 ;                 //Carriage A velocity in pulse/sec
int speedb = 0 ;                 //Carriage B velocity in pulse/sec
int speedc = 0 ;                 //Carriage C velocity in pulse/sec
//---------------------------------------------------------------------------------------------------

//Driver Setting
int DS = 1000 ;            // Driver resolution from (400 to 25400) step / rev
//We may use 2500 resolution
//----------------------------------------------------------------------------------------------------

//miscellaneous
int move_finished = 1; // Used to check if move is completed
//int flag = 0 ;         //Calculator end of calculations flag Use 1 to mask calculation and zero to permit
const float pi = 22 / 7; // PI constant

/*
  //Functions definition
  void Inv_Kin()                    // Inverse Kinematic Calculator "to calculate carriage travel ".
  void Inv_Jac()                    // Inverse Jacobian Calculator  "to calculate carriage velocity ".
  void Stepper_Initial()            // Set stepper mootion parameters
  //void Trouble_shoot()              // Used for trouble shooting issues
*/
//------------------------------------------------------------------------------------------------------
//********************************************Motor setup*********************************************

AccelStepper stepperA(1, 2, 3);   // 1 = pul/dir Driver interface.
// Pin 2 connected to pul pin.
// Pin 3 connected to DIR pin.

AccelStepper stepperB(1, 7, 8);   // 1 = pul/dir Driver interface.
// Pin 7 connected to pul pin.
// Pin 8 connected to DIR pin.

AccelStepper stepperC(1, 5, 6);   // 1 = pul/dir Driver interface.
// Pin 5 connected to pul pin.
// Pin 6 connected to DIR pin.
//---------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

void setup() {

  //Serial initialization
  Serial.begin(9600);  // Start the Serial monitor with Baud rate 9600
  /*stepperA.setMaxSpeed(100000);      // Set Max Speed of motor_A
    stepperB.setMaxSpeed(100000);      // Set Max Speed of motor_B
    stepperC.setMaxSpeed(100000);      // Set Max Speed of motor_C*/
  stepperA.setAcceleration(50000.0);  // Acceleration of motor_A
  stepperB.setAcceleration(50000.0);  // Acceleration of motor_B
  stepperC.setAcceleration(50000.0);  // Acceleration of motor_C

}

void loop() {

  //----------------------------------------------------------------------------------------------
  // Fuctions Calling
  if (move_finished == 1) {
    Input();
    //Circle();
    Inv_Kin();
    Inv_Jac();
    Stepper_Initial();
    move_finished = 0;
    stepperA.setMaxSpeed(speeda);     // Set Max Speed of motor_A
    stepperB.setMaxSpeed(speedb);      // Set Max Speed of motor_B
    stepperC.setMaxSpeed(speedc);      // Set Max Speed of motor_C
    Serial.print("Moving End-effector to the required position ...");

  }

  //---------------------------------------------------------------------------------------------------------------------------------
  if (move_finished == 0) {
    // Check if the Steppers have reached desired position
    //************************************Set relative travel distance***********************
    stepperA.moveTo(S1);  // Set new move position for a Stepper
    stepperB.moveTo(S2);  // Set new move position for a Stepper
    stepperC.moveTo(S3);  // Set new move position for a Stepper

    delay(100);  // Wait 100 milli-seconds before moving the Steppers
    //-----------------------------------------------------------------------------------------------------
    //************************************ MOTOR_A ******************************************
    /*stepperA.moveTo(S1);  // Set new move position for a Stepper
      stepperA.setSpeed(speeda);           //Set Constant Speed of motor_A
      //--------------------------------------------------------------------------------------
      //************************************ MOTOR_B ******************************************
      stepperB.moveTo(S2);  // Set new move position for b Stepper
      stepperB.setSpeed(speedb);           //Set Constant Speed of motor_B

      //---------------------------------------------------------------------------------------
      //************************************ MOTOR_C ******************************************
      stepperC.moveTo(S3);  // Set new move position for c Stepper
      stepperC.setSpeed(speedc);           //Set Constant Speed of motor_C
      //---------------------------------------------------------------------------------------

      delay(100);  // Wait 100 milli-seconds before moving the Steppers*/
    if ((stepperA.distanceToGo() != 0) || (stepperB.distanceToGo() != 0) || (stepperC.distanceToGo() != 0) ) {
      Serial.println("stepper speed");
      Serial.println(Lv1);
      Serial.println(Lv2);
      Serial.println(Lv3);
      Serial.println("STEPS PER SECOND");
      Serial.println(speeda);
      Serial.println(speedb);
      Serial.println(speedc);

      Serial.println("stepperA.distanceToGo()");
      Serial.println(stepperA.distanceToGo());
      Serial.println("stepperB.distanceToGo()");
      Serial.println(stepperB.distanceToGo());
      Serial.println("stepperC.distanceToGo()");
      Serial.println(stepperC.distanceToGo());
      Serial.println("S1");
      Serial.println(S1);
      Serial.println("S2");
      Serial.println(S2);
      Serial.println("S3");
      Serial.println(S3);
      //***************************************CONSTANT SPEED OPTION************************
      /*stepperA.runSpeed();  // Move Stepper X into position
        stepperB.runSpeed();  // Move Stepper Y into position
        stepperC.runSpeed();  // Move Stepper Z into position*/
      //**************************************VARIABLE SPEED OPTION*************************
      stepperA.run();  // Move Stepper X into position
      stepperB.run();  // Move Stepper Y into position
      stepperC.run();  // Move Stepper Z into position
    }

    // If move is completed display message on Serial Monitor
    if ((stepperA.distanceToGo() == 0) && (stepperC.distanceToGo() == 0) && (stepperB.distanceToGo() == 0) ) {
      Serial.print("************************* ...");
      Serial.println("COMPLETED!");
      Serial.println("");
      Serial.println("Enter Next Move Values (0,0,0 for reset): ");  // Get ready for new Serial monitor values
      move_finished = 1; // Reset move variable
    }
  }
}
