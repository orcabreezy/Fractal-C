#include <iostream>

#include "src/benchmark.cpp"
#include "image.h"
#include "bmp.h"

void benchmarking() {

  size_t size = 30000;
  double time_a = benchmark(true_matrix, size);
  double time_b = benchmark(flat_matrix, size);


  std::cout << "time a: " << time_a << std::endl;
  std::cout << "time_b: " << time_b << std::endl;
}

void imageCreation() {
  std::string filename = "../test.bmp";
  size_t x = 400;
  size_t y = 300;

  Pixel** image = new Pixel*[x];
  for (size_t i = 0; i < x; i++) {
    image[i] = new Pixel[y];
  }
  for (size_t i = 0; i < x; i++) {
    for (size_t j = 0; j < y; j++) {
      
      image[i][j] = Pixel();
      image[i][j].r = static_cast<unsigned char>(double(j) * (255.0/double(y)));
      image[i][j].g = static_cast<unsigned char>(double(i+j) * (255.0/double(y + x)));
      image[i][j].b = static_cast<unsigned char>(double(i) * (255.0/double(x)));
     }
  }
  PureImage pi(x, y, image);

  BmpImage bmp(pi);
  bmp.writeImage(filename);

}

void rreadImage() {

  BmpImage p = BmpImage::readImage("../DSCF8100.bmp");

  Pixel** imageArray = p.image.getData();  

  for (int i = 0; i < 2000; i++) {
    for (int j = 0; j < 2000; j++) {
      imageArray[i][j].r = 0;
    }
  }
  p.writeImage("../DSCF2.bmp");
}

int main() {

  // imageCreation();
  // rreadImage();

  std::cout << "main file executing" << std::endl;
  
  return EXIT_SUCCESS;
}



