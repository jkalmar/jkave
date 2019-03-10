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

#include "Shader.h"

#include "spdlog/spdlog.h"

Shader::Shader()
{

}

Shader::~Shader()
{
clean_up();
}



void Shader::use_program()
{
   // Load the shader into the rendering pipeline
   glUseProgram( shaderProgram );
}

bool Shader::init()
{
   // Generate our shader. This is similar to glGenBuffers() and glGenVertexArray(), except that this returns the ID
   shaderProgram = glCreateProgram();

   for( const auto& iAttrLoc : attrLoc )
   {
      glBindAttribLocation( shaderProgram, iAttrLoc.first, iAttrLoc.second.c_str() );
   }

   if( !init_vertex_shader() )
      return false;

   if( !init_fragment_shader() )
      return false;

   // All shaders has been create, now we must put them together into one large object
   return link_shaders();
}

bool Shader::init_vertex_shader()
{
   spdlog::info( "Preparing vertex shader" + vertextPath );

   std::string str = read_file( vertextPath.c_str() );

   char *src = const_cast<char *>( str.c_str() );
   int32_t size = str.length();

   vertexshader = glCreateShader( GL_VERTEX_SHADER );

   glShaderSource( vertexshader, 1, &src, &size );

   glCompileShader( vertexshader );

   int wasCompiled = 0;

   glGetShaderiv( vertexshader, GL_COMPILE_STATUS, &wasCompiled );

   if( wasCompiled == 0 )
   {
      spdlog::error( "Vertex shader cc err: " + shader_cc_err( vertexshader ) );
      return false;
   }

   glAttachShader( shaderProgram, vertexshader );
   return true;
}

bool Shader::init_fragment_shader()
{
   spdlog::info( "Preparing fragment shader" + fragmentPath );

   std::string str = read_file( fragmentPath.c_str() );

   char *src = const_cast<char *>( str.c_str() );
   int32_t size = str.length();

   fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

   glShaderSource( fragmentShader, 1, &src, &size );

   glCompileShader( fragmentShader );

   int wasCompiled = 0;
   glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &wasCompiled );

   if( wasCompiled == false )
   {
      spdlog::error( "Fragment shader cc err: " + shader_cc_err( fragmentShader ) );
      return false;
   }

   glAttachShader( shaderProgram, fragmentShader );
   return true;
}

bool Shader::link_shaders()
{
   // Link. At this point, our shaders will be inspected/optized and the binary code generated
   // The binary code will then be uploaded to the GPU
   glLinkProgram( shaderProgram );

   // Verify that the linking succeeded
   int isLinked;
   glGetProgramiv( shaderProgram, GL_LINK_STATUS, ( int * )&isLinked );

   if( isLinked == false )
      spdlog::error( "Shader linking err: " + shader_link_err( shaderProgram ) );

   return isLinked != 0;
}

void Shader::clean_up()
{
   glUseProgram( 0 );

   glDetachShader( shaderProgram, vertexshader );
   glDetachShader( shaderProgram, fragmentShader );
   if( geometryShader ) glDetachShader( shaderProgram, geometryShader );

   glDeleteProgram( shaderProgram );

   glDeleteShader( vertexshader );
   glDeleteShader( fragmentShader );
   if( geometryShader ) glDeleteShader( geometryShader );
}

void Shader::add_attr_location( int index, const std::string& attr )
{
   attrLoc.emplace_back( index, attr );
}

std::string Shader::read_file( const char *file )
{
   std::ifstream t( file );
   std::stringstream buffer;
   buffer << t.rdbuf();

   std::string ret = buffer.str();

   return ret;
}

std::string Shader::shader_link_err( GLuint shaderId )
{
   std::string ret;

   int theLen;
   glGetProgramiv( shaderId, GL_INFO_LOG_LENGTH, &theLen );

   char *theInfo = new char[theLen];
   glGetProgramInfoLog( shaderProgram, theLen, &theLen, theInfo );

   ret = theInfo;
   delete [] theInfo;

   return ret;
}

std::string Shader::shader_cc_err( GLuint shaderId )
{
   std::string ret;

   int theLen;
   glGetShaderiv( shaderId, GL_INFO_LOG_LENGTH, &theLen );

   // Get shader info log
   char *theInfo = new char[theLen];
   glGetShaderInfoLog( shaderId, theLen, &theLen, theInfo );

   ret = theInfo;
   delete [] theInfo;

   return ret;
}
