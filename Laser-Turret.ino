/*
This code is meant to control the motion of a laser pen that will be pointing on a vertical grid board.
The board has a grid drawn on it, with a horizontal range of [-12,12], and a vertical range of [-11,11].
The origin is a central single point (0,0), at the center of the [-12,12]x[-11,11] rectangle. This rectangular grid is made up of small squares of side 2cm each, so that each unit of horizontal or vertical distance on the grid is 2cm long.
There will be an error margin of 2cm on each point on the grid. So the laser pointer will be considered to be at the point where x = 1 iff x is in [0,1]. In the same manner the pointer will be defined to be at the point (2,5), iff x is in [1,2], and y is in [4,5]. Hence generally the laser is at the point P(a,b) iff (x,y) is in [a-1,a]x[b-1,b]
*/
# include<Servo.h>
#include<Math.h>//we include this because we will need sine, cosine, tangent, and square roots ie namely sin(x), cos(x), tan(x), sqrt(x), etc.
//# include<LiquidCrystal.h>//we shall not use this in this project because of lack of space
//first we create our two servo objects
Servo HServo,VServo;
int HServoPin = 2; //horizontal servo will be attached to pin 1
int VServoPin = 3; ; //vertical servo will be attached to pin 2

int buttonUp = 4; //up button will be attached to pin 3
int buttonDown = 5; //down  button will be attached to pin 4
int buttonLeft = 6;  //left  button will be attached to pin 5
int buttonRight = 7; //right button will be attached to pin 6
int functionButton = 8; //this button will reverse control between manual and automatic
char mode = “manual” // the are two modes of operation, manual, and machine. We will begin in //manual mode always
int manualLed = 9; //this led will be on only when the control is in manual mode.
int machineLed = 10; //this led will be on only when the control is in machine mode.
int xList[] = {1,2,4,6,8,10,-1,-5,-10}// list of x-coordinates to plot 
int yList[] = {1,2,4,6,8,10,-1,-5,-10}// list of y-coordinates to plot

double Xpos ; // x-coordinate of point on screen 
double Ypos; // y-coordinate of point on screen
double distance; // the distance from the screen to the laser source
int Vangle = 0;
int Hangle = 0;
char directions;
long clocks, time1, time2, duration;


void setup()
{
pinMode(machineLed, OUTPUT);
pinMode(manualLed, OUTPUT);
digitalWrite(manualLed, HIGH);// the manual led is ON, at the start of program because mode is manual
Serial.begin(9600);//start serial communication between my arduino circuit and my computer
delay(1000); /*this delay is just to ensure that there is enough time for serial communication to be established before we start running other parts of our code
*/
HServo.attach(HServo);
VServo.attach(VServoPin);
}
//This function will move the laser vertically depending on which direction is pressed
int verticalButton(string directions){
if directions == "UP"{ Vangle +=1;}
if directions == "DOWN"{Vangle -=1;}
if Vangle >= 180{Vangle = 180;}
if Vangle <= 0{Vangle = 0;}
VServo.write(Vangle)
return Vangle;
}
//This function will move the laser horizontally depending on which direction is pressed
int horizontalButton(string directions){
if (directions == "RIGHT"){ Hangle +=1;}
if (directions == "LEFT"){Hangle -=1;}
if (Hangle >= 180){Hangle = 180;}
if (Hangle <= 0){Hangle = 0;}
HServo.write(Hangle)
return Hangle;
}

//the automatic function will move the laser to predefined points on its own accord
void machine(){
Serial.println(“I see that you are now in machine mode”)
Serial.println(“For now the points you entered in your sketch will be used”);

}




void loop()
{
/*This function call lets the user decide at any point whether to switch between manual or automatic control of the laser pointer. Each time the switch is pressed, the control method will switch to the other method.
*/
if (digitalRead(functionButton) == HIGH && mode == “manual”){
mode = “machine”;
digitalWrite(manualLed, LOW);
digitalWrite(machineLed,HIGH);
machine();
}
if (digitalRead(functionButton) == HIGH && mode == “machine”){
mode = “manual”;
digitalWrite(machineLed,LOW);
digitalWrite(manualLed, HIGH);
}


//Call and pass and UP direction to the verticalButton() function
if (digitalRead(buttonUp) == HIGH && mode == “manual”){
directions = "UP";
verticalButton(directions);
}

//Call and pass and DOWN direction to the verticalButton() function
if (digitalRead(buttonDown) == HIGH && mode == “manual”){
directions = "DOWN";
verticalButton(directions);
}

//Call and pass and RIGHT direction to the horizontalButton() function
if (digitalRead(buttonRight) == HIGH && mode == “manual”){
directions = "RIGHT";
horizontalButton(directions);
}

//Call and pass and LEFT direction to the horizontalButton() function
if (digitalRead(buttonLeft) == HIGH && mode == “manual”){
directions = "LEFT";
horizontalButton(directions);
}




}
