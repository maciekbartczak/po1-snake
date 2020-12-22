#include "snake.h"
#include "screen.h"
#include <cstring>
#include <thread>
#include <ncurses.h>

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
  level = 1;
  isPaused = true;
  displayHelp = true;
  snakeHead.x = geom.topleft.x + (geom.size.x / 2) + 1;
  snakeHead.y = geom.topleft.y + (geom.size.y / 2);
  bodyLength = 0;
  food.x = geom.topleft.x + geom.size.x / 2;
  food.y = geom.topleft.y + 5;
  snakeDir = KEY_RIGHT;
  t = std::chrono::system_clock::now();
  fps = 15;
  gameOver = false;
}

void CSnake::paint() {
    CFramedWindow::paint();
    if(!gameOver){
      eatFood();
      paintFood();
      paintSnake();
      paintLevel();
      if(displayHelp){
        paintHelp();
      }
      if(isPaused){
        paintPause();
      }
    }else{
      paintGameOver();
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

  if(isPaused || gameOver){
      if(CFramedWindow::handleEvent(c)){
        moveWithWindow(c);
        return true;
      }
  }

  if( c == 'h'){
    displayHelp = !displayHelp;
    return true;
  }
  if( c == 'p' ){
    isPaused = !isPaused;
    return true;
  }
  if( c == 'r' ){
    resetGame();
    return true;
  }
  t += std::chrono::milliseconds(1000 / fps);
  this_thread::sleep_until(t);
  if( moveSnake(c) ){
    if ( checkCollision() ){
      gameOver = true;
    }
    return true;
  }
  if(!isPaused){
    moveSnake(snakeDir);
    if ( checkCollision() ){
      gameOver = true;
    }
    return true;
  }

  return false;
}

void CSnake::paintPause(){
  const char caption[] = "GAME PAUSED";
  gotoyx( geom.topleft.y + (geom.size.y / 2), geom.topleft.x + ((geom.size.x - std::strlen(caption)) / 2) );
  printl("%s", caption);
}

void CSnake::paintLevel() {
  gotoyx(geom.topleft.y - 1, geom.topleft.x);
  printl("| LEVEL %d | ",level);
}

void CSnake::paintSnake(){
  gotoyx(snakeHead.y,snakeHead.x);
  printc('*');
  for (auto & i : snakeBody){
    gotoyx(i.y,i.x);
    printc('S');
  }
}

void CSnake::paintFood(){
  gotoyx(food.y,food.x);
  printc('o');
}

bool CSnake::moveSnake(int c) {
  int deltaX = 0, deltaY = 0;
  switch(c){
  case KEY_UP:
    if(bodyLength > 0 && snakeDir == KEY_DOWN){
      return false;
    }
    deltaY = -1;
    break;
  case KEY_DOWN:
    if(bodyLength > 0 && snakeDir == KEY_UP){
      return false;
    }
    deltaY = 1;
    break;
  case KEY_RIGHT:
    if(bodyLength > 0 && snakeDir == KEY_LEFT){
      return false;
    }
    deltaX = 1;
    break;
  case KEY_LEFT:
    if(bodyLength > 0 && snakeDir == KEY_RIGHT){
      return false;
    }
    deltaX = -1;
    break;
  default:
    return false;
  }
  if( bodyLength == snakeBody.size() ){
    for (int i = 0; i < (int) snakeBody.size() - 1; i++){
      snakeBody[i] = snakeBody[i + 1];
    }
  }
  if(bodyLength >= 1){
    snakeBody.resize(bodyLength);
    snakeBody[bodyLength - 1] = snakeHead;
  }

  snakeHead.x = snakeHead.x + deltaX;
  snakeHead.y = snakeHead.y + deltaY;
  if (snakeHead.x == geom.topleft.x){
    snakeHead.x = geom.topleft.x + geom.size.x - 2;
  }
  if (snakeHead.y == geom.topleft.y){
    snakeHead.y = geom.topleft.y + geom.size.y - 2;
  }
  if (snakeHead.x == geom.topleft.x + geom.size.x - 1){
    snakeHead.x = geom.topleft.x + 1;
  }
  if (snakeHead.y == geom.topleft.y + geom.size.y - 1){
    snakeHead.y = geom.topleft.y + 1;
  }
  snakeDir = c;
  return true;
}
void CSnake::generateFood() {
  food.x = geom.topleft.x + 2 + rand() % (geom.size.x - 4);
  food.y = geom.topleft.y + 2 + rand() % (geom.size.y - 4);
  if (food.x == snakeHead.x && food.y == snakeHead.y){
    return generateFood();
  }
  for ( auto i : snakeBody){
    if (food.x == i.x && food.y == i.y){
      return generateFood();
    }
  }
}

void CSnake::eatFood() {
  if( snakeHead.x == food.x && snakeHead.y == food.y ){
    bodyLength++;
    level++;
    fps++;
    generateFood();
  }
}
void CSnake::moveWithWindow(int c) {
  int deltaX = 0, deltaY = 0;
  switch(c){
  case KEY_UP:
    deltaY = -1;
    break;
  case KEY_DOWN:
    deltaY = 1;
    break;
  case KEY_RIGHT:
    deltaX = 1;
    break;
  case KEY_LEFT:
    deltaX = -1;
    break;
  }
  snakeHead.x += deltaX;
  snakeHead.y += deltaY;
  for( auto &i : snakeBody){
    i.x += deltaX;
    i.y += deltaY;
  }
  food.x += deltaX;
  food.y += deltaY;
}

void CSnake::paintGameOver() {
  const char caption[] = "GAME OVER, YOUR SCORE: ";
  gotoyx( geom.topleft.y + (geom.size.y / 2), geom.topleft.x + ((geom.size.x - (std::strlen(caption) + std::to_string(level).size())) / 2) );
  printl("%s%d", caption,level);
}
bool CSnake::checkCollision() {
  for (auto i : snakeBody){
    if (snakeHead.x == i.x && snakeHead.y == i.y){
      return true;
    }
  }
  return false;
}

void CSnake::resetGame() {
  gameOver = false;
  displayHelp = false;
  isPaused = false;
  fps = 15;
  level = 1;
  bodyLength = 0;
  snakeBody.clear();
  snakeHead.x = geom.topleft.x + (geom.size.x / 2) + 1;
  snakeHead.y = geom.topleft.y + (geom.size.y / 2);
  food.x = geom.topleft.x + geom.size.x / 2;
  food.y = geom.topleft.y + 5;
  snakeDir = KEY_RIGHT;
}
