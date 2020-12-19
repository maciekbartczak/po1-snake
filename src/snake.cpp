#include "snake.h"
#include "screen.h"
#include <cstring>

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
  level = 1;
  isPaused = true;
  displayHelp = true;
}

void CSnake::paint() {
    CFramedWindow::paint();
    paintLevel();
    if(displayHelp){
      paintHelp();
    }
    if(isPaused){
      paintPause();
    }
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
bool CSnake::handleEvent(int c) {
  if(isPaused){
      if(CFramedWindow::handleEvent(c)){
        return true;
      }
  }
  if( c == 'h'){
    displayHelp = !displayHelp;
  }
  if( c == 'p' ){
    isPaused = !isPaused;
  }
  return true;
}

void CSnake::paintPause(){
  const char caption[] = "GAME PAUSED";
  gotoyx( geom.topleft.y + (geom.size.y / 2), geom.topleft.x + ((geom.size.x - std::strlen(caption)) / 2) );
  printl("%s", caption);
}

void CSnake::paintLevel() {
  gotoyx(geom.topleft.y - 1, geom.topleft.x);
  printl("| LEVEL %d |",level);
}