#include "menu.h"

// Init menu
menu::menu(){
  particle = tools::load_bitmap_ex("particle.png");
  perlin = tools::load_bitmap_ex("perlin_2.png");
  perlin_2 = tools::load_bitmap_ex("perlin_3.png");


}

// Destory menu
menu::~menu(){

}
// Update animation and wait for input
void menu::update(){


  r+=tools::random_int(-1,1);
  g+=tools::random_int(-1,1);
  b+=tools::random_int(-1,1);


  x+=tools::random_int(-1,1);
  y+=tools::random_int(-1,1);
  x1+=tools::random_int(-1,1);
  y1+=tools::random_int(-1,1);



  if(keyListener::key[ALLEGRO_KEY_A]){
   for(int i=0; i<30; i++){
      gamePixels.push_back(Pixel(mouseListener::mouse_x,mouseListener::mouse_y,((float)tools::random_int(-400,400)/100),((float)tools::random_int(-400,400)/100),particle));

    }
  }


  if(keyListener::key[ALLEGRO_KEY_G]){
   for(int i=0; i<10; i++){
      gamePixels.push_back(Pixel(mouseListener::mouse_x,mouseListener::mouse_y,((float)tools::random_int(-200,200)/100),((float)tools::random_int(-200,200)/100),particle));

    }
  }

   if(keyListener::key[ALLEGRO_KEY_Q]){
   for(int i=0; i<1; i++){
      gamePixels.push_back(Pixel(mouseListener::mouse_x,mouseListener::mouse_y,((float)tools::random_int(-200,200)/100),((float)tools::random_int(-200,200)/100),particle));

    }
  }

  angle+=1;

  if(mouseListener::mouse_button & 1){
   for(int i=0; i<50; i++){
      gamePixels.push_back(Pixel(mouseListener::mouse_x,mouseListener::mouse_y,cos(i)*((float)tools::random_int(170,230)/100),sin(i)*((float)tools::random_int(170,230)/100),particle));

    }


  }
//
  if(mouseListener::mouse_button & 2){
  for(int i=0; i<75; i++){
      gamePixels.push_back(Pixel(mouseListener::mouse_x,mouseListener::mouse_y,cos(i)*((float)tools::random_int(170,230)/100),sin(i)*((float)tools::random_int(170,230)/100)));

   }


  }
  if(keyListener::keyPressed[ALLEGRO_KEY_F]){
          gameSpawners.push_back(Spawner());

    }









  for(int i=0; i<gameSpawners.size(); i++){
    gameSpawners.at(i).update();
    for(int j=0; j<10; j++)
      gamePixels.push_back(Pixel((int)gameSpawners.at(i).getX(),(int)gameSpawners.at(i).getY(),cos(j)*((float)tools::random_int(170,230)/100),sin(j)*((float)tools::random_int(170,230)/100),particle));


  }

    for(int i=0; i<gamePixels.size(); i++){
    if(!gamePixels.at(i).update())
      gamePixels.erase(gamePixels.begin()+i);
  }


}

// Draw images to screen
void menu::draw(){



  // Background
  al_clear_to_color( al_map_rgb(r,g,b));

  al_draw_bitmap(perlin,x1,y1,0);
  al_draw_bitmap(perlin_2,x,y,0);



  for(int i=0; i<gamePixels.size(); i++){
    gamePixels.at(i).draw();
  }



}




