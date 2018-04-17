// Setup Pin Mode

void pinMode(int blinkPin,int switchPin,int xPin, int yPin,int button1Pin){
  pinMode(blinkPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(button1Pin, INPUT);
}
