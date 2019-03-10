/*
 * Copyright (c) 2019 jkalmar <janko.kalmar@google.com>
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

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

/**
 * @todo write docs
 */
class Shader
{
public:
   Shader();
   ~Shader();

   void use_program();
   bool init();

   void clean_up();

   std::string vertextPath;
   std::string fragmentPath;
   std::string geometryPath;

   void add_attr_location( int index, const std::string &attr );

private:
   bool init_vertex_shader();
   bool init_fragment_shader();
   bool link_shaders();

   std::string read_file( const char *file );
   std::string shader_link_err( GLuint shaderId );
   std::string shader_cc_err( GLuint shaderId );

   // The handle to our shader program
   GLuint shaderProgram = 0;

   // The handles to the induvidual shader
   GLuint vertexshader = 0;
   GLuint fragmentShader = 0;
   GLuint geometryShader = 0;

   std::vector< std::pair< int, std::string > > attrLoc;
};

#endif // SHADER_H
