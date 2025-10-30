// canvas.cpp


#include "canvas.h"
#include "filter.h"
#include "main.h"
#include "compute.h"
#include "gpuProgram.h"
#include "strokefont.h"

#include <sstream>


// The following are measured in pixels:

#define BORDER_PIXELS 20 // blank border around each image
#define TEXT_HEIGHT   16 // height of text
#define TEXT_MARGIN   10 // distance from image to text above


// Get the scale factor for mapping images into their areas on the
// screen.  Also get the ll and ur image corners on the screen.

void Canvas::getRegionScale( float &imageScale, float &xScale, float &yScale, vec2 &ll, vec2 &ur)

{
  // Find dimensions (in pixels) of each of six regions in 2 row x 3 column grid

  vec2 regionDim( canvasWidth / 3.0  -  2*BORDER_PIXELS, 
		  canvasHeight / 2.0 - (2*BORDER_PIXELS + TEXT_HEIGHT + TEXT_MARGIN) );

  // Find the space occupied by an image, including its border and title text
  
  vec2 imageDim( image->width, image->height );

  // Find how much the image should be scaled to fit in its region

  float extraPixelsInX;
  float extraPixelsInY;

  if (regionDim.x / imageDim.x < regionDim.y / imageDim.y) {
    imageScale = regionDim.x / imageDim.x;
    extraPixelsInX = 0;
    extraPixelsInY = regionDim.y - imageScale * imageDim.y;
  } else {
    imageScale = regionDim.y / imageDim.y;
    extraPixelsInX = regionDim.x - imageScale * imageDim.x;
    extraPixelsInY = 0;
  }

  // Find corners lower-left and upper-right (in pixels) of image within each region

  ll = vec2( BORDER_PIXELS + extraPixelsInX/2, BORDER_PIXELS + extraPixelsInY/2 );
  
  ur = ll + imageScale * imageDim;

  // Convert pixel coordinates to window coordinates in [-1,1]x[-1,1]

  xScale = 2.0 / (float) canvasWidth;
  yScale = 2.0 / (float) canvasHeight;

  regionDim = vec2( regionDim.x * xScale, regionDim.y * yScale );
  ll        = vec2( ll.x        * xScale, ll.y        * yScale );
  ur        = vec2( ur.x        * xScale, ur.y        * yScale );
}



// Draw the six images in a 2 row x 3 column grid:
//
//        image    filter    result
//
//       imageFT  filterFT  resultFT

void Canvas::draw()

{
  float imageScale, xScale, yScale;
  vec2  ll, ur;
  
  getRegionScale( imageScale, xScale, yScale, ll, ur );

  // Apply transform to texture coordinates

  mat4 Tinv = (recentMovementTransform * accumulatedTransform).inverse();
  
  vec3 texLL3 = (Tinv * vec4(0,0,0,1)).toVec3();
  vec3 texUR3 = (Tinv * vec4(1,1,0,1)).toVec3();

  vec2 texLL( texLL3.x, texLL3.y );
  vec2 texUR( texUR3.x, texUR3.y );

  // Draw images

  image->draw(     vec2( -1.000+ll.x,  0+ll.y ), vec2( -1.000+ur.x,  0+ur.y ), texLL, texUR );
  imageFT->draw(   vec2( -1.000+ll.x, -1+ll.y ), vec2( -1.000+ur.x, -1+ur.y ), texLL, texUR );

  filter->draw(    vec2( -0.333+ll.x,  0+ll.y ), vec2( -0.333+ur.x,  0+ur.y ), texLL, texUR );
  filterFT->draw(  vec2( -0.333+ll.x, -1+ll.y ), vec2( -0.333+ur.x, -1+ur.y ), texLL, texUR );

  result->draw(    vec2(  0.333+ll.x,  0+ll.y ), vec2(  0.333+ur.x,  0+ur.y ), texLL, texUR );
  resultFT->draw(  vec2(  0.333+ll.x, -1+ll.y ), vec2(  0.333+ur.x, -1+ur.y ), texLL, texUR );
  
  // Draw boxes around images

  drawBox( vec2( -1.000+ll.x,  0+ll.y ), vec2( -1.000+ur.x,  0+ur.y ) );
  drawBox( vec2( -1.000+ll.x, -1+ll.y ), vec2( -1.000+ur.x, -1+ur.y ) );

  drawBox( vec2( -0.333+ll.x,  0+ll.y ), vec2( -0.333+ur.x,  0+ur.y ) );
  drawBox( vec2( -0.333+ll.x, -1+ll.y ), vec2( -0.333+ur.x, -1+ur.y ) );

  drawBox( vec2(  0.333+ll.x,  0+ll.y ), vec2(  0.333+ur.x,  0+ur.y ) );
  drawBox( vec2(  0.333+ll.x, -1+ll.y ), vec2(  0.333+ur.x, -1+ur.y ) );
  
  // Draw image titles

  string title;

  strokeFont->drawStrokeString( imageFilename.c_str(),                       -1.000+ll.x,  0+ur.y+TEXT_MARGIN*yScale, TEXT_HEIGHT*yScale, 0, LEFT );
  strokeFont->drawStrokeString( (string("FT of ") + imageFilename).c_str(),  -1.000+ll.x, -1+ur.y+TEXT_MARGIN*yScale, TEXT_HEIGHT*yScale, 0, LEFT );

  strokeFont->drawStrokeString( filterFilename.c_str(),                      -0.333+ll.x,  0+ur.y+TEXT_MARGIN*yScale, TEXT_HEIGHT*yScale, 0, LEFT );
  strokeFont->drawStrokeString( (string("FT of ") + filterFilename).c_str(), -0.333+ll.x, -1+ur.y+TEXT_MARGIN*yScale, TEXT_HEIGHT*yScale, 0, LEFT );
    
  strokeFont->drawStrokeString( "inverse FT of product",                      0.333+ll.x,  0+ur.y+TEXT_MARGIN*yScale, TEXT_HEIGHT*yScale, 0, LEFT );
  strokeFont->drawStrokeString( "product of FTs",                             0.333+ll.x, -1+ur.y+TEXT_MARGIN*yScale, TEXT_HEIGHT*yScale, 0, LEFT );

  // Draw status messages

  strokeFont->drawStrokeString( (showMagnitude ? "showing magnitudes" : "showing phases"),
				0.98, -0.98, TEXT_HEIGHT*yScale, 0, RIGHT ); // lower-right

  strokeFont->drawStrokeString( (logScale ? "FT log scaling" : "FT unscaled"), 
				-0.98, -0.98, TEXT_HEIGHT*yScale, 0, LEFT ); // lower-left

  char msg[1000];
  sprintf( msg, "edit: %s in radius %.1f", (editMode == 'A' ? "add" : "subtract"), editRadius );
  strokeFont->drawStrokeString( msg,
				0, -0.98, TEXT_HEIGHT*yScale, 0, CENTRE ); // lower-left
}




// Copy complex array to texture image with RGB values in [0,255]


void Canvas::copyToTexture( ComplexArray2D *c, Texture *t, bool isFT, bool isFilter )

{
  bool shiftToCentre = isFT;
  bool applyLogScale = isFT && logScale;
  bool normalize     = isFT || isFilter;
  
  // Check for matching arrays

  if (c->dimX != (int) t->width || c->dimY != (int) t->height) {
    cerr << "Canvas::copyToTexture: array dimensions do not match: " << c->dimX << " x " << c->dimY << " and " << t->width << " x " << t->height << endl;
    exit(1);
  }

  // Find min and max by which to normalize complex values for display

  float min, max;
  
  if (normalize) {

    min = MAXFLOAT;
    max = -MAXFLOAT;
    
    for (int x=0; x<c->dimX; x++)
      for (int y=0; y<c->dimY; y++) {

	float val;

	if (isFT)
	  val = (showMagnitude ? abs((*c)(x,y)) : arg((*c)(x,y)));
	else
	  val = ((*c)(x,y)).real();

	if (applyLogScale)
	  val = logf( 1 + val );

	if (val < min) min = val;
	if (val > max) max = val;
      }

    if (min == max)
      max = min+1; // avoid division by zero in image of single value
  }

  // Copy to texture, normalizing

  for (int x=0; x<c->dimX; x++)
    for (int y=0; y<c->dimY; y++) {

      // For FTs, shift so that origin is in centre of image
      
      complex<double> val;

      if (!shiftToCentre)
	val = (*c)(x,y);
      else
	val = (*c)( (x + c->dimX/2) % c->dimX, (y + c->dimY/2) % c->dimY ); // same as ( (x-halfX+dimX) % dimX, (y-halfY+dimY) % dimY )

      // Extract magnitude or phase
      
      float val2;

      if (isFT)
	val2 = (showMagnitude ? abs(val) : arg(val));
      else
	val2 = val.real();

      // For the FT, because there are a few very large values
      // (e.g. the DC component), log scale the values
      
      if (applyLogScale)
	val2 = logf( 1 + val2 );

      if (normalize)
	val2 = (val2 - min) / (max - min) * 255;

      t->pixel(x,y) = { (unsigned char) val2, (unsigned char) val2, (unsigned char) val2, 255 };
    }

  // Flag the texture as updated so that it is sent again to the GPU

  t->updated = true;
}



// Draw a box on the canvas

void Canvas::drawBox( vec2 ll, vec2 ur )

{
  vec4 colour(0,0,0,1);
  vec3 lightDir(1,1,1);
  mat4 M = identity4();

  vec3 pts[4] = { vec3( ll.x, ll.y, 0 ),
		  vec3( ur.x, ll.y, 0 ),
		  vec3( ur.x, ur.y, 0 ),
		  vec3( ll.x, ur.y, 0 ) };
    
  segs->drawSegs( GL_LINE_LOOP, pts, colour, NULL, 4, M, M, lightDir );
}



// Mouse button is pressed

void Canvas::startMouseMotion( float x, float y, int button, int mods )

{
  initMousePosition = vec2(x,y);
  mouseDragging = true;
  mouseMoved = false;
  recentMovementTransform = identity4();

  if (button == GLFW_MOUSE_BUTTON_LEFT)
    mouseMode = TRANSLATE;
  else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    mouseMode = SCALE;
}



// Mouse is moved

#define HYSTERESIS_DISTANCE 2.9  // do nothing until moved at least three pixels

void Canvas::mouseMotion( float x, float y )

{
  if (!mouseDragging)
    return;

  vec2 mousePosition( x, y );
  vec2 imageCentre( image->width/2, image->height/2 );

  if ((mousePosition - initMousePosition).length() < HYSTERESIS_DISTANCE)
    return; // some hysteresis to avoid transformation upon click

  mouseMoved = true;

  float imageScale, xScale, yScale;
  vec2  ll, ur;
  
  getRegionScale( imageScale, xScale, yScale, ll, ur );

  if (mouseMode == TRANSLATE) {

    // The transformation is of the [0,1]x[0,1] coordinates of the image scaled to its screen size

    recentMovementTransform = translate( +(mousePosition.x - initMousePosition.x) / (float) (imageWidth * imageScale),
					 -(mousePosition.y - initMousePosition.y) / (float) (imageHeight * imageScale),
					 0 );

  } else if (mouseMode == SCALE) {

    // scale about the imageCentre

    float scaleFactor = 1 + (mousePosition.y - initMousePosition.y) / (float) canvasHeight;

    recentMovementTransform
      = translate( 0.5, 0.5, 0 )
      * scale( scaleFactor, scaleFactor, 1 )
      * translate( -0.5, -0.5, 0 );
  }
}


// Mouse button is released

void Canvas::stopMouseMotion()

{
  accumulatedTransform = recentMovementTransform * accumulatedTransform;
  recentMovementTransform = identity4();
  mouseDragging = false;

  if (!mouseMoved) { // Clicked without movement
    
    float imageX, imageY;
    if (findMouseInImageFT( imageX, imageY )) { // Edit 'imageFT'
      compute->editImageFT( imageX, imageY, editMode, editRadius );
      copyToTexture( compute->imageFT , imageFT, true, false );
    }
  }
}



// Find the position of the mouse (in [0,1]x[0,1]) in the imageFT

bool Canvas::findMouseInImageFT( float &imageX, float &imageY )

{
  // Find the LL and UR corners of 'imageFT' in the [-1,1]x[-1,1]
  // window coordinate system.
  
  float imageScale, xScale, yScale;
  vec2  ll, ur;
  
  getRegionScale( imageScale, xScale, yScale, ll, ur );

  // Find the cursor position relative to the LL and UR corners of 'imageFT'
  
  vec2 imageLL( -1.000+ll.x, -1+ll.y );
  vec2 imageUR( -1.000+ur.x, -1+ur.y );

  double xpos, ypos;
  glfwGetCursorPos( window, &xpos, &ypos );

  float x = (        xpos       /(float)canvasWidth *2-1 - imageLL.x) / (imageUR.x - imageLL.x);
  float y = ((canvasHeight-ypos)/(float)canvasHeight*2-1 - imageLL.y) / (imageUR.y - imageLL.y);

  // Return false iff cursor is outside 'imageFT'
  
  if (x < 0 || x > 1 || y < 0 || y > 1)
    return false;

  // Apply transform (x,y) to get coordinates within [0,1]x[0,1] texture

  mat4 Tinv = (recentMovementTransform * accumulatedTransform).inverse();
  
  vec3 texLL = (Tinv * vec4(0,0,0,1)).toVec3(); // corner coordinate in window 
  vec3 texUR = (Tinv * vec4(1,1,0,1)).toVec3();

  imageX = texLL.x + x *(texUR.x - texLL.x);
  imageY = texLL.y + y *(texUR.y - texLL.y);

  return true;
}




// Handle key press

void Canvas::keyPress( int key )

{
  // ignore key presses while the mouse is being dragged
  
  if (mouseDragging)
    return;

  // handle key press

  switch (key) {

  case 'F': // Compute forward FTs

    cout << "Compute forward FTs" << endl;
    
    compute->forwardFT_2D( compute->image,  compute->imageFT );
    compute->forwardFT_2D( compute->filter, compute->filterFT );
    compute->forwardFT_2D( compute->result, compute->resultFT );

    // Update FT images on canvas

    copyToTexture( compute->imageFT,  imageFT,  true, false );
    copyToTexture( compute->filterFT, filterFT, true, false );
    copyToTexture( compute->resultFT, resultFT, true, false );
    
    break;

  case 'I': // Compute inverse FTs
  case 'B':

    cout << "Compute inverse FTs" << endl;
    
    compute->inverseFT_2D( compute->imageFT,  compute->image );
    compute->inverseFT_2D( compute->filterFT, compute->filter );
    compute->inverseFT_2D( compute->resultFT, compute->result );

    // Update non-FT images on canvas

    copyToTexture( compute->image,  image,  false, false );
    copyToTexture( compute->filter, filter, false, true  );
    copyToTexture( compute->result, result, false, false );
    
    break;

  case 'X': // Compute product
    
    cout << "Compute product" << endl;

    compute->product_2D( compute->imageFT, compute->filterFT, compute->resultFT, true ); // true = shift filter to origin

    // Update resultFT on canvas

    copyToTexture( compute->resultFT, resultFT, true, false );
      
    break;

  case 'M': // toggle phase/magnitude display of FT image
    
    showMagnitude = !showMagnitude;

    // Update FT images on canvas

    copyToTexture( compute->imageFT,  imageFT,  true, false );
    copyToTexture( compute->filterFT, filterFT, true, false );
    copyToTexture( compute->resultFT, resultFT, true, false );
    
    break;

  case 'L': // toggle log display

    logScale = !logScale;

    // Update FT images on canvas

    copyToTexture( compute->imageFT,  imageFT,  true, false );
    copyToTexture( compute->filterFT, filterFT, true, false );
    copyToTexture( compute->resultFT, resultFT, true, false );

    break;

  case '+':
  case '=':
    editRadius *= 1.1;
    break;

  case '-':
  case '_':
    editRadius /= 1.1;
    break;

  case 'A':
  case 'S':
    editMode = key;
    break;

  case 'Z': // reset image transformations

    accumulatedTransform = identity4();
    recentMovementTransform = identity4();
    break;

  default:

    cout << endl
	 << "f   compute all forward FTs" << endl
	 << "i   compute all inverse FTs" << endl
	 << "x   multiply image FT and filter FT" << endl
	 << "a   set additive editing" << endl
	 << "s   set subtractive editing" << endl
	 << "+/- inc/dec editing radius" << endl
	 << "m   toggle magnitude/phase in FT display" << endl
	 << "l   toggle log scaling of FT display" << endl
	 << "z - reset image transformations" << endl
	 << endl
	 << "click in FT of " << imageFilename << " to edit" << endl
	 << "drag left mouse to translate" << endl
	 << "drag right mouse to zoom" << endl;
  }
}



// Shaders for canvas rendering


char *Canvas::vertexShader = R"XX(

#version 300 es

uniform mediump mat4 MVP;

layout (location = 0) in mediump vec4 position;
layout (location = 1) in mediump vec4 colour_in;

out mediump vec4 colour;


void main()

{
  gl_Position = MVP * position;
  colour = colour_in;
}

)XX";


char *Canvas::fragmentShader = R"XX(

#version 300 es

in mediump vec4 colour;

out mediump vec4 fragColour;


void main()

{
  fragColour = colour;
}

)XX";



