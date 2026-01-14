#include <Arduino.h>
#include "yboard.h"

// These pins are found on the back of the Y-board
// They can be used to either detect or provide voltage
// Examples are provided at the end of loop()
#define PIN_1 8
#define PIN_2 15


void setup() {
  Serial.begin(9600);
  Yboard.setup();
  
  // Currently, PIN_1 (#8) is set up to detect voltage and PIN_2 (#15) is set up to provide it
  // Modify this if you'd like
  pinMode(PIN_1, INPUT);
  pinMode(PIN_2, OUTPUT);
  
  //Add any code you want to run just once here.
}

void loop() {
  // Add any code you want to run repeatedly here.
  // Below are some examples of how to use different parts of the Y-Board.
  // Delete anything you don't need, and add anything you want.
  // For a full list of functions available on the Y-board, see the header file at .pio/libdeps/esp32/Y-Board v4/include/yboard.h from lines 39-330.
  
  // ========LEDS========
  Yboard.set_led_brightness(128);       // Set the brightness of all LEDs to 50% (128 out of 255)
  Yboard.set_all_leds_color(0, 255, 0); // Set all LEDs to green
  Yboard.set_led_color(1, 255, 0, 0);   // Set the first LED to red
  // ====================


  // ========BUTTONS AND SWITCHES========
  bool button_1;  // Declare variables like these at the top of your file (before setup()) so you can use them to store values.
  bool switch_1;  //

  // Use these commands to get values from the buttons and switches.
  button_1 = Yboard.get_button(1);  
  switch_1 = Yboard.get_switch(1);
  // Then use those values however you need them
  // ====================================
  

  // ========ROTARY ENCODER (KNOB)========
  int knob_position;        // Declare variables like these at the top of your file (before setup()) so you can use them to store values.
  bool knob_button_pressed; //

  // Use these commands to get values from the rotary encoder (knob).
  knob_position = Yboard.get_knob();
  knob_button_pressed = Yboard.get_knob_button();
  // Then use those values however you need them
  // =====================================


  // ========DISPLAY========
  Yboard.display.clearDisplay(); // Clear the display
  Yboard.display.setTextSize(1); // Set text size to 1 (smallest)
  Yboard.display.setTextColor(SSD1306_WHITE); // Set text color to white
  Yboard.display.setCursor(0, 0); // Set cursor to top-left corner
  Yboard.display.println("Hello, Y-Board!"); // Print text to the display

  // You can also draw shapes on the display. Here are some examples:
  Yboard.display.drawLine(0, 10, 127, 10, SSD1306_WHITE); // Draw a horizontal line across the display
  Yboard.display.drawRect(10, 15, 50, 30, SSD1306_WHITE); // Draw a rectangle
  Yboard.display.fillRect(70, 15, 50, 30, SSD1306_WHITE); // Draw a filled rectangle
  Yboard.display.drawCircle(30, 50, 10, SSD1306_WHITE); // Draw a circle
  Yboard.display.fillCircle(90, 50, 10, SSD1306_WHITE); // Draw a filled circle
  Yboard.display.drawTriangle(110, 40, 120, 60, 100, 60, SSD1306_WHITE); // Draw a triangle
  Yboard.display.fillTriangle(50, 40, 60, 60, 40, 60, SSD1306_WHITE); // Draw a filled triangle

  //ANY time you make changes to the display, they won't be shown until you call this function:
  Yboard.display.display(); // Update the display to show the changes
  //(Including if you clear the display)
  // =======================

  // ========ACCELEROMETER========
  // Here's an example of how to get angle data from the accelerometer. The Values the accelerometer gives are between 0 and 999.

  int x_value;  //Declare variables like these at the top of your file (before setup()) so you can use them to store values.
  int y_value;  //
  int z_value;  //

  // Use a block like this to get data from the accelerometer using the variables you declared. The if() makes sure you're only getting data when it's available.
  if (Yboard.accelerometer_available()) {
    accelerometer_data accel_data = Yboard.get_accelerometer();
    x_value = accel_data.x;
    y_value = accel_data.y;
    z_value = accel_data.z;
  }
  // Then you can use the x_value, y_value, and z_value variables to do whatever you want with the accelerometer data.
  // ============================


  // ========PLAY NOTES========
  // This plays a song on the speaker. The notes are specified in the string.
  Yboard.play_notes("T160 V2 O5 F D. C#8 D. C#8 D8 B8- O4 G8 F"); // BYU Fight Song
  // See lab 7 for info on how these strings work
  // ==========================

  // Use these functions--digitalWrite() and digitalRead()--to detect and provide voltage for anything else
  // A good place to start is with something you build on your breadboard :)

  // =========READING EXTERNAL VOLTAGE=========
  if (digitalRead(PIN_1)){ // digitalRead keeps an eye on PIN_1 (pin 8). Feel free to change between PIN_1 and PIN_2
    Yboard.set_all_leds_color(255,0,0); // If voltage is detected in PIN_1, then all the Yboard LEDs will be set to red.
  } else {
    Yboard.set_all_leds_color(0,0,0); // If voltage is NOT detected in PIN_1, then all the Yboard LEDs will be turned off.
  }
  // Feel free to change or mess around with any of these values/functions
  // ==========================

  // =========PROVIDING VOLTAGE=========
  if (Yboard.get_button(1)) {  // the get_button analyzes the state of button 1. If it is pressed it report "TRUE" otherwise it will report "FALSE."

    Yboard.display.setCursor(3, 3); // Try removing some of these lines to see what happens! (maybe nothing)
    Yboard.display.println("Button 1 pressed!");
    Yboard.display.display();

    digitalWrite(PIN_2, HIGH);  // this command will provide voltage from PIN_2 (pin 15).
  } else {
    digitalWrite(PIN_2, LOW);   // This stops providing voltage from PIN_2.

    Yboard.display.clearDisplay(); // This code erases the previous message, but could cause conflicts with other lines
    Yboard.display.display(); // Comment out or adjust this code if needed
  }
  // ==========================
  
}
