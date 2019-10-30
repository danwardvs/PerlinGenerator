/**
 * Noise
 * A.D.S. Games
 * 06/05/2017
**/
#ifndef Noise_H
#define Noise_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <vector>

#include "keyListener.h"
#include "mouseListener.h"
#include "tools.h"
#include "state.h"

// Noise
class Noise : public state{
  public:
    Noise();
    virtual ~Noise();

    void update();
    void draw();

    static void setParams(int newWidth, int newHeight, float newOctaveCount);
    static void setDisplay(ALLEGRO_DISPLAY *newDisplay);
  private:

    std::vector<std::vector<float>>  generate_white_noise(int,int);


    std::vector<std::vector<float>> perlin_noise;
    //float white_noise [width][height];
    std::vector<std::vector<std::vector<float>>> smooth_noise;
    std::vector<std::vector<float>> generate_smooth_noise(int,int,int);

    ALLEGRO_BITMAP *sprite;
    ALLEGRO_BITMAP *generated_bitmap;

    static int width;
    static int height;
    static int octave_count;
    static ALLEGRO_DISPLAY *display;




};

#endif // Noise_H
