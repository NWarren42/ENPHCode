// texture.h


#ifndef TEXTURE_H
#define TEXTURE_H

#include "headers.h"
#include "gpuProgram.h"


#define TEX_UNIT_ID 0 // texture unit to use for full-window texture


typedef struct { unsigned char r, g, b, a; } Pixel;


class Texture {

  static char *vertexShader;
  static char *fragmentShader;
  GPUProgram  *GPUProg;

  void registerWithOpenGL();
  void loadTexture( string filename );

  bool registeredWithOpenGL; // true once texture is registerd with OpenGL

 public:

  GLubyte *texmap; 

  string name;
  GLuint textureID;
  unsigned int width, height;
  bool hasAlpha;
  bool updated; // true if texture was changed.  forces a re-transmission to the GPU.

  static bool useMipMaps;

  Texture() {
    GPUProg = NULL;
    texmap = NULL;
    updated = false;
  }

  // texture from file

  Texture( string filename ) {

    loadTexture( filename ); // sets 'texmap'

    name = filename;
    GPUProg = NULL;
    registeredWithOpenGL = false;
    updated = false;
  }

  // Texture from file, placed in array of given size

  Texture( string filename, unsigned int _width, unsigned int _height ) {

    Texture t(filename); // load temporary copy from file

    if (t.width > _width || t.height > _height) {
      cerr << "Image " << filename << " is too large (" << t.width << " x " << t.height
	   << " ) to fit within array of size " << _width << " x " << _height << "." << endl;
      exit(1);
    }

    // Re-position

    width  = _width;
    height = _height;
    createEmptyTexture();

    unsigned int xOffset = (width  - t.width)  / 2;
    unsigned int yOffset = (height - t.height) / 2;

    for (unsigned int x=0; x<t.width; x++)
      for (unsigned int y=0; y<t.height; y++)
	pixel( x+xOffset, y+yOffset ) = t.pixel( x, y );

    // Done
    
    name = filename;
    GPUProg = NULL;
    registeredWithOpenGL = false;
    updated = false;
  }

  

  // empty texture
  
  Texture( unsigned int texWidth, unsigned int texHeight ) {

    name = "texture";
    width = texWidth;
    height = texHeight;
    createEmptyTexture(); // sets 'texmap'
    GPUProg = NULL;
    registeredWithOpenGL = false;
    updated = false;
  }

  // copy constructor

  Texture( Texture &t ) {

    width    = t.width;
    height   = t.height;
    hasAlpha = t.hasAlpha;
    name     = t.name;
    
    texmap = new GLubyte[ width * height * (hasAlpha ? 4 : 3) ];
    memcpy( texmap, t.texmap, width * height * (hasAlpha ? 4 : 3) );

    // must register this as a new texture, at which time 'GPUProg'
    // and 'textureID' will be set

    GPUProg = NULL;
    registeredWithOpenGL = false;
    updated = false;
  }

  // Reference elements as a(x,y)
  
  unsigned char & operator()( int x, int y ) {
    return texmap[ x + width * y ];
  }

  // destructor

  ~Texture() {

    if (texmap != NULL)
      delete [] texmap;

    if (GPUProg != NULL)
      delete GPUProg;
  }

  void activate( int textureUnit ) {
    
    if (!registeredWithOpenGL) {
      GPUProg = new GPUProgram();
      GPUProg->init( vertexShader, fragmentShader, "texture" );
      registerWithOpenGL();
      registeredWithOpenGL = true;
    }

    glActiveTexture( GL_TEXTURE0 + textureUnit );
    glBindTexture( GL_TEXTURE_2D, textureID );
    if (hasAlpha) {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else
      glDisable(GL_BLEND);
  }

  void deactivate( int textureUnit ) {
    glBindTexture( GL_TEXTURE_2D, 0 );
  }


  void createEmptyTexture();
  void draw( vec2 lowerLeft, vec2 upperRight, vec2 texLL, vec2 texUR );
  void copyImageFrom( Texture *src );

  Pixel & pixel( int x, int y );

  float toLuminance( Pixel &p );
};


#endif
