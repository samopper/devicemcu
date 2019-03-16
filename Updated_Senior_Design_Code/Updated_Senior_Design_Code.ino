/*------------------------------------------------------------
-----------------Fall Detector (Alert Device)-----------------
----------University of New Haven Senior Design 2019----------
----------Kevin Taisma, Samuel Opper, Anthony Gioino----------
------Professor Bijan Kirimi and Professor Mohsen Sarraf------
------------------------------------------------------------*/



#include <Adafruit_LSM9DS1.h>                                           //adafruit sensor library



#define speakerPin 8                                                    //buzzer to sound alert tone 
#define buttonPin 2                                                     //button to turn off alert tone


enum states {STEADY, FALL, ALERT};                                      //the different states the code will be in
states current_state = STEADY;                                          //start in the steady state
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();                              //create lsm sensor
SoftwareSerial Hc08(2, 3);                                              //create hc08 module

double x = 0;                                                              //initialize x component
double y = 0;                                                              //initialize y component
double z = 0;                                                              //initialize z component
double mag = 0;                                                            //initialize magnitude
double falltime = 0;

void setup()
{
  pinMode(speakerPin, OUTPUT);                                          //buzzer                      
  //attachInterrupt(digitalPinToInterrupt(buttonPin), reset, RISING);     //interrupt
  Serial.begin(9600);                                                   //initiate serial


  
  while (!Serial)                                                       //idk
  {
    delay(1);
  }


  
  if (!lsm.begin())                                                     //idk
  {
    while (1);
  }
}

void loop()
{
   lsm.read();                                                       //read sensors 
      sensors_event_t a, m, g, temp;                                    //get values
      lsm.getEvent(&a, &m, &g, &temp);                                  //idk

      x = abs(a.acceleration.x);                                        //x component
      y = abs(a.acceleration.y);                                        //y component
      z = abs(a.acceleration.z);                                        //z component

      mag = sqrt((x*x)+(y*y)+(z*z));                                    //vector magnitude calculation
  switch(current_state)                                                 //different code for different states
  {
     
    case STEADY:
      
      //Serial.println(mag);                                                                  //should normally be 9.81

                                                
      if(mag < 4)                                                       //a value less than 9.81 indicates falling
      {
        current_state = FALL;
        Serial.println("FALLING");                                      //change to fall state
        falltime = millis();
      }
      break;


   
   case FALL:
      /*
      Sound buzzer for 10 seconds
      If buzzer finishes sounding for 10 seconds, state = ALERT
      If interrupt pin detects rising edge, state = STEADY 
      */
      
      
      if(mag < 4)                                                       //a value less than 9.81 indicates falling
      { 
            
      //Serial.println(mag);     
      }
      else
      {
        falltime = millis() - falltime;
        //Serial.println(falltime);
        current_state = STEADY;
        if(falltime > 200)
        {
          current_state = ALERT;
        }
      }
      break;


   
   case ALERT:
      /*
      Use bluetooth to tell the phone a fall was detected
      Then return to the steady state
      */
      Serial.println("FALL DETECTED");
      Hc08.write(1);//send  1 (alert) to phone
      current_state = STEADY;
      
      break;
  }
}



void reset()                                                            //this function is called when the pin 2 detects a rising edge
{
  current_state = STEADY;                                               //bring the state back to steady
}



