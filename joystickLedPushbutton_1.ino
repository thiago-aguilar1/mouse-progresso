/* 
 *  
 *  19 jun 2024
 */

#include <Mouse.h>


/* Do joystick   */
int horzPin = A1;       /* Analog output of horizontal joystick pin   */
int vertPin = A0;       /*  Analog output of vertical joystick pin  */
int selPin = 9;         /*  select button pin of joystick   */

int vertZero, horzZero;        /* Stores the initial value of each axis, usually around 512  */
int vertValue, horzValue;         /* Stores current analog output of each axis  */
const int sensitivity = 300;       /* Higher sensitivity value = slower mouse, should be <= about 500 */
int mouseClickFlag = 0;


/* Do botão e led   */
int pushButton = 20;    /*  o botão serve para ativar ou desativar o joystick    */
int ledRed = 21;       /*  o led indica se o joystick está ativado ou não    */


bool estadoButton = false;   /*  para o botão controlar o led e o mouse    */


void setup()
{
//  Serial.begin(9600);
  pinMode(horzPin, INPUT);       /* Set both analog pins as inputs  */   
  pinMode(vertPin, INPUT);
  pinMode(selPin, INPUT);        /* set button select pin as input  */
  digitalWrite(selPin, HIGH);     /*   Pull button select pin high   */
  delay(1000);        /*  short delay to let outputs settle   */
  vertZero = analogRead(vertPin);      /* get the initial values  */
  horzZero = analogRead(horzPin);      /* Joystick should be in neutral position when reading these   */


  pinMode(pushButton, INPUT_PULLUP);
  pinMode(ledRed, OUTPUT);
  digitalWrite(ledRed, estadoButton);


  Mouse.end();
  
}



void loop()
{
  if (digitalRead(pushButton) == LOW) {  /* verifica se o botão foi apertado / acionado */
    estadoButton = !estadoButton;
    while (digitalRead(pushButton) == LOW){ }

    delay(600);
    
    if (estadoButton){
      digitalWrite(ledRed, estadoButton);
      Mouse.begin();   
    }
    else{
      digitalWrite(ledRed, estadoButton);
      Mouse.end();
    }
    
  }



  
  vertValue = analogRead(vertPin) - vertZero;     /*   read vertical offset  */ 
  horzValue = analogRead(horzPin) - horzZero;     /*  read horizontal offset   */

/*
  Serial.print("x ");
  Serial.println(horzValue);
  Serial.print("y ");
  Serial.println(vertValue);
 */
 
/* Mouse.move(xpos,ypos,wheel)
 * Mouse.move is always relative to the last position of the mouse cursor   
 */

  if (vertValue != 0)
    Mouse.move(0, vertValue/sensitivity, 0);       /*  move mouse on y axis  */
  if (horzValue != 0)
    Mouse.move((horzValue/sensitivity), 0, 0);     /*  move mouse on x axis   */

    
  if ((digitalRead(selPin) == 0) && (!mouseClickFlag))   /* if the joystick button is pressed  */
  {
    mouseClickFlag = 1;
    Mouse.press(MOUSE_LEFT);      /* click the left button down  */
  }
  else if ((digitalRead(selPin))&&(mouseClickFlag))     /* if the joystick button is not pressed  */
  {
    mouseClickFlag = 0;
    Mouse.release(MOUSE_LEFT);    /*  release the left button   */
  }

  
  
}
