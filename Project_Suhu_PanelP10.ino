#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "ArialRoundedMTBold16.h"
#include <Adafruit_MLX90614.h>
#include <Calibri10.h>
#include "Verdana10.h"
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define BARIS 1
#define KOLOM 1
#define FONT ArialRoundedMTBold16

int pinpir = 2;
int statuspir = 0;
int buz = 4;
int vprox = 3;
int vbuzz = 5;
int gnd = 12;

float suhu;
float lastread;
uint32_t lastMillis;
int timeout = 500;
char h[5]; //hasil
int a; //angka yang telah ditambahh 2

DMD led_modul_tri (BARIS, KOLOM);

void scan_module()
{
  led_modul_tri.scanDisplayBySPI();
  
}
void setup() {
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan_module);
  led_modul_tri.clearScreen(true);

  pinMode(pinpir, INPUT);
  pinMode(buz, OUTPUT);
  //coklat = vcc 3
  pinMode(vprox, OUTPUT);
  digitalWrite(vprox, HIGH);
  //merah vcc 5
  pinMode(vbuzz, OUTPUT);
  digitalWrite(vbuzz, HIGH);
//  //ungu 12 gnd
//  pinMode(gnd, OUTPUT); 
//  digitalWrite(gnd, LOW);
  delay(10);
  Serial.begin(9600);
  digitalWrite(buz, HIGH);
  delay (500);
  digitalWrite(buz, LOW);
  delay (500);
  digitalWrite(buz, HIGH);
  delay (500);
  digitalWrite(buz, LOW);
  delay (500);

  mlx.begin();
        led_modul_tri.selectFont(Calibri10);
        led_modul_tri.drawString(10,-1,"cek",3,GRAPHICS_NORMAL);
        led_modul_tri.drawString(7,8,"suhu",4,GRAPHICS_NORMAL);
}

void loop() {
    statuspir = digitalRead(pinpir);
      //a = (mlx.readObjectTempC()) + 2;
     Serial.println(a);
   
    if (statuspir == LOW){
        digitalWrite(buz, HIGH);
        delay (50);
        digitalWrite(buz, LOW);
        delay(500);
        //Serial.println("Gerakan terdeteksi!!!");
        led_modul_tri.clearScreen(true);   
        
        a = (mlx.readObjectTempC()) + 2;

        dtostrf( a,4,4,h); //(float value, min width, jml angka setelah desimal,var nyimpan nilai string i mean char)
        suhu = map(a, 0 , 30, 0 ,10); //(suhu, fromLow, fromHigh, toLow, toHigh);
        

        led_modul_tri.selectFont(Calibri10);
        led_modul_tri.drawString(4,-1,"Suhu",4, GRAPHICS_NORMAL);
        led_modul_tri.selectFont(SystemFont5x7);
        led_modul_tri.drawString(24,1,":",1, GRAPHICS_NORMAL);
        led_modul_tri.selectFont(Calibri10);
        led_modul_tri.drawString(3,8, h, 4, GRAPHICS_NORMAL);   //baris atas
        led_modul_tri.drawString(23,8,"'C" ,2, GRAPHICS_NORMAL);
        
        Serial.println(h);
        delay(2000);
        led_modul_tri.clearScreen( true );
      
    }
   else {
        Serial.println("Zonk!!!");
        
        led_modul_tri.selectFont(Calibri10);
        led_modul_tri.drawString(10,-1,"cek",3,GRAPHICS_NORMAL);
        led_modul_tri.drawString(7,8,"Suhu",4,GRAPHICS_NORMAL);
   }
   
}
