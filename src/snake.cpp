#include "snake.h"
#include "screen.h"

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{

}

void CSnake::paint() {
  CFramedWindow::paint();
  paintHelp();
}
void CSnake::paintHelp() {
  gotoyx(geom.topleft.y + 3, geom.topleft.x + 3);
  printl("%s", "h - toggle help");
  gotoyx(geom.topleft.y + 4, geom.topleft.x + 3);
  printl("%s", "p - pause");
  gotoyx(geom.topleft.y + 5, geom.topleft.x + 3);
  printl("%s", "r - restart");
  gotoyx(geom.topleft.y + 6, geom.topleft.x + 3);
  printl("%s", "arrows - move snake (play mode)");
  gotoyx(geom.topleft.y + 7, geom.topleft.x + 12);
  printl("%s","move window (pause mode)");
}
