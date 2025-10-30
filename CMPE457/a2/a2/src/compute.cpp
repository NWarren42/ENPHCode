// compute.cpp


#include "compute.h"



// Forward FFT for 1D complex arrays

void Compute::forwardFT_1D( complex<double> *src, complex<double> *dest, int n )

{
  fftw_plan p = fftw_plan_dft_1d( n,
				  reinterpret_cast<fftw_complex*>( src ),
				  reinterpret_cast<fftw_complex*>( dest ), 
				  FFTW_FORWARD, FFTW_ESTIMATE );

  fftw_execute( p );

  fftw_destroy_plan( p );
}



void Compute::forwardFT_2D( ComplexArray2D *src, ComplexArray2D *dest )

{
#if 1

  // TEMPORARY CODE FROM FFTW LIBRARY.  DISABLE THIS ONCE YOU HAVE IMPLEMENTED IT BELOW.
  
  fftw_plan p = fftw_plan_dft_2d( src->dimY, src->dimX, // dimY, then dimX is the correct order
				  (fftw_complex *) src->a,
				  (fftw_complex *) dest->a, 
				  FFTW_FORWARD, FFTW_ESTIMATE );

  fftw_execute( p );

  fftw_destroy_plan( p );

#else

  // The 2D FFT is implemented as a 1D FFT on all rows, then a 1D FFT
  // on all columns of that result.  Be careful to not overwrite the
  // 'src' array in the first step.

  int dimX = src->dimX;
  int dimY = src->dimY;

  // [YOUR CODE HERE]



  
#endif
}


// Compute the 1D inverse FFT as
//
//    dest = conjugate( 1/n * ft1D( conjugate(src) ) )


void Compute::inverseFT_1D( complex<double> *src, complex<double> *dest, int n )

{
  // [YOUR CODE HERE]
  


}



// Compute the 2D inverse FFT


void Compute::inverseFT_2D( ComplexArray2D *src, ComplexArray2D *dest )

{
#if 1

  // TEMPORARY CODE FROM FFTW LIBRARY.  DISABLE THIS ONCE YOU HAVE IMPLEMENTED IT BELOW.
  
  fftw_plan p = fftw_plan_dft_2d( src->dimY, src->dimX,
				  (fftw_complex *) src->a,
				  (fftw_complex *) dest->a, 
				  FFTW_BACKWARD, FFTW_ESTIMATE );

  fftw_execute( p );

  fftw_destroy_plan( p );

  // Scale inverse
  
  dest->scale( 1.0 / (float) (dest->dimX * dest->dimY) );

#else

  // The inverse 2D FFT is *identical* to the forward 2D FFT, except
  // that inverseFT_1D() is called instead of forwardFT_1D().  Once
  // your code in forwardFT_2D() is working, copy it here and make
  // this minor change.
  //
  // But this now relies on your inverseFT_1D(), so errors in inverseFT_1D()
  // may manifest only after you start using your own inverseFT_2D().
  
  int dimX = src->dimX;
  int dimY = src->dimY;

  // [YOUR CODE HERE]



  
#endif
}


// Compute the spectral product component-wise as
//
//    product[x,y] = a[x,y] * b[x,y]
//
// for all x and y.
//
// If 'b' is a filter, 'shiftB' will be true.  Such filters have their
// origin in the centre of the spatial-domain window (i.e. at
// (N/2,M/2)) for an N x M filter image.  Before multiplying, they
// must be shifted so that the filter origin is moved to the image
// origin.

void Compute::product_2D( ComplexArray2D *a, ComplexArray2D *b, ComplexArray2D *product, bool shiftB )

{
  int N = a->dimX;
  int M = a->dimY;

  if (b->dimX != N || product->dimX != N || b->dimY != M || product->dimY != M) {
    cerr << "Compute::product_2D: mis-matched array dimensions" << endl;
    exit(1);
  }

  if (shiftB) {

    // Shift 'b' as described above, then multiply

    ComplexArray2D shiftedB( *b );
    
    int colStartIndex = 1;
    for (int x=0; x<N; x++) {
      for (int y=colStartIndex; y<M; y += 2)
	shiftedB(x,y) = - shiftedB(x,y);
      colStartIndex = 1 - colStartIndex;
    }
    
    for (int x=0; x<N; x++)
      for (int y=0; y<M; y++)
	(*product)(x,y) = (*a)(x,y) * shiftedB(x,y);

  } else {

    // Multiply without shifting 'b'

    for (int x=0; x<N; x++)
      for (int y=0; y<M; y++)
	(*product)(x,y) = (*a)(x,y) * (*b)(x,y);
  }
}


// Modulate 'imageFT' within a given radius around (x,y), where (x,y)
// are in [0,1]x[0,1].
//
// For subtractive edits (editMode == 'S'), do this by multiplying the
// image values by one minus a Gaussian that has a standard deviation
// of half the radius.  The Gaussian should *not* be normalized; it
// should have a value of 1.0 at its centre.  Nothing should be
// changed outside a circle of the given radius.
//
// For additive edits (editMode == 'A'), do this by multiplying the
// image values by one plus 0.1 of the same Gaussian.
//
// Each entry in imageFT is a complex<double>. ONLY THE MAGNITUDE OF
// THE COMPLEX VALUE SHOULD BE MODIFIED.  DO NOT MODIFY THE PHASE.
//
// Pixels are addressed as (*imageFT)(x,y) for x,y in [0,dimX-1] x
// [0,dimY-1], where dimX = imageFT->dimX and dimY = imageFT->dimY.
//
// For FT images, the displayed FT image is really the log of the FT.
// So, to apply the edit to the *displayed* log image when you have
// the *actual* non-log values in the array, you must first take the
// log of the array value, apply the factor, then store the exp of the
// result.  But do this carefully and handle values of zero.
//
// Also, FT images are symmetric around the origin, so a change at
// image(x,y) should also be made at image(-x,-y).
//
// Use the wrap() function to keep things inside the image.

void Compute::editImageFT( float imageX, float imageY, char editMode, float editRadius )

{
  // Convert image coordinates (imageX,imageY) in [0,1]x[0,1] to pixel
  // coordinates (xCentre,yCentre) in [0,dimX-1]x[0,dimY-1].
  //
  // Undo the (+dimX/2,+dimY/2) translation in the displayed image
  // and use 'mod' to keep within imageFT dimensions.
  //
  // This means that (xCentre,yCentre) = (0,0) when the mouse clicks
  // at the centre of the FT image.

  int width  = imageFT->dimX;
  int height = imageFT->dimY;

  int xCentre = ((int) rint(imageX * (width -1)) + width /2) % width;
  int yCentre = ((int) rint(imageY * (height-1)) + height/2) % height;

  // Output for debugging:
  
  cout << "pixel (" << xCentre << "," << yCentre << ") = " << (*imageFT)(xCentre,yCentre) << endl;

  float sigma = 0.5 * editRadius;

  // [YOUR CODE HERE]



}



int Compute::wrap( int pos, int dim )

{
  if (pos < 0)
    return pos+dim;
  else if (pos >= dim)
    return pos-dim;
  else
    return pos;
}
