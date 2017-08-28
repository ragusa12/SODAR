#include <Servo.h>
#include <stdint.h>

#define echoPin 3
#define trigPin 4

Servo servo;

void setup() {
  servo.attach(2);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int i;
  for ( i = 0; i < 180; i++ ) {
    capture(i);
  }
  for (; i > 0; i--) {
    capture(i);
  }
}

void capture( int a ) {
  servo.write(a);
  delay(10);
  uint8_t dat[] = { a, getDistance() };
  Serial.write(dat, 2);
}

uint8_t getDistance() {
  long int duration;
  double distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite( trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite( trigPin, LOW);
  duration = pulseIn( echoPin, HIGH );
  distance = ( (double) duration / 2 ) * (double) 0.00034029;
  uint8_t d = (double) distance / 0.01953125;
  return d;
}
