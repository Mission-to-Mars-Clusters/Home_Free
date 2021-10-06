const int REVERSE_LEFT = 12;
const int FORWARD_LEFT = 11;
const int ENABLE_LEFT = 10;
const int ENABLE_RIGHT = 9;
const int REVERSE_RIGHT = 8;
const int FORWARD_RIGHT = 7;

const int RIGHT_FEEDBACK = 2; 
const int LEFT_FEEDBACK = 3;

volatile int leftCounter = 0;
volatile int rightCounter = 0;


void setup()
{
  SetupPins(); // Setup the pins
  
  Serial.begin(115200);
  
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK), LeftMotorISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK), RightMotorISR, RISING);
}

void loop()
{
  EnableMotors();
  
  Forward();
  delay(1000 * 5); // Wait for 5 seconds
  Brake();
  delay(1000); // Wait for 1 second
  Reverse();
  delay(1000 * 2); // Wait for 2 seconds
  Brake();
  
  DisableMotors();
  delay(1000 * 5);
  
  // Move the Rover forward 2 meters 
  
  
  Serial.print("Left Counter: ");
  Serial.println(leftCounter);
  
  Serial.print("Right Counter: ");
  Serial.println(rightCounter);
}

void SetupPins(){
  pinMode(REVERSE_LEFT, OUTPUT);
  pinMode(FORWARD_LEFT, OUTPUT);
  pinMode(ENABLE_LEFT, OUTPUT);
  pinMode(ENABLE_RIGHT, OUTPUT);
  pinMode(REVERSE_RIGHT, OUTPUT);
  pinMode(FORWARD_RIGHT, OUTPUT); 
}

void Forward(){
  digitalWrite(FORWARD_LEFT, HIGH);
  digitalWrite(FORWARD_RIGHT, HIGH);
}

void Brake(){
  digitalWrite(FORWARD_LEFT, LOW);
  digitalWrite(FORWARD_RIGHT, LOW);
  digitalWrite(REVERSE_LEFT, LOW);
  digitalWrite(REVERSE_RIGHT, LOW);
}

void Reverse(){
  digitalWrite(REVERSE_LEFT, HIGH);
  digitalWrite(REVERSE_RIGHT, HIGH);
}

void EnableMotors(){
  digitalWrite(ENABLE_LEFT, HIGH);
  digitalWrite(ENABLE_RIGHT, HIGH);
}

void DisableMotors(){
  digitalWrite(ENABLE_LEFT, LOW);
  digitalWrite(ENABLE_RIGHT, LOW);
}

void LeftMotorISR(){
  leftCounter++;
}

void RightMotorISR(){
  rightCounter++;
}
