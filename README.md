# ESP32-BLE-Keyboard
A step-by-step guide for building a 5-button Bluetooth keyboard using an ESP32 microcontroller and connecting it to a PC. This keyboard will function as a Bluetooth Human Interface Device (HID) that communicates wirelessly with your computer.

Prerequisites
Hardware Components:

ESP32 development board (such as ESP32-WROOM-32 or ESP32 DevKit V1)
5 push buttons
5 resistors (10 kΩ)
Jumper wires (male-to-male and male-to-female)
Breadboard (optional, for prototyping)
Software:

Arduino IDE (for programming the ESP32)
ESP32 BLE Keyboard library (GitHub link)
BLE (Bluetooth Low Energy) supported on the PC
Step 1: Setting Up the Environment
Install Arduino IDE if you haven't already.

Add ESP32 Board to Arduino IDE:

Go to File > Preferences.
In the Additional Board Manager URLs field, add this URL: https://dl.espressif.com/dl/package_esp32_index.json.
Go to Tools > Board > Boards Manager, search for "ESP32" and install it.
Install the ESP32 BLE Keyboard Library:

In Arduino IDE, go to Sketch > Include Library > Manage Libraries.
Search for "ESP32 BLE Keyboard" by T-vK and install it.
Step 2: Setting Up the Circuit
Connect the Buttons to the ESP32 GPIO pins.
Choose five GPIO pins on the ESP32 to connect the buttons. Common pins for buttons are GPIO 13, 12, 14, 27, and 26.
Connect one leg of each button to the chosen GPIO pin.
Connect a 10 kΩ resistor between each button's GPIO pin and GND.
Connect the other leg of each button to 3.3V to act as a pull-up, ensuring the GPIO pin registers HIGH when the button is pressed.
Step 3: Writing the Code
Open a New Sketch in Arduino IDE.

Include the ESP32 BLE Keyboard Library:

cpp
Copy code
#include <BleKeyboard.h>
Define Pins and Initialize the BLE Keyboard:

cpp
Copy code
BleKeyboard bleKeyboard("ESP32 Keyboard", "Aziz's Devices", 100); // Device name, manufacturer, and battery level

// Define button pins
const int buttonPins[5] = {13, 12, 14, 27, 26}; // Assign each button to a GPIO pin
const char keyMappings[5] = {'a', 'b', 'c', 'd', 'e'}; // Map each button to a specific key
Initialize Buttons in setup():

cpp
Copy code
void setup() {
    Serial.begin(115200);
    bleKeyboard.begin();
    for (int i = 0; i < 5; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP); // Set buttons as input with internal pull-up
    }
}
Program the Button Logic in loop():

cpp
Copy code
void loop() {
    if (bleKeyboard.isConnected()) { // Check if the keyboard is connected via BLE
        for (int i = 0; i < 5; i++) {
            if (digitalRead(buttonPins[i]) == LOW) { // Button pressed (LOW because of pull-up)
                bleKeyboard.print(keyMappings[i]); // Send the mapped key
                delay(200); // Debounce delay to avoid multiple keypresses
            }
        }
    }
}
Upload the Code to your ESP32 board.

Step 4: Connecting the ESP32 Keyboard to the PC
Power the ESP32 with a USB cable or a suitable power source.
Turn on Bluetooth on your PC.
The ESP32 should appear as a Bluetooth device named "ESP32 Keyboard" (or the name you set).
Pair the ESP32 with your PC as you would with any Bluetooth keyboard.
Step 5: Testing the Keyboard
Open a text editor on your PC.
Press each button and check if it types the corresponding character (as set in keyMappings[]).
If each button correctly types its assigned character, the setup is successful!
Additional Enhancements
Debouncing: Improve reliability by adding a more sophisticated debouncing mechanism.
Multiple Keypresses: Modify the code to handle multiple simultaneous keypresses if required.
Battery Power: For wireless convenience, power the ESP32 with a battery pack if you intend to use it without a USB connection.**
