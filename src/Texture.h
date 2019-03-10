/*
 * Copyright (c) 2019 jkalmar <email>
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

#ifndef TEXTURE_H
#define TEXTURE_H

#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL2/SDL.h>

/**
 * @todo write docs
 */
class Texture
{
public:
   /**
    * Default constructor
    */
   Texture();

   /**
    * Destructor
    */
   ~Texture();

   bool init();

   void render();


   GLuint vao[1];
   GLuint vbo[2];

   uint32_t points;
   uint16_t valsPerPoint;
   uint16_t valsPerColor;

   uint32_t positionAttributeIndex = 0;
   uint32_t colorAttributeIndex = 1;
};

#endif // TEXTURE_H
