const int REVERSE_LEFT = 12;
const int FORWARD_LEFT = 11;
const int ENABLE_LEFT = 10;
const int ENABLE_RIGHT = 9;
const int REVERSE_RIGHT = 8;
const int FORWARD_RIGHT = 7;

const int RIGHT_FEEDBACK = 2; 
const int LEFT_FEEDBACK = 3;

const int TRIGGER_PIN = 4;
const int ECHO_PIN = 5;
const int MAX_DISTANCE = 200;

volatile int leftCounter = 0;
volatile int rightCounter = 0;

const int meterInRevs = 435;

int speedLeft = 80;
int speedRight = 80;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
  SetupPins(); // Setup the pins
  
  Serial.begin(115200);
  sonar.ping_cm();
  
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK), LeftMotorISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK), RightMotorISR, RISING);
}

void loop()
{
  delay(50);
  int distance = sonar.ping_cm();
  if (distance == 0 || distance > 12){
    Forward(160);
    
  }


  // Ping
  // Brake IF we are under 12 cm
  // Delay
  // Reverse
  // Brake IF distance is = or > 12 cm
  // PivotLeft (60, 4400)
  // Brake
  // Forward
  
}

void story8()
{
  // Move forward at least the lenght of the rover
  // 60 = motor speed, 4400 = delay
  
  // Moves in a figure 8 pattern
  // Have not tested on a Rover
  ForwardPivotLeft(60, 4400); 
  ForwardPivotLeft(60, 4400);
  ForwardPivotLeft(60, 4400);
  ForwardPivotLeft(60, 4400);
  
  ForwardPivotRight(60, 4400);
  ForwardPivotRight(60, 4400);
  ForwardPivotRight(60, 4400);
  ForwardPivotRight(60, 4400);
  
  exit(0);
}

void story7()
{
  // Move Forward at least the length of the rover
  // 60 = motor speed, 4400 = delay
  
  // Moves in a box, turning left
  // Have not tested on a Rover
  ForwardPivotLeft(60, 4400); 
  ForwardPivotLeft(60, 4400);
  ForwardPivotLeft(60, 4400);
  ForwardPivotLeft(60, 4400);
  
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
  Reverse();
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

void ForwardPivotLeft(int speed, int ms)
{
  Forward(160);
  delay(3000);
  Brake(); 
  delay(1000);
  PivotLeft(speed, ms);
  Brake();
  delay(1000);
}

void ForwardPivotRight(int speed, int ms) 
{
  Forward(160);
  delay(3000);
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
  digitalWrite(FORWARD_RIGHT, HIGH);
  analogWrite(ENABLE_RIGHT, speed);
  digitalWrite(REVERSE_LEFT, HIGH);
  analogWrite(ENABLE_LEFT, speed);
  delay(ms);
}

void PivotRight(int speed, int ms)
{ //90 degree
  digitalWrite(FORWARD_LEFT, HIGH);
  analogWrite(ENABLE_LEFT, speed);
  digitalWrite(REVERSE_RIGHT, HIGH);
  analogWrite(ENABLE_RIGHT, speed);
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

void Reverse()
{
  digitalWrite(REVERSE_LEFT, HIGH);
  digitalWrite(REVERSE_RIGHT, HIGH);
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
