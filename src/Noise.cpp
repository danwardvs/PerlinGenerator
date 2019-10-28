#include "Noise.h"

// Init Noise
Noise::Noise(){

  std::cout<<"Starting generation\n";

  sprite = tools::load_bitmap_ex("pixel.png");


  int width=800;
  int height=600;

  float octaveCount = 6.5;

  for(int i=0; i<octaveCount; i++){
    std::cout<<"Generated octave "<<i<<" of "<<octaveCount<<".\n";
    smooth_noise.push_back(generate_smooth_noise(width,height,pow(2,i)));
  }


  float persistance = 0.5f;

  float amplitude=1;
  float totalAmplitude=0;

  perlin_noise.resize(width,std::vector<float>(height,0));


  for(int i=octaveCount-1;i>0;i--){
    amplitude *= persistance;
    totalAmplitude += amplitude;
    std::cout<<"Blended octave "<<i<<" of "<<octaveCount<<".\n";


    for(int j=0; j<width; j++){
      for(int k=0; k<height; k++){
        perlin_noise[j][k] += smooth_noise[i][j][k] * amplitude;
      }

    }

  }
  std::cout<<"Normalizing\n";
  for(int i=0;i<width;i++){
    for(int j=0; j<height;j++){
      perlin_noise[i][j] /= totalAmplitude;
    }
  }

    std::cout<<"Drawing\n";

    ALLEGRO_BITMAP *oldTarget;
    oldTarget = al_get_target_bitmap();
    generated_bitmap = al_create_bitmap(width,height);

    al_set_target_bitmap(generated_bitmap);
    al_draw_filled_rectangle(0,0,width,height, al_map_rgb(255,255,255));

   for(int i=0;i<perlin_noise.size();i++){

    for(int j=0; j<perlin_noise[0].size();j++){
      //std::cout<<"Drawing row "<<i<<", column "<<j<<" of "<<perlin_noise.size()<<".\n";

      //al_put_blended_pixel(i,j,al_map_rgba_f(perlin_noise[i][j],perlin_noise[i][j],perlin_noise[i][j],perlin_noise[i][j]));
        al_draw_tinted_bitmap(sprite,al_map_rgba_f(perlin_noise[i][j],perlin_noise[i][j],perlin_noise[i][j],perlin_noise[i][j]),i,j,0);

    }
  }
  al_save_bitmap("perlin.png",generated_bitmap);

  al_set_target_bitmap(oldTarget);



}



// Destory Noise
Noise::~Noise(){

}
// Update animation and wait for input
void Noise::update(){



}
std::vector<std::vector<float>> Noise::generate_white_noise(int newWidth, int newHeight){

  std::vector<std::vector<float>> newWhiteNoise;
  newWhiteNoise.resize(newWidth,std::vector<float>(newHeight,0));

  for(int i=0;i<newWidth;i++){
    for(int j=0; j<newHeight;j++){
      newWhiteNoise[i][j]=((float)tools::random_int(2,1000))/1000;
    }
  }

  return newWhiteNoise;

}

std::vector<std::vector<float>> Noise::generate_smooth_noise(int newWidth,int newHeight,int newWavelength){

  std::vector<std::vector<float>> newWhiteNoise = generate_white_noise(newWidth,newHeight);

  std::vector<std::vector<float>> newSmoothNoise;
  newSmoothNoise.resize(newWidth,std::vector<float>(newHeight,0));


  int samplePeriod = newWavelength;
  float sampleFrequency = 1.0f/((float)samplePeriod);


  for(int i=0;i<newWidth;i++){

    int sample_i0 = (i/samplePeriod) * samplePeriod;
    int sample_i1 = (sample_i0 + samplePeriod) % newWidth;
    float horizontal_blend = (float)(i - sample_i0) * sampleFrequency;

    for(int j=0; j<newHeight;j++){

      int sample_j0 = (j/samplePeriod) * samplePeriod;
      int sample_j1 = (sample_j0 + samplePeriod) % newHeight;
      float vertical_blend = (float)(j - sample_j0) * sampleFrequency;


      float top = tools::interpolate(newWhiteNoise[sample_i0][sample_j0],newWhiteNoise[sample_i1][sample_j0],
      horizontal_blend);

      float bottom = tools::interpolate(newWhiteNoise[sample_i0][sample_j1],newWhiteNoise[sample_i1][sample_j1],
      horizontal_blend);


     newSmoothNoise[i][j]=tools::interpolate(top,bottom,vertical_blend);



    }
  }
  return newSmoothNoise;
  std::cout<<"done generating\n";

}

// Draw images to screen
void Noise::draw(){



  // Background
  al_clear_to_color( al_map_rgb(0,0,0));
  al_draw_bitmap(generated_bitmap,0,0,0);




}




