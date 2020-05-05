int time_needed = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  time_needed = millis();
  Serial.println("Hello World my name is Wanjun. ");
  time_needed = millis() - time_needed;
  Serial.print("That took ");
  Serial.print(time_needed);
  Serial.println(" milliseconds to type. ");
}
