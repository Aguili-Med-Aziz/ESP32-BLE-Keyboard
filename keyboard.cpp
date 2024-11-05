#include <BleKeyboard.h>   // Include the BLE Keyboard library

// Instantiate the BLE keyboard
BleKeyboard bleKeyboard("ESP32 Keyboard", "ESP32", 100);

// Define button pins
const int buttonPins[5] = {13, 12, 14, 27, 26}; // Assign each button to a GPIO pin

// Define key codes for letters 'A', 'B', 'C', 'D', 'E'
const char keyCodes[5] = {'A', 'B', 'C', 'D', 'E'};

// Button states
bool buttonState[5] = {0, 0, 0, 0, 0};
bool lastButtonState[5] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(115200);

  // Start BLE Keyboard
  bleKeyboard.begin();

  // Initialize button pins
  for (int i = 0; i < 5; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Set each button pin as input with pullup
  }

  Serial.println("ESP32 BLE Keyboard started. Waiting for connection...");
}

void loop() {
  // Check if BLE keyboard is connected
  if (bleKeyboard.isConnected()) {

    // Check each button
    for (int i = 0; i < 5; i++) {
      buttonState[i] = digitalRead(buttonPins[i]);

      // Check if the button state has changed (button pressed)
      if (buttonState[i] == LOW && lastButtonState[i] == HIGH) {
        // Send the corresponding letter for this button
        bleKeyboard.print(keyCodes[i]);
        delay(100);   // Small delay to simulate keypress duration
      }
      lastButtonState[i] = buttonState[i]; // Update the last state
    }
  }
  delay(10);  // Small delay for stability
}
