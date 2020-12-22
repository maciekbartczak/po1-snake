#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include <vector>
#include <chrono>

class CSnake:public CFramedWindow {
public:
  CSnake(CRect r, char _c = ' ');
  void paint();
  bool handleEvent(int c);

private:
  unsigned int fps;
  unsigned int level;
  bool displayHelp;
  bool isPaused;
  bool gameOver;
  void paintHelp();
  void paintPause();
  void paintLevel();
  void paintSnake();
  void paintFood();
  void paintGameOver();
  bool moveSnake(int c);
  bool checkCollision();
  int snakeDir;
  CPoint snakeHead;
  std::vector<CPoint> snakeBody;
  unsigned int bodyLength;
  CPoint food;
  void generateFood();
  void eatFood();
  void moveWithWindow(int c);
  std::chrono::time_point<std::chrono::system_clock> t;
  void resetGame();
};

#endif
