// filter.h


#ifndef FILTER_H
#define FILTER_H

#include "headers.h"
#include <fstream>

class Filter {

 public:

  float *filter;

  string name;
  unsigned int width, height;

  Filter() {
    filter = NULL;
  }

  Filter( string filename, unsigned int _width, unsigned int _height ) {

    // Set up array
    
    width  = _width;
    height = _height;

    filter = new float[ width*height ];

    for (unsigned int i=0; i<width*height; i++)
      filter[i] = 0;

    // Read filter

    readFilter( filename, width, height ); // centre the filter in 'filter'
  }

  ~Filter() {
    if (filter != NULL)
      delete [] filter;
  }

  // Reference elements as a(x,y)
  
  float & operator()( int x, int y ) {
    return filter[ x + width * y ];
  }

  void readFilter( string filename, unsigned int _width, unsigned int _height );
};


#endif
