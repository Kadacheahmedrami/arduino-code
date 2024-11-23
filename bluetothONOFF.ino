



void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
 
}

void loop() {
  if(Serial.available()>0){
char data = Serial.read();
if(data == 'a'){
  digitalWrite(13,HIGH);
}if(data =='b'){
  digitalWrite(13,LOW);
}

  }
  
}

