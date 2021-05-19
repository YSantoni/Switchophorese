//VULCAIN INNOVATION
//06/11/2020

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       
#include <TouchScreen.h>
#include "bitmaps.h"

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

uint8_t YP = A2;  // must be an analog pin
uint8_t XM = A3;  // must be an analog pin
uint8_t YM = 8;   // can be a digital pin
uint8_t XP = 9;   // can be a digital pin
uint8_t SwapXY = 0;

uint16_t TS_LEFT = 920;
uint16_t TS_RT  = 150;
uint16_t TS_TOP = 940;
uint16_t TS_BOT = 120;
char *name = "Unknown controller";

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 560 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 560);
TSPoint tp;

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define SWAP(a, b) {uint16_t tmp = a; a = b; b = tmp;}

int16_t BOXSIZE;
int16_t PENRADIUS = 3;
uint16_t identifier, oldcolor, currentcolor;
uint8_t Orientation = 1;    //Landscape

// Assign human-readable names to some common (and less common) 16-bit color values:
#define TEST 0xff9effde 
#define ALICEBLUE 0xF7DF
#define ANTIQUEWHITE 0xFF5A
#define AQUA 0x07FF
#define AQUAMARINE 0x7FFA
#define AZURE 0xF7FF
#define BEIGE 0xF7BB
#define BISQUE 0xFF38
#define BLACK 0x0000
#define BLANCHEDALMOND 0xFF59
#define BLUE 0x001F
#define BLUEVIOLET 0x895C
#define BROWN 0xA145
#define BURLYWOOD 0xDDD0
#define CADETBLUE 0x5CF4
#define CHARTREUSE 0x7FE0
#define CHOCOLATE 0xD343
#define CORAL 0xFBEA
#define CORNFLOWERBLUE 0x64BD
#define CORNSILK 0xFFDB
#define CRIMSON 0xD8A7
#define CYAN 0x07FF
#define DARKBLUE 0x0011
#define DARKCYAN 0x0451
#define DARKGOLDENROD 0xBC21
#define DARKGREY 0xAD55
#define DARKGREEN 0x0320
#define DARKKHAKI 0xBDAD
#define DARKMAGENTA 0x8811
#define DARKOLIVEGREEN 0x5345
#define DARKORANGE 0xFC60
#define DARKORCHID 0x9999
#define DARKRED 0x8800
#define DARKSALMON 0xECAF
#define DARKSEAGREEN 0x8DF1
#define DARKSLATEBLUE 0x49F1
#define DARKSLATEGREY 0x2A69
#define DARKTURQUOISE 0x067A
#define DARKVIOLET 0x901A
#define DEEPPINK 0xF8B2
#define DEEPSKYBLUE 0x05FF
#define DIMGREY 0x6B4D
#define DODGERBLUE 0x1C9F
#define FIREBRICK 0xB104
#define FLORALWHITE 0xFFDE
#define FORESTGREEN 0x2444
#define FUCHSIA 0xF81F
#define GAINSBORO 0xDEFB
#define GHOSTWHITE 0xFFDF
#define GOLD 0xFEA0
#define GOLDENROD 0xDD24
#define GREY 0x8410
#define GREEN 0x0400
#define GREENYELLOW 0xAFE5
#define HONEYDEW 0xF7FE
#define HOTPINK 0xFB56
#define INDIANRED 0xCAEB
#define INDIGO 0x4810
#define IVORY 0xFFFE
#define KHAKI 0xF731
#define LAVENDER 0xE73F
#define LAVENDERBLUSH 0xFF9E
#define LAWNGREEN 0x7FE0
#define LEMONCHIFFON 0xFFD9
#define LIGHTBLUE 0xAEDC
#define LIGHTCORAL 0xF410
#define LIGHTCYAN 0xE7FF
#define LIGHTGOLDENRODYELLOW 0xFFDA
#define LIGHTGREEN 0x9772
#define LIGHTGREY 0xD69A
#define LIGHTPINK 0xFDB8
#define LIGHTSALMON 0xFD0F
#define LIGHTSEAGREEN 0x2595
#define LIGHTSKYBLUE 0x867F
#define LIGHTSLATEGREY 0x7453
#define LIGHTSTEELBLUE 0xB63B
#define LIGHTYELLOW 0xFFFC
#define LIME 0x07E0
#define LIMEGREEN 0x3666
#define LINEN 0xFF9C
#define MAGENTA 0xF81F
#define MAROON 0x8000
#define MEDIUMAQUAMARINE 0x6675
#define MEDIUMBLUE 0x0019
#define MEDIUMORCHID 0xBABA
#define MEDIUMPURPLE 0x939B
#define MEDIUMSEAGREEN 0x3D8E
#define MEDIUMSLATEBLUE 0x7B5D
#define MEDIUMSPRINGGREEN 0x07D3
#define MEDIUMTURQUOISE 0x4E99
#define MEDIUMVIOLETRED 0xC0B0
#define MIDNIGHTBLUE 0x18CE
#define MINTCREAM 0xF7FF
#define MISTYROSE 0xFF3C
#define MOCCASIN 0xFF36
#define NAVAJOWHITE 0xFEF5
#define NAVY 0x0010
#define OLDLACE 0xFFBC
#define OLIVE 0x8400
#define OLIVEDRAB 0x6C64
#define ORANGE 0xFD20
#define ORANGERED 0xFA20
#define ORCHID 0xDB9A
#define PALEGOLDENROD 0xEF55
#define PALEGREEN 0x9FD3
#define PALETURQUOISE 0xAF7D
#define PALEVIOLETRED 0xDB92
#define PAPAYAWHIP 0xFF7A
#define PEACHPUFF 0xFED7
#define PERU 0xCC27
#define PINK 0xFE19
#define PLUM 0xDD1B
#define POWDERBLUE 0xB71C
#define PURPLE 0x8010
#define RED 0xF800
#define ROSYBROWN 0xBC71
#define ROYALBLUE 0x435C
#define SADDLEBROWN 0x8A22
#define SALMON 0xFC0E
#define SANDYBROWN 0xF52C
#define SEAGREEN 0x2C4A
#define SEASHELL 0xFFBD
#define SIENNA 0xA285
#define SILVER 0xC618
#define SKYBLUE 0x867D
#define SLATEBLUE 0x6AD9
#define SLATEGREY 0x7412
#define SNOW 0xFFDF
#define SPRINGGREEN 0x07EF
#define STEELBLUE 0x4416
#define TAN 0xD5B1
#define TEAL 0x0410
#define THISTLE 0xDDFB
#define TOMATO 0xFB08
#define TURQUOISE 0x471A
#define VIOLET 0xEC1D
#define WHEAT 0xF6F6
#define WHITE 0xFFFF
#define WHITESMOKE 0xF7BE
#define YELLOW 0xFFE0
#define YELLOWGREEN 0x9E66

//////////////////////////////////////////////////////////////////////////////////////////// Defining variables
int currentPage=0; // navigation


unsigned long initSec = 1; // initial timer
unsigned long initMin = 0;
unsigned long initHour = 0;

unsigned long runSec = 0;// run time
unsigned long runMin = 0;
unsigned long runHour = 0;

int fPulseSec = 0; //first pulse
int fPulseMilliSec = 0;

int lPulseSec = 0; // last pulse
int lPulseMilliSec = 0;

int ratio = 50; // Ratio pulse back

bool linear = true; //touch icons
bool expo = false;
bool ok = false;
bool back = false;
bool Start = false;
bool pause = true;


int Init = 0; // id of boxes on initscreen
int Pulse = 0;

//////////////////////////////////////////////////////////////////////////////////////////// Setup
void setup(void)
{
    uint16_t tmp;
    tft.begin(9600);

    tft.reset();
    identifier = tft.readID();
   
    if (0) {
   
    } else if (identifier == 0x9341) {
        name = "ILI9341 BLUE";
        TS_LEFT = 917; TS_RT = 125; TS_TOP = 126; TS_BOT = 950;
        SwapXY = 1;
       
    }
    else {
        name = "unknown";
    }
    switch (Orientation) {      // adjust for different aspects
        case 0:   break;        //no change,  calibrated for PORTRAIT
        case 1:   tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;  break;
        case 2:   SWAP(TS_LEFT, TS_RT);  SWAP(TS_TOP, TS_BOT); break;
        case 3:   tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;  break;
    }

    Serial.begin(9600);
    ts = TouchScreen(XP, YP, XM, YM, 300);     //call the constructor AGAIN with new values.
    tft.begin(identifier);    
    tft.setRotation(Orientation);
   // tft.fillScreen(BLACK);


}  
//////////////////////////////////////////////////////////////////////////////////////////// Loop   
void loop()
{
//=========================== welcome Screen ========================= //
  
  if (currentPage==0){

    welcome_screen();
     while(currentPage==0){
       tp = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        pinMode(XP, OUTPUT);
        pinMode(YM, OUTPUT);
      if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
      
      if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570)
      currentPage=1; 
     
      }
  }

//=========================== Init Screen ========================= //
if (currentPage==1){

    init_screen();
     
      while(currentPage==1){
        
        tp = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        pinMode(XP, OUTPUT);
        pinMode(YM, OUTPUT);
        
     if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
     
     if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530)
        drawFrameRED("+");
      
     if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800)
        drawFrameRED("-");

// selection paramètres

   
     if ( tp.x > 380 && tp.x < 500 && tp.y > 590 && tp.y < 730)//init seconds
        Init = 1;
        if ( Init == 1)
           {
                if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800 && initSec < 59)// + button
                {initSec=initSec+1;
                drawFrameRED("+");}
                else if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530 && initSec > 0)// - button
                {initSec=initSec-1;
                drawFrameRED("-");}
                //delay(10);

                tft.drawRect(170, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
                tft.fillRect(170, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
                
                tft.setCursor(176, 68);
                tft.setTextSize(3);
                tft.setTextColor(YELLOW);
                tft.print(initSec);}
         
          
           
     if ( tp.x > 530 && tp.x < 650 && tp.y > 590 && tp.y < 730)//init minutes
       Init = 2;
        if ( Init == 2)
              {                
                if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800 && initMin < 59)// + button
                {initMin=initMin+1;}
                else if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530 && initMin > 0)// - button
                {initMin=initMin-1;}
                  delay(10);
                                  
                tft.drawRect(110, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
                tft.fillRect(110, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
                
                tft.setCursor(116, 68);
                tft.setTextSize(3);
                tft.setTextColor(YELLOW);
                tft.print(initMin);}


     
     if ( tp.x > 690 && tp.x < 800 && tp.y > 590 && tp.y < 730)//init hours
       Init = 3;
        if ( Init == 3)
              {                
                if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800 )// + button
                {initHour=initHour+1;}
                else if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530 && initHour > 0)// - button
                {initHour=initHour-1;}
                  delay(10);
                                  
                tft.drawRect(50, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
                tft.fillRect(50, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
                tft.setCursor(56, 68);
                tft.setTextSize(3);
                tft.setTextColor(YELLOW);
                tft.print(initHour);}


                
                
       if ( tp.x > 380 && tp.x < 500 && tp.y > 320 && tp.y < 360)//Run seconds
        Init = 4;
        if ( Init == 4)
           {
                if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800 && runSec < 59)// + button
                {runSec=runSec+1;
                drawFrameRED("+");}
                else if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530 && runSec > 0)// - button
                {runSec=runSec-1;
                drawFrameRED("-");}
                //  delay(10);

                tft.drawRect(170, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
                tft.fillRect(170, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
                 
                 tft.setCursor(176, 148);
                 tft.setTextSize(3);
                 tft.setTextColor(YELLOW);
                 tft.print(runSec);
              } 

           if ( tp.x > 530 && tp.x < 650 && tp.y > 320 && tp.y < 370)//Run minutes
            Init = 5;
             if ( Init == 5)
              {                
                if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800 && runMin < 59)// + button
                {runMin=runMin+1;}
                else if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530 && runMin > 0)// - button
                {runMin=runMin-1;}
                  delay(10);
                                  
                tft.drawRect(110, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
                tft.fillRect(110, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
    
                tft.setCursor(116, 148);
                tft.setTextSize(3); 
                tft.setTextColor(YELLOW);
                tft.print(runMin);}


           if ( tp.x > 690 && tp.x < 800 && tp.y > 320 && tp.y < 370)//Run hours
            Init = 6;
             if ( Init == 6)
              {                
                if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800 && runHour < 99)// + button
                {runHour=runHour+1;}
                else if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530 && runHour > 0)// - button
                {runHour=runHour-1;}
                  delay(10);
                                  
                tft.drawRect(50, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
                tft.fillRect(50, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
                tft.setCursor(56, 148);
                tft.setTextSize(3); 
                tft.setTextColor(YELLOW);
                tft.print(runHour);}
                
      if (tp.x > 120 && tp.x < 250  && tp.y > 130 && tp.y < 250)
        currentPage=2;
       
      }
    
}     
//fin selection paramètres 

//============================ Pulse screen ========================== //

if (currentPage==2){
    pulse_screen(linear,expo);
        
    while(currentPage==2){
      tp = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        pinMode(XP, OUTPUT);
        pinMode(YM, OUTPUT);

      if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
      if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530)
        drawFrameRED("+");
      
      if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800)
        drawFrameRED("-");
// sélection paramètres

      if ( tp.x > 490 && tp.x < 620 && tp.y > 710 && tp.y < 820)//First pulse Milliseconds
        Pulse = 1;
        if ( Pulse == 1)
           {
                if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800 && fPulseMilliSec < 99)// + button
                {fPulseMilliSec=fPulseMilliSec+1;
                drawFrameRED("+");}
                else if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530 && fPulseMilliSec > 0)// - button
                {fPulseMilliSec=fPulseMilliSec-1;
                drawFrameRED("-");}
                  //delay(5);

                 tft.drawRect(130, (tft.height()/5)-20, BOXSIZE+10, BOXSIZE - 10, BLACK);
                 tft.fillRect(130, (tft.height()/5)-20, BOXSIZE+10, BOXSIZE - 10, BLACK);
    
                 tft.setCursor(136, 36);
                 tft.setTextSize(3); 
                 tft.setTextColor(YELLOW);
                 tft.print(fPulseMilliSec);}

      if ( tp.x > 680 && tp.x < 810 && tp.y > 710 && tp.y < 820)//First pulse secondes
        Pulse = 2;
        if ( Pulse == 2)
           {
                if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800)// + button
                {fPulseSec=fPulseSec+1;
                drawFrameRED("+");}
                else if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530 && fPulseSec > 0)// - button
                {fPulseSec=fPulseSec-1;
                drawFrameRED("-");}
                  //delay(5);

                 tft.drawRect(66, (tft.height()/5)-20, BOXSIZE+10, BOXSIZE - 10, BLACK);
                 tft.fillRect(66, (tft.height()/5)-20, BOXSIZE+10, BOXSIZE - 10, BLACK);
                 
                 tft.setCursor(70, 36);
                 tft.setTextSize(3); 
                 tft.setTextColor(YELLOW);
                 tft.print(fPulseSec);}

      if ( tp.x > 490 && tp.x < 620 && tp.y > 540 && tp.y < 660)//Last pulse milliseconds
        Pulse = 3;
        if ( Pulse == 3)
           {
                if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800 && lPulseMilliSec < 99)// + button
                {lPulseMilliSec=lPulseMilliSec+1;
                drawFrameRED("+");}
                else if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530 && lPulseMilliSec > 0)// - button
                {lPulseMilliSec=lPulseMilliSec-1;
                drawFrameRED("-");}
                  //delay(5);

                 tft.drawRect(130, ((tft.height()*2)/5)-20, BOXSIZE, BOXSIZE - 10, BLACK);
                 tft.fillRect(130, ((tft.height()*2)/5)-20, BOXSIZE, BOXSIZE - 10, BLACK);
                 tft.setCursor(136, 84);
                 tft.setTextSize(3);
                 tft.setTextColor(YELLOW);
                  tft.print(lPulseMilliSec);}

      
      if ( tp.x > 680 && tp.x < 810 && tp.y > 540 && tp.y < 660)//Last pulse secondes
        Pulse = 4;
        if ( Pulse == 4)
           {
                if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800)// + button
                {lPulseSec=lPulseSec+1;
                drawFrameRED("+");}
                else if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530 && lPulseSec > 0)// - button
                {lPulseSec=lPulseSec-1;
                drawFrameRED("-");}
                  //delay(5);

                  tft.drawRect(66, ((tft.height()*2)/5)-20, BOXSIZE+10, BOXSIZE - 10, BLACK);
                  tft.fillRect(66, ((tft.height()*2)/5)-20, BOXSIZE+10, BOXSIZE - 10, BLACK);
                  tft.setCursor(70, 84);
                  tft.setTextSize(3); 
                  tft.setTextColor(YELLOW);
                  tft.print(lPulseSec);}



      if ( tp.x > 580 && tp.x < 700 && tp.y > 380 && tp.y < 500)//Ratio pulse back
        Pulse = 5;
        if ( Pulse == 5)
           {
                if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800 && ratio < 100)// + button
                {ratio=ratio+1;
                drawFrameRED("+");}
                else if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530 && ratio > 0)// - button
                {ratio=ratio-1;
                drawFrameRED("-");}
                  //delay(5);

                 tft.drawRect(96, ((tft.height()*3)/5)-20, BOXSIZE+8, BOXSIZE - 10, BLACK);
                 tft.fillRect(96, ((tft.height()*3)/5)-20, BOXSIZE+8, BOXSIZE - 10, BLACK);
                 tft.setCursor(100, 132);
                 tft.setTextSize(3); 
                 tft.setTextColor(YELLOW);
                  tft.print(ratio);}

       
        if ( tp.x > 680 && tp.x < 990 && tp.y > 110 && tp.y < 250 )//Linear time ramp
              
              Pulse = 6;
              int L=100;
              int H=40;
               if ( Pulse == 6)
               { linear = true;                  
                  expo = false;
                  tft.drawRoundRect(117, 192, L-4, H-4, 8, BLACK);
                  tft.setCursor( 140, 202);
                  tft.setTextSize(2);
                   tft.setTextColor(AQUAMARINE);
                    tft.print("expo");
                    
                  tft.drawRoundRect(10, 192, L-4, H-4, 8, FUCHSIA);
                 tft.setCursor( 22, 202);
                 tft.setTextSize(2);
                  tft.setTextColor(FUCHSIA);
                    tft.print("linear");
                 delay(10);}
               
               

         if ( tp.x > 350 && tp.x < 650 && tp.y > 110 && tp.y < 250 )//exponential time ramp
             
              Pulse = 7;
              
               if ( Pulse == 7)
               { expo = true;
                 linear = false;

                 tft.drawRoundRect(10, 192, L-4, H-4, 8, AQUAMARINE);
                 tft.setCursor( 22, 202);
                 tft.setTextSize(2);
                  tft.setTextColor(AQUAMARINE);
                    tft.print("linear");
                    
                 tft.drawRoundRect(117, 192, L-4, H-4, 8, FUCHSIA);
                 tft.setCursor( 140, 202);
                 tft.setTextSize(2);
                  tft.setTextColor(FUCHSIA);
                    tft.print("expo");
                 delay(10);}
                 
               


// Fin selection paramètres

      if (tp.x > 120 && tp.x < 250  && tp.y > 830 && tp.y < 905)
        currentPage=1;
                    
      if (tp.x > 120 && tp.x < 250  && tp.y > 130 && tp.y < 250)
        currentPage=3;
    
    }
}

 //============================ Recap screen ========================== //   

if (currentPage==3){
    recap_screen(linear);

    while(currentPage==3){
      tp = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        pinMode(XP, OUTPUT);
        pinMode(YM, OUTPUT);

      if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;

    
      if (tp.x > 120 && tp.x < 250  && tp.y > 830 && tp.y < 905)
        currentPage=2;
        
      if (tp.x > 120 && tp.x < 330  && tp.y > 110 && tp.y < 250)
        currentPage=4;
      }

}
//============================ Run screen ========================== //

if (currentPage==4){
        
int positive = 38;
int negative = 34;
int32_t previousMillis = 0;
int32_t currentMillis = 0;  

bool isTimer = true;
unsigned long pauseTime = 0;
unsigned long pauserun = 0;
unsigned long elapsedInitTime = 0;
unsigned long elapsedRunTime = 0;
unsigned long pauseInitStart = 0;
unsigned long pauseInitEnd = 0;
unsigned long startRun =0;
unsigned long startInit =0;
unsigned long runMillis = 0;
unsigned long pauseRunStart = 0;
unsigned long pauseRunEnd = 0;
unsigned long pulseMillis = 0;
unsigned long previousfPulseMillis=0; //initilized to start on positive pulse
unsigned long firstMillis = 0;
unsigned long pulsebMillis = 0;

unsigned long previousbPulseMillis=0;

long runTimer = runSec*1000+runMin*60000+runHour*3600000; // en millisecondes; // running screen

long Tsf = fPulseSec * 1000 + fPulseMilliSec * 10; // Total forward pulse
long Tsb = Tsf*ratio/100; // Total backward pulse
long Tef = lPulseSec * 1000 + lPulseMilliSec * 10; // Total forward pulse
long Teb = Tef*ratio/100; // Total backward pulse
long Ts=Tsf+Tsb; // Total start f+b pulses
long Te=Tef+Teb; // Total end f+b pulses


// linear equation
long nbPulse = 2*runTimer/(Ts+Te);
long increment = (Te-Ts)/(nbPulse-1);

// exponential equation
long incrementExpo = (runTimer - Ts)*(runTimer - Te);
long nbPulseExpo = log(Te/Ts)+1;

long count = 0;
bool signePulse = true; //true = + , false = -
bool backward = false;



        pinMode ( positive, OUTPUT);
        //DDRA |= 1 << DDA0;
        pinMode ( negative, OUTPUT);
        //DDRA |= 1 << DDA2;
 
        digitalWrite(positive,LOW);
        //PORTA &= ~( 1 << PORTA0);
        digitalWrite(negative,LOW);
        //PORTA &= ~( 1 << PORTA2);
        

run_screen();


    while(currentPage==4){
      
      tp = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        pinMode(XP, OUTPUT);
        pinMode(YM, OUTPUT);

        
         currentMillis = millis();   

             
//unsigned long timeCheck1 = micros();
if (pauseTime>0){         
if (pauseInitEnd >0 && pauseInitStart>0){elapsedInitTime = (pauseInitEnd-pauseInitStart);}

if ( currentMillis-startInit < (initSec*1000+initMin*60000+initHour*3600000)+elapsedInitTime && pause == false && isTimer == true){                                                     //init Timer

            digitalWrite(positive, HIGH);
      //PORTA |= 1 << PORTA0;
            //isTimer = true;
      startRun = millis();
}
    if (currentMillis - previousMillis >= 1000 && pause == false && isTimer == true ) {    

    previousMillis = currentMillis;
    
    long timeInitText = (initSec+initMin*60+initHour*3600+elapsedInitTime/1000)-(currentMillis-startInit)/1000;
    long hourInitText = timeInitText / 3600;
    long minInitText = (timeInitText-(hourInitText*60))/60;
    long secInitText = timeInitText-((hourInitText*60)+(minInitText*60));
    
    tft.fillRect(85,48,160,30,BLACK); // Timer text
    tft.setTextSize(3); 
    tft.setTextColor(WHITE);
    tft.setCursor(115, 50); //timer
    tft.print(hourInitText);
    tft.print(":");
    tft.print(minInitText-(hourInitText*59));
    tft.print(":");
    tft.print(secInitText);

    
    } 


    
  if( (currentMillis-startInit) < (initSec*1000+initMin*60000+initHour*3600000)+elapsedInitTime && pause == true){ //pause before init is finished
      
  digitalWrite(positive, LOW);
  //PORTA &= ~( 1 << PORTA0);
  
}
      
  if(currentMillis-startInit >= (initSec*1000+initMin*60000+initHour*3600000)+elapsedInitTime && isTimer == true){                                                                                                                    // init timer finished
 
  digitalWrite(positive, LOW);
  //PORTA &= ~( 1 << PORTA0);
  
  isTimer = false;
  
  }

}
  
runMillis = millis();


if (pauseRunEnd >0 && pauseRunStart>0){elapsedRunTime = (pauseRunEnd-pauseRunStart);}

if ( runMillis-startRun < (runSec*1000+runMin*60000+runHour*3600000)+elapsedRunTime && pause == false && isTimer == false ){    //Run Timer

if(linear == true){                                               ///// Linear equation
if (back == false){

   
    
    tft.setCursor(135, 135); //time pulse
    tft.setTextSize(4); 
    tft.setTextColor(BLACK);
    tft.print(" +");
    tft.setTextColor(RED);
    tft.setCursor(135, 135);
    tft.print("+");
    
    
pulseMillis = millis();
digitalWrite(positive, HIGH);

if (count>0 && pulseMillis-previousfPulseMillis >= Tsf+(count*increment)-(count*increment)*ratio/100){//-(Tsb+(count*increment)*ratio/100)){
digitalWrite(positive, LOW);

back = true;
previousbPulseMillis=millis();}

if(count==0 && pulseMillis - startRun >= Tsf ){ // for the first pulse only
//delay(Tsf);
digitalWrite(positive, LOW);

back = true;
previousbPulseMillis=millis();}
 
}
firstMillis = millis();
if (back == true){
     
    tft.setCursor(135, 135); //time pulse
    tft.setTextSize(4); 
    tft.setTextColor(BLACK);
    tft.print("+");
    tft.setTextColor(BLUE);
    tft.setCursor(135, 135);
    tft.print(" -");
    
  pulsebMillis = millis();
digitalWrite(negative, HIGH);

if (pulsebMillis-previousbPulseMillis >= Tsb+(count*increment)*ratio/100){//(Tsf(+(count*increment))*ratio/100){
  digitalWrite(negative, LOW);
  
  back = false;
  previousfPulseMillis=millis();
  count++;
 
}
}
}
if(expo == true){
if (back == false){
    
    tft.setCursor(135, 135); //time pulse
    tft.setTextSize(4); 
    tft.setTextColor(RED);
    tft.print("+ ");
    
pulseMillis = millis();
digitalWrite(positive, HIGH);
if (pulseMillis-previousfPulseMillis >= Tsf +(incrementExpo*count)){
digitalWrite(positive, LOW);
back = true;
previousbPulseMillis=millis();}
}
if (back == true){
   
    tft.setCursor(135, 135); //time pulse
    tft.setTextSize(4); 
    tft.setTextColor(BLUE);
    tft.print(" -");
    
  pulsebMillis = millis();
digitalWrite(negative, HIGH);
if (pulsebMillis-previousbPulseMillis >= Tsb +(incrementExpo*count)*ratio/100){
  digitalWrite(negative, LOW);
  back = false;
  previousfPulseMillis=millis();
  count++;
}
}
}    
  if (runMillis - previousMillis >= 1000 ) {    // Run timer
    // save the last time you blinked the Screen
    previousMillis = runMillis;
    
   
    //int32_t timeText = (runSec+runMin*60+runHour*3600+elapsedRunTime/1000)-(runMillis-startRun)/1000; //décomposer l'opération
    
    unsigned long HourinSeconds = runHour*3600;
    unsigned long MinuteinSeconds = runMin*60;
    unsigned long elapsedRunTimeSeconds = elapsedRunTime/1000;
    unsigned long TickingTime = (runMillis-startRun)/1000;
    unsigned long timeText = runSec+MinuteinSeconds+HourinSeconds+elapsedRunTimeSeconds-TickingTime;
    unsigned long hourText = timeText/3600;
    unsigned long minText = (timeText-(hourText*60))/60;
    unsigned long secText = timeText-((hourText*60)+(minText*60));
    //unsigned int minsText = minText-(hourText*60);           //toujours positif, comme laurie
    tft.fillRect(85,48,170,30,BLACK);
    tft.setTextSize(3); 
    tft.setTextColor(WHITE);
    tft.setCursor(105, 50); //timer
    tft.print(hourText);
    tft.print(":");
    tft.print(minText-(hourText*59));
    tft.print(":");
    tft.print(secText);

    tft.fillRect(179,88,110,30,BLACK); 
    tft.setCursor(90, 90); //nombre pulses
    tft.setTextSize(2); 
    tft.setTextColor(WHITE);
    tft.print("Nb Pulses:");
    tft.setTextColor(LAWNGREEN);
    tft.print(count);

/*if(linear == true){
       tft.fillRect(189,118,150,30,BLACK); 
    tft.setCursor(70, 120); //time pulse
    tft.setTextSize(2); 
    tft.setTextColor(WHITE);
    tft.print("Time Pulse:");
    tft.setTextColor(LAWNGREEN);
    tft.print(Tsf+(count*increment)+Tsb);}

if(expo == true){
       tft.fillRect(189,118,150,30,BLACK); 
    tft.setCursor(70, 120); //time pulse
    tft.setTextSize(2); 
    tft.setTextColor(WHITE);
    tft.print("Time Pulse:");
    tft.setTextColor(LAWNGREEN);
    tft.print((Tsf +(incrementExpo*count)*ratio/100));}*/

    } 

}
if( (runMillis-startRun) < (runSec*1000+runMin*60000+runHour*3600000)+elapsedRunTime && pause == true && isTimer == false ){ //pause before Run is finished
 
  digitalWrite(positive, LOW);
  digitalWrite(negative, LOW);
}

if( (runMillis-startRun) >= (runSec*1000+runMin*60000+runHour*3600000)+elapsedRunTime && isTimer == false ){
  digitalWrite(positive, LOW);
  digitalWrite(negative, LOW);
}


     if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE)continue ;


    

      if (tp.x > 380 && tp.x < 690  && tp.y > 150 && tp.y < 290)
        {
        if(isTimer == true && pauseTime < 1 ){startInit=millis();}
        if (isTimer == true && pause == false){pauseInitStart = millis();}
        if (isTimer == true && pause == true){pauseInitEnd = millis();}
        if (isTimer == false && pause == false){pauseRunStart = millis();}
        if (isTimer == false && pause == true){pauseRunEnd = millis();}
        pauseTime=millis();
        if(isTimer == false){pauserun=millis();}
        
        if (pause == true) {pauseAndStart();
       
        }
          else {run_screen();
          }
        delay(50);
      pause = !pause;
      }
      
      
      if (tp.x > 120 && tp.x < 250  && tp.y > 830 && tp.y < 905)
        currentPage=3;

    }
}      
  

}


///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// ====== Custom Functions ======
///////////////////////////////////////////////////////////////////////////////////////////////////////


// Highlights the button when pressed
void drawFrameRED(char sign) {
               
           if (sign = "+"){    
               
               if (tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800)
         
               {// if(tp.x > 180 && tp.x < 360  && tp.y > 580 && tp.y < 800)
                tft.drawRoundRect(228, 38, 62, 62, 13, RED);
                tft.setCursor(239, 41);
                tft.setTextSize(8); 
                tft.setTextColor(CRIMSON);
                tft.print("+"); 
                delay(50);}

                 tft.drawRoundRect(228, 38, 62, 62, 13, GREY);
                tft.setCursor(239, 41);
                tft.setTextSize(8); 
                tft.setTextColor(BLACK);
                tft.print("+"); 
           }

          if (sign = "-"){    
               
               if (tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530)
         
               {// if(tp.x > 180 && tp.x < 360  && tp.y > 310 && tp.y < 530)
                tft.drawRoundRect(228, 116, 62, 62, 13, RED);
                tft.setCursor(239, 120);
                tft.setTextSize(8); 
                tft.setTextColor(CRIMSON);
                tft.print("-");
                delay(50);}

                tft.drawRoundRect(228, 116, 62, 62, 13, GREY);
                tft.setCursor(239, 120);
                tft.setTextSize(8); 
                tft.setTextColor(BLACK);
                tft.print("-"); 
           }
}

//============================ welcome screen ========================== //

void welcome_screen(void)

{

tft.fillScreen(WHITE); 


// LOGO

int h = 135,w = 354, row, col, buffidx=0; // Brand logo (voir BITMAPS_H)
  for (row=90; row<h; row++) { // For each scanline...
    for (col=0; col<w; col++) { // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      
      tft.drawPixel(col+58, row, pgm_read_word(vulcain + buffidx));
     
      buffidx++;
    } // end pixel   
  }  
tft.fillRect(232, 0, 90, tft.height(), WHITE);

tft.setTextColor(PURPLE);
    tft.setTextSize(1);
    tft.setCursor(2, 228);
    tft.print("Touch to begin science");

}

//============================ init screen ========================== //

void init_screen(void)

{   tft.fillScreen(WHITE);  
    
    tft.setTextSize(1);
    tft.setTextColor(PURPLE);
    tft.setCursor( 4, 4);
    tft.print("PFGE electropheresis");
    
    tft.setTextSize(2);                                             //timer init
    tft.setTextColor(BLACK);
    tft.setCursor( 1, tft.height()/3);
    tft.print("Init");

    BOXSIZE = tft.width() / 7;  

    tft.drawRect(50, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.fillRect(50, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.setCursor(56, 68);
    tft.setTextSize(3); 
    tft.setTextColor(YELLOW);
    tft.print(initHour);

     tft.setCursor(50, 98);
    tft.setTextSize(1);
    tft.setTextColor(PURPLE);
    tft.print("hour");

      tft.setTextSize(3);
      tft.setCursor(95, 68);
    tft.setTextColor(BLACK);
    tft.print(":");
                                         
    tft.drawRect(110, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.fillRect(110, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.setCursor(116, 68);
    tft.setTextSize(3); 
    tft.setTextColor(YELLOW);
    tft.print(initMin);

     tft.setCursor(110, 98);
    tft.setTextSize(1);
    tft.setTextColor(PURPLE);
    tft.print("minute");

      tft.setTextSize(3);
      tft.setCursor(155, 68);
    tft.setTextColor(BLACK);
    tft.print(":");

      tft.drawRect(170, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.fillRect(170, tft.height()/4, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.setCursor(176, 68);
    tft.setTextColor(YELLOW);
    tft.print(initSec);

    tft.setCursor(170, 98);
    tft.setTextSize(1);
    tft.setTextColor(PURPLE);
    tft.print("second");

    
    
    

    tft.setCursor( 8, ((tft.height()*3) /4)-20);                                  //timer Run
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.print("Run");

     BOXSIZE = tft.width() / 7;                                                   
     
        tft.drawRect(50, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.fillRect(50, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.setCursor(56, 148);
    tft.setTextSize(3); 
    tft.setTextColor(YELLOW);
    tft.print(runHour);

    tft.setCursor(50, 178);
    tft.setTextSize(1);
    tft.setTextColor(PURPLE);
    tft.print("hour");

      tft.setTextSize(3);
      tft.setCursor(95, 148);
    tft.setTextColor(BLACK);
    tft.print(":");
    
    
    tft.drawRect(110, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.fillRect(110, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.setCursor(116, 148);
    tft.setTextSize(3); 
    tft.setTextColor(YELLOW);
    tft.print(runMin);

    tft.setCursor(110, 178);
    tft.setTextSize(1);
    tft.setTextColor(PURPLE);
    tft.print("minute");

      tft.setTextSize(3);
      tft.setCursor(155, 148);
    tft.setTextColor(BLACK);
    tft.print(":");

      tft.drawRect(170, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.fillRect(170, ((tft.height()*2)/3)-20, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.setCursor(176, 148);
    tft.setTextColor(YELLOW);
    tft.print(runSec);

    tft.setCursor(170, 178);
    tft.setTextSize(1);
    tft.setTextColor(PURPLE);
    tft.print("second");
    

    BOXSIZE = tft.width() / 5 ; // + button
   tft.drawRoundRect(227, 37, BOXSIZE, BOXSIZE, 14, BLACK);
   tft.drawRoundRect(228, 38, BOXSIZE-2, BOXSIZE-2, 13, GREY);
   tft.setCursor(239, 41);
   tft.setTextSize(8); 
     tft.setTextColor(BLACK);
     tft.print("+");
      

      BOXSIZE = tft.width() / 5 ; // - button
   tft.drawRoundRect(227, 115, BOXSIZE, BOXSIZE, 14, BLACK);
   tft.drawRoundRect(228, 116, BOXSIZE-2, BOXSIZE-2, 13, GREY);
   tft.setCursor(239, 120);
   tft.setTextSize(8); 
     tft.setTextColor(BLACK);
     tft.print("-");
   
    
      
    BOXSIZE = tft.width() / 7; // OK button
    tft.drawRect(270, 192, BOXSIZE, BOXSIZE - 4, RED);
    tft.fillRect(270, 192, BOXSIZE, BOXSIZE - 4, BLACK);
    tft.setCursor(280, 206);
    tft.setTextSize(2); 
     tft.setTextColor(WHITE);
     tft.print("OK");
   
}
  
//============================ Pulse screen ========================== //
  
void pulse_screen(bool linear, bool expo)

{   tft.fillScreen(WHITE);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.setCursor( 2, (tft.height()/5)-20);
    tft.print("first");
    tft.setCursor( 4, (tft.height()/4)-13);
    tft.print("pulse");

    BOXSIZE = tft.width() / 7; //First pulse
    tft.drawRect(67, (tft.height()/5)-20, BOXSIZE+10, BOXSIZE - 10, BLACK);
    tft.fillRect(67, (tft.height()/5)-20, BOXSIZE+10, BOXSIZE - 10, BLACK);
    tft.setCursor(71, 36);
    tft.setTextSize(3); 
    tft.setTextColor(YELLOW);
    tft.print(fPulseSec);

      tft.setCursor(117, 36);
    tft.setTextColor(BLACK);
    tft.print(":");

      tft.drawRect(130, (tft.height()/5)-20, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.fillRect(130, (tft.height()/5)-20, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.setCursor(136, 36);
    tft.setTextColor(YELLOW);
    tft.print(fPulseMilliSec);

      tft.setCursor(178, 36);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.print("ms");
    tft.setTextSize(1);
    tft.print("x10");
    
    
    

    tft.setCursor( 2, ((tft.height()*2)/5)-20);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.print("last");
    tft.setCursor( 4, ((tft.height()*2)/4)-23);
    tft.println("pulse");

     BOXSIZE = tft.width() / 7; //Last pulse
    tft.drawRect(67, ((tft.height()*2)/5)-20, BOXSIZE+10, BOXSIZE - 10, BLACK);
    tft.fillRect(67, ((tft.height()*2)/5)-20, BOXSIZE+10, BOXSIZE - 10, BLACK);
    tft.setCursor(71, 84);
    tft.setTextSize(3); 
    tft.setTextColor(YELLOW);
    tft.print(lPulseSec);

      tft.setCursor(117, 84);
    tft.setTextColor(BLACK);
    tft.print(":");

      tft.drawRect(130, ((tft.height()*2)/5)-20, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.fillRect(130, ((tft.height()*2)/5)-20, BOXSIZE, BOXSIZE - 10, BLACK);
    tft.setCursor(136, 84);
    tft.setTextColor(YELLOW);
    tft.print(lPulseMilliSec);

      tft.setCursor(178, 84);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.print("ms");
    tft.setTextSize(1);
    tft.print("x10");

    
    
    tft.setCursor( 20, ((tft.height()*3)/5)-5);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.print("Ratio");
    
    BOXSIZE = tft.width() / 7; // Ratio
    tft.drawRect(96, ((tft.height()*3)/5)-20, BOXSIZE+8, BOXSIZE - 10, BLACK);
    tft.fillRect(96, ((tft.height()*3)/5)-20, BOXSIZE+8, BOXSIZE - 10, BLACK);
    tft.setCursor(100, 132);
    tft.setTextSize(3); 
    tft.setTextColor(YELLOW);
    tft.print(ratio);
   
    tft.setTextColor(BLACK);
    tft.setCursor(152, 132);
    tft.print ("%");

    tft.drawLine(1, 162, 200, 162, BLUE); // Time ramp
    tft.setCursor( 4, 168);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.print("Time ramp");

      int L=100;
    int H=40;
   if (linear = true ){                                     //linear is true
    tft.drawRoundRect(8, 190, L, H, 8, BLACK); // linear
    tft.drawRoundRect(10, 192, L-4, H-4, 8, FUCHSIA);
    tft.fillRoundRect(10, 192, L-4, H-4,8, GREY);
    tft.setCursor( 22, 202);
    tft.setTextColor(FUCHSIA);
    tft.print("linear");
    
    tft.drawRoundRect(115, 190, L, H, 8, BLACK); // exponential
    tft.drawRoundRect(117, 192, L-4, H-4, 8, BLACK);
    tft.fillRoundRect(117, 192, L-4, H-4,8, GREY);
    tft.setCursor( 140, 202);
    tft.setTextColor(AQUAMARINE);
    tft.print("expo");}

    else if(expo = true ){                                                   //expo is true
    tft.drawRoundRect(8, 190, L, H, 8, BLACK); // linear
    tft.drawRoundRect(10, 192, L-4, H-4, 8, BLACK);
    tft.fillRoundRect(10, 192, L-4, H-4,8, GREY);
    tft.setCursor( 22, 202);
    tft.setTextColor(AQUAMARINE);
    tft.print("linear");
    
    tft.drawRoundRect(115, 190, L, H, 8, BLACK); // exponential
    tft.drawRoundRect(117, 192, L-4, H-4, 8, FUCHSIA);
    tft.fillRoundRect(117, 192, L-4, H-4,8, GREY);
    tft.setCursor( 140, 202);
    tft.setTextColor(FUCHSIA);
    tft.print("expo");}
    
    
    

     BOXSIZE = tft.width() / 5 ; // + button
   tft.drawRoundRect(227, 37, BOXSIZE, BOXSIZE, 14, BLACK);
   tft.drawRoundRect(228, 38, BOXSIZE-2, BOXSIZE-2, 13, GREY);
   tft.setCursor(239, 41);
   tft.setTextSize(8); 
     tft.setTextColor(BLACK);
     tft.print("+");

      BOXSIZE = tft.width() / 5 ; // - button
   tft.drawRoundRect(227, 115, BOXSIZE, BOXSIZE, 14, BLACK);
   tft.drawRoundRect(228, 116, BOXSIZE-2, BOXSIZE-2, 13, GREY);
   tft.setCursor(239, 120);
   tft.setTextSize(8); 
     tft.setTextColor(BLACK);
     tft.print("-");

 
   tft.setTextColor(BLACK); // escape
   tft.setTextSize(3); 
   tft.setCursor(290, 4);
   tft.print("<");
  
        
    BOXSIZE = tft.width() / 7; // OK button
    tft.drawRect(270, 192, BOXSIZE, BOXSIZE - 4, RED);
    tft.fillRect(270, 192, BOXSIZE, BOXSIZE - 4, BLACK);
    tft.setCursor(280, 206);
    tft.setTextSize(2); 
     tft.setTextColor(WHITE);
     tft.print("OK");
       
}

//============================ Recap screen ========================== //

void recap_screen(bool linear)

{   tft.fillScreen(WHITE);

    int L=100;
      int H=40;
    tft.drawRoundRect(217, 37, L, H, 8, BLACK); // chosen function 
    tft.drawRoundRect(219, 39, L-4, H-4, 8, BLACK);
    tft.fillRoundRect(219, 39, L-4, H-4,8, GREY);
    tft.setCursor( 229, 49);
    tft.setTextSize(2);
    tft.setTextColor(AQUAMARINE);
    if (linear == true){
    tft.print("linear");}
    else if (expo == true){
      tft.setCursor( 240, 49);
      tft.print("expo");}

    tft.drawLine(20, 20, 20, 200, GREY); // GRAPH
     for (int i=20; i<200; i+=21)
    tft.drawLine(18, i, 22, i, GREY);
    tft.setTextSize(1);
    tft.setCursor( 18, 18);
    tft.setTextColor(GREY);
    tft.print("^");
    
      tft.drawLine(20, 200, 200, 200, GREY);
      for (int i=20; i<200; i+=21)
    tft.drawLine(i, 198, i, 202, GREY);
    tft.setCursor( 198, 197);
    tft.print(">");

    if (linear == true){
      for (int i=20; i<200; i++)
  {
    tft.drawPixel(i,220-i,GREEN);
  }
    }
   else if (expo == true){  
          for (int i=20; i<200; i++)
  {
    tft.drawPixel(i,180-(i*i)/220,RED);
  }
    } 

    
   
     tft.setCursor(40, 180);
    tft.setTextSize(1); 
    tft.setTextColor(PURPLE);
    tft.print("First pulse=");
    tft.print(fPulseSec);
    tft.print(":");
    tft.print(fPulseMilliSec);
        
     tft.setCursor(100, 20);
    tft.setTextSize(1); 
    tft.setTextColor(PURPLE);
    tft.print("Last pulse=");
    tft.print(lPulseSec);
    tft.print(":");
    tft.print(lPulseMilliSec);

      tft.setCursor(160, 100);
    tft.setTextSize(1); 
    tft.setTextColor(BLACK);
    tft.print("Return Ratio: ");
    tft.setTextSize(2);
    //tft.setCursor(160, 110);
    tft.print(ratio);
    tft.print("%");

    tft.setCursor(160, 130);
    tft.setTextSize(1); 
    tft.setTextColor(BLACK);
    tft.print("Run Time: ");
    tft.setTextSize(2);
    //tft.setCursor(160, 150);
    tft.print(runHour);
    tft.print(":");
    tft.print(runMin);
    tft.print(":");
    tft.print(runSec);

        tft.setCursor(158, 160);
    tft.setTextSize(1); 
    tft.setTextColor(BLACK);
    tft.print("Init Time: ");
    tft.setTextSize(2);
    //tft.setCursor(160, 150);
    tft.print(initHour);
    tft.print(":");
    tft.print(initMin);
    tft.print(":");
    tft.print(initSec);


   tft.setTextColor(BLACK); // escape
   tft.setTextSize(3); 
   tft.setCursor(290, 4);
   tft.print("<");
  


      tft.drawRoundRect(217, 194, L, H, 4, BLACK); // Start button
    tft.drawRoundRect(219, 196, L-4, H-4, 4, BLACK);
    tft.fillRoundRect(219, 196, L-4, H-4,4, CRIMSON);
    tft.setCursor(232, 208);
    tft.setTextSize(2); 
    tft.setTextColor(WHITE);
    tft.print("BEGIN>");
     
}

//============================ Run screen ========================== //
void run_screen(void)

{   tft.fillScreen(BLACK);
  

    tft.setTextColor(WHITE); // escape
    tft.setTextSize(3); 
    tft.setCursor(290, 4);
    tft.print("<");  
    
    tft.setCursor(105, 50); //timer
    tft.setTextSize(3); 
    tft.setTextColor(WHITE);
    tft.print(initHour);
    tft.print(":");
    tft.print(initMin);
    tft.print(":");
    tft.print(initSec);

    tft.setCursor(90, 90); //nombre pulses
    tft.setTextSize(2); 
    tft.setTextColor(WHITE);
    tft.print("Nb Pulses:");
    tft.setTextColor(LAWNGREEN);
    tft.print("00");

    /*tft.setCursor(70, 120); //time pulse
    tft.setTextSize(2); 
    tft.setTextColor(WHITE);
    tft.print("Time Pulse:");
    tft.setTextColor(LAWNGREEN);
    tft.print("00");*/


    int L=100;
      int H=40;
      tft.drawRoundRect(110, 184, L, H, 4, WHITE); // Pause button button
    tft.drawRoundRect(112, 186, L-4, H-4, 4, BLACK);
    tft.fillRoundRect(112, 186, 96, 36,4, CRIMSON);
    tft.setCursor(125, 198);
    tft.setTextSize(2); 
    tft.setTextColor(WHITE);
    tft.print("START>");

    tft.setCursor(2, 2);
    tft.setTextSize(1); 
    tft.setTextColor(LIGHTCYAN);
    tft.print("Freeze");
   
}
void pauseAndStart()
{
  
        tft.setCursor(2, 2);
    tft.setTextSize(1); 
    tft.setTextColor(BLACK);
    tft.print("Freeze");

        tft.fillRoundRect(112, 186, 96, 36,4, CRIMSON);
    tft.setCursor(117, 198);
    tft.setTextSize(2); 
    tft.setTextColor(WHITE);
    tft.print("PAUSE H");
    tft.fillRect( 191, 202, 6,5,CRIMSON);//signe pause ||
}
// THE END
