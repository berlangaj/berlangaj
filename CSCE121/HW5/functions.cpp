#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

#define INFO(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;

using std::cout;
using std::endl;
using std::string;

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

int* createSeam(int length) {
  int* seami = new int[length];
  for (int i = 0; i < length; i++) {
    seami[i] = 0;
  }
  return seami;
}

void deleteSeam(int* seam) {
  delete[] seam;
 }

bool loadImage(string filename, Pixel** image, int width, int height) {
  cout << "Loading Image..." << endl;
  std::ifstream ifs (filename);
  if (!ifs.is_open()) {  //check if file is open
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }

  char type[2];
  ifs >> type;
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) {  //check if it is right type
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }

  int w = 0;
  int h = 0;
  ifs >> w >> h;
  if (!ifs.good()) {       //check for integer value
    cout << "Error: read non-integer value" << endl;
    return false;
  }

  if( w != width) {   //not the right width
    cout << "Error: input width (" << width << ") does not match value in file (" << w << ")" << endl;
    return false;
  }

  if( h != height) {   //not the right width
    cout << "Error: input height (" << height << ") does not match value in file (" << h << ")" << endl;
    return false;
  }
  int maxColor = 0;
  ifs >> maxColor;
  if ( maxColor != 255) {    //not using correct rgb values
    cout << "Error: file is not using RGB color values" << endl;
    return false;
  }
  int numVal = width * height * 3;
  int countVal = 0;
  for (int row = 0; row < height; row++) {
    for (int column = 0; column < width; column++) {
      int r, g, b = 0;
      char space;
      
      ifs >> r;  //check red value
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
        ifs >> std::noskipws >> space;
      }

      ifs >> g;  //check green value
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
        ifs >> std::noskipws >> space;
      }

      ifs >> b;   //check blue value
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
        ifs >> std::noskipws >> space;
      }

      if(countVal == numVal) {  //check if there is right amount of color values
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
  std::ofstream ofs;
  ofs.open(filename);
  if(!ofs.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl; //failed to open image
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
      ofs << endl; //will output values of image
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

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  int column = start_col;
  int energyDown;
  int energyLeft;
  int energyRight;
  int totalEnergy;
  seam[0] = column; 
  totalEnergy = energy(image, column, 0, width, height);
  for(int i = 1; i < height; i++) {
    if(column == 0) {
      energyDown = energy(image, column, i, width, height);
      energyRight = energy(image, column + 1, i, width , height);
      if(energyDown <= energyRight) {
        totalEnergy += energyDown;
        seam[i] = column;
      } else {
        totalEnergy += energyRight;
        seam[i] = column + 1;
        column++;
      }
    } else if (column == width - 1) {
        energyDown = energy(image, column, i, width, height);
        energyLeft = energy(image, column - 1, i, width, height);
        if(energyDown <= energyLeft) {
          totalEnergy += energyDown;
          seam[i] = column;
        } else {
          totalEnergy += energyLeft;
          seam[i] = column - 1;
          column--;
        } 
      } else {
            energyDown = energy(image, column, i, width, height);
            energyLeft = energy(image, column - 1, i, width, height);
            energyRight = energy(image, column + 1, i, width, height);
            if(energyDown < energyRight && energyDown < energyLeft){
                totalEnergy += energyDown;
                seam[i] = column;
            } else if(energyRight < energyDown && energyRight < energyLeft){
                totalEnergy += energyRight;
                seam[i] = column + 1;
                column++;
            } else if(energyLeft < energyDown && energyLeft < energyRight){
                totalEnergy += energyLeft;
                seam[i] = column - 1;
                column--;
            } else {
                if(energyDown == energyLeft && energyDown == energyRight){
                    totalEnergy += energyDown;
                    seam[i] = column;
                } else if(energyDown == energyLeft && energyDown != energyRight){
                    totalEnergy += energyDown;
                    seam[i] = column;
                } else if(energyDown == energyRight && energyDown != energyLeft){
                    totalEnergy += energyDown;
                    seam[i] = column;
                } else if(energyLeft == energyRight && energyLeft != energyDown){
                    totalEnergy += energyRight;
                    seam[i] = column + 1;
                    column++;
                }
            }
        }
    }
    
    return totalEnergy;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  int row = start_row;
  int energyRight;
  int energyUp;
  int energyDown;
  int totalEnergy = 0;
  seam[0] = row;
  totalEnergy += energy(image, 0, row, width, height);
  for(int i = 1; i < width; i++){
    if(row == 0){
      energyRight = energy(image, i, row, width, height);
      energyDown = energy(image, i, row + 1, width, height);
      if(energyRight <= energyDown){
        seam[i] = row;
        totalEnergy += energyRight;
      } else {
          seam[i] = row + 1;
          row++;
          totalEnergy += energyDown;
        }
      } else if(row == height - 1){
          energyUp = energy(image, i, row - 1, width, height);
          energyRight = energy(image, i, row, width, height);
          if(energyRight <= energyUp){
            seam[i] = row;
            totalEnergy += energyRight;
          } else{
              seam[i] = row - 1;
              row--;
              totalEnergy += energyUp;
            }
          } else{
              energyRight = energy(image, i, row, width, height);
              energyDown = energy(image, i, row + 1, width, height);
              energyUp = energy(image, i, row - 1, width, height);
              if(energyRight < energyUp && energyRight < energyDown){
                totalEnergy += energyRight;
                seam[i] = row;
              } else if(energyUp < energyRight && energyUp < energyDown){
                  totalEnergy += energyUp;
                  seam[i] = row - 1;
                  row--;
              } else if(energyDown < energyRight && energyDown < energyUp){
                  totalEnergy += energyDown;
                  seam[i] = row + 1;
                  row++;
              } else{
                if(energyRight == energyDown && energyRight == energyUp){
                    totalEnergy += energyRight;
                    seam[i] = row;
                } else if(energyRight == energyDown && energyRight != energyUp){
                    totalEnergy += energyRight;
                    seam[i] = row;
                } else if(energyRight == energyUp && energyRight != energyDown){
                    totalEnergy += energyRight;
                    seam[i] = row;
                } else if(energyUp == energyDown && energyUp != energyRight){
                    totalEnergy += energyUp;
                    seam[i] = row - 1;
                    row--;
                }
            }
        }
    }
    return totalEnergy;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  int* minSeam = new int[height];
  int minEnergy = loadVerticalSeam(image, 0, width, height, minSeam);
  int currentEnergy;
  for(int i = 1; i < width; i++){
    int* seam = new int[height];
    currentEnergy = loadVerticalSeam(image, i, width, height, seam);
    if(currentEnergy < minEnergy){
      minEnergy = currentEnergy;
      for(int i = 0; i < height; i++){
        minSeam[i] = seam[i];
      }
    }
    delete[] seam;
  }
  return minSeam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  int* minSeam = new int[width];
  int minEnergy = loadHorizontalSeam(image, 0, width, height, minSeam);
  int currentEnergy;
  for(int i = 1; i < height; i++){
    int* seam = new int[width];
    currentEnergy = loadHorizontalSeam(image, i, width, height, seam);
    if(currentEnergy < minEnergy){
      minEnergy = currentEnergy;
      for(int i = 0; i < width; i++){
        minSeam[i] = seam[i];
      }
    }
    delete[] seam;
  }
  return minSeam;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
  for(int i = 0; i < height; i++){
    int column = verticalSeam[i];
    for(int j = column; j < width - 1; j++){
      image[j][i] = image[j + 1][i];
    }
  }
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
  for(int i = 0; i < width; i++){
  int row = horizontalSeam[i];
    for(int j = row; j < height - 1; j++){
      image[i][j] = image[i][j + 1];
    }
  }
}

