/*
  Snail Mail Detector v1.0
 
 Initializes PIR Sensor and waits for it to calibrate (50 secs)
 Checks pin 3 (pirPin) to detect state change when Digital PIR Sensor detects motion.
 Writes to Serial Port the Motion Detected Alert message
   
 The circuit: 
 * For wiring schematic please visit: http://highmu.com/?p=69
 
 created 01 Jan. 2014
 by Daniel Roman
 
 */
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 50; // 50 seconds for PANASONIC PIR 
int pirPin = 3;      // Pir sensor output is connected to Pin 3
int pirState = HIGH; // initialize PIR Sensor state to HIGH
int val = 0; 


void setup() {
  // initialize serial port:
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  
  // give sensor time to calibrate
  Serial.print("calibrating sensor ");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
  
}

void loop() {

  // read Arduino pin to detect change in logic state
  // When motion is detected, logic state should be LOW
  // and HIGH when there is no motion detected
  val = digitalRead(pirPin);
 
  if (val == LOW) {
    if (pirState == HIGH) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not
      // state
      pirState = LOW;     
    }   
  } else {
    if (pirState == LOW) {
      Serial.println("Motion ended!");
      pirState = HIGH;
    }
  }
}
