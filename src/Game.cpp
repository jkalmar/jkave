/*
 * Copyright (c) 2019 jkalmar <janko.kalmar@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Game.h"

#include "Utils.h"

#include <spdlog/spdlog.h>

#include <SDL2/SDL.h>

#include <glm/glm.hpp>

void Game::init()
{
   /* Initialize SDL */
   SDL_LOG_ERR( ! _env.init() );

   _color.r = 0.0;
   _color.g = 0.0;
   _color.b = 0.0;
   _color.a = 1.0;
}

void Game::deinit()
{
   /* Deinitialize everything */
   _env.deinit();
}

void Game::main_loop()
{

   while( _running )
   {
      glClearColor( _color.r, _color.g, _color.b, _color.a );
      glClear( GL_COLOR_BUFFER_BIT );

      handle_input();
      render();


      /* Place your simulation code and rendering code here */
      SDL_GL_SwapWindow( _env.get_window() );
   }
}

void Game::handle_input()
{
   SDL_Event e;

   while( SDL_PollEvent( &e ) != 0 )
   {
      if( e.type == SDL_QUIT )
      {
         _running = false;
      }

      // Also check if the type of event is SDL_KEYDOWN that means the user pressed the button( the button is down )
      if( e.type == SDL_KEYDOWN )
      {
         // SDL has some defines to check keysym agains
         switch( e.key.keysym.sym )
         {
         case SDLK_UP:
            spdlog::info( "Up button pressed" );
            _color = glm::vec4( 1.0, 0.0, 0.0, 1.0 );
            break;

         case SDLK_DOWN:
            spdlog::info( "Down button pressed" );
            _color = glm::vec4( 0.0, 1.0, 0.0, 1.0 );
            break;

         case SDLK_LEFT:
            spdlog::info( "Left button pressed" );
            _color = glm::vec4( 0.0, 0.0, 1.0, 1.0 );

            break;

         case SDLK_RIGHT:
            spdlog::info( "Right button pressed" );
            _color = glm::vec4( 1.0, 1.0, 1.0, 1.0 );

            break;

         case SDLK_SPACE:
            spdlog::info( "Space button pressed" );
            break;

         case SDLK_p:
            spdlog::info( "P button pressed" );
            _paused = !_paused;
            break;

         case SDLK_ESCAPE:
            spdlog::info( "ESC button pressed" );
            _running = false;
            break;
         }
      }
   }
}

void Game::render()
{
}


