#include <Servo.h>

const int echoPin = 7;
const int trigPin = 8;

Servo servo;


void setup() {
  servo.attach(9);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  Serial.begin(115200);
}

void loop() {
  for(int i=0; i<=180; i++){
    servo.write(i);
    if (i % 10 == 0) {
      sendData(i);
    }
    delay(15);
  }
  
  for(int i=180; i>=0; i--){
    servo.write(i);
    if (i % 10 == 0) {
      sendData(i * 1.0);
    }
    delay(15);
  }
}

float readDist() {
  const float speedOfSoundMPerSec = 340.0;
  const float speedOfSoundCmPerUs = speedOfSoundMPerSec / 10000.0;
  return readPulse() * speedOfSoundCmPerUs / 2.0;    
}

float readPulse() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  return duration;
}

void sendData(float angle) {
    float dist = readDist();
    Serial.println(dist);
    Serial.println(2.0 * 3.14 * angle / 360);
}
