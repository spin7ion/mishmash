#include <MiniQDriver.h>

void setup() { 
  MiniQDriver miniQ= *new MiniQDriver();
  miniQ.setModeSpeedPWM(MOVE_FORWARD,255);
  delay(1000);
  miniQ.setMode(STOP);//останавливаемся
  miniQ.setMode(MOVE_BACKWARD,false);//тележка едет назад
  delay(1000);//ничего не происходит  
  while(miniQ.renewConf())//вручную обновляем состояние
    delay(10);
  miniQ.setSpeedPWM(0);
  miniQ.setSpeedConvert(128,255);
  miniQ.setModeSpeedPercent(TURN_LEFT,25);//Задаём скорость в процентах, ШИМ=128+128*25/100=160
  delay(500);
  miniQ.setMode(STOP);//делаем паузу
  delay(1000);
  miniQ.setMode(TURN_LEFT);//возобновляем движение
  delay(500);  
  miniQ.setSpeedConvert(0,255);//восстанавливаем стандарное правило преобразования скорости
  miniQ.setModeSpeedPercent(TURN_RIGHT,100);//Задаём скорость в процентах, ШИМ=255
  delay(250);
  miniQ.setMode(STOP);//делаем паузу
  delay(1000);
  miniQ.setMode(TURN_RIGHT);//возобновляем движение
  delay(500);
  miniQ.setMode(STOP);//останавливаем тележку
  //!последняя команда важна, в противном случае тележка будет продолжать движение до отключения питания!
}
// the loop routine runs over and over again forever:
void loop() {
  
}
