#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

// implement for part 1

int* createSeam(int length) {
  int* seam1 = new int[length];
  for (int j = 0; j < length; j++) {
    seam1[j] = 0;
  }
  return seam1;
}

void deleteSeam(int* seam) {
  delete[] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  cout << "Loading image..." << endl;
  ifstream ifs (filename);
  if(!ifs.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }
  char type[2];
  ifs >> type;
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) {
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }

  int w = 0;
  int h = 0;
  ifs >> w >> h;
  if (!ifs.good()) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }

  if( w != width) {
    cout << "Error: input width (" << width << ") does not match value in file (" << w << ")" << endl;
    return false;
  }

  if( h != height) {
    cout << "Error: input height (" << height << ") does not match value in file (" << h << ")" << endl;
    return false;
  }
  int maxColor = 0;
  ifs >> maxColor;
  if ( maxColor != 255) {
    cout << "Error: file is not using RGB color values" << endl;
    return false;
  }
  int numVal = width * height * 3;
  int countVal = 0;
  for (int row = 0; row < height; row++) {
    for (int column = 0; column < width; column++) {
      int r, g, b = 0;
      char space;
      
      ifs >> r;
      if(ifs.eof() && (countVal < numVal)) {
        cout << "Error: not enough color values" << endl;
        ifs.clear();
        return false;
      } else if(!ifs.good() && (countVal != numVal)) {
        cout << "Error: read non-integer value" << endl;
        ifs.clear();
        return false;
      } else {
        countVal++;
        ifs >> noskipws >> space;
      }

      ifs >> g;
      if(ifs.eof() && (countVal < numVal)) {
        cout << "Error: not enough color values" << endl;
        ifs.clear();
        return false;
      } else if(!ifs.good() && (countVal != numVal)) {
        cout << "Error: read non-integer value" << endl;
        ifs.clear();
        return false;
      } else {
        countVal++;
        ifs >> noskipws >> space;
      }

      ifs >> b;
      if(ifs.eof() && (countVal < numVal)) {
        cout << "Error: not enough color values" << endl;
        ifs.clear();
        return false;
      } else if(!ifs.good() && (countVal != numVal)) {
        cout << "Error: read non-integer value" << endl;
        ifs.clear();
        return false;
      } else {
        countVal++;
        ifs >> noskipws >> space;
      }

      if(countVal == numVal) {
        if (!ifs.eof()) {
          cout << "Error: too many color values" << endl;
          ifs.clear();
          return false;
        }
      }

      if( r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0) {
        cout << "Error: invalid color value " << r << endl;
        ifs.clear();
        return false;
      }

      image[column][row].r = r;
      image[column][row].g = g;
      image[column][row].b = b;
    }
  }
  ifs.clear();
  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {

  cout << "Outputting image..." << endl;
  ofstream ofs;
  ofs.open(filename);
  if(!ofs.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  } else {
    ofs << "P3" << endl;
    ofs << width << " " << height << endl;
    ofs << 255 << endl;
    for (int row = 0; row < height; row++) {
      for (int column = 0; column < width; column++) {
        ofs << image[column][row].r << " ";
        ofs << image[column][row].g << " ";
        ofs << image[column][row].b << " ";
      }
      ofs << endl;
    }
  }
  ofs.close();
  return true;

} 

int energy(Pixel** image, int x, int y, int width, int height) { 
  int EnergyX = 0;
  int EnergyY = 0;
  int totalEnergy = 0;

  int red = 0;
  int green = 0;
  int blue = 0;

  if (x == (width-1)) {
    red = image[0][y].r - image[x-1][y].r;
    green = image[0][y].g - image[x-1][y].g;
    blue = image[0][y].b - image[x-1][y].b;
  } 
  else if(x == 0) {
    red = image[x+1][y].r - image[width-1][y].r;
    green = image[x+1][y].g - image[width-1][y].g;
    blue = image[x+1][y].b - image[width-1][y].b;
  } 
  else {
    red = image[x+1][y].r - image[x-1][y].r;
    green = image[x+1][y].g - image[x-1][y].g;
    blue = image[x+1][y].b - image[x-1][y].b;
  }
  EnergyX = pow(red, 2) + pow(green, 2) + pow(blue, 2);

  red = 0;
  green = 0;
  blue = 0;

  if (y == (height-1)) {
    red = image[x][0].r - image[x][y-1].r;
    green = image[x][0].g - image[x][y-1].g;
    blue = image[x][0].b - image[x][y-1].b;
  } else if(y == 0) {
    red = image[x][y+1].r - image[x][height-1].r;
    green = image[x][y+1].g - image[x][height-1].g;
    blue = image[x][y+1].b - image[x][height-1].b;
  } else {
    red = image[x][y+1].r - image[x][y-1].r;
    green = image[x][y+1].g - image[x][y-1].g;
    blue = image[x][y+1].b - image[x][y-1].b;
  }
  EnergyY = pow(red, 2) + pow(green, 2) + pow(blue, 2);

  totalEnergy = EnergyX + EnergyY;
  return totalEnergy;

}

// implement for part 2

// uncomment for part 2
/* 

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  return 0;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  return 0;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  return nullptr;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  return nullptr;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
}


void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
}*/
