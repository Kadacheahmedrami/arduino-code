#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
  // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  int gasValue = analogRead(A0);
  Serial.println(gasValue);

    if(gasValue>400){
    myservo.write(0);
       myservo.write(180);
       
     Serial.println("==================");
    }


   if(gasValue<300){
    myservo.write(0);
       myservo.write(0);
       
     Serial.println("==================");
    }

        
 
  
  
}