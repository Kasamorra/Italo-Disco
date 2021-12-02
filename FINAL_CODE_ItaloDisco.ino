//ITALO DISCO
//RGB-LED with joystick colour control
//joystick mixes two colors (Red-Green, Green-Blue, or Blue-Red)
//pressing the joystick up/down increases/decreases first color
//pressing the joystick right/left increases/decreases second color
//clicking the joystick switches which colors get mixed
//Pins Joystick: A0, A3, 2
//Pins LED: 6, 9, 11

//Joystick
const int xPin = A0; //x-axis
const int yPin = A3; //y-axis
int xVal; //value on x-axis
int yVal; //value on y-axis
const int switchPin = 2; //joystick as pushbutton
int switchValOld = 1; //old state (0 = pressed, 1 = not pressed)
int switchValNew; //new state

//Colors
const int redPin = 6; 
const int bluePin = 9; 
const int greenPin = 11;
int xColPin = 9; //current LED on x-axis, default: blue
int yColPin = 11; //current LED on y-axis, default: green
int xCol = 0; //current shade of color on x-axis
int yCol = 0; //current shade of color on y-axis
const int shadeStep = 1; //steps by which shade is altered
const int xArr[] = {redPin, bluePin, greenPin}; //order of colors to be mapped to x-axis
const int yArr[] = {greenPin, redPin, bluePin}; //order of colors to be mapped to y-axis
const int cArr[] = {bluePin, greenPin, redPin}; //order of colors to be left out
int comboState = 1; //current color combination (1 - 2 - 3)
const int delayTime = 200;

void setup() {
  //Joystick
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH); //pull-up resistor switch

  //Colors
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

}

void loop() {
  
  //Reading the joystick value
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  switchValNew = digitalRead(switchPin);

  //switching color combo
  if(switchValOld == 0 && switchValNew == 1)
  { //checks if button was pressed -> switches combo when not pressed anymore
    comboState = (comboState + 1) % 3;
  }
  switchValOld = switchValNew;

  //assigning colors according to the current color combo
  xColPin = xArr[comboState];
  yColPin = yArr[comboState];
  
  //increasing color on x-axis
  if(xVal > 600)
  {
    xCol = xCol + shadeStep;
    
    if(xCol > 248)
    {
      xCol = 255;
    }
  }

  //decreasing color on x-axis
  if(xVal < 400)
  {
    xCol = xCol - shadeStep;
    if(xCol < 3)
    {
      xCol = 0;
    }
  }


  //increasing color on y-axis
  if(yVal < 400)
  {
    yCol = yCol + shadeStep;
    if(yCol > 245)
    {
      yCol = 255;
    }
  }

  //decreasing color on y-axis
  if(yVal > 600)
  {
    yCol = yCol - shadeStep;
    if(yCol < 3)
    {
      yCol = 0;
    }
  }

  //Turning LEDs on/off, accordingly
  analogWrite(xColPin, xCol);
  analogWrite(yColPin, yCol);
  digitalWrite(cArr[comboState], LOW); //turns off third color

  delay(delayTime);
}
