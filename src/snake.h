#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include <vector>

class CSnake:public CFramedWindow
{
public:
  CSnake(CRect r, char _c = ' ');
  void paint();
  bool handleEvent(int c);
private:
  unsigned int level;
  bool displayHelp;
  bool isPaused;
  void paintHelp();
  void paintPause();
  void paintLevel();
  void paintSnake();
  void paintFood();
  bool moveSnake(int c);
  int snakeDir;
  CPoint snakeHead;
  std::vector<CPoint> snakeBody;
  unsigned int bodyLength;
  CPoint food;
  void generateFood();
  void eatFood();
  void moveWithWindow(int c);
};

#endif
