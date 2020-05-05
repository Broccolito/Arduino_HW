const int pwm = 10;
const int analogpin0 = 0;
const int analogpin1 = 1;

boolean extra_credit = false;
int a0, a1;
float voltage0, voltage1, analogoutput;

void setup() {
  Serial.begin(9600);
  pinMode(pwm, OUTPUT);
}

void loop() {


  if(!extra_credit){
    /*This is the code if the homework were to be
    done without extra credit*/
    analogWrite(pwm, 75);
    a0 = analogRead(analogpin0);
    a1 = analogRead(analogpin1);
    Serial.print("A0 is reading ");
    Serial.print(a0);
    Serial.print(" and A1 is reading ");
    Serial.println(a1);

    if(a0 > a1){
     Serial.println("And A0 is greater than A1.");
    }

    if(a0 == a1){
     Serial.println("And A0 is equal to than A1.");
    }

    if(a0 < a1){
      Serial.println("And A0 is less than A1.");
    }
    
  }else{

    /*This is the code that contains the extra credit*/
    a0 = analogRead(analogpin0);
    a1 = analogRead(analogpin1);

    //Convert a0 and a1 to voltage
    voltage0 = a0 * (5.0 / 1023.0);
    voltage1 = a1 * (5.0 / 1023.0);

    analogoutput = (voltage1 / 5) * 100;
    analogWrite(pwm, analogoutput);
    
    //Compare a0 to a1 and commute using the Serial
    if(abs(voltage1 - voltage0) <= 0.05){

      Serial.println("The system matches up");

    }else{

      if(a1 > a0){ 
        Serial.println("A1 is running high"); 
      }else{
        Serial.println("A1 is running low");  
      }
      
    }

  }


}
