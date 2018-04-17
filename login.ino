// Define Login Mechanism

void login(){
  // HTTP Mechanism
  String result = http("http://api.teleclawapi.live/api/users/loginAdmin","json",loginParams());
  Serial.println(result);
  if(result != "error"){
    // Response Handling
    StaticJsonBuffer<300> JSONBuffer;                        
    JsonObject& parsed = JSONBuffer.parseObject(result);
    if (!parsed.success()) {   //Check for errors in parsing
      Serial.println("Parsing failed");
      return;
    }
    String param1 = parsed["response"]["id"];
    String param2 = parsed["response"]["userId"];
    userToken = param1;
    userId = param2;
    JSONBuffer.clear();
  }
}

String loginParams(){
  const size_t capacity = JSON_OBJECT_SIZE(3) + 60;
  DynamicJsonBuffer JSONbuffer(capacity);
  JsonObject& JSONencoder = JSONbuffer.createObject(); 
  
  JSONencoder["username"] = apiUsername;
  JSONencoder["password"] = apiPassword; 
  
  String jsonStr;
  JSONencoder.printTo(jsonStr);
  JSONbuffer.clear();
  return jsonStr;
}
