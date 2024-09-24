 # 🛫 Simulador de Voo com Arduino usando Link2FS 🛬

Este projeto configura um **simulador de voo** utilizando **2 Arduinos** conectados ao programa **Link2FS**, que permite a comunicação entre os Arduinos e um simulador. A ideia é controlar diversos **displays de 7 segmentos** que mostram informações como frequências de rádio, código do transponder, altitude, velocidade e outras informações do **piloto automático**. 

## 📝 Documento que explica sore as configurações

[![GoogleDrive](https://img.shields.io/badge/-GoogleDrive-FFA500?style=for-the-badge&logo=GoogleDrive&logoColor=white)](https://drive.google.com/file/d/1BnJAFFcH8REipLK50jNiEcZ51p1NylsN/view?usp=sharing)

---

## 📋 Descrição do Projeto

O projeto foi dividido em duas partes, uma para cada Arduino, onde cada um controla uma parte dos displays:

- **Arduino 1**: Controla 8 displays, cada um com 5 dígitos e um ponto decimal no terceiro dígito. Estes displays mostram as frequências de rádio (Com, Nav).
- **Arduino 2**: Controla 6 displays restantes, com diferentes configurações:
  - 1 display com 5 dígitos.
  - 2 displays com 4 dígitos.
  - 2 displays com 3 dígitos (algumas posições desligadas).
  - 1 display com 3 dígitos, com apenas o primeiro, terceiro e quinto dígitos ligados.

Ambos os Arduinos se comunicam via **Serial.begin(115200)** e utilizam o método `shiftOut()` para enviar os dados serialmente para os **registradores de deslocamento 74HC595**, que controlam os segmentos dos displays.

---

## 🔌 Configuração dos Displays

Os **displays de 7 segmentos** são de cátodo comum e possuem 5 dígitos cada. Abaixo está a configuração de cada Arduino:

### 🖥️ Arduino 1

Controla 8 displays com 5 dígitos cada e um ponto decimal no **terceiro dígito**. Cada display recebe informações das frequências de rádio, conforme as seguintes opções de comunicação:

- `=A` **Com 1 frequency**
- `=B` **Com 1 s/b frequency**
- `=C` **Com 2 frequency**
- `=D` **Com 2 s/b frequency**
- `=E` **Nav 1 frequency**
- `=F` **Nav 1 s/b frequency**
- `=G` **Nav 2 frequency**
- `=H` **Nav 2 s/b frequency**

### 🖥️ Arduino 2

Controla os 6 displays restantes com diferentes configurações:

- 1 display com 5 dígitos, exibindo:
  - `=b` **AP altitude set**

- 2 displays com 4 dígitos, exibindo:
  - `=c` **AP vertical speed set**
  - `=J` **Transponder code**

- 2 displays com 3 dígitos (ligados a partir do segundo dígito, deixando o primeiro e último desligados), exibindo:
  - `=d` **AP heading set**
  - `=f` **AP speed set (knots)**

- 1 display com 3 dígitos (apenas o primeiro, terceiro e quinto dígitos ligados), exibindo:
  - `=I` **ADF1 frequency**

---

## 🔧 Tecnologias Utilizadas

- **Arduino** para controle de hardware.
- **Registradores de deslocamento 74HC595** para controlar os displays de 7 segmentos.
- **Link2FS** para comunicação com o simulador de voo.
- **Serial.begin(115200)** para comunicação entre o simulador e os Arduinos.
- **C/C++** para programar o Arduino, usando `Serial.println` para impressão das informações recebidas.

---

## 🖥️ Códigos de Comunicação do Simulador

Os códigos usados para comunicação com o simulador e os displays são os seguintes:

### Nav/Com Radios
- `=A` Com 1 frequency
- `=B` Com 1 s/b frequency
- `=C` Com 2 frequency
- `=D` Com 2 s/b frequency
- `=E` Nav 1 frequency
- `=F` Nav 1 s/b frequency
- `=G` Nav 2 frequency
- `=H` Nav 2 s/b frequency
- `=I` ADF1 frequency
- `=J` Transponder code

### Autopilot
- `=b` AP altitude set
- `=c` AP vertical speed set
- `=d` AP heading set
- `=f` AP speed set (knots)

---

## 🚀 Observações 
- Esses 2 códigos foram escritos por Inteligência Artificial com base nos comandos que fui dando
- Ainda não testei o funcionamento no simulador
---

## 🤝 Contribuições

Se você encontrar algum **erro** no código ou tiver sugestões de **melhoria**, por favor, abra uma **issue** ou faça um **pull request**. Sua ajuda é muito bem-vinda!
