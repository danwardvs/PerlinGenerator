/*
 * Main
 * Sets up Allegro stuffs
 * Calls state machine update and draw functions
 * 2017/11/14
 */
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <mouseListener.h>
#include <keyListener.h>

#include "init.h"
#include "state.h"
#include "menu.h"
#include "Noise.h"

// Current state object
state *currentState = nullptr;

// FPS system variables
int fps;
double old_time = 0;
const float MAX_FPS = 60;
int frames_array[100];
int frame_index = 0;

// Closing or naw
bool closing = false;
bool joystick_enabled = false;

// Allegro events
ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
ALLEGRO_TIMER* timer = nullptr;
ALLEGRO_DISPLAY *display = nullptr;

// Input listener wrapper classes
mouseListener m_listener;
keyListener k_listener;

// Delete game state and free state resources
void clean_up(){
  delete currentState;
}

// Change game screen
void change_state(){
  //If the state needs to be changed
  if( nextState != STATE_NULL ){
    //Delete the current state
    if( nextState != STATE_EXIT ){
      delete currentState;
    }

    //Change the state
    switch( nextState ){
      case STATE_INIT:
        currentState = new init();
        std::cout<<"Switched state to initialization.\n";
        break;
      case STATE_MENU:
        currentState = new menu();
        std::cout<<"Switched state to main menu.\n";
        break;

      case STATE_NOISE:
        currentState = new Noise();
        std::cout<<"Switched state to noise.\n";
        break;
      case STATE_EXIT:
        std::cout<<"Exiting program.\n";
        closing = true;
        break;
      default:
        currentState = new menu();
    }

    //Change the current state ID
    stateID = nextState;

    //NULL the next state ID
    nextState = STATE_NULL;
  }
}

// Setup game
void setup(){

  srand(time(NULL));

  std::cout<<"Initializing Allegro.";
  // Init allegro
  if( !al_init())
    tools::abort_on_error( "Allegro could not initilize", "Error");

  // Window title
  al_set_window_title(display,"Loading...");

  // Controls
  al_install_keyboard();
  al_install_mouse();

  // GFX addons
  al_init_image_addon();
  al_init_primitives_addon();

  // Font
  al_init_ttf_addon();


  // Aquire screen

  //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
  display = al_create_display(400, 300);
  Noise::setDisplay(display);

  if( !display)
    tools::abort_on_error( "Screen could not be created", "Error");

  // Timer
  timer = al_create_timer(1.0 / MAX_FPS);

  // Register events
  event_queue = al_create_event_queue();
  al_register_event_source( event_queue, al_get_display_event_source(display));
  al_register_event_source( event_queue, al_get_timer_event_source(timer));
  al_register_event_source( event_queue, al_get_keyboard_event_source());

  // Timer
  al_start_timer(timer);

  // Window title
  al_set_window_title(display,"Perlin Noise Generator");

  std::cout<<" Sucesss.\n";


  // Probably never going to be relevant but pretty cool anyways
  uint32_t version = al_get_allegro_version();
  int major = version >> 24;
  int minor = (version >> 16) & 255;
  int revision = (version >> 8) & 255;
  int release = version & 255;

  std::cout<<"Allegro version "<<major<<"."<<minor<<"."<<revision<<"."<<release<<"\n";

  // This is actually completely irrelevant other than making fun of Allan's PC when he runs this
  // Sorry, your PC is a very nice PC
  std::cout<<"Running as "<<al_get_app_name()<<", with "<<al_get_ram_size()<<" MB RAM.\n";

}

// Handle events
void update(){
  // Event checking
  ALLEGRO_EVENT ev;
  al_wait_for_event( event_queue, &ev);

  // Timer
  if( ev.type == ALLEGRO_EVENT_TIMER){
    // Change state (if needed)
    change_state();

    // Update listeners
    m_listener.update();
    k_listener.update();
    // Update state
    currentState -> update();
  }
  // Exit
  else if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
    closing = true;
  }
  // Keyboard
  else if( ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP){
    k_listener.on_event( ev.type, ev.keyboard.keycode);
  }

  // Drawing
  if( al_is_event_queue_empty(event_queue)){
    // Clear buffer
    al_clear_to_color( al_map_rgb(0,0,0));

    // Draw state graphics
    currentState -> draw();

    // Flip (OpenGL)
    al_flip_display();

    // Update fps buffer
    for( int i = 99; i > 0; i--)
      frames_array[i] = frames_array[i - 1];
    frames_array[0] = (1.0/(al_get_time() - old_time));
    old_time = al_get_time();

    int fps_total = 0;
    for( int i = 0; i < 100; i++)
      fps_total += frames_array[i];

    // FPS = average
    fps = fps_total/100;
   // al_set_window_title(display,tools::convertIntToString(fps).c_str());

  }
}

// Start here
int main(int argc, char **argv){

  if(argc>1){
    std::cout<<"WE SPECIFIED AN ARGUMENT!";




    Noise::setWidth(tools::convertStringToInt(argv[1]));

    if(argc>2)
        Noise::setHeight(tools::convertStringToInt(argv[2]));

    if(argc>3)
        Noise::setOctaveCount(tools::convertStringToInt(argv[3]));

    if(argc>4)
      Noise::setBackground(!(std::string(argv[4]) == "transparent"));


    if(argc>5)
        Noise::setPath(argv[5]);



    }




  }
  // Basic init
  setup();

  //Set the current state ID
  stateID = STATE_INIT;
  currentState = new init();

  // Run game
  while(!closing)
    update();

  // Destory display
  al_destroy_display(display);

  return 0;
}
