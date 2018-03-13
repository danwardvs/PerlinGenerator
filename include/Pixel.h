#ifndef PIXEL_H
#define PIXEL_H

#include "allegro5/allegro_primitives.h"

#include "tools.h"

class Pixel
{
  public:
    Pixel(int,int,int);
    Pixel(int,int,float,float);
    Pixel(int,int,float,float,ALLEGRO_BITMAP *);


    virtual ~Pixel();

    void draw();
    bool update();

  protected:

  private:

    int r;
    int g;
    int b;
    int alpha=0;

    float x;
    float y;

    float vel_x;
    float vel_y;

    ALLEGRO_BITMAP *sprite=nullptr;

};

#endif // PIXEL_H
