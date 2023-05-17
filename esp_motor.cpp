
/*  Motor Connections(M)
            __
      motor1(O):  :(O)motor4
               |  |
               |  |
      motor2(O):__:(O)motor3
*/

#include <AFMotor.h> //To Control Motor Movements
//#include <Servo.h>   //To Control Servo motor

#define MAX_DISTANCE 200
#define MAX_SPEED 130 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20
//#define led A4
//#define led2 A5

#define D0 A0
#define D1 A1
#define D2 A2
#define D3 A3
// V0 = D0 Forward
// V1 = D1 Backward
// V2 = D2 Left
// V3 = D3 Right

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

boolean goesForward = false;
boolean goesBackward = false;

unsigned int speedSet = 0;
int pos = 0;
unsigned int Fd = 0; // Variable to store Right IR sensor value:
unsigned int Bd = 0;  // Variable to store Left IR sensor value:
unsigned int Ld = 0;
unsigned int Rd = 0;
void setup()
{
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  Serial.begin(9600); // initailize serial communication at 9600 bits per second:
  delay(2000);
}

void loop()
{
  Fd = digitalRead(D0); // read the value from Right IR sensor:
  Bd = digitalRead(D1); // read the value from Right IR sensor:
  Ld = digitalRead(D2); // read the value from Right IR sensor:
  Rd = digitalRead(D3); // read the value from Right IR sensor:
  //  delay(700);
  Serial.println(Fd);
  //  delay(700);
  Serial.println(Bd);
  //  delay(700);
  Serial.println(Ld);
  //  delay(700);
  Serial.println(Rd);
  if (Fd == 1 && Bd == 0 && Ld == 0 && Rd == 0)
  {
    moveForward();
    // delay(2000);
    Serial.println("******************FORWARD");
  }
  else if (Fd == 0 && Bd == 1 && Ld == 0 && Rd == 0)
  {
    moveBackward();
    // delay(2000);
    Serial.println("******************BACK");
  }
  else if (Fd == 0 && Bd == 0 && Ld == 1 && Rd == 0)
  {
    turnLeft(100);
    Serial.println("***************** LEFT ");
    //    delay(100);
  }
  else if (Fd == 0 && Bd == 0 && Ld == 0 && Rd == 1)
  {
    turnRight(100);
    Serial.println("***************** RIGHT");
    //    delay(100);
  }
  else if (Fd == 1 && Bd == 0 && Ld == 1 && Rd == 0) {
    turnLeft(50);
    moveForward();
  }
  else if (Fd == 1 && Bd == 0 && Ld == 0 && Rd == 1) {
    turnRight(50);
    moveForward();
  }
  else if (Fd == 0 && Bd == 1 && Ld == 0 && Rd == 1) {
    turnRight(50);
    moveBackward();
  }
  else if (Fd == 0 && Bd == 1 && Ld == 1 && Rd == 1) {
    turnRight(50);
    moveBackward();
  }
  else
  {
    moveStop();
    // delay(2000);
    Serial.println("******************STOP");
  }
  delay(50);
  Fd = 0;
  Bd = 0;
  Ld = 0;
  Rd = 0;
  // ######################################################
}

void moveStop()
{
  //  digitalWrite(led2, HIGH);
  goesForward = false;
  goesBackward = false;
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward()
{
  if (!goesForward)
  {
    //    T_count = 0;
    Serial.println("!!!!!!!!!!!!     F     !!!!!!!!!!!!!!");
    //    digitalWrite(led, HIGH);
    //    digitalWrite(led2, LOW);
    goesForward = true;
    goesBackward = false;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 5)
    {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward()
{
  if (!goesBackward)
  {
    //    T_count = 0;
    //    digitalWrite(led2, HIGH);
    Serial.println("!!!!!!!!!!!!     B     !!!!!!!!!!!!!!");
    goesForward = false;
    goesBackward = true;
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    for (speedSet = 0; speedSet < 110; speedSet += 6)
    {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
    delay(400);
  }
}

int turnRight(int z)
{
  motor1.setSpeed(130);
  motor2.setSpeed(130);
  motor3.setSpeed(130);
  motor4.setSpeed(130);
  Serial.println("******* RIGHT TURN ********");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(z);
  motor1.setSpeed(MAX_SPEED);
  motor2.setSpeed(MAX_SPEED);
  motor3.setSpeed(MAX_SPEED);
  motor4.setSpeed(MAX_SPEED);
}

int turnLeft(int z)
{
  motor1.setSpeed(130);
  motor2.setSpeed(130);
  motor3.setSpeed(130);
  motor4.setSpeed(130);
  Serial.println("******* LEFT TURN ********");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(z);
  motor1.setSpeed(MAX_SPEED);
  motor2.setSpeed(MAX_SPEED);
  motor3.setSpeed(MAX_SPEED);
  motor4.setSpeed(MAX_SPEED);
}
