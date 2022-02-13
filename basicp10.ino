#include <SPI.h>       
#include <DMD.h>    
#include <TimerOne.h>  
#include "Arial_black_16.h"
#include "Arial_Black_16_ISO_8859_1.h"
#include "Arial14.h"
//#include "SystemFont5x7.h

#define DISPLAYS_ACROSS 1 //-> Number of P10 panels used, side to side.
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

char *Text = "";
void ScanDMD() { 
  dmd.scanDisplayBySPI();
}

void setup(void) {
  //led panel components
  Timer1.initialize(1000);          
  Timer1.attachInterrupt(ScanDMD);   
  dmd.clearScreen(true);   
  Serial.begin(115200); 

}

void loop(void) {
  //dmd.selectFont(Arial_Black_16_ISO_8859_1);
  //dmd.selectFont(Arial_Black_16);
  dmd.selectFont(Arial_14);
  //dmd.selectFont(SystemFont5x7);
 
  Text = "2022";

//********************** afficher du text ***************
  //  dmd.drawBox(0, 0, 31, 15, GRAPHICS_NORMAL);
  // dmd.drawString(2, 1, Text,strlen(Text), GRAPHICS_NORMAL);


// //****************************   clignoter  ***********************
  // dmd.drawBox(0, 0, 31, 15, GRAPHICS_NORMAL);
  // dmd.drawString(2, 1, Text,strlen(Text),GRAPHICS_NORMAL );
  // delay(2000);
  // dmd.clearScreen(true);
  // delay(1000);
  

//**************** défiler *******************
  dmd.drawMarquee(Text, strlen(Text), 0, 2);
  long start=millis();
  long timer=start;
  boolean ret=false;
  int interval=100;
  while(!ret){
    if ((timer+interval) < millis()) {
      ret=dmd.stepMarquee(1,0);
      timer=millis();
      Serial.println(ret);
    }
  }

}
