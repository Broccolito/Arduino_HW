int time_needed = 0;

void setup() {
  Serial.begin(38400);
}

void loop() {
  time_needed = millis();
  Serial.println("1234567890123456789012345678");
  time_needed = millis() - time_needed;
  Serial.print("That took ");
  Serial.print(time_needed);
  Serial.println(" milliseconds to type. ");
}
