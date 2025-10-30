// filter.cpp

#include "headers.h"
#include "filter.h"


// Read a filter, but centre it in a float array of the given dimensions

void Filter::readFilter( string filename, unsigned int _width, unsigned int _height )

{
  ifstream in( filename, ios_base::in );

  if (!in) {
    cerr << "Could not open " << filename << endl;
    exit(1);
  }

  // Get size and scale
    
  unsigned int filterX, filterY;
  float scale, val;
    
  in >> filterX >> filterY;
  in >> scale;

  if (filterX > width || filterY > height) {
    cerr << "Filter of size " << filterX << "x" << filterY
	 << " is too large to fit in specified dimensions of "
	 << width << "x" << height << endl;
    exit(1);
  }

  // Get filter values and centre them in the array
    
  unsigned int xOffset = (width  - filterX) / 2;
  unsigned int yOffset = (height - filterY) / 2;

  for (unsigned int x=0; x<filterX; x++)
    for (unsigned int y=0; y<filterY; y++) {
      in >> val;
      (*this)( x+xOffset, y+yOffset ) = val * scale;
    }
}
