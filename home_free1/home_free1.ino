const int REVERSE_LEFT = 12;
const int FORWARD_LEFT = 11;
const int ENABLE_LEFT = 10;
const int ENABLE_RIGHT = 9;
const int REVERSE_RIGHT = 8;
const int FORWARD_RIGHT = 7;

void setup()
{
  pinMode(REVERSE_LEFT, OUTPUT);
  pinMode(FORWARD_LEFT, OUTPUT);
  pinMode(ENABLE_LEFT, OUTPUT);
  pinMode(ENABLE_RIGHT, OUTPUT);
  pinMode(REVERSE_RIGHT, OUTPUT);
  pinMode(FORWARD_RIGHT, OUTPUT);
}

void loop()
{
  digitalWrite(ENABLE_LEFT, HIGH);
  digitalWrite(ENABLE_RIGHT, HIGH);
  
  Forward();
  delay(1000 * 5); // Wait for 5 seconds
  Brake();
  delay(1000); // Wait for 1 second
  Reverse();
  delay(1000 * 2); // Wait for 2 seconds
  Brake();
  
  digitalWrite(ENABLE_LEFT, LOW);
  digitalWrite(ENABLE_RIGHT, LOW);
  delay(1000 * 5);

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

//

/*   digitalWrite(FORWARD_LEFT, LOW);
  digitalWrite(FORWARD_LEFT, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(FORWARD_LEFT, LOW);
  digitalWrite(11, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  
   digitalWrite(10, LOW);
  digitalWrite(ENABLE_LEFT, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(ENABLE_LEFT, LOW);
  digitalWrite(11, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  
   digitalWrite(9, LOW);
  digitalWrite(ENABLE_RIGHT, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(ENABLE_RIGHT, LOW);
  digitalWrite(9, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  
  digitalWrite(8, LOW);
  digitalWrite(REVERSE_RIGHT, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(REVERSE_RIGHT, LOW);
  digitalWrite(8, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  
  digitalWrite(7, LOW);
  digitalWrite(FORWARD_RIGHT, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(FORWARD_RIGHT, LOW);
  digitalWrite(7, HIGH);
  delay(1000); // Wait for 1000 millisecond(s) */