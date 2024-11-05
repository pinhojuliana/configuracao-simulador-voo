#include <SPI.h>
#include <ShiftRegister74HC595.h>


ShiftRegister74HC595<8> sr3(8, 9, 10); 
ShiftRegister74HC595<8> sr4(11, 12, 13); 

void displayDigit(int digit, int position, bool decimal) {
  static const byte digitCodes[] = {
    0b11000000, 
    0b11111001, 
    0b10100100,
    0b10110000, 
    0b10011001, 
    0b10010010, 
    0b10000010, 
    0b11111000, 
    0b10000000, 
    0b10010000  
  };

  byte segmentPattern = digitCodes[digit];
  if (decimal) {
    segmentPattern &= 0b01111111; 
  }

  if (position < 8) {
    sr3.set(position, segmentPattern);
  } else {
    sr4.set(position - 8, segmentPattern);
  }
}

void setup() {
  Serial.begin(115200);
  sr3.setAllLow();
  sr4.setAllLow();
}

void loop() {
  if (Serial.available() >= 1) {
    char command = Serial.read();
    switch (command) {
      case 'd':
        displayDigit(0, 1, false);
        displayDigit(3, 2, false);
        displayDigit(0, 3, false);
        displayDigit(1, 9, false);
        displayDigit(4, 10, false);
        displayDigit(0, 11, false);
        break;  

      case 'f':
        displayDigit(0, 1, false);
        displayDigit(3, 2, false);
        displayDigit(0, 3, false);
        displayDigit(1, 9, false);
        displayDigit(4, 10, false);
        displayDigit(0, 11, false);
        break;  

      case 'I':
        displayDigit(1, 0, false);
        displayDigit(0, 2, false);
        displayDigit(5, 4, false);
        break;  

      default:
        Serial.println("Comando desconhecido");
        break;
    }
  }
}