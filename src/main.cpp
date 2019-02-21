#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

#include "spdlog/spdlog.h"

#include "Enviroment.h"
#include "Utils.h"

#include "Game.h"



int main( int argc, char **argv )
{
   (void)argc;
   (void)argv;

   Game theGame;

   theGame.init();
   theGame.main_loop();
   theGame.deinit();

   spdlog::info( "Resource path is: {}", Enviroment::get_env_path() );

   return 0;
}
