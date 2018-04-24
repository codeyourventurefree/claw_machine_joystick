// Define Variables
boolean engaged = false;

// Define Mechanism when receiving input from joystick
void switchState(int buttonState){
  if(buttonState == LOW){
    if(engaged == false){
      engageGame();
      initClaw();
    }
  }
}

void catchGift(int button1State){
  if(button1State == HIGH){
    // Serial.println(catchParams());
    String gizwitsUrl = "https://api.gizwits.com/app/control/";
    gizwitsUrl += did;
    String result = http(gizwitsUrl,"gizwits",catchParams()); 
    Serial.println(result);
  }
}

String catchParams(){
  const size_t capacity = JSON_OBJECT_SIZE(2) + 60;
  DynamicJsonBuffer JSONbuffer(capacity);
  JsonObject& JSONencoder = JSONbuffer.createObject();
  
  JsonObject& attrs = JSONencoder.createNestedObject("attrs");
  attrs["CatchGift"] = 1;
  
  String jsonStr;
  JSONencoder.printTo(jsonStr);
  JSONbuffer.clear();
  return jsonStr;
}

void joyStickControl(int xVal,int yVal){
  xVal = map(xVal, 0, 4095, 0, 5);
  yVal = map(yVal, 0, 4095, 0, 5);
  // Serial.println(xVal);
  // Serial.println(yVal);
  String gizwitsUrl = "https://api.gizwits.com/app/control/";
  gizwitsUrl += did;
  if(xVal == 5){
    // Serial.println("Move Right");
    http(gizwitsUrl,"gizwits",controlParams("MoveUp",1)); 
    http(gizwitsUrl,"gizwits",controlParams("MoveUp",0));
  }    
  if(xVal == 0){
    // Serial.println("Move Left");
    http(gizwitsUrl,"gizwits",controlParams("MoveDown",1)); 
    http(gizwitsUrl,"gizwits",controlParams("MoveDown",0));
  }
  if(yVal == 5){
    // Serial.println("Move Right");
    http(gizwitsUrl,"gizwits",controlParams("MoveRight",1)); 
    http(gizwitsUrl,"gizwits",controlParams("MoveRight",0));
  }    
  if(yVal == 0){
    // Serial.println("Move Left");
    http(gizwitsUrl,"gizwits",controlParams("MoveLeft",1)); 
    http(gizwitsUrl,"gizwits",controlParams("MoveLeft",0));
  }    
}

String controlParams(String action,int actionVal){
  const size_t capacity = JSON_OBJECT_SIZE(2) + 60;
  DynamicJsonBuffer JSONbuffer(capacity);
  JsonObject& JSONencoder = JSONbuffer.createObject();
  
  JsonObject& attrs = JSONencoder.createNestedObject("attrs");
  attrs[action] = actionVal;
  
  String jsonStr;
  JSONencoder.printTo(jsonStr);
  JSONbuffer.clear();
  return jsonStr;
}

void engageGame(){
  engaged = true;
  String url = "http://api.teleclawapi.live/api/machines/66b3324a-6c27-4289-a91d-f9215c3dea65/gamePlay?access_token=";
  url += userToken;
  // Serial.println(url);
  // Serial.println(gameParams());
  String result = http(url,"json",gameParams());
  Serial.println(result);
  if(result != "error"){
    // Response Handling
    DynamicJsonBuffer JSONBuffer;
    JsonObject& parsed = JSONBuffer.parseObject(result);
    if (!parsed.success()) {   //Check for errors in parsing
      Serial.println("Parsing failed");
      engaged = false;  
      return;
    }
    String param1 = parsed["result"]["gizwits"]["init"]["appid"];;
    String param2 = parsed["result"]["gizwits"]["control"]["did"];
    String param3 = parsed["result"]["gizwits"]["init"]["token"];
    appId = param1;
    did = param2;
    token = param3;
    JSONBuffer.clear();
  } else {
    engaged = false;  
  }
}

String gameParams(){
  const size_t capacity = JSON_OBJECT_SIZE(2) + 60;
  DynamicJsonBuffer JSONbuffer(capacity);
  JsonObject& JSONencoder = JSONbuffer.createObject();
  
  JsonObject& data = JSONencoder.createNestedObject("data");
  data["productId"] = "34e4e4b2-dd5b-450f-b43f-38c15dca4671";
  data["userId"] = userId;
  
  String jsonStr;
  JSONencoder.printTo(jsonStr);
  JSONbuffer.clear();
  return jsonStr;
}

void initClaw(){
  String gizwitsUrl = "https://api.gizwits.com/app/control/";
  gizwitsUrl += did;
  String result = http(gizwitsUrl,"gizwits",initClawParams());
  engaged = false;
}

String initClawParams(){
  const size_t capacity = JSON_OBJECT_SIZE(2) + 60;
  DynamicJsonBuffer JSONbuffer(capacity);
  JsonObject& JSONencoder = JSONbuffer.createObject();
  
  JsonObject& attrs = JSONencoder.createNestedObject("attrs");
  attrs["InitCatcher"] = "1e1a0e080404040407000001";
  
  String jsonStr;
  JSONencoder.printTo(jsonStr);
  JSONbuffer.clear();
  return jsonStr;
            
}

