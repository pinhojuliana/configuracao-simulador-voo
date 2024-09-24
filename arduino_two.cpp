// Arduino 2
#include <SPI.h>

// Definições de pinos
const int latchPin = 10;  // Pino de travamento (latch)
const int clockPin = 13;  // Pino de clock
const int dataPin = 11;   // Pino de dados

// Total de displays
const int numDisplays = 6;

// Comandos para comunicação
char commands[numDisplays] = {'b', 'c', 'J', 'd', 'f', 'I'};
int displayValues[numDisplays][5];  // Valores para os displays

void setup() {
  // Configurar pinos
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(115200);
  Serial.println("Iniciando Arduino 2...");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    char command = input.charAt(0);

    // Processar entrada
    for (int i = 0; i < numDisplays; i++) {
      if (command == commands[i]) {
        // Extrair os valores dos dígitos da string recebida
        String valueStr = input.substring(1, 6);  // 5 dígitos
        for (int j = 0; j < 5; j++) {
          displayValues[i][j] = valueStr.charAt(j) - '0';
        }
        updateDisplay(i);
      }
    }
  }
}

// Função para atualizar o display
void updateDisplay(int displayIndex) {
  digitalWrite(latchPin, LOW);
  
  switch (displayIndex) {
    case 0:  // Display com 5 dígitos (comando 'b')
      for (int digit = 0; digit < 5; digit++) {
        shiftOut(dataPin, clockPin, MSBFIRST, displayValues[displayIndex][digit]);
      }
      break;

    case 1: case 2:  // Display com 4 dígitos (comando 'c' e 'J')
      for (int digit = 1; digit < 5; digit++) {
        shiftOut(dataPin, clockPin, MSBFIRST, displayValues[displayIndex][digit]);
      }
      break;

    case 3: case 4:  // Display com 3 dígitos (contando do segundo dígito)
      shiftOut(dataPin, clockPin, MSBFIRST, 0);  // Primeiro dígito desligado
      for (int digit = 1; digit < 4; digit++) {
        shiftOut(dataPin, clockPin, MSBFIRST, displayValues[displayIndex][digit]);
      }
      shiftOut(dataPin, clockPin, MSBFIRST, 0);  // Último dígito desligado
      break;

    case 5:  // Display com 3 dígitos, pulando o 2º e 4º dígitos
      shiftOut(dataPin, clockPin, MSBFIRST, displayValues[displayIndex][0]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0);  // 2º dígito desligado
      shiftOut(dataPin, clockPin, MSBFIRST, displayValues[displayIndex][2]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0);  // 4º dígito desligado
      shiftOut(dataPin, clockPin, MSBFIRST, displayValues[displayIndex][4]);
      break;
  }
  
  digitalWrite(latchPin, HIGH);
}
