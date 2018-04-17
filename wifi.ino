// Wifi Setup Procedure

void wifi(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(blinkPin, LOW);    
    delay(1000);
    digitalWrite(blinkPin, HIGH);    
    delay(1000);
  }
  digitalWrite(blinkPin, HIGH);
}
