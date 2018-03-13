#include "Spawner.h"

Spawner::Spawner()
{
  //ctor
}

Spawner::~Spawner()
{
  //dtor
}
void Spawner::update(){

    x+=vel_x;
    y+=vel_y;

    vel_x+=(float)tools::random_int(-10,10)/100;
    vel_y+=(float)tools::random_int(-10,10)/100;

    if(x>1024)
      vel_x=-vel_x;
    if(0>x)
      vel_x=-vel_x;
    if(y>768)
      vel_y=-vel_y;
    if(0>y)
      vel_y=-vel_y;



}
