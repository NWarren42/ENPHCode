// compute.h


#ifndef COMPUTE_H
#define COMPUTE_H

#include "headers.h"
#include "texture.h"
#include "filter.h"

#include <complex>  // include this before fftw3.h to make FFTW's fftw_complex == C++'s complex<double> 
#include <fftw3.h>


typedef enum { TRANSLATE, ROTATE, SCALE, INTENSITY } EditMode;
typedef enum { FORWARD, BACKWARD } ProjectionMode;



// A 2D array of complex numbers

class ComplexArray2D {

 public:

  complex<double> *a;  // stored in row-major order

  int dimX, dimY;

  ComplexArray2D() {
    a = NULL;
  }

  // array of specified dimensions
  
  ComplexArray2D( int _dimX, int _dimY ) {

    dimX = _dimX;
    dimY = _dimY;

    a = new complex<double>[ dimX * dimY ];
  }

  // copy constructor
  
  ComplexArray2D( ComplexArray2D &c ) {

    dimX = c.dimX;
    dimY = c.dimY;

    a = new complex<double>[ dimX * dimY ];

    complex<double> *src = c.a;
    complex<double> *dst = a;
    
    for (int i=0; i<dimX*dimY; i++)
      *dst++ = *src++;
  }

  // Convert rgb texture to scalar luminance values in the complex array
  
  ComplexArray2D( Texture *t ) {

    dimX = t->width;
    dimY = t->height;

    a = new complex<double>[ dimX * dimY ];

    for (int x=0; x<dimX; x++)
      for (int y=0; y<dimY; y++)
	(*this)(x,y) = complex<double>( t->toLuminance( t->pixel(x,y) ), 0 );
  }

  // Convert the given float array to complex
  
  ComplexArray2D( Filter *t, unsigned int _dimX, unsigned int _dimY ) {

    dimX = _dimX;
    dimY = _dimY;

    a = new complex<double>[ dimX * dimY ];

    for (int x=0; x<dimX; x++)
      for (int y=0; y<dimY; y++)
	(*this)(x,y) = complex<double>( (*t)(x,y), 0 );
  }

  ~ComplexArray2D() {
    if (a != NULL)
      delete [] a;
  }

  // Reference elements as a(x,y)
  
  complex<double> & operator()( int x, int y ) {
    return a[ x + dimX * y ];
  }

  // Scale array elements by a factor

  void scale( double factor ) {

    complex<double>* p = a;

    for (int i=0; i<dimX*dimY; i++)
      *p++ *= factor;
  }
};


// All computations are done with arrays of complex numbers that are local to the Compute class.
//
// The Canvas class takes these complex arrays and converts them to textures for display.


class Compute {

 public:

  int dimX, dimY;

  ComplexArray2D *image;      // original image
  ComplexArray2D *imageFT;    // FT of original image
  ComplexArray2D *filter;     // filter
  ComplexArray2D *filterFT;   // FT of filter
  ComplexArray2D *result;     // product
  ComplexArray2D *resultFT;   // FT of product

  Compute( Texture *_image, Filter *_filter ) {

    dimX = _image->width;
    dimY = _image->height;

    image    = new ComplexArray2D( _image );
    imageFT  = new ComplexArray2D( dimX, dimY );
    filter   = new ComplexArray2D( _filter, dimX, dimY );
    filterFT = new ComplexArray2D( dimX, dimY );
    result   = new ComplexArray2D( dimX, dimY );
    resultFT = new ComplexArray2D( dimX, dimY );
  }

  void computeSolution();

  void forwardFT_1D( complex<double> *src, complex<double> *dest, int n );
  void inverseFT_1D( complex<double> *src, complex<double> *dest, int n );
  void forwardFT_2D( ComplexArray2D *src, ComplexArray2D *dest );
  void inverseFT_2D( ComplexArray2D *src, ComplexArray2D *dest );
  void product_2D( ComplexArray2D *a, ComplexArray2D *b, ComplexArray2D *product, bool shiftB );
  void editImageFT( float imageX, float imageY, char editMode, float editRadius );
  int  wrap( int pos, int dim );
};

#endif
