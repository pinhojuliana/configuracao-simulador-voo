// Arduino 1
#include <SPI.h>

// Definições de pinos
const int latchPin = 10;  // Pino de travamento (latch)
const int clockPin = 13;  // Pino de clock
const int dataPin = 11;   // Pino de dados

// Total de displays
const int numDisplays = 8;

// Comandos para comunicação
char commands[numDisplays] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
int displayValues[numDisplays][5];  // Valores para os displays

void setup() {
  // Configurar pinos
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(115200);
  Serial.println("Iniciando Arduino 1...");
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
  
  for (int digit = 0; digit < 5; digit++) {
    int value = displayValues[displayIndex][digit];
    shiftOut(dataPin, clockPin, MSBFIRST, value);  // Envia os valores para o 74HC595

    // Configura o ponto decimal no terceiro dígito
    if (digit == 2) {
      shiftOut(dataPin, clockPin, MSBFIRST, 0b10000000);  // Ponto decimal ativado
    } else {
      shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000);  // Sem ponto decimal
    }
  }
  
  digitalWrite(latchPin, HIGH);
}
