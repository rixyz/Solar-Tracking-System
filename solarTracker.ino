#include <ESP32Servo.h>
int servoPin1 = 12;  
int servoPin2 = 13;
int servoPin3 = 14;

int maxDegree = 210, offsetValue = 500, distance = 3;
int x1Position = 90, x2Position = 90, yPosition = 105;
int east, west, north, south;
Servo ServoX1, ServoX2, ServoY;

void setup() {
  Serial.begin(9600);

  ServoX1.attach(servoPin1);
  ServoX2.attach(servoPin2);
  ServoY.attach(servoPin3);

  ServoX1.write(x1Position);
  ServoX2.write(x2Position);
  ServoY.write(yPosition);

  delay(3000);
}

void loop() {
  east = analogRead(34);  // 4 LDR input pins
  west = analogRead(35);  
  north = analogRead(32);
  south = analogRead(33);

  Serial.printf("\n%d, %d, %d, %d\n", east, west, north, south);
  if (((east - west) >= offsetValue) && (x1Position <= 135)) {
    Serial.printf("East - West = %d\n", east - west);

    x1Position += distance;
    ServoX1.write(x1Position);

    x2Position -= distance;
    ServoX2.write(x2Position);

  } else if (((west - east) >= offsetValue) && (x1Position >= 45)) {
    Serial.printf("East - West %d\n", east - west);

    x1Position -= distance;
    ServoX1.write(x1Position);

    x2Position += distance;
    ServoX2.write(x2Position);
  } else if ((x1Position <= 45) || (x1Position >= 135)) Serial.printf("X Stop \n");

  if (((north - south) >= offsetValue) && (yPosition <= 120)) {
    yPosition += distance;
    ServoY.write(yPosition);
    
  } else if (((south - north) >= offsetValue) && (yPosition >= 90)) {
    yPosition -= distance;
    ServoY.write(yPosition);
    
  } else if ((yPosition <= 90) || (yPosition >= 120)) Serial.printf("Y Stop \n");

  Serial.printf("X Position: %d %d\n", x1Position, x2Position);
  Serial.printf("Y Position: %d\n", yPosition);


  delay(500);
}
