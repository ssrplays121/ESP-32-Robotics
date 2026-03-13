// Pin Definitions
const int potX = 34; // VRx connected to GPIO 34
const int potY = 35; // VRy connected to GPIO 35
const int swPin = 27; // SW connected to GPIO 32

void setup() {
  Serial.begin(115200);
  
  // The switch pin needs a pull-up resistor because joysticks 
  // usually connect to GND when pressed.
  pinMode(swPin, INPUT_PULLUP);
}

void loop() {
  // Read analog values (0 - 4095)
  int xValue = analogRead(potX);
  int yValue = analogRead(potY);
  
  // Read button state (0 = pressed, 1 = not pressed)
  int btnState = digitalRead(swPin);

  // Print raw values to Serial Monitor
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | Button: ");
  Serial.println(btnState == LOW ? "PRESSED" : "RELEASED");

  // Optional: Simple Direction Logic
  if (xValue < 500) Serial.println("-> Direction: LEFT");
  else if (xValue > 3500) Serial.println("-> Direction: RIGHT");
  
  if (yValue < 500) Serial.println("-> Direction: UP");
  else if (yValue > 3500) Serial.println("-> Direction: DOWN");

  delay(200); // Slow down the output for readability
}