//The resistor used to connect with Thermistor is 10K Ohm

//blue (L1), green(L2), yellow(L3) and red (L4) LED are attached to digital pins 3,5,7,9
int bluepin = 3;
int greenpin = 5;
int yellowpin = 7;
int redpin = 9;

int pinread = 2; //Read Analog Pin
int units = 0; //The output from the analog reader

int resistor = 10000; //The resistance of the resistor in parallel with the thermistor
float therm_resistance = 0; // The resistance of the thermistor
float volt = 0; //Voltage from the analog pin
int time_wait = 0;
float temperature = 25;

//Extra Credit Yes Please
boolean extra_credit = true;

float unitsToVoltage(int units) {
  /*unitsToVoltage(units):Parameter list = units[int],
  return type = [float], This should take a number “units” 
  and convert it to a voltage using the formula 
  voltage=units*5/1023 then return the voltage.*/
  float voltage;
  voltage = units * 5 / 1023;
  return(voltage);
}

int voltageToMilliseconds(float volts) {
  /*voltageToMilliseconds(volts):Parameter list = volts[float],
  return type = [int], This should take a number “volts” 
  and convert it to a time in milliseconds using the formula 
  wait= 200/volts and return that value.*/
  int wait;
  wait = 200/volts;
  return(wait);
}

//Extra credit function
float linearInterpolation(float x1, float y1, float x2, float y2, float x){
  float y;
  y = y1 - ((y2 - y1)/(x2 - x1)) * x1 + ((y2 - y1)/(x2 - x1)) * x;
  return(y);
}

float voltageToTemperature(float volts) {
  //x input in linearInterpolation should be volts
  //Thermistor Numeber: MF52A103G4050E
  //Temp: 20 Resistance: 12610.20824 Ohm
  //Temo: 40 Resistance: 5213.639596 Ohm
  float temp;
  therm_resistance = (volts/(5 - volts)) * resistor; //Convert volt to resistance
  temp = linearInterpolation(12610.20824, 20, 5213.639596, 40, therm_resistance);
  return(temp);
}

//Turn the L1 on for wait milliseconds and off for wait milliseconds.
void blink1(int wait) {
  digitalWrite(bluepin, HIGH);
  delay(wait);
  digitalWrite(bluepin, LOW);
  delay(wait);
}

//Turn L1 and L2 on for wait milliseconds and off for wait milliseconds.
void blink2(int wait) {
  digitalWrite(bluepin, HIGH);
  digitalWrite(greenpin, HIGH);
  delay(wait);
  digitalWrite(bluepin, LOW);
  digitalWrite(greenpin, LOW);
  delay(wait);
}

//Turn L1, L2 and L3 on for wait milliseconds and off for wait milliseconds.
void blink3(int wait) {
  digitalWrite(bluepin, HIGH);
  digitalWrite(greenpin, HIGH);
  digitalWrite(yellowpin, HIGH);
  delay(wait);
  digitalWrite(bluepin, LOW);
  digitalWrite(greenpin, LOW);
  digitalWrite(yellowpin, LOW);
  delay(wait);
}

//Turn L1, L2, L3 and L4 on for wait milliseconds and off for wait milliseconds.
void blink4(int wait) {
  digitalWrite(bluepin, HIGH);
  digitalWrite(greenpin, HIGH);
  digitalWrite(yellowpin, HIGH);
  digitalWrite(redpin, HIGH);
  delay(wait);
  digitalWrite(bluepin, LOW);
  digitalWrite(greenpin, LOW);
  digitalWrite(yellowpin, LOW);
  digitalWrite(redpin, LOW);
  delay(wait);
}



void setup() {
  Serial.begin(9600);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(yellowpin, OUTPUT);
  pinMode(redpin, OUTPUT);
}


void loop() {

  units = analogRead(pinread);
  volt = unitsToVoltage(units);
  
  if(!extra_credit){
    
    time_wait = voltageToMilliseconds(volt);
    if(time_wait > 801){
      blink1(time_wait);  
    }else if(time_wait > 601){
      blink2(time_wait);
    }else if(time_wait > 401){
      blink3(time_wait);  
    }else{
      blink4(time_wait);  
    }
    
  }else{

    temperature = voltageToTemperature(volt);
    //20 1000ms wait and 40 1ms wait
    time_wait = linearInterpolation(20, 1000, 40, 1, temperature);

    if(temperature < 25){
      blink1(time_wait);  
    }else if(temperature < 30){
      blink2(time_wait);
    }else if(temperature > 35){
      blink3(time_wait);  
    }else{
      blink4(time_wait);  
    }
    
  }
  
}
