#include <gtest/gtest.h>

#include "BmpImage.h"
#include "PureImage.h"
#include "Pixel.h"

int add(int a, int b) {
    return a + b;
}

TEST(bmpFileTest, TestCreateLoad) {

    size_t x = 50;
    size_t y = 80;
    size_t width, height = 100;
    std::string filename = "bmpFileTest.bmp";

    PureImage im(width, height);

    im.imageData[x][y].r = 255;

    BmpImage p(im);

    p.writeImage(filename);

    BmpImage q = BmpImage::readImage(filename);
    
    unsigned char red, green, blue;
    red = q.image.imageData[x][y].r;
    green = q.image.imageData[x][y].g;
    blue = q.image.imageData[x][y].b;

    EXPECT_EQ(red, 255);
    EXPECT_EQ(green, 0);
    EXPECT_EQ(blue, 0);
}

TEST(AdditionTest, HandlesPositiveInput) {
    EXPECT_EQ(add(1, 1), 2);
    EXPECT_EQ(add(2, 4), 6); 
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}