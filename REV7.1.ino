///04.15.2023 

#include<Servo.h>
#include <AccelStepper.h>
#include <Keypad.h>

#define dirPin 7
#define stepPin 6
#define motorInterfaceType 1

#define dirPin1 4
#define stepPin1 2

//Keypad Declaration
const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[rows] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[cols] = {26, 27, 28}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
// Create a new instance of the AccelStepper class:
AccelStepper stepper1 = AccelStepper(motorInterfaceType, stepPin1, dirPin1);
// Servo Declaration
Servo s1;
Servo s2;
Servo s3;
Servo s4;


void setup()

{
  Serial.begin(9600);
  
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);

  stepper1.setMaxSpeed(2000);
  stepper1.setAcceleration(750);
  
  s1.attach(12);
  s2.attach(11);
  s3.attach(10);
  s4.attach(9);
  
}

void loop()
{

homing();
delay(1000);

char customKey = customKeypad.getKey();
Serial.println(customKey);

bool Run = false;

while (customKey == '*')
{
  Run = true;
  if (Run == true)
  {
    AutoRunning();
  }
  else
  {
    break;
    }
  delay(5000);
  customKey = customKeypad.getKey();
}

while (customKey == '#')
{
  Run = false;
  homing();
  delay(1000);
  customKey = customKeypad.getKey();
}

while (customKey == '1')
{
  Run = true;
  ManualRetrieveFromF0S1();
  delay(200);
  customKey = customKeypad.getKey();
}

while (customKey == '2')
{
  Run = true;
  ManualRetrieveFromF0S2();
  delay(200);
  customKey = customKeypad.getKey();
}

while (customKey == '3')
{
  Run = true;
  ManualRetrieveFromF0S3();
  delay(200);
  customKey = customKeypad.getKey();
}

while (customKey == '4')
{
  Run = true;
  ManualRetrieveFromF1S1();
  delay(200);
  customKey = customKeypad.getKey();
}

while (customKey == '5')
{
  Run = true;
  ManualRetrieveFromF1S2();
  delay(200);
  customKey = customKeypad.getKey();
}

while (customKey == '6')
{
  Run = true;
  ManualRetrieveFromF1S3();
  delay(200);
  customKey = customKeypad.getKey();
}


while (customKey == '0')
{
  Run = true;
  AutoRetrieve();
  delay(200);
  customKey = customKeypad.getKey();
}


}

void AutoRunning()
{
  Picked();
  delay(1000);
  TurntoS1();
  delay(1000);
  ArmF1S1();
  delay(1000);
  Freearm();
  delay(500);
  Turntohome();
  delay(500);
  Picked();
  delay(1000);
  TurntoS2();
  delay(1000);
  ArmF1S1(); // no need to turn the table as it is the middle slot
  delay(1000);
  Freearm();
  delay(500);
  Turntohome();
  delay(500);
  Picked();
  delay(1000);
  TurntoS3();
  delay(1000);
  ArmF1S1();
  delay(1000);
  Freearm();
  delay(500);
  Turntohome();
  delay(100);
  ///////////////////////////////////////Floor 0 complete
  Picked();
  delay(1000);
  floor1();
  delay(5000);
  TurntoS1();
  delay(1000);
  ArmF1S1();
  delay(1000);
  Freearm();
  delay(500);
  Turntohome();
  delay(500);
  floor0();
  delay(1000);
  Picked();
  delay(1000);
  floor1();
  delay(1000);
  TurntoS2();
  delay(1000);
  ArmF1S1();
  delay(1000);
  Freearm();
  delay(500);
  Turntohome();
  delay(500);
  floor0();
  delay(1000);
  Picked();
  delay(1000);
  floor1();
  delay(1000);
  TurntoS3();
  delay(1000);
  ArmF1S1();
  delay(1000);
  Freearm();
  delay(500);
  Turntohome();
  delay(500);
  floor0();
  delay(1000);
  Turntohome();
  delay(1000);
  
 
}

void Picked()
{
  homing();
  delay(1000);
  Turntopick();
  delay(1000);
  pick();
  delay(1000);
  grip_pick();
  delay(1000);
  ArmSafe();
  delay(1000);
  Turntohome();
  delay(1000);
  Readytodrop();
  delay(1000);
}

void homing()
{
  s1.write(5);
  s2.write(45);
  s3.write(45);
  s4.write(40);
}

void pick()
{
  s1.write(0);
  delay(400);
  s2.write(0);
  delay(400);
  s3.write(125);
  delay(400);
  s4.write(40);
}

void grip_pick()
{
  s1.write(0);
  s2.write(0);
  s3.write(125);
  s4.write(120);
}

void ArmSafe()
{
  s1.write(5);
  s2.write(45);
  s3.write(45);
  s4.write(120);
}

void Readytodrop()
{
  s1.write(0);
  delay(3000);
  s2.write(0);
  delay(3000);
  s3.write(5);
  delay(3000);
  s4.write(120);
  delay(3000);
}

void ArmF1S1()
{
  s1.write(85);
  delay(3000);
  s3.write(5); //test
  delay(3000);
  s2.write(37);
  delay(3000);
  s3.write(60);
  delay(3000);
  s4.write(40);
  delay(3000);
  
}

void Freearm()
{
  
  s3.write(0);
  delay(1000);
  s2.write(30);
  delay(1000);
}
  

void Readytoretrieve()
{
  s1.write(0);
  delay(200);
  s2.write(0);
  delay(200);
  s3.write(10);
  delay(200);
  s4.write(40);
  delay(200);
}

void RetreveArmF1S1()
{
  s1.write(85);
  delay(200);
  s2.write(37);
  delay(200);
  s3.write(60);
  delay(200);
  s4.write(100);
  delay(200);
  s3.write(10);
  delay(200);
  s2.write(0);
  delay(200);
  s1.write(50);
  delay(200);
}

void deliver()
{
  s1.write(5);
  s2.write(45);
  s3.write(45);
  s4.write(135);
}

void drop_table()
{
  s1.write(0);
  s2.write(0);
  s3.write(125);
  delay(200);
  s4.write(40);
}



  
void returnhome()
{
  s1.write(5);
  s2.write(45);
  s3.write(45);
  s4.write(110);
}





void ArmF1S2()
{
  s1.write(5);
  s2.write(45);
  s3.write(45);
  s4.write(100);
}

void ArmF2S3()
{
  s1.write(5);
  s2.write(45);
  s3.write(45);
  s4.write(100);
}

void floor1()
{
  stepper.moveTo(-15500);
  stepper.runToPosition();
  delay(1000);
}

void floor0()
{
  stepper.moveTo(0);
  stepper.runToPosition();
  delay(1000);
}

void Turntopick()
{
  stepper1.moveTo(-1107);
  stepper1.runToPosition();
  delay(1000);
}

void Turntohome()
{
  stepper1.moveTo(0);
  stepper1.runToPosition();
  delay(1000);
}

void Turntotablesafe()
{
  stepper1.moveTo(20);
  stepper1.runToPosition();
  delay(1000);
}

void TurntoS1()
{
  stepper1.moveTo(145);
  stepper1.runToPosition();
  delay(1000);
}

void TurntoS2()
{
  stepper1.moveTo(-15);
  stepper1.runToPosition();
  delay(1000);
}

void TurntoS3()
{
  stepper1.moveTo(-150);
  stepper1.runToPosition();
  delay(1000);
}

///////////////////////////////////////////////////////////////////////////////////////waste
void Comingout() // The part has been put back on the deck
{
  RetrieveArmF0S1();
  delay(1000);
  Turntohome();
  delay(5000);
  Turntopick();
  delay(1000);
  deliver();
  delay(1000);
  drop_table();
  delay(1000);
  returnhome();
  delay(1000);
  Turntohome();
  delay(1000); 
}
////////////////////////////////////////////////////////////////////////////////////////////waste



///////////////////////////////////////////retrieve F0S1

void ManualRetrieveFromF0S1()
{
  Retrieve();
  delay(1000);
  TurntoS1();
  delay(1000);
  RetrieveArmF0S1();
  delay(1000);
  Turntopick();
  delay(1000);
  pick();
  delay(1000);
  ungrip();
  delay(1000);
  Turntohome();
  delay(1000);
  homing();
  delay(1000);
  
  
  //void Comingout();
  //delay(1000);

  
}
void Retrieve() //arm is at tablesafe position and ready to pick the part from the shelves
{
  homing();
  delay(1000);
  ArmSafe();
  delay(1000);
  Turntohome();
  delay(1000);
  ReadytoRetrieve();
  delay(1000);
  
}  

void ReadytoRetrieve()
{
  s1.write(0);
  delay(200);
  s2.write(0);
  delay(200);
  s3.write(10);
  delay(200);
  s4.write(40);
  delay(200);
}



void RetrieveArmF0S1()
{
  s3.write(5);
  delay(7500);
  s1.write(85);
  delay(750);
  s2.write(37);
  delay(750);
  s3.write(60);
  delay(750);
  s4.write(125);
  delay(750);
  s3.write(0);
  delay(750);
  s2.write(24);
  delay(750);
  s1.write(35);
  delay(750);
}

void ungrip()
{
  s1.write(0);
  s2.write(0);
  s3.write(125);
  s4.write(40);
}




///////////////////////////////////////////retrieve F0S2

void ManualRetrieveFromF0S2()
{
  Retrieve();
  delay(500);
  TurntoS2();
  delay(500);
  RetrieveArmF0S1();
  delay(500);
  Turntopick();
  delay(500);
  pick();
  delay(500);
  ungrip();
  delay(500);
  Turntohome();
  delay(500);
  homing();
  delay(500);
  
  
  //void Comingout();
  //delay(1000);

  
}

///////////////////////////////////////////retrieve F0S3

void ManualRetrieveFromF0S3()
{
  Retrieve();
  delay(500);
  TurntoS3();
  delay(500);
  RetrieveArmF0S1();
  delay(500);
  Turntopick();
  delay(500);
  pick();
  delay(500);
  ungrip();
  delay(500);
  Turntohome();
  delay(500);
  homing();
  delay(500);
  
  
  //void Comingout();
  //delay(1000);

  
}


///////////////////////////////////////////retrieve F1S1

void ManualRetrieveFromF1S1()
{
  Retrieve();
  delay(500);
  floor1();
  delay(500);
  TurntoS1();
  delay(500);
  RetrieveArmF0S1();
  delay(500);
  floor0();
  delay(500);
  Turntopick();
  delay(500);
  pick();
  delay(500);
  ungrip();
  delay(500);
  Turntohome();
  delay(500);
  homing();
  delay(500);
  
  
  //void Comingout();
  //delay(1000);
  
}

///////////////////////////////////////////retrieve F1S2

void ManualRetrieveFromF1S2()
{
  Retrieve();
  delay(500);
  floor1();
  delay(500);
  TurntoS2();
  delay(500);
  RetrieveArmF0S1();
  delay(500);
  floor0();
  delay(500);
  Turntopick();
  delay(500);
  pick();
  delay(500);
  ungrip();
  delay(500);
  Turntohome();
  delay(500);
  homing();
  delay(500);
  
  
  //void Comingout();
  //delay(1000);
  
}

///////////////////////////////////////////retrieve F1S3

void ManualRetrieveFromF1S3()
{
  Retrieve();
  delay(500);
  floor1();
  delay(500);
  TurntoS3();
  delay(500);
  RetrieveArmF0S1();
  delay(500);
  floor0();
  delay(500);
  Turntopick();
  delay(500);
  pick();
  delay(500);
  ungrip();
  delay(500);
  Turntohome();
  delay(500);
  homing();
  delay(500);
  
  
  //void Comingout();
  //delay(1000);
  
}

/////////////////////////////////////////////////////////////////////////////////////////////////Manuual Retrieve Completed



void AutoRetrieve()
{
  ManualRetrieveFromF0S1();
  delay(1000);
  ManualRetrieveFromF0S2();
  delay(1000);
  ManualRetrieveFromF0S3();
  delay(1000);
  ManualRetrieveFromF1S1();
  delay(1000);
  ManualRetrieveFromF1S2();
  delay(1000);
  ManualRetrieveFromF1S3();
  delay(1000);
  Turntohome();
  delay(1000);
}
