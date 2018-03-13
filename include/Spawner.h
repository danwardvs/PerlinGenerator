#ifndef SPAWNER_H
#define SPAWNER_H


#include "Pixel.h"
#include "tools.h"

class Spawner
{
  public:
    Spawner();
    virtual ~Spawner();

    void update();
    float getX(){return x;}
    float getY(){return y;}

  protected:

  private:
    float x=500;
    float y=500;
    float vel_x;
    float vel_y;

};

#endif // SPAWNER_H
