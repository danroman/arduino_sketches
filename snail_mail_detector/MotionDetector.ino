/*
  Snail Mail Detector v1.0
 
 Initializes PIR Sensor and waits for it to calibrate (50 secs)
 Checks pin 3 (pirPin) to detect state change when Digital PIR Sensor detects motion.
 Writes to Serial Port the Motion Detected Alert message
   
 The circuit: 
 * Digital PIR Sensor Connected to Pin 3
 * Xbee RX Port connected Arduino TX0
 * Xbee TX Port connected to Arduino RX0:
 
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
  
  // Uncomment the following 6 lines to enable Xbee pin sleep mode
  //Serial.println("Putting Xbee into pin sleep mode");
  //Serial.flush();
  //delay(1100);      //Delay required before trying to enter command mode
  //Serial.print("+++");
  //delay(1100);
  //Serial.println("ATSM 1"); // Set Xbee to Sleep Mode 1 (Pin sleep)        
  ////////////////////// sleep mode code end /////////
}

void loop() {
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
