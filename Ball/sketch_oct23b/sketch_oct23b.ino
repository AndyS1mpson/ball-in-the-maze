#include "Adafruit_GFX.h"   //основная графическая библиотека для дисплеев 
#include "TouchScreen.h"    //библиотека для работы с сенсорным экраном
#include <SWTFT.h> // Hardware-specific library

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

//максимальное и миниальное напряжение по x и по y
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

//Объект,отвечающий за прикосновения к экрану
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);    

//цвета для вывода игры на экран
#define  BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define MAGENTA 0xF81F

//Объект,отвечающий за работу с экраном
SWTFT tft;    

//размер кнопок движения 60 на 60
#define BOXSIZE 60
#define PENRADIUS 3

//Координаты точки
struct Point      
{
public:
  short x;
  short y;
};

#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack
{
private:
  T* stackPtr;                      // указатель на стек
  const int size;                   // максимальное количество элементов в стеке
  int top;                          // номер текущего элемента стека
public:
  Stack(int = 100);                 // по умолчанию размер стека равен 100 элементам
  Stack(const Stack<T>&);           // конструктор копирования
  ~Stack();                         // деструктор

  inline void push(const T&);       // поместить элемент в вершину стека
  inline void pop();                // удалить элемент из вершины стека и вернуть его
  inline bool isEmpty();
  inline T& getTopLink();

};

// реализация методов шаблона класса STack
template<typename T>
T& Stack<T>::getTopLink()
{
  return stackPtr[top - 1];
}
// конструктор Стека
template <typename T>
Stack<T>::Stack(int maxSize) :
  size(maxSize) // инициализация константы
{
  stackPtr = new T[size]; // выделить память под стек
  top = 0; // инициализируем текущий элемент нулем;
}

// конструктор копирования
template <typename T>
Stack<T>::Stack(const Stack<T>& otherStack) :
  size(otherStack.getStackSize()) // инициализация константы
{
  stackPtr = new T[size]; // выделить память под новый стек
  top = otherStack.getTop();

  for (int ix = 0; ix < top; ix++)
    stackPtr[ix] = otherStack.getPtr()[ix];
}

// функция деструктора Стека
template <typename T>
Stack<T>::~Stack()
{
  delete[] stackPtr; // удаляем стек
}

// функция добавления элемента в стек
template <typename T>
inline void Stack<T>::push(const T& value)
{
  // проверяем размер стека
  if(top < size); // номер текущего элемента должен быть меньше размера стека
  stackPtr[top++] = value; // помещаем элемент в стек
}

// функция удаления элемента из стека
template <typename T>
inline void Stack<T>::pop()
{
  // проверяем размер стека
  if(top > 0); // номер текущего элемента должен быть больше 0
  stackPtr[--top]; // удаляем элемент из стека
}

template<typename T>
bool Stack<T>::isEmpty()
{
  return !top;
}
#endif // STACK_H#pragma once




#define WALL 1
#define ROAD 0
#define TOP 0b0001
#define RIGHT 0b0010
#define BOTTOM 0b0100
#define LEFT 0b1000
#define EMPTY 0b0000

int DX[4] = { -1, 0, 1, 0 };
int DY[4] = { 0, 1, 0, -1 };
int NEIGHTBOURS[4] = { TOP, RIGHT, BOTTOM, LEFT };

struct Cell
{
  Cell()
  {
    x = y = 0;
 //проверка,"посещали" ли мы элемент массива
    visited = false;
 //Соседи рассматриваемой ячейки
    neightbours = 0b0000;
  }

  Cell(int x, int y)
  {
    this->x = x;
    this->y = y;
    visited = false;
    neightbours = 0b0000;
  }

  short x;
  short y;
  bool visited;
  int neightbours;
};

/*
 * Мы используем сетку 15 (строки) на 13 (столбцы), заполненную 0 и 1
   0 означает, что это свободная ячейка, и мы можем использовать ее по своему желанию
   1 означает, что это стена, и мы не можем ее использовать
   На самом деле мы работаем с сеткой 7x6 (мы удваиваем
   и увеличить число на 1, чтобы получить окончательную сетку)
   Мы используем алгоритм DFS, который работает просто:
   1. Выберите начальную ячейку
   2. Проверьте, можем ли мы посетить любую соседнюю камеру
     Y => выбрать случайную соседку
         положить его в стек
         отметьте путь к соседству
     N => ячейка посещена
   3. Извлеките ячейку из стека, вернитесь к 2
 */

//Функция,которая генерирует лабиринт
char** GenerateMaze(int startX, int startY, int rows, int cols)
{
  // create grid of cells
  Cell** grid = new Cell * [rows]; // rows

  for (int i = 0; i < rows; ++i)
  {
    grid[i] = new Cell[cols];
    for (int j = 0; j < cols; j++)
      grid[i][j] = Cell(i, j);
  }

  Stack<Cell>* callStack = new Stack<Cell>();

  grid[startX][startY].visited = true;
  
//Возьмем случайного соседа для начальной ячейки
//и положим этого соседа в стек

  int neightbours = EMPTY;
  int randomNeightbour;

  for (int i = 0; i < 4; ++i)
  {
    int x = startX + DX[i];
    int y = startY + DY[i];

    if (x > -1 && x < rows && y > -1 && y < cols)
      if (!grid[x][y].visited)
        neightbours += NEIGHTBOURS[i];
  }

  do
  {
    randomNeightbour = rand() % 4;
  } while ((neightbours & NEIGHTBOURS[randomNeightbour]) == 0);

  grid[startX][startY].neightbours += NEIGHTBOURS[randomNeightbour];

  int _x = startX + DX[randomNeightbour];
  int _y = startY + DY[randomNeightbour];

  grid[_x][_y].visited = true;

  callStack->push(grid[_x][_y]);

  do
  {
    Cell current = callStack->getTopLink();   //Изменяем
    neightbours = EMPTY;
    
    // проверяем,есть ли у нас соседи
    for (int i = 0; i < 4; ++i)
    {
      int x = current.x + DX[i];
      int y = current.y + DY[i];

      if (x > -1 && x < rows && y > -1 && y < cols)
        if (!grid[x][y].visited)
          neightbours += NEIGHTBOURS[i];
    }

    if (neightbours == EMPTY)
    {
      callStack->pop();
      continue;
    }

    // если есть,выбираем одного рандомного и кладем в стек
    do
    {
      randomNeightbour = rand() % 4;
    } while ((neightbours & NEIGHTBOURS[randomNeightbour]) == 0);

    grid[current.x][current.y].neightbours += NEIGHTBOURS[randomNeightbour];
    _x = current.x + DX[randomNeightbour];
    _y = current.y + DY[randomNeightbour];

    grid[_x][_y].visited = true;
    callStack->push(grid[_x][_y]);

  } while (!callStack->isEmpty());    //Изменяем

  int _rows = rows * 2 + 1;
  int _cols = cols * 2 + 1;

  //теперь у нас есть ссылки между ячейками, 
  //и нам нужно преобразовать их в нашу обычную сетку, которую мы собираемся вернуть
  
  char** resultGrid = new char* [_rows];
  for (int i = 0; i < _rows; ++i)
  {
    resultGrid[i] = new char[_cols];
    for (int j = 0; j < _cols; ++j)
      resultGrid[i][j] = WALL;
  }

  for (int gridI = 0, resultGridI = 1; gridI < rows; gridI++, resultGridI += 2)
  {
    for (int gridJ = 0, resultGridJ = 1; gridJ < cols; gridJ++, resultGridJ += 2)
    {
      for (int k = 0; k < 4; ++k)
      {
        if ((grid[gridI][gridJ].neightbours & NEIGHTBOURS[k]) != EMPTY)
        {
          resultGrid[resultGridI][resultGridJ] = ROAD;
          resultGrid[resultGridI + DX[k]][resultGridJ + DY[k]] = ROAD;
          resultGrid[resultGridI + 2 * DX[k]][resultGridJ + 2 * DY[k]] = ROAD;
        }
      }
    }
  }

  // очищаем память
  for (int i = 0; i < rows; ++i)
    delete[] grid[i];
  delete[] grid;
  delete callStack;

  return resultGrid;
}

static int level=1;
//Класс,отвечающий за игру,передвижение,прорисовку
class Game
{
private:
  static const short cols = 13; //x
  static const short rows = 15;  //y
  char mas[rows][cols];
  Point Ball_Coordinates;
  Point Start;
  Point Finish;
  char _direction;
public:
  Game();
  void ContinuousMove();
  void SetDirection(char);
  void Move();
  void Show();
};
void Game::SetDirection(char d)
{
  _direction = d;
}

Game::Game()
{
  //Serial.println("a");
  char** grid = GenerateMaze(0, 0, 7,6);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      mas[i][j] = grid[i][j];
    }
  }
  for (int i = 0; i < rows; ++i)
    delete[] grid[i];
  delete[] grid;
  Ball_Coordinates.x = Start.x = 1;
  Ball_Coordinates.y = Start.y = 1;
  Finish.x = 11;
  Finish.y = 13;
}
void Game::Show()
{
  //Рисуем лабиринт,мяч и финиш
  for (int i =0; i <rows; i++)
  {
      for (int j = 0; j <cols; j++) 
      {
      if (i == Ball_Coordinates.y && j == Ball_Coordinates.x)
      {
        tft.fillCircle((tft.width()-(17*(Ball_Coordinates.x+0.5))),(tft.height()-((17*(Ball_Coordinates.y+0.5)))),5,BLACK);       
      }
      else if(i==Finish.y && j==Finish.x)
          tft.fillRect(tft.width()-(j+1)*17,tft.height()-((i+1)*17),17,17,MAGENTA);
      else if (mas[i][j] == 1)
      {
       tft.fillRect(tft.width()-(j+1)*17,tft.height()-((i+1)*17),17,17,GREEN);
      }
      else if (mas[i][j] == 0)
       {       
        tft.fillRect(tft.width()-(j+1)*17,tft.height()-((i+1)*17),17,17,WHITE);
       }
   //Проверяем,дошел ли мяч до финиша,и есои да,генерируем новый массив
       if(Ball_Coordinates.x==11 && Ball_Coordinates.y==13)
       {
        Ball_Coordinates.x = 1;
        Ball_Coordinates.y = 1;
        level++;

        char** grid1 = GenerateMaze(0, 0, 7,6);
        for (int i = 0; i < rows; i++)
        {
          for (int j = 0; j < cols; j++)
          {
            mas[i][j] = grid1[i][j];
          }
          }
          for (int i = 0; i < rows; ++i)
            delete[] grid1[i];
            delete[] grid1;
//Рисуем экран с номером уровня и затем прорисовваем новый уровень
   tft.fillScreen(BLACK);  
   tft.setRotation(2);
   tft.setCursor(80,140);
   tft.println(" Level: " );
   tft.setCursor(130,140);
   tft.println(level);
   delay(2000);
   tft.setCursor(0,0);
   tft.setRotation(4); 
   tft.fillScreen(BLACK);
   tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
  tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);

    //для кнопки "a"
  //tft.setCursor(190,20);
   tft.fillRect(190,20,190,20,BLACK);
   tft.fillCircle(230,30,15,BLACK); 
    //для кнопки "w"
    //tft.setCursor(135,10);
    tft.fillRect(139,10,23,45,BLACK);
    tft.fillCircle(150,45,15,BLACK);
    //для кнопки "s"
    tft.fillRect(80,20,23,35,BLACK);
    tft.fillCircle(90,20,15,BLACK);
    //для кнопки "d"
    tft.fillRect(20,20,35,20,BLACK);
    tft.fillCircle(20,30,15,BLACK);
       }
    }
  }
}


  
void Game::Move()
{

  switch (_direction)
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

#define MINPRESSURE 10
#define MAXPRESSURE 1000

void setup(void) {
  // put your setup code here, to run once:
  tft.reset();
  uint16_t identifier = tft.readID();
  
  tft.begin(identifier);
 //Заливаме экран черным
   tft.fillScreen(BLACK);
 //поворачиваем экран 
   tft.setRotation(2);
   tft.setCursor(30,140);
   tft.println("The Game 'The ball in the maze'");
   delay(2000);
   tft.fillScreen(BLACK);
   
   tft.setCursor(80,140);
   tft.println(" Level: " );
   tft.setCursor(130,140);
   tft.println(level);
   delay(2000);
   tft.setCursor(0,0);
 //поворачиваем обратно
   tft.setRotation(4);
  //Заполняем экран черным цветом
  tft.fillScreen(BLACK);

//заливаем место для кнопок цветами
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
  tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);

    //для кнопки "a"
  //tft.setCursor(190,20);
   tft.fillRect(190,20,190,20,BLACK);
   tft.fillCircle(230,30,15,BLACK); 
    //для кнопки "w"
    //tft.setCursor(135,10);
    tft.fillRect(139,10,23,45,BLACK);
    tft.fillCircle(150,45,15,BLACK);
    //для кнопки "s"
    tft.fillRect(80,20,23,35,BLACK);
    tft.fillCircle(90,20,15,BLACK);
    //для кнопки "d"
    tft.fillRect(20,20,35,20,BLACK);
    tft.fillCircle(20,30,15,BLACK);
  pinMode(13, OUTPUT);
}
 Game ball;
void loop() {
  // put your main code here, to run repeatedly:

  ball.Show();

  digitalWrite(13, HIGH);
  //if(_kbhit())
  //{
  //Считываем нажатие на экран
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
    
 //переводим координаты точки в удобную нам систему координат
    p.x = tft.width()-(map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
    p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0)); 
    p.x= p.x+p.y;
    p.y=p.y-p.x;
    p.y=-p.y;
    p.x=p.x-p.y;
    p.x=tft.width()-p.x+BOXSIZE;
  //проверяем,нажал ли пользователь в области кнопок 
    if(p.y<BOXSIZE )
    {
    char button;
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    if (p.y < (TS_MINY-5)) {
      
      // press the bottom of the screen to erase 
     

   
      if(p.x<BOXSIZE)
      button='d';
      if(p.x>BOXSIZE && p.x<BOXSIZE*2)
      button='s';
      if(p.x>BOXSIZE*2 && p.x<BOXSIZE*3)
      button='w';
      if(p.x>BOXSIZE*3 && p.x<BOXSIZE*4)
      button='a';
      ball.SetDirection(button);
    }
    }
  }
  //}
     ball.Move();
 
    }
