
 /*Rotary Encoder Demo
  rot-encode-demo.ino
  Demonstrates operation of Rotary Encoder
  Displays results on Serial Monitor
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/
 
 // Rotary Encoder Inputs
 #define inputCLK 6 //D4
 #define inputDT 7 //D5
 
 float counter = 0.00; 
 float price = 0.00;
 int currentStateCLK;
 int previousStateCLK; 
 
 String encdir ="";
 
 void setup() { 
   
   // Set encoder pins as inputs  
   pinMode (inputCLK,INPUT);
   pinMode (inputDT,INPUT);
   
   // Setup Serial Monitor
   Serial.begin (9600);
   
   // Read the initial state of inputCLK
   // Assign to previousStateCLK variable
   previousStateCLK = digitalRead(inputCLK);
 
 } 
 
 void loop() { 
   price = counter/10;
  // Read the current state of inputCLK
   currentStateCLK = digitalRead(inputCLK);
    
   // If the previous and the current state of the inputCLK are different then a pulse has occured
   if (currentStateCLK != previousStateCLK){ 
       
     // If the inputDT state is different than the inputCLK state then 
     // the encoder is rotating counterclockwise
     if (digitalRead(inputDT) != currentStateCLK) {
      
       counter --;
       
       if(counter < 0){
        counter = 0;
       }
       
       encdir ="CCW";
       
     } else {
       // Encoder is rotating clockwise
       counter ++;
  
       encdir ="CW";
       
     }
     price = counter/10;
    
     Serial.print(" Price: ");
     Serial.println(price);
    
   } 
   // Update previousStateCLK with the current state
   previousStateCLK = currentStateCLK; 
 }
