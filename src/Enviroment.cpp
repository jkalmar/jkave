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

#include "Enviroment.h"
#include "Utils.h"

#include <iostream>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "spdlog/spdlog.h"


Enviroment::Enviroment()
{

}

Enviroment::~Enviroment()
{
}

bool Enviroment::init()
{
   SDL_Init( SDL_INIT_EVERYTHING );
   IMG_Init( IMG_INIT_PNG );
   TTF_Init();

   _window = SDL_CreateWindow( "jcave",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH, WINDOW_HEIGHT,
                               SDL_WINDOW_OPENGL );

   _gl_context = SDL_GL_CreateContext( _window );

   set_opengl_attrs();

   glewExperimental = GL_TRUE;
   glewInit();

   return _window && _gl_context;
}

bool Enviroment::deinit()
{
   SDL_GL_DeleteContext( _gl_context );
   SDL_DestroyWindow( _window );

   TTF_Quit();
   IMG_Quit();
   SDL_Quit();

   return true;
}

void Enviroment::set_opengl_attrs()
{
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
   SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

   SDL_GL_SetSwapInterval( 1 );
}


SDL_Window *Enviroment::get_window()
{
   return _window;
}

std::string Enviroment::get_env_path( const std::string &subDir )
{
   const char PATH_SEP = '/';

   static std::string baseRes;

   if( baseRes.empty() )
   {
      char *basePath = SDL_GetBasePath();

      if( basePath )
      {
         baseRes = basePath;
         SDL_free( basePath );
      }
      else
      {
         std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
         return "";
      }

      //We replace the last bin/ with res/ to get the the resource path
      size_t pos = baseRes.rfind( "build" );
      baseRes = baseRes.substr( 0, pos ) + "res" + PATH_SEP;
   }

   return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture *Enviroment::load_texture( const std::string &file, SDL_Renderer *ren )
{
   SDL_Texture *texture = IMG_LoadTexture( ren, file.c_str() );

   SDL_LOG_ERR( texture == nullptr );


   return texture;
}

