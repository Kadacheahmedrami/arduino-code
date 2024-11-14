#include <Servo.h>

int trigPin = 8;
int echoPin = 9;
int enA = 3;
int in1 = 2;
int in2 = 4;
int enB = 6;
int in3 = 5;
int in4 = 7;

Servo myServo;
int servoPin = 10;

int distanceThreshold = 10;
int forwardCooldown = 1000;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(90);
  Serial.println("Setup complete. Car is ready to move.");
}

void loop() {
  int distance = measureDistance();
  
  Serial.print("Front Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < distanceThreshold) {
    Serial.println("Obstacle detected. Stopping car.");

    stopCar();

    int rightDistance = checkDirection(10);
    Serial.print("Right Distance: ");
    Serial.print(rightDistance);
    Serial.println(" cm");

    int leftDistance = checkDirection(170);
    Serial.print("Left Distance: ");
    Serial.print(leftDistance);
    Serial.println(" cm");

    myServo.write(90);
    delay(200);

    if (rightDistance > leftDistance) {
      Serial.println("More space on the right. Reversing and turning right.");
      reverseCar();
      turnRight();
    } else {
      Serial.println("More space on the left. Reversing and turning left.");
      reverseCar();
      turnLeft();
    }

    Serial.println("Moving forward briefly to escape the obstacle.");
    moveForward();
    delay(forwardCooldown);
  } else {
    Serial.println("No obstacle detected. Moving forward.");
    moveForward();
  }

  delay(100);
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW3);
  analogWrite(enA, 190);
  analogWrite(enB, 190);
  Serial.println("Moving forward.");
}

void stopCar() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  Serial.println("Car stopped.");
}

void reverseCar() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 190);
  analogWrite(enB, 190);
  Serial.println("Reversing for 0.5 seconds.");
  delay(500);
  stopCar();
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Turning right.");
  delay(500);
  stopCar();
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Turning left.");
  delay(500);
  stopCar();
}

int checkDirection(int angle) {
  myServo.write(angle);
  delay(500);
  int distance = measureDistance();
  Serial.print("Distance at ");
  Serial.print(angle == 0 ? "right" : "left");
  Serial.print(" angle (");
  Serial.print(angle);
  Serial.print("): ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

