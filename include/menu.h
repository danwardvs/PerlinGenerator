/**
 * MENU
 * A.D.S. Games
 * 06/05/2017
**/
#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>

#include "keyListener.h"
#include "mouseListener.h"
#include "joystickListener.h"
#include "tools.h"
#include "state.h"
#include "Pixel.h"
#include "Spawner.h"

// Menu
class menu : public state{
  public:
    menu();
    virtual ~menu();

    void update();
    void draw();

  private:

    int r=100;
    int b=100;
    int g=100;
    int angle;
    float x=0;
    float y=0;
    float x1=0;
    float y1=0;
    std::vector<Pixel> gamePixels;
    std::vector<Spawner> gameSpawners;

    ALLEGRO_BITMAP *particle;
    ALLEGRO_BITMAP *perlin;
    ALLEGRO_BITMAP *perlin_2;






};

#endif // MENU_H
