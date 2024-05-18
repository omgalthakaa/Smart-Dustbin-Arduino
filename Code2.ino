// Define the pins for the HC-SR04 sensor
const int trigPin = 2;
const int echoPin = 3;
const int flamePin =5;
const int flamePinAnalog =A5;
const int mq135Pin = A0;
// Define the pins for the LEDs
const int greenLedPin = 13;
const int yellowLedPin = 12;
const int blueLedPin = 11;
const int redLedPin = 10;
const int whiteLedPin = 9;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set the trigPin as an OUTPUT
  pinMode(trigPin, OUTPUT);
  // Set the echoPin as an INPUT
  pinMode(echoPin, INPUT);

  // Set the MQ-135 pin as INPUT
  pinMode(mq135Pin, INPUT);
  //flamepinanalog
  pinMode(flamePinAnalog, INPUT);
  // Set the flame sensor pin as INPUT
  pinMode(flamePin, INPUT);

  // Set the LED pins as OUTPUTs
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(whiteLedPin, OUTPUT);
}

void loop() {
  // Variables to store the distance and duration
  long duration, inches;

  // Variables to store gas and flame readings
  int gasReading = analogRead(mq135Pin);
  int flameReading = digitalRead(flamePin);
  int flamePinAnalogReading = analogRead(flamePinAnalog);

  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond pulse to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in inches
  inches = duration / 74 / 2;

  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.print(inches);
  Serial.println(" inches");


  // Print gas reading for debugging
  Serial.print("Gas Reading: ");
  Serial.println(gasReading);

  // Print flame reading for debugging
  Serial.print("Flame Reading: ");
  Serial.println(flameReading);

  Serial.print("Flame Reading (Analog): ");
  
  // Set pin 7 (flamePin) to analog mode
  pinMode(flamePin, INPUT_PULLUP);
  int flameReadingAnalog = analogRead(flamePin);
  Serial.println(flameReadingAnalog);
  // Control the LEDs based on distance thresholds

    // Control the LEDs based on sensor readings
    //if (gasReading > 500 && ( flameReading == HIGH |||| flameReadingAnalog > 500))
    if (flameReading == LOW || flameReadingAnalog > 500) {
      // If gas concentration is high and flame is detected
      digitalWrite(redLedPin, HIGH);
      digitalWrite(whiteLedPin, LOW);
      Serial.println("Fire Detected!");
    }
    else{
      digitalWrite(redLedPin, LOW);
      digitalWrite(whiteLedPin, HIGH);
      Serial.println("No Fire Detected!");

    }
    
    if (inches > 15) {
    digitalWrite(greenLedPin, HIGH);   // Green LED on
    digitalWrite(yellowLedPin, LOW);   // Yellow LED off
    digitalWrite(blueLedPin, LOW);      // Red LED off
    Serial.print("Green: ");
  } else if (inches >= 5 && inches <= 15) {
    digitalWrite(greenLedPin, LOW);    // Green LED off
    digitalWrite(yellowLedPin, HIGH);  // Yellow LED on
    digitalWrite(blueLedPin, LOW);      // Red LED off
    Serial.print("Yellow: ");
  } else {
    digitalWrite(greenLedPin, LOW);    // Green LED off
    digitalWrite(yellowLedPin, LOW);   // Yellow LED off
    digitalWrite(blueLedPin, HIGH);     // Red LED on
    Serial.print("Blue: ");
  }

  // Wait for a short time before next reading
  delay(1000);
}
