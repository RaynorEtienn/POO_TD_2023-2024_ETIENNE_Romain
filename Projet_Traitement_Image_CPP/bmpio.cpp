#include "bmpio.h"                             // Include the declaration for the BMPIO class
#include "EasyBMP.h"                           // EasyBMP library for BMP file manipulation
#include "EasyBMP_BMP.h"                       // BMP specific functions and data structures
#include "EasyBMP_DataStructures.h"            // Data structures used by EasyBMP
#include "EasyBMP_VariousBMPutilities.h"       // Utility functions provided by EasyBMP
#include "image4ui8.h"                         // Include the definition for Image4UI8, a custom image class

#include <fstream>                             // For file input/output operations
#include <iostream>                            // For input/output streaming operations (e.g., std::cerr)
#include <cmath>                               // For mathematical operations, such as std::round

// BMPIO class definition for loading and saving BMP images
Image *
BMPIO::load(std::string const & _file) const  // Load function to read a BMP file and return an Image pointer
{
    BMP AnImage;                              // Create a BMP object to work with BMP files
    bool open = AnImage.ReadFromFile(_file.c_str());  // Attempt to open and read the BMP file
    if (!open)                                // Check if the file opening failed
    {
        std::cerr << "We can't open " << _file << std::endl;  // Output error message
        return nullptr;                       // Return nullptr to indicate failure
    }

    // Successfully opened the file, proceed to read image properties and pixels
    unsigned int const width = AnImage.TellWidth();   // Get the image width
    unsigned int const height = AnImage.TellHeight(); // Get the image height
    unsigned int const max = 255;                     // Maximum color value for 8-bit color depth

    Image4UI8 * res = new Image4UI8(width,height,max); // Create an Image4UI8 object for the image

    // Loop through each pixel to read and convert its color values
    for (unsigned int h = 0; h < height; h++)
    {
        for (unsigned int w = 0; w < width; w++)
        {
            RGBApixel Temp = AnImage.GetPixel(w,h); // Read pixel at (w, h)
            // Set the color and alpha values in the Image4UI8 object, normalized to [0,1]
            res->set(w,h,0,float(Temp.Red)/float(max));
            res->set(w,h,1,float(Temp.Green)/float(max));
            res->set(w,h,2,float(Temp.Blue)/float(max));
            res->set(w,h,3,float(Temp.Alpha)/float(max));
        }
    }
    // After reading all pixels, return the image object
    return res;  // Return the populated Image4UI8 object
}

bool
BMPIO::save(std::string const & _file, Image const * const  _image) const  // Save function to write an Image to a BMP file
{
    BMP AnImage;  // Create a BMP object for file operations
    AnImage.SetSize(_image->width(),_image->height());  // Set the BMP image size
    Image4UI8 const * const image = dynamic_cast<Image4UI8 const * const>(_image);  // Dynamic cast to specific image type

    unsigned short const max = (image!=nullptr)?image->max():65535;  // Determine the max color value based on image type

    // Iterate over each pixel to set its color in the BMP
    for(unsigned int j = 0; j < _image->height(); j++)
    {
        for(unsigned int i = 0; i < _image->width(); i++)
        {
            // Convert normalized color values back to 8-bit and set them in the BMP
            unsigned short val_Red = std::round(_image->val(i,j,0)*float(max));
            AnImage(i,j)->Red = val_Red;

            unsigned short val_Green = std::round(_image->val(i,j,1)*float(max));
            AnImage(i,j)->Green = val_Green;

            unsigned short val_Blue = std::round(_image->val(i,j,2)*float(max));
            AnImage(i,j)->Blue = val_Blue;

            unsigned short val_Alpha = std::round(_image->val(i,j,3)*float(max));
            AnImage(i,j)->Alpha = val_Alpha;
        }
    }
    // Attempt to write the BMP image to file
    bool open = AnImage.WriteToFile(_file.c_str());
    if (!open)  // Check if the file writing failed
    {
        std::cerr << "We can't open " << _file << std::endl;  // Output error message
        return false;  // Return false to indicate failure
    }
    return true;  // Return true to indicate success
}

// Static registration of the BMPIO class for handling BMP files
// Allows for dynamic creation based on file extension
static ImageIO::Register<BMPIO> registerBMPIO1("BMP");
static ImageIO::Register<BMPIO> registerBMPIO2("bmp");
