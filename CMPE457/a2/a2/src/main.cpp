// ECG extractor


#include <fstream>

#include "headers.h"
#include "gpuProgram.h"
#include "canvas.h"
#include "compute.h"
#include "strokefont.h"
#include "filter.h"
#include "main.h"


#define windowWidth  1600
#define windowHeight 1200


Canvas     *canvas;      // code to display image
Compute    *compute;	 // code to compute things
GLFWwindow *window;      // main window
StrokeFont *strokeFont;  // code to draw characters

vec2 currentMousePosition;
bool mousePositionChanged;


// Handle a keypress and record the state (UP or DOWN) of the arrows

void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )

{
  // Note that GLFW always returns the uppercase letter, even if the lowercase letter was pressed.

  if (action == GLFW_PRESS)
    
    switch (key) {
      
    case GLFW_KEY_ESCAPE: // quit upon ESC
      glfwSetWindowShouldClose( window, GL_TRUE );
      break;

    default: // Inform the compute code of a keypress (by way of the canvas)
      canvas->keyPress( key );
    }
}


  
// Error callback

void errorCallback( int error, const char* description )

{
  cerr << "Error " << error << ": " << description << endl;
  exit(1);
}



// Callbacks for when window size changes


void windowReshapeCallback( GLFWwindow* window, int width, int height )

{
  canvas->reshape( width, height );
}

void framebufferReshapeCallback( GLFWwindow* window, int width, int height )

{
  glViewport( 0, 0, width, height );
}



// Mouse motion callback
//
// Only enabled when mouse button is down (which is done in mouseButtonCallback())

void mousePositionCallback( GLFWwindow* window, double x, double y )

{
  mousePositionChanged = true;

  currentMousePosition = vec2( x, y );
}



// Mouse button callback

void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods )

{
  if (action == GLFW_PRESS) {

    double x, y;
    glfwGetCursorPos(window, &x, &y );

    // Inform the compute removal code
    //
    // Convert mouse coords to image coords with y going up
    
    canvas->startMouseMotion( x, y, button, mods );

    mousePositionChanged = false;

    // enable mouse motion events
    
    glfwSetCursorPosCallback( window, mousePositionCallback );

  } else if (action == GLFW_RELEASE) {

    // disable mouse movement events
      
    glfwSetCursorPosCallback( window, NULL );

    // Inform the compute code
    
    canvas->stopMouseMotion();
  }
    
}


// Main program


int main( int argc, char **argv )

{
  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " image filter" << endl;
    exit(1);
  }

  // Read the image

  Texture *image  = new Texture( argv[1] );

  unsigned int w = image->width;
  unsigned int h = image->height;
  
  if (w%2 != 0 || h%2 != 0) {
    cerr << "Image must have even dimensions, not " << w << "x" << h << endl;
    exit(1);
  }

  // Read the filter

  Filter *filter = new Filter( argv[2], w, h );  // place filter in same-size array as 'image'

  // Trap all errors (do this *before* creating the window)

  glfwSetErrorCallback( errorCallback );
  
  // Init everything

  if (!glfwInit())
    return 1;
  
#ifdef MACOS
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
  glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
#else
  glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_ES_API );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
#endif

  window = glfwCreateWindow( windowWidth, windowHeight, "Convolution Theorem", NULL, NULL );
  
  if (!window) {
    glfwTerminate();
    return 1;
  }

  glfwSetWindowPos( window, 100, 100 ); // position near the upper-left corner at (100,100)

  glfwMakeContextCurrent( window );
  glfwSwapInterval( 1 );
  gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );

  // Define callbacks

  glfwSetWindowSizeCallback( window, windowReshapeCallback );
  glfwSetFramebufferSizeCallback( window, framebufferReshapeCallback );
  glfwSetKeyCallback( window, keyCallback );
  glfwSetMouseButtonCallback( window, mouseButtonCallback );

  // Set up 
  
  strokeFont = new StrokeFont();
  compute = new Compute( image, filter );
  canvas = new Canvas( windowWidth, windowHeight, image->width, image->height, argv[1], argv[2], compute );

  // Get window size in case it was changed to fit screen

  {
    int w, h;

    glfwGetWindowSize( window, &w, &h );
    canvas->reshape( w, h );
  
    glfwGetFramebufferSize( window, &w, &h );
    glViewport( 0, 0, w, h );
  }

  // Main loop

  while (!glfwWindowShouldClose( window )) {

    // Clear, display, and check for events

    glClearColor( 1, 1, 1, 1 );	// white background
    glClear( GL_COLOR_BUFFER_BIT );
    
    canvas->draw();
      
    glfwSwapBuffers( window );
    glfwPollEvents();

    // Inform the compute code if the mouse moved.

    if (mousePositionChanged) {

      // Convert mouse coords to image coords with y going up
    
      canvas->mouseMotion( currentMousePosition.x, currentMousePosition.y );

      mousePositionChanged = false;
    }
  }

  // Clean up

  glfwDestroyWindow( window );
  glfwTerminate();

  return 0;
}
