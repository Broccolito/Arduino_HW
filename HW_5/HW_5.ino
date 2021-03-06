//Variables for the LED lights
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int list[] = {led1, led2, led3, led4, led5};

//Variables for the Joystick
int joyPin1 = 2;
int joyPin2 = 3;
int X = 0; //Reading from joypin1
int Y = 0; //Reading from joypin2
int joybutton = 10; //Digital 10 for input
bool joystatus = false;                                                                                                                                                                                                                                        

//Variables for Photoresistor
//Photo resistor connected to analog 0 and 1
int ResistorPin1 = 4;
int ResistorPin2 = 5;
int photoresist1 = 0; //Values for the photoresistor
int photoresist2 = 0; //Values for the photoresistor
int lightSituation = 0;

//Variabe for Iteration
int i;

//Extra Credit Yes Please!
bool extra_credit = true;

//Turn all lights off except for one
void turn1On(int onLED, int LEDlist[]) {

  for(i = 0; i < sizeof(list) - 1; i++){

    if(i == onLED){
      digitalWrite(i, HIGH);  
    }else{
      digitalWrite(i, LOW);  
    }
    
  }
  
}

//Turn all LED lights off
void allOff(int LEDlist[]) {

  for(i = 0; i < sizeof(list) - 1; i++){

    digitalWrite(i, LOW);  
    
  }
  
}

//Turn all LED lights on
void allOn(int LEDlist[]) {

  for(i = 0; i < sizeof(list) - 1; i++){

    digitalWrite(i, HIGH);  
    
  }
  
}

//Calibrate your system so you record what the photoresistor
//values are when the LED’s are on the left and right
//This function is only accurate under the experiment setup
int getLightPosition(int leftPhotoresist, int rightPhotoresist){
  
  if( abs(leftPhotoresist - rightPhotoresist) <= 5 ){
    if(leftPhotoresist < 15){
      return(3);      
    }else{
      return(6);      
    }    
  }else{
    if((leftPhotoresist - rightPhotoresist) < 15){
      return(1);      
    }else if((leftPhotoresist - rightPhotoresist) < 35){      
      return(2);    
    }else if(-(leftPhotoresist - rightPhotoresist) < 15){      
      return(5);    
    }else if(-(leftPhotoresist - rightPhotoresist) < 35){     
      return(4);    
    }    
  }
  
}



void setup() {
  
  Serial.begin(9600);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(joybutton, INPUT);

}

void loop() {

  X = analogRead(joyPin1);
  Y = analogRead(joyPin2);
  photoresist1 = analogRead(ResistorPin1);
  photoresist2 = analogRead(ResistorPin2);
  joystatus = digitalRead(joybutton);
  if(joystatus == LOW){

    allOn(list);
    
  }else{

    //For test Purposes
    /*
     *Serial.println("The reading of No.1");
     *Serial.print(photoresist1);
     *Serial.println();
     *Serial.println("The reading of No.2");
     *Serial.print(photoresist2);
     *Serial.println();
     */
    
    //The readings from the X analog pin (X) should be used
    //to determine which light is blinking
    if(X == 0){
      turn1On(led1, list);  
    }else if(X < 400){
      turn1On(led2, list);
    }else if(X < 600){
      turn1On(led3, list);  
    }else if(X < 1022){
      turn1On(led4, list);  
    }else{
      turn1On(led5, list); //For some reason this LED never turns on
    }
  
    if(!extra_credit){
      Y = Y/3;
      delay(Y);
      allOff(list);
      delay(Y);
    }else{
      lightSituation = getLightPosition(photoresist1, photoresist2);
      Serial.print("The current light situation is:  ");
      Serial.println(lightSituation);
    }
  
    
  }
  

}
