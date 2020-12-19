#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include <ncurses.h>

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
};

#endif
