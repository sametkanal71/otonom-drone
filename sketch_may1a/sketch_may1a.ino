#include <Servo.h>
#include <NewPing.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define TRIGGER_PIN 5
#define ECHO_PIN 6
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
SoftwareSerial gpsSerial(4, 3);
TinyGPSPlus gps;

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

int speed = 100;
int throttle = 0;

void setup() {
  motor1.attach(6);
  motor2.attach(9);
  motor3.attach(10);
  motor4.attach(11);
}

void loop() {
  unsigned long start = millis();
  
  while (millis() - start < 1000) {
    gpsSerial.listen();
    while (gpsSerial.available()) {
      if (gps.encode(gpsSerial.read())) {
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();
        // Programlanmış yola göre drone'u uçurmak için kod yazılabilir
      }
    }
  }

  int distance = sonar.ping_cm();

  if (distance > 0 && distance < 50) {
    motor1.write(speed);
    motor2.write(speed);
    motor3.write(0);
    motor4.write(0);
  } else {
    motor1.write(throttle + speed);
    motor2.write(throttle + speed);
    motor3.write(throttle);
    motor4.write(throttle);
  }
}



//Arduino kartı
//Motorlar (en az 4 adet)
//ESC'ler (her motor için bir tane)
//Lipo pil
//Drone iskeleti
//Ultrasonik mesafe sensörleri
//Gyro sensörü
//GPS modülü