/*
 *Include libraries to be imported 
 */

#include <Servo.h>
Servo myservo;  // create servo object to control a servo

#include <Keypad.h>
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {13, 12, 10, 8}; 
byte colPins[COLS] = {7, 6, 1, 5};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);  

//Ultrasonic
int echoPin = 3;
int trigPin = 4;
long duration, distance;

//Microservo
int servoPin = 9;
int v_servo = 0;

//Switch Control
int control = 2;
int v_control = 0;

//Interrupt
byte interruptPin = 2;
byte state = LOW;

//Get the switch status 
bool switch_status(){

  v_control = analogRead(control);
  if(v_control < 200){
    //The Switch is open
    return(false);  
  }else{
    //The Switch is closed
    return(true);  
  }
  
}

//Potential Meter
int PMPin = 11;
int v_PM = 0;
float voltage = 0;

//Convert the PM reading to voltage
float toVoltage(int PM_Value){
  
  return(PM_Value * (5.0 / 1023.0));
  
}

//Set Rotation
int theta = 0;

//Set Offset
int offset = 0; 

//Extra Credit
bool extra_credit = false;

//Get theta angle from distance
int gettheta(long Distance){

  return(Distance * 3);
  
}

//Use the Echo sensor to get distance
int getdistance(){

  //Clear the trig Pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance 
  distance = duration * 0.034/2;

  //*****************************
  //For test purpose:
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
  //*****************************

  //Return distance in CM
  return(distance);
  
}

//Control servo position based on angle and offset
void control_servo(int angle, int Offset){

  angle = angle - Offset * 3;
  if(angle < 0){
    angle = 0;  
  }
  myservo.write(angle);                  // sets the servo position according to the scaled value
  delay(15);
  
}

//ISR Function for interrupt
void interrupt1(){
  state = !state;
}

void setup() {
  Serial.begin(9600);

  //For the Echo sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //For interrupt
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt1, RISING);

  //For servo Motor
  myservo.attach(servoPin);

}

void loop() {

  //If the switch is pressed then the motor working state is changed
  digitalWrite(servoPin, state);
  
  //Get the offset value
  if(!extra_credit){
    offset = 0;  
  }else{
    char customKey = customKeypad.getKey(); //Get Keyboard Input
    offset = customKey;
  }

  //Get the distance
  distance = getdistance();
  //Serial.println(distance);

  //Get the theta angle
  theta = gettheta(distance);
  //Make sure maximum theta equals to 180 degrees
  if(theta > 180){
    theta = 180;  
  }

  //Rotate the servo motor
  control_servo(theta, offset);

}
