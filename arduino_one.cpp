#include <SPI.h>
#include <ShiftRegister74HC595.h>

ShiftRegister74HC595<8> sr1(2, 3, 4); 
ShiftRegister74HC595<8> sr2(5, 6, 7); 

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
    sr1.set(position, segmentPattern);
  } else {
    sr2.set(position - 8, segmentPattern);
  }
}

void setup() {
  Serial.begin(115200);
  sr1.setAllLow();
  sr2.setAllLow();
}

void loop() {
  if (Serial.available() >= 1) {
    char command = Serial.read();
    switch (command) {
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
        for (int i = 0; i < 8; i++) {
          displayDigit(1, i * 5 + 0, false);
          displayDigit(2, i * 5 + 1, false);
          displayDigit(3, i * 5 + 2, true);  
          displayDigit(4, i * 5 + 3, false);
          displayDigit(5, i * 5 + 4, false);
        }
        break;
        
      case 'b':
        displayDigit(1, 0, false);
        displayDigit(2, 1, false);
        displayDigit(3, 2, false);
        displayDigit(4, 3, false);
        displayDigit(5, 4, false);
        break;

      case 'c':
      case 'J':
        displayDigit(1, 0, false);
        displayDigit(2, 1, false);
        displayDigit(3, 2, false);
        displayDigit(4, 3, false);
        break;

      case 'd':
      case 'f':
       sr1.set(0, 0xFF); 
        displayDigit(2, 1, false);
        displayDigit(3, 2, false);
        displayDigit(4, 3, false);
        sr1.set(4, 0xFF);
        break;

      case 'I':
        displayDigit(1, 0, false);
        sr1.set(1, 0xFF); 
        displayDigit(3, 2, false);
        sr1.set(3, 0xFF); 
        displayDigit(5, 4, false);
        break;

      default:
        Serial.println("Comando não reconhecido");
        break;
    }
  }
}