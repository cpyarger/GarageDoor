/*
||  Simple Password Entry Using Matrix Keypad
||  4/5/2012 Updates Nathan Sobieck: Nathan@Sobisource.com
||
*/


//* is to validate password   
//# is to reset password attempt

/////////////////////////////////////////////////////////////////

#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip

Password password = Password( "0000" );

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8}; //connect to the column pinouts of the keypad
int DL=0;
long Timer;
long previousMillis = 0;
long interval = 1000*3;//60*5;  //1 sec, 1 min, 5 min    
// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
 pinMode(13, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(9,OUTPUT);
 
 digitalWrite(13, HIGH);
 digitalWrite(10, HIGH);

  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  keypad.getKey();
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
	Serial.print("Pressed: ");
	Serial.println(eKey);
	switch (eKey){
	  case '*': checkPassword(); break;
	  case '#': password.reset();doorLight(); break;
    //case '0': doorLight();break;
	  //case '*'&&'#': doorLight(); break;
	  default: password.append(eKey);
     }
  }
}

void wrong(){
digitalWrite(9,LOW);
digitalWrite(11, HIGH);
Serial.print("WrongFunction");
}
void right(){
digitalWrite(9,HIGH);
digitalWrite(11, LOW);
}
void indicatorOff(int del){
  delay(del);
  digitalWrite(9,LOW);
  digitalWrite(11,LOW);
}
void checkPassword(){
  if (password.evaluate()){
    Serial.println("Success");
   right();

    digitalWrite(13, HIGH);

    digitalWrite(10, LOW);
    delay(2000);
    if (DL!=0){
    digitalWrite(13, LOW);
    DL=1;
    }
    digitalWrite(10, HIGH);
    indicatorOff(0);
  }else{
    Serial.println("Wrong");
    //add code to run if it did not work
  wrong();
  password.reset();
  indicatorOff(500);
  }
}
void doorLight(){
if (DL!=1){
  digitalWrite(13,LOW);
  DL=1;
}
else{
  digitalWrite(13,HIGH);
  DL=0;
}

}
//  digitalWrite(13,HIGH);



