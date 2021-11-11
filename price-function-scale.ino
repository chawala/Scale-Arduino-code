
// Olav Kallhovd sept2017
// Tested with      : HX711 asian module on channel A and YZC-133 3kg load cell
// Tested with MCU  : Arduino Nano, ESP8266
//-------------------------------------------------------------------------------------
// This is an example sketch on how to use this library
// Settling time (number of samples) and data filtering can be adjusted in the config.h file

#include <Wire.h> // For I2C
#include <LiquidCrystal_I2C.h> // Added library*
#include "HX711.h"

#define calibration_factor 25100.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  4
#define LOADCELL_SCK_PIN  5

HX711 scale;

LiquidCrystal_I2C lcd(0x27,16,2); // 0x27 is the default I2C bus address of the backpack-see article


const int eepromAdress = 0;
//**********display**********
int Select = 11; //8
int counter = 0,state=0,Btn;
float elon;
 //**********display***********

 // Rotary Encoder Inputs
 #define inputCLK 6 //D4
 #define inputDT 7 //D5
 
 float counter1 = 0.00; 
 float price = 0.00;
 int currentStateCLK;
 int previousStateCLK; 

void setup() {
  
    // Set encoder pins as inputs  
   pinMode (inputCLK,INPUT);
   pinMode (inputDT,INPUT);
   // Read the initial state of inputCLK
   // Assign to previousStateCLK variable
   previousStateCLK = digitalRead(inputCLK);
   pinMode(Select,INPUT_PULLUP);
  //****scale-setup*****
  Serial.println("HX711 scale demo");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  Serial.println("Readings:");
  //****setup-end********
   
 // Setup Serial Monitor
   Serial.begin (9600);
  
 //*****display*********

  // Set off LCD module
  lcd.init();
  lcd.init();
  lcd.backlight();
  //******************display************
}

void loop() {
  
  //previousStateCLK = currentStateCLK;  
  //rotary
    price = counter1/20;
  // Read the current state of inputCLK
   currentStateCLK = digitalRead(inputCLK);
    
   // If the previous and the current state of the inputCLK are different then a pulse has occured
   if (currentStateCLK != previousStateCLK){ 
       
     // If the inputDT state is different than the inputCLK state then 
     // the encoder is rotating counterclockwise
     if (digitalRead(inputDT) != currentStateCLK) {
      
       counter1 --;
       
       if(counter1 < 0){
        counter1 = 0;
       }
       
       //encdir ="CCW";
       
     } else {
       // Encoder is rotating clockwise
       counter1 ++;
  
       //encdir ="CW";
       
     }
    
     Serial.print(" Price: ");
     Serial.println(price);
     //lcd.clear();
     lcd.setCursor (10,0);   // Go to home of first line
     lcd.print("Price:"); 
     //lcd.setCursor (10,1);   // Go to home of first line
     //
     lcd.print(price); 
   }
   // Update previousStateCLK with the current state
     previousStateCLK = currentStateCLK;  
  //End rotary 
   Btn = digitalRead(Select);
  if(Btn == LOW){
    scale.tare();
    lcd.clear();
  }
  //scale start
  elon = scale.get_units(), 2;
  Serial.print("Reading: ");
  Serial.print(elon); //scale.get_units() returns a float
  Serial.print(" kg"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  lcd.setCursor (0,0);   // Go to home of first line
  lcd.print("WEIGHT:");    // 
  lcd.setCursor (0,1);   // Go to home of first line
  lcd.print(elon); 
  lcd.setCursor (4,1);   // Go to home of first line
  lcd.print("KG"); 
 // lcd.setCursor (10,0);   // Go to home of first line
  //lcd.print("Price:"); 
  lcd.setCursor (10,1);   // Go to home of first line
  lcd.print(price*elon);
  delay(10); 
  //scale end
 
}
