#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
//#include <SFE_BMP180.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>
#include <Stepper.h>

const int stepsPerRevolution=200 ;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int revo;

#define sw 2

int menu1 = 5;
int count = 1;

#define led 6

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
//#define SCREEN_ADDRESS 0x76
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
float temp;



void setup() {
  Serial.begin(9600);
  pinMode(sw,HIGH);
  pinMode(led, OUTPUT);
  myStepper.setSpeed(150);
   
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
 
  }

   display.setTextColor(WHITE);
    if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }
     bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();


}

void loop() {

 sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  
   if(digitalRead(sw)==HIGH){
    delay(100);
    count++;
    if(count==5)
    count=1;
    }

     myStepper.step(stepsPerRevolution);
   /* while(count==1)  {
      digitalWrite(led,HIGH);
      delay(1000);
      digitalWrite(led,LOW);
      delay(1000);}*/
    switch(count){
      case 1:
      
      //Serial.print(count);
     /* digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
      delay(1000); */
     // display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(50, 40);
      display.print("1:1");
    
      display.display();
      delay(500);
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      break;
      case 2:
      //Serial.print("2");
      display.setTextSize(2);
      display.setCursor(50, 40);
      display.println("1:2");
      display.display();
      delay(1000);
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      break; 
      case 3:
      Serial.print("3");
      display.setTextSize(2);
      display.setCursor(50, 40);
      display.println("1:3");
      display.display();
      delay(1500);
      digitalWrite(led, HIGH);
      delay(1500);
      digitalWrite(led, LOW);
      break;
      case 4:
      Serial.print("4");
      display.setTextSize(2);
      display.setCursor(50, 40);
      display.println("1:4");
      display.display();
      delay(2000);
      digitalWrite(led, HIGH);
      delay(2000);
      digitalWrite(led, LOW);
      break;
      }

   
  
 // delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Pressu :"); 
  display.setCursor(60, 0);
  temp = pressure_event.pressure/1.33;
  display.print(temp);
  display.setCursor(105,0);
  display.print("hPa"); 
 
  display.setCursor(0, 10);
  display.println("Temper :");
  display.setCursor(60, 10);
  display.println(temp_event.temperature); 
  display.setCursor(100, 10);
  display.println("C");
  display.display();  

/* Serial.print(count);
 display.setTextSize(2);
 display.setCursor(50, 40);
      display.print(count);
      display.display();*/

}
