 #include <LiquidCrystal.h> // includes the LiquidCrystal Library 

 #define inputA 2
 #define inputB 3
 
 #define stepPin 50
 #define dirPin 52
 
 int counter = 0; 
 int aState;
 int aLastState;  
 int lastCounter = 0;
 volatile int stepStack = 500; 
 int stepsToTake = 50;

LiquidCrystal lcd(8, 9, 13,10, 11, 12);

 void isr ()  {
  aState = digitalRead(inputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(inputB) != aState) { 
        stepStack += stepsToTake;
        counter ++;
     } else {
        stepStack -= stepsToTake;
        counter --;
     }
  
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
}

 void setup() { 
  
   lcd.begin(16,2);
   lcd.clear();
   lcd.print("Position: ");
   lcd.print(10);
   lcd.print("deg"); 
  lcd.setCursor(2, 1);
   lcd.print("last name"); // last name on second line
   lcd.setCursor(0,0);  // cursor to first position first line

   pinMode (inputA,INPUT);
   pinMode (inputB,INPUT);

   pinMode (stepPin,OUTPUT);
   pinMode (dirPin,OUTPUT);

   attachInterrupt (0,isr,FALLING); // interrupt 0 always connected to pin 2 on Arduino UNO

   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(inputA);   
 } 
 
 void loop() { 


     
  if(stepStack > 0) {
    while(stepStack > 0) {
      digitalWrite(dirPin,LOW);
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(500);
      stepStack--;
    } 
  } else if(stepStack < 0) {
    while(stepStack < 0) {
    
      digitalWrite(dirPin,HIGH);
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(500);
      stepStack++;
    }
  }
  //Serial.println(stepStack);
  
 }

