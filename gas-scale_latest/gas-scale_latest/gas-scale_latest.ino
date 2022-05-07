

// Funnie Chawala May 2022
// Tested with      : HX711 
// Tested with MCU  : Arduino Nano
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
int Select1 = 12;
int Select2 = 8;
int counter = 0,state=0;
int Btn,Btn1,Btn2;

float elon,aku,value,fc;
float Nine = 1.1;// 12kg
float Ninenteen = 2.1;// 18kg
float Fortyeight = 3.1;// 48kg
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
  //scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
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
      // 
    lcd.setCursor (0,0);   // Go to home of first line
    lcd.print("SELECT GAS TANK"); 
    delay(2000);
    lcd.clear(); 
     
   // 9KG Switch
    digitalWrite(Select,HIGH);
    Btn = digitalRead(Select);
    
   // 19KG Switch  
    digitalWrite(Select2,HIGH);
    Btn1 = digitalRead(Select2);
    
   // 48KG Switch
    digitalWrite(Select1,HIGH);
    Btn2 = digitalRead(Select1);
 /* if(Btn == LOW){
    scale.tare();
    lcd.clear();
  }
  */
  // 9KG Gas Tank selection Start
   while(Btn == LOW){
   // scale.tare();
     //lcd.clear();
  
  //Gas Tank Selection End
  
  //scale start
  elon = scale.get_units(), 2;
  fc = elon-3.00; // Was 2.97kg
  
  Serial.print("Reading: ");
  Serial.print(elon); //scale.get_units() returns a float
  Serial.print(" kg"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  lcd.setCursor (0,0);   // Go to home of first line
  lcd.print("REMAINING GAS");    // 
  lcd.setCursor (0,1);   // Go to home of first line
  lcd.print(fc-Nine); //was elon
  lcd.setCursor (4,1);   // Go to home of first line
  lcd.print("KG"); 
  lcd.setCursor (10,0);   // Go to home of first line
  //lcd.print("F:"); 
 // lcd.setCursor (10,1);   // Go to home of first line
 // lcd.print(value);
  delay(10); 
  //scale end
   }

   // 19KG Gas Tank selection Start
   while(Btn1 == LOW){
   // scale.tare();
     //lcd.clear();
  
  //Gas Tank Selection End
  
  //scale start
  elon = scale.get_units(), 2;
  fc = elon-3.00; // Was 2.97kg
  
  Serial.print("Reading: ");
  Serial.print(elon); //scale.get_units() returns a float
  Serial.print(" kg"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  lcd.setCursor (0,0);   // Go to home of first line
  lcd.print("REMAINING GAS");    // 
  lcd.setCursor (0,1);   // Go to home of first line
  lcd.print(fc-Ninenteen); //was elon
  lcd.setCursor (4,1);   // Go to home of first line
  lcd.print("KG"); 
  lcd.setCursor (10,0);   // Go to home of first line
  //lcd.print("F:"); 
 // lcd.setCursor (10,1);   // Go to home of first line
 // lcd.print(value);
  delay(10); 
  //scale end
   }

   // 48KG Gas Tank selection Start
   while(Btn2 == LOW){
   // scale.tare();
     //lcd.clear();
  
  //Gas Tank Selection End
  
  //scale start
  elon = scale.get_units(), 2;
  fc = elon-3.00; // Was 2.97kg
  
  Serial.print("Reading: ");
  Serial.print(elon); //scale.get_units() returns a float
  Serial.print(" kg"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  lcd.setCursor (0,0);   // Go to home of first line
  lcd.print("REMAINING GAS");    // 
  lcd.setCursor (0,1);   // Go to home of first line
  lcd.print(fc-Fortyeight); //was elon
  lcd.setCursor (4,1);   // Go to home of first line
  lcd.print("KG"); 
  lcd.setCursor (10,0);   // Go to home of first line
  //lcd.print("F:"); 
 // lcd.setCursor (10,1);   // Go to home of first line
 // lcd.print(value);
  delay(10); 
  //scale end
   }
}
