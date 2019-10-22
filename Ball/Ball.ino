
#include "Adafruit_GFX.h"   //основная графическая библиотека для дисплеев 
#include "MCUFRIEND_kbv.h"  //библиотека, которая поддерживает драйверы экранов дисплея 
#include "TouchScreen.h"    //библиотека для работы с сенсорным экраном
#include "UTFT.h"
#include <UTouch.h>
//#include <Adafruit_TFTLCD.h>
#include <SWTFT.h> // Hardware-specific library
#include <TouchScreen.h>



#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

//максимальное и миниальное напряжение по x и по y
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);    //Объект,отвечающий за прикосновения к экрану

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

SWTFT tft;    //Объект,отвечающий за работу с экраном

#define BOXSIZE 60
#define PENRADIUS 3
struct Point      //Point coordinates
{
public:
  short x;
  short y;
};

class Game
{
private:
  static const short cols = 24; //x
  static const short rows = 32;  //y
  const unsigned char mas[rows][cols];
  Point Ball_Coordinates;

public:
  Game() :mas{ {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1},
            {1,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,0,1,1,1,1,1},
            {1,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1,1,1,1,1},
            {1,1,1,1,1,1,0,1,0,1,0,0,1,0,1,1,0,1,0,1,1,1,1,1},
            {1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1,1,1,1,1},
            {1,0,1,1,0,1,1,1,1,1,0,0,1,0,1,1,1,1,0,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1},
            {1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1},
            {1,1,0,0,0,1,0,0,1,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1},
            {1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1},
            {1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1},
            {1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1,0,1,1,1,1,1},
            {1,0,1,1,0,1,1,0,1,0,1,1,1,0,1,0,0,0,0,1,1,1,1,1},
            {1,0,1,0,0,0,1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1},
            {1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
            {1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
            {1,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1},
            {1,0,1,0,1,1,1,1,1,0,0,0,1,0,1,0,0,1,0,1,1,1,1,1},
            {1,0,1,0,0,0,0,0,1,1,1,0,0,0,1,0,1,1,0,1,1,1,1,1},
            {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},}
  {

    Ball_Coordinates.x = 0;
    Ball_Coordinates.y = 1;
  }

  void Move(char);
  void Show();
  
  void FinishGame();
};
void Game::Show()
{

  for (int i = 0; i < rows; i++)
  {
 
    for (int j = 0; j < cols; j++)
    {
      if (i == Ball_Coordinates.y && j == Ball_Coordinates.x)
      {
        //Serial.println("ball");
        tft.fillRect((Ball_Coordinates.x),(10*Ball_Coordinates.y+BOXSIZE),10,10,BLACK);  
            
      }
      else if (mas[i][j] == 1)
      {
       tft.fillRect(i*10,BOXSIZE+j*10,10,10,GREEN);
      }
      else if (mas[i][j] == 0)
       {       
        tft.fillRect(i*10,BOXSIZE+j*10,10,10,WHITE);
       }
    
//FinishGame();
      //}
    }
    //std::cout << std::endl;
  }
  }
void Game::Move(char button)
{

  switch (button)
  {
  case 'w':
    if (mas[Ball_Coordinates.y - 1][Ball_Coordinates.x] != 1 && Ball_Coordinates.y <=rows)
      Ball_Coordinates.y--;
    break;
  case 's':
    if (mas[Ball_Coordinates.y + 1][Ball_Coordinates.x] != 1 && Ball_Coordinates.y >= 0)
      Ball_Coordinates.y++;
    break;
  case 'a':
    if (mas[Ball_Coordinates.y][Ball_Coordinates.x - 1] != 1 && Ball_Coordinates.x >= 0)
      Ball_Coordinates.x--;
    break;
  case 'd':
    if (mas[Ball_Coordinates.y][Ball_Coordinates.x + 1] != 1 && Ball_Coordinates.x <cols)
      Ball_Coordinates.x++;
    break;

  }
}


void setup() {
  // put your setup code here, to run once:
  tft.fillScreen(BLACK);//Заполняет экран черным цветом
 
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
  tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
  

  Serial.begin(9600);
  pinMode(13, OUTPUT);
 
}
  Game ball;
#define MINPRESSURE 10
#define MAXPRESSURE 1000

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  
  ball.Show();
  char button;
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    if (p.y < (TS_MINY-5)) {
      Serial.println("erase");
      // press the bottom of the screen to erase 
      tft.fillRect(0, BOXSIZE, tft.width(), tft.height()-BOXSIZE, BLACK);
    }
    // scale from 0->1023 to tft.width
    p.x = tft.width()-(map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
    p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
    
    if(p.y<BOXSIZE )
    {
      if(p.x<BOXSIZE)
      button='d';
      if(p.x>BOXSIZE && p.x<BOXSIZE*2)
      button='s';
      if(p.x>BOXSIZE*2 && p.x<BOXSIZE*3)
      button='w';
      if(p.x>BOXSIZE*3 && p.x<BOXSIZE*4)
      button='a';
    }
    }
    ball.Move(button);
    }
  
