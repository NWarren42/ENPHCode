// canvas.h


#ifndef CANVAS_H
#define CANVAS_H


#include <vector>
#include "headers.h"
#include "main.h"
#include "compute.h"
#include "texture.h"
#include "filter.h"
#include "seq.h"
#include "gpuProgram.h"
#include "drawSegs.h"


// Show 6 images: 3 spatial and 3 corresponding spectral

class Canvas {

  unsigned int canvasWidth, canvasHeight;
  unsigned int imageWidth,  imageHeight;

  string imageFilename;
  string filterFilename;

  static char *vertexShader;
  static char *fragmentShader;
  GPUProgram  *GPUProg;

  Segs *segs;

  Compute *compute;

  bool showMagnitude;
  bool logScale;
  bool histoEq;
  
  bool mouseDragging;
  bool mouseMoved;
  vec2 initMousePosition;

  char editMode;
  float editRadius;

  mat4 accumulatedTransform;    // all transforms so far, in one matrix
  mat4 recentMovementTransform; // most recent transform made during a movement edit

  enum { TRANSLATE, SCALE } mouseMode;

 public:

  Texture *image;      // original image
  Texture *imageFT;    // FT of original image
  Texture *filter;     // filter image
  Texture *filterFT;   // FT of filter image
  Texture *result;     // result image
  Texture *resultFT;   // FT of result image

  Filter  *floatFilter;

  Canvas( unsigned int c_width, unsigned int c_height, unsigned int i_width, unsigned int i_height, string _imageFilename, string _filterFilename, Compute *_compute ) {

    canvasWidth  = c_width;
    canvasHeight = c_height;

    imageWidth  = i_width;
    imageHeight = i_height;

    imageFilename  = (_imageFilename.substr(  _imageFilename.find_last_of("/")  + 1 )); // use only the base filename
    filterFilename = (_filterFilename.substr( _filterFilename.find_last_of("/") + 1 ));

    GPUProg = new GPUProgram();
    GPUProg->init( vertexShader, fragmentShader, "canvas" );

    segs = new Segs();

    showMagnitude = true;
    logScale = true;
    histoEq = false;
    mouseDragging = false;

    editMode = 'S';
    editRadius = 10;

    accumulatedTransform = identity4();
    recentMovementTransform = identity4();

    compute = _compute;

    // Set up texture for the six images shown
    //
    // Note that the actual data is stored in the Compute instance.
    // These textures are copied from that data and used only for display.
    
    image    = new Texture( i_width, i_height );
    imageFT  = new Texture( i_width, i_height );
    filter   = new Texture( i_width, i_height );
    filterFT = new Texture( i_width, i_height );
    result   = new Texture( i_width, i_height );
    resultFT = new Texture( i_width, i_height );

    // Put the initial compute data into the textures
    
    copyToTexture( compute->image,  image,  false, false );  // false = !isFT, false = !isFilter
    copyToTexture( compute->filter, filter, false, true );   // false = !isFT, true  = isFilter

    image->updated = false;
    filter->updated = false;
  }

  void getRegionScale( float &imageScale, float &xScale, float &yScale, vec2 &ll, vec2 &ur);
  void draw();
  void drawBox( vec2 ll, vec2 ur );
  void copyToTexture( ComplexArray2D *c, Texture *t, bool isFT, bool isFilter );
  
  void startMouseMotion( float x, float y, int button, int mods );
  void mouseMotion( float x, float y );
  void stopMouseMotion();
  bool findMouseInImageFT( float &imageX, float &imageY );
  void keyPress( int key );

  void reshape( unsigned int width, unsigned int height ) {
    canvasWidth = width;
    canvasHeight = height;
  }
};


#endif
