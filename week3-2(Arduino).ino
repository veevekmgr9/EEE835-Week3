int myLed = 6;  //initiate variable myLed and assign it to pin 6 
int input = 0;  //initial variable input set to 0 which is to store incoming serial data 

void setup() {  
    pinMode(myLed,OUTPUT); //set pin 6 as an Output pin 
    Serial.begin(115200); //start serial communication 
    Serial1.begin(115200); //start serial1 communication
    while(!Serial); //wait until serial monitor to get ready 
    Serial.println("Serial is ready!"); //print a message 
}  

void loop() {  
    //Check the available data from serial1 monitor 
    if(Serial1.available() > 0){  
        input = Serial1.read(); // Read the incoming data and set it to input variable 
        //Check whether the input is letters or any others 
        if(input >= 'a' && input <= 'z' || input >= 'A' && input <= 'Z'){ 
            Serial.println("Letter Pressed "); // message to show it is letter 
            digitalWrite(myLed,HIGH); // Turn ON LED  
        } else{  
            Serial.println("Number Pressed ");  //message 
            digitalWrite(myLed,LOW); // Turn OFF LED
        }  
        Serial.flush(); // Flush the serial 
    }  
    delay(5); // Wait for 5 ms 

}  