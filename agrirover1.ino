#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// --- Pin Definitions ---
#define SOIL_MOISTURE_PIN A0
#define LDR_PIN A1
#define TEMP_PIN A2
#define SERVO_PIN 11

// --- Motor Pin Definitions ---
#define EN_A 9
#define IN1 8
#define IN2 7
#define EN_B 10
#define IN3 12
#define IN4 13

// --- Object Initialization ---
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo soilServo;

// --- Servo Positions ---
const int SENSOR_UP_POS = 0;
const int SENSOR_DOWN_POS = 90;

// --- NEW: Variable to track total motor runtime ---
unsigned long totalMovementTime = 0;
const int moveDuration = 2000; // Define movement time as a constant

void setup(){
  Serial.begin(9600);
  
  soilServo.attach(SERVO_PIN);
  soilServo.write(SENSOR_UP_POS);
  
  pinMode(EN_A, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print("Agri-Rover I2C");
  lcd.setCursor(0, 1); 
  lcd.print("Online!");
  delay(2000); 
  lcd.clear(); 
}

void loop(){
  stopMotors();
  readAndDisplaySensors();
  delay(1000); 

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moving Forward...");
  lcd.setCursor(0, 1);
  lcd.print("Sensor is UP");
  moveForward();
  delay(moveDuration); 
  
  // --- NEW: Add the last movement time to our total ---
  totalMovementTime += moveDuration;
}

void readAndDisplaySensors() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lowering sensor..");
  
  soilServo.write(SENSOR_DOWN_POS);
  delay(1000);

  lcd.setCursor(0, 1);
  lcd.print("Reading soil...");
  delay(500);

  int soilRaw = analogRead(SOIL_MOISTURE_PIN);
  int soilMoisturePercent = map(soilRaw, 870, 179, 0, 100); 
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);

  int lightRaw = analogRead(LDR_PIN);
  int lightPercent = map(lightRaw, 6, 679, 0, 100);
  
  int tempRaw = analogRead(TEMP_PIN);
  float voltage = tempRaw * 5.0 / 1024.0;
  float tempC = (voltage - 0.5) * 100;
  
  // --- MODIFIED: Enhanced Serial Monitor Output ---
  Serial.println("---------- Rover Status ----------");
  Serial.print("Soil Moisture: "); Serial.print(soilMoisturePercent); Serial.println("%");
  Serial.print("Ambient Light: "); Serial.print(lightPercent); Serial.println("%");
  Serial.print("Temperature:   "); Serial.print(tempC); Serial.println(" C");
  Serial.print("Total Motor On-Time: "); Serial.print(totalMovementTime / 1000.0); Serial.println(" sec");
  Serial.println("----------------------------------");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil:"); lcd.print(soilMoisturePercent); lcd.print("%  ");
  lcd.print("Light:"); lcd.print(lightPercent); lcd.print("% ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: "); lcd.print(tempC, 1); lcd.print(" C      ");

  delay(2000);
  
  soilServo.write(SENSOR_UP_POS);
  delay(1000);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN_A, 200);
  analogWrite(EN_B, 200);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN_A, 0);
  analogWrite(EN_B, 0);
}