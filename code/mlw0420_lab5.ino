/*
 * Matthew Wilson
 * mlw0420@unt.edu
 * CSCE 3612.001
 * 4/28/2022
 * This is my submission for lab 5.
 */

#include "LIS3DHTR.h"
#include<Wire.h>
#include"TFT_eSPI.h"

LIS3DHTR<TwoWire> LIS;//accelerometer
TFT_eSPI tft;//lcd display

#define LCD_BACKLIGHT (72Ul)

const int pinA = WIO_KEY_A;
const int pinB = WIO_KEY_B;
const int pinBuzzer = WIO_BUZZER;
const int pinLED = LED_BUILTIN;

int x = 0, xp = 0;

unsigned int Aflag = 0, Bflag = 0;

unsigned long cMil = 0, pMil = 0, cSec = 0, pSec = 0, secInterval = 1000, sec = 40, minu = 58, hour = 23;

unsigned int pixelX = 20, pixelY = 100;

unsigned long cMilb = 0, pMilb = 0; 

void setup() {
  Serial.begin(9600);
  
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

    //start accelerometer
  LIS.begin(Wire1);

  //check if accelerometer started properly
  if(!LIS){
    Serial.println("ACCEL ERROR");
    while(1);
  }

  //set data rate and scale range of accelerometer
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
  LIS.setFullScaleRange(LIS3DHTR_RANGE_2G);

  //setup buzzer
  pinMode(pinBuzzer, OUTPUT);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_GREEN);
  tft.setTextSize(6);
  tft.setTextColor(TFT_BLACK); 
  tft.setCursor(pixelX, pixelY);

  digitalWrite(LCD_BACKLIGHT, HIGH);

  //set up interrupts
  attachInterrupt(digitalPinToInterrupt(pinA), PressA, RISING);
  attachInterrupt(digitalPinToInterrupt(pinB), PressB, RISING);
}

void loop(){ 
  cMil = millis();

  x = LIS.getAccelerationX()*10;

  if(cMil - pMil >= secInterval){
    digitalWrite(pinLED, HIGH);
    
    tft.setCursor(pixelX, pixelY);
    tft.fillScreen(TFT_GREEN);

    if(sec > 59){
      sec = 0;
      minu++;
    }

    if(minu > 59){
      minu = 0;
      hour++;
    }
    
    if(hour > 23){
      hour = 0;
    }
    
    if(hour < 10){
      tft.print('0');
      tft.print(hour);
      tft.print(':');
    }
  
    else{
      tft.print(hour);
      tft.print(':');
    }
    
    if(minu < 10){
      tft.print('0');
      tft.print(minu);
      tft.print(':');
    }
  
    else{
      tft.print(minu);
      tft.print(':');
    }

    if(sec < 10){
      tft.print('0');
      tft.print(sec);
    }
  
    else{
      tft.print(sec);
    }

    sec++;

    digitalWrite(pinLED, LOW);
    
    pMil = cMil;
  }
  
  if(Aflag == 1){
    Buzz();
    
    minu++;

    if(minu > 59){
      minu = 0;
      //hour++;
    }

    tft.setCursor(pixelX, pixelY);
    tft.fillScreen(TFT_GREEN);

    if(hour < 10){
      tft.print('0');
      tft.print(hour);
      tft.print(':');
    }
  
    else{
      tft.print(hour);
      tft.print(':');
    }
    
    if(minu < 10){
      tft.print('0');
      tft.print(minu);
      tft.print(':');
    }
  
    else{
      tft.print(minu);
      tft.print(':');
    }

    if(sec < 10){
      tft.print('0');
      tft.print(sec);
    }

    else{
      tft.print(sec);
    }
    
    Aflag = 0;
  }

  if(Bflag == 1){
    Buzz();
    
    hour++;

    if(hour > 23){
      hour = 0;
    }

    tft.setCursor(pixelX, pixelY);
    tft.fillScreen(TFT_GREEN);

    if(hour < 10){
      tft.print('0');
      tft.print(hour);
      tft.print(':');
    }
  
    else{
      tft.print(hour);
      tft.print(':');
    }
    
    if(minu < 10){
      tft.print('0');
      tft.print(minu);
      tft.print(':');
    }
  
    else{
      tft.print(minu);
      tft.print(':');
    }

    if(sec < 10){
      tft.print('0');
      tft.print(sec);
    }

    else{
      tft.print(sec);
    }
    
    Bflag = 0;
  } 

  cSec = sec;

  if(cSec - pSec >= 6){
    digitalWrite(LCD_BACKLIGHT, LOW);
    
    pSec = cSec;
    //xp = xc;
  }

  else if(x != xp){
    pSec = cSec;

    //digitalWrite(LCD_BACKLIGHT, HIGH);
  }

  else if(x >= 6){
    digitalWrite(LCD_BACKLIGHT, HIGH);
  }

  Serial.println(x);

  xp = x;
}

void PressA(){Aflag = 1;}

void PressB(){Bflag = 1;}

void Buzz(){
   pMilb = millis();

   analogWrite(pinBuzzer, 128);

   while(cMilb < pMilb + 300){
    cMilb = millis();
   }

   analogWrite(pinBuzzer, 0);
}
