#include <Keyboard.h>

#define button_pin 2
#define dash_time 250
#define timeout 500
#define arraySize 28
#define KEY_BACKSPACE 0x08

String morseCode[arraySize][2] = {
  {"a",".-"},
  {"b","-..."},
  {"c","-.-."},
  {"d","-.."},
  {"e","."},
  {"f","..-."},
  {"g","--."},
  {"h","...."},
  {"i",".."},
  {"j",".---"},
  {"k","-.-"},
  {"l",".-.."},
  {"m","--"},
  {"n","-."},
  {"o","---"},
  {"p",".--."},
  {"q","--.-"},
  {"r",".-."},
  {"s","..."},
  {"t","-"},
  {"u","..-"},
  {"v","...-"},
  {"w",".--"},
  {"x","-..-"},
  {"y","-.--"},
  {"z","--.."}, 
  {" ","------"}, 
  {"",""}, 
};

void setup() {
  Keyboard.begin();
  Serial.begin(9600);
  pinMode(button_pin, INPUT_PULLUP);

}

void loop() {
  if (digitalRead(button_pin) == LOW) {
    String character = formChar(button_pin);
    //Serial.println(character);
    //Serial.println(correspondingChar(character));
    if (character.equals("......")) {
      Keyboard.press(KEY_BACKSPACE);
      Keyboard.releaseAll();
    }
    else {
      Keyboard.print(correspondingChar(character));
    }
    
  }
  //Serial.println(digitalRead(button_pin));
  //Keyboard.print(button(button_pin));
}

String correspondingChar(String code) {
  for (int i=0; i<arraySize; i++) {
    if (morseCode[i][1].equals(code)) {
      //Serial.println("match found");
      return morseCode[i][0];
    }
  }
  return "";
}

String formChar(int pin){
  String finalChar = "";
  // if button clicked
  if (digitalRead(pin) == LOW){
    // call button
    //Serial.println("initial press");
    String currentPress = button(pin);
    finalChar += currentPress;
    // mark time
    unsigned long currentTime = millis();
    // keep checking for button until timeout
    while (millis() - currentTime < timeout) {
      //Serial.println(millis() - currentTime);
      if (digitalRead(pin) == LOW){
        //Serial.println("additional press");
        currentPress = button(button_pin);
        finalChar += currentPress;
        currentTime = millis();
      }
    }
  }
  return finalChar;
}



String button(int pin) {
  unsigned long time = 0;
  
  // if button clicked
  if (digitalRead(pin) == LOW){
    //Serial.println("click instantiated");
    
    // mark time and hold until button held
    unsigned long currentTime = millis();
    while (digitalRead(pin) == LOW){
      //Serial.println("holding");
      //Serial.println(millis());
    }

    // mark time held
    time = millis() - currentTime;
    //Serial.println(time);
    if (time > 15 && time < dash_time) {
      return ".";
    }
    else if (time >= dash_time) {
      return "-";
    }
    else {
      return "";
    }
  }
  return "";
}
