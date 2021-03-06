/**
 * MENU
 * Danny Van Stemp
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
#include "tools.h"
#include "state.h"
#include "Noise.h"

// Menu
class menu : public state{
  public:
    menu();
    virtual ~menu();

    void update();
    void draw();

  private:

    ALLEGRO_FONT *menu_font;
    int width=800;
    int height=600;
    int octave_count=7;
    std::string path;
    bool background;





};

#endif // MENU_H
