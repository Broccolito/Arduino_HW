/**************
Wanjun Gu
MAE 170 
Arduino HW2
OCT 21th 2018
***************/

//Constant Variables
const int buttonpin_1 = 3; //This button is for addition
const int buttonpin_2 = 4; //This button is for substraction

//Variables that will change
int buttonstate_1 = 0; //variable for reading the pushbutton status
int buttonstate_2 = 0; //variable for reading the pushbutton status
int count = 0;
boolean again = false; //Detect repetition of clicking

void setup() {
  
  Serial.begin(9600);

  while (!Serial) {
    ; // Proceed the program only if Arduino is connected
  }
  
  pinMode(buttonpin_1, INPUT);
  pinMode(buttonpin_2, INPUT);
  
}

void loop() {
  
  buttonstate_1 = digitalRead(buttonpin_1);
  buttonstate_2 = digitalRead(buttonpin_2);
  
  if(buttonstate_1 == HIGH){
    Serial.println("Button 1 is pressed");
    if(again){
      count = count + 1;
    }
    again = false;
  }else if(buttonstate_2 == HIGH){
    Serial.println("Button 2 is pressed");
    if(again){
    count = count - 1;
    }
    again = false;
  }else{
    Serial.print("The current count is ");
    Serial.println(count);
    again = true;
  }

}
