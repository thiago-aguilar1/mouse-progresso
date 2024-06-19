/* com ajuda de https://guiarobotica.com/push-button-arduino/ 
 * 18 de jun de 2024
 * 
 */

int pushButton = 20;
int ledRed = 21;
bool estadoLed = false;

void setup() {
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(ledRed, OUTPUT);
  digitalWrite(ledRed, estadoLed);

}

void loop() {

  if (digitalRead(pushButton) == LOW) {
    estadoLed = !estadoLed;
    digitalWrite(ledRed, estadoLed);
    while (digitalRead(pushButton) == LOW) { }  //deboucing do acionamento do botão
    delay(300);  //deboucing do acionamento do botão
  }

}
