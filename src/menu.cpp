#include "menu.h"

// Init menu
menu::menu(){

    menu_font = al_load_ttf_font( "calibri.ttf", 24, 0);
    width = Noise::getWidth();
    height = Noise::getHeight();
    path = Noise::getPath();
    background = Noise::getBackground();

}

// Destory menu
menu::~menu(){

}
// Update animation and wait for input
void menu::update(){
    if(keyListener::keyPressed[ALLEGRO_KEY_G]){
          set_next_state( STATE_NOISE);

    }



}

// Draw images to screen
void menu::draw(){
    al_clear_to_color(al_map_rgb(150,150,150));

    al_draw_textf(menu_font, al_map_rgb( 0, 0, 0), 25, 25, 0, "Welcome to Perlin Noise Generator!");

    al_draw_textf(menu_font, al_map_rgb( 0, 0, 0), 25, 60, 0, "Width: %i",width);
    al_draw_textf(menu_font, al_map_rgb( 0, 0, 0), 25, 95, 0, "Height: %i",height);
    al_draw_textf(menu_font, al_map_rgb( 0, 0, 0), 25, 130, 0, "Octave Count: %i",octave_count);
    if(background)
      al_draw_textf(menu_font, al_map_rgb( 0, 0, 0), 25, 165, 0, "Solid Background");
    else
        al_draw_textf(menu_font, al_map_rgb( 0, 0, 0), 25, 165, 0, "Transparent Background");

    al_draw_textf(menu_font, al_map_rgb( 0, 0, 0), 25, 200, 0, "Path: %s",path.c_str());

    al_draw_textf(menu_font, al_map_rgb( 0, 0, 0), 300, 250, 1, "Generate!(G)");




}




