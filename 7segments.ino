#include <TM1637Display.h>

// Define the connections pins
#define CLK 2  // Clock pin
#define DIO 3  // Data pin

// Initialize the display object
TM1637Display display(CLK, DIO);

void setup() {
  // Set the brightness of the display (0-7)
  display.setBrightness(5);

  // Clear the display at startup
  display.clear();
}

void loop() {
  // Example: display a static number
  int number = 1234;
  display.showNumberDec(number); // Display the number 1234

  delay(2000);  // Wait 2 seconds

  // Example: display a number with leading zeros (e.g., 0032)
  number = 32;
  display.showNumberDec(number, true); // 'true' enables leading zeros

  delay(2000);  // Wait 2 seconds

  // Example: display each digit in sequence
  for (int i = 0; i <= 9999; i++) {
    display.showNumberDec(i, true);  // Display i with leading zeros
    delay(100);  // Delay to create a counting effect
  }
}
