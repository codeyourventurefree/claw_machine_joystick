// Define HTTP Request Mechanism
String http(String url, char* headerType, String params){
  // Define Response
  String response;
  
  HTTPClient http;
  http.begin(url);
  digitalWrite(blinkPin, LOW);

  // Headers Handling
  http.addHeader("Accept", "application/json"); 
  http.addHeader("Content-Type", "application/json");
  if(headerType == "gizwits" || headerType == "gizwitsMove"){
    http.addHeader("X-Gizwits-Application-Id", appId); 
    http.addHeader("X-Gizwits-User-token", token);
  }
  
  // HTTP Mechanism
  int httpResponseCode = http.POST(params);
  
  // Denug Message
  Serial.println(httpResponseCode);  
  
  if(httpResponseCode == 200){
    response = http.getString();
  } else {
    response = "error";
  }
  http.end();
  digitalWrite(blinkPin, HIGH);
  return response;
}
