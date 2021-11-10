#include <NewPing.h>

const int REVERSE_LEFT = 12;
const int FORWARD_LEFT = 11;
const int ENABLE_LEFT = 10;
const int ENABLE_RIGHT = 9;
const int REVERSE_RIGHT = 8;
const int FORWARD_RIGHT = 7;

// Arduino pins for receiving feedback from rover's hall sensors
const int RIGHT_FEEDBACK = 2; 
const int LEFT_FEEDBACK = 3;

// Arduino pins tied to pins on rover's ultrasonic sensor
const int TRIGGER_PIN = 4;
const int ECHO_PIN = 5;
const int MAX_DISTANCE = 200;

// Arduino pins tied to pins on sensors underneath rover
const int TRIGGER_DOWN = 13;
const int ECHO_DOWN = 17;

volatile int leftCounter = 0;
volatile int rightCounter = 0;

const int meterInRevs = 435;

int speedLeft = 80;
int speedRight = 80;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonarDown(TRIGGER_DOWN, ECHO_DOWN, MAX_DISTANCE);

void setup()
{
  SetupPins(); // Setup the pins
  AttachInterrupts(); // Attach ISRs to feedback pins
  
  Serial.begin(115200);
  sonar.ping_cm();
  sonarDown.ping_cm();
}

void loop()
{
  story10();
}


void story10()
{
  // Move forward, unless drop > 12cm
  // If drop is < 12cm?
    // Move forward
  // else there is a drop
    // Brake
    // Reverse
    // Ping
    // Delay
    // Until 10cm from the drop
  delay(50);
  int drop = sonarDown.ping_cm();
  Forward(160);
  if (drop > 12) {
    Brake();
    delay(500);
    Reverse(255);
    delay(750);
    exit(0);
  }
}

void story9()
{
  // Delay to ensure NewPing is able to accurately match ping to echo
  delay(50);
  int distance = sonar.ping_cm();
  if (distance == 0 || distance > 12){
    Forward(160);
  } else {
    Brake();
    delay(1000);
    Reverse(255);
    delay(2000);
    Brake();
    delay(1000);
    PivotLeft(225, 750);
    Brake();
    delay(1000);
    Forward(160);
  }
}


void story8()
{
  // Move forward at least the lenght of the rover
  // 60 = motor speed, 4400 = delay
  
  // Moves in a figure 8 pattern
  // Have not tested on a Rover
  
  int speed = 225;
  int delay = 750;
  
  ForwardPivotLeft(speed, delay); 
  ForwardPivotLeft(speed, delay);
  ForwardPivotLeft(speed, delay);
  ForwardPivotLeft(speed, delay);
  
  ForwardPivotRight(speed, delay);
  ForwardPivotRight(speed + 30, delay + 180);
  ForwardPivotRight(speed, delay);
  ForwardPivotRight(speed, delay + 100);
  
  exit(0);
}

void story7()
{
  // Move Forward at least the length of the rover
  // 60 = motor speed, 4400 = delay
  
  // Moves in a box, turning left
  // Have not tested on a Rover
  int speed = 225;
  int delay = 750;
  
  ForwardPivotLeft(speed, delay); 
  ForwardPivotLeft(speed, delay);
  ForwardPivotLeft(speed, delay);
  ForwardPivotLeft(speed, delay);
  
  exit(0);
}

void story6()
{
  if (millis() >= 10000){ // Has the timer hit 10 seconds?
    Brake();
  } else {
    Forward(160);
    
    if (rightCounter > leftCounter){
      speedLeft = speedLeft + 5; 
      Turn(speedLeft, speedRight);
    } else if (leftCounter > rightCounter){
      speedRight = speedRight + 5;
      Turn(speedLeft, speedRight);
    } else {
      Turn(speedLeft, speedRight); // Go straight with equal speeds
    }
  }  
}

void story5()
{
  Forward(100);
  delay(2000);
    
  Turn(160, 80);
  delay(2000);
    
  Turn(80, 160);
  delay(2000);
    
  Turn(160, 80);
  delay(2000);
    
  Turn(80, 160);
  delay(2000);
  
  Brake();
  exit(0);
}

void story4()
{
  // Move the Rover forward 2 meters
  if (leftCounter < (meterInRevs * 2)){
    Forward(100);
  } else {
    Brake();
  }
}

void story3()
{
  Forward(100);
  delay(1000 * 5); // Wait for 5 seconds
  Brake();
  delay(1000); // Wait for 1 second
  Reverse(255);
  delay(1000 * 2); // Wait for 2 seconds
  Brake();
  
  delay(1000 * 5);
}

void SetupPins()
{
  pinMode(REVERSE_LEFT, OUTPUT);
  pinMode(FORWARD_LEFT, OUTPUT);
  pinMode(ENABLE_LEFT, OUTPUT);
  pinMode(ENABLE_RIGHT, OUTPUT);
  pinMode(REVERSE_RIGHT, OUTPUT);
  pinMode(FORWARD_RIGHT, OUTPUT); 
}

void AttachInterrupts()
{
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK), LeftMotorISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK), RightMotorISR, RISING);
}

void ForwardPivotLeft(int speed, int ms)
{
  Forward(160);
  delay(1500);
  Brake(); 
  delay(1000);
  PivotLeft(speed, ms);
  Brake();
  delay(1000);
}

void ForwardPivotRight(int speed, int ms) 
{
  Forward(160);
  delay(1500);
  Brake(); 
  delay(1000);
  PivotRight(speed, ms);
  Brake();
  delay(1000);
}

void Forward(int speed)
{
  ForwardRight(speed);
  ForwardLeft(speed);
}

void ForwardRight(int speed)
{
  digitalWrite(FORWARD_RIGHT, HIGH);
  analogWrite(ENABLE_RIGHT, speed);
}

void ForwardLeft(int speed)
{
  digitalWrite(FORWARD_LEFT, HIGH);
  analogWrite(ENABLE_LEFT, speed);
}

void Turn(int speedLeft, int speedRight)
{
  ForwardRight(speedRight);
  ForwardLeft(speedLeft);
}

void PivotLeft(int speed, int ms)
{ //90 degree
  ForwardRight(speed);
  ReverseLeft(speed);
  delay(ms);
}

void PivotRight(int speed, int ms)
{ //90 degree
  ForwardLeft(speed);
  ReverseRight(speed);
  delay(ms);
}

void Brake()
{
  digitalWrite(FORWARD_LEFT, LOW);
  digitalWrite(FORWARD_RIGHT, LOW);
  digitalWrite(REVERSE_LEFT, LOW);
  digitalWrite(REVERSE_RIGHT, LOW);
  
  DisableMotors();
}

void Reverse(int speed)
{
  ReverseLeft(speed);
  ReverseRight(speed);
}

void ReverseLeft(int speed)
{
  digitalWrite(REVERSE_LEFT, HIGH);
  analogWrite(ENABLE_LEFT, speed);
}

void ReverseRight(int speed)
{
  digitalWrite(REVERSE_RIGHT, HIGH);
  analogWrite(ENABLE_RIGHT, speed);
}

void EnableMotors()
{
  digitalWrite(ENABLE_LEFT, HIGH);
  digitalWrite(ENABLE_RIGHT, HIGH);
}

void DisableMotors()
{
  digitalWrite(ENABLE_LEFT, LOW);
  digitalWrite(ENABLE_RIGHT, LOW);
}

void LeftMotorISR()
{
  leftCounter++;
}

void RightMotorISR()
{
  rightCounter++;
}
