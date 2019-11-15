// Angel Soto 
// Joystick - Arduino

//Library
#include <LiquidCrystal.h>
using namespace std;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// board connections
int VRx = A0;
int VRy = A1;
int SW = 2;

// init values
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;
float x_coord = 0;
float y_coord = 0;
int sensitivity = 15;

int x_coord_min = 20;
int x_coord_max = 40;
int y_coord_min = 20;
int y_coord_max = 40;
/*
//This block of code below is an alternative to the above block, with the aim being
//to create a random x/y-coord target range upon startup each time.
//If this is indeed used, delete the above block as well as this paragraph.
//Note that this code has not been tested. Test it and tweak it if necessary.
//You will need the device to do this.
int x_coord_min = random(-50, 50);
int x_coord_max = random(-50, 50);
int y_coord_min = random(-50, 50);
int y_coord_max = random(-50, 50);
*/

void setup() {
 Serial.begin(9600);

 pinMode(VRx, INPUT);
 pinMode(VRy, INPUT);
 pinMode(SW, INPUT_PULLUP);

 // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:

  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);

  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  
  if(abs(mapX) > sensitivity)
  {
    x_coord += mapX;//x_coord is mutated by joystick input.
  }
  if (abs(mapY) > sensitivity)
  {
    y_coord += mapY;//y_coord is mutated by joystick input.
  }

  //below is for the first line on the LCD
  lcd.clear();
  lcd.print("X:");
  lcd.print(x_coord/1000);
  lcd.print(" Y:");
  lcd.print(y_coord/1000);

  //below is for the second line of the LCD
  lcd.setCursor(0, 1);
  lcd.print("X(");
  lcd.print(x_coord_min);
  lcd.print("-");
  lcd.print(x_coord_max);
  lcd.print(")Y(");
  lcd.print(y_coord_min);
  lcd.print("-");
  lcd.print(y_coord_max);
  lcd.print(")");  

  //below is for the Serial Monitor's display
  Serial.print("X: ");
  Serial.print(x_coord);
  Serial.print(" | Y: ");
  Serial.print(y_coord);
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  // Turn on the display:
  lcd.display();

  delay(100);
  

}
