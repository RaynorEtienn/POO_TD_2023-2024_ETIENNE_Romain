#include "filterdownscaling.h"

#include <iostream>     // For standard input/output streaming operations
#include <assert.h>     // For the assert macro used for internal error checking
#include <cmath>        // For mathematical functions, such as floor
#include <string>       // For string manipulation
#include <sstream>      // For string stream operations
// #include <omp.h>    // Commented out, potentially for parallel operations with OpenMP

#include "image1i16.h"  // Include the declaration for single-channel 16-bit images
#include "image3ui16.h" // Include the declaration for three-channel 16-bit images
#include "image4ui8.h"  // Include the declaration for four-channel 8-bit images


filterdownscaling::filterdownscaling()
{

}

// Sets the new dimensions for the rescaling operation based on a string input
bool filterdownscaling::setParameters(std::string const & _line)
{
    std::string line = _line;            // Copy the input line to a local variable
    std::stringstream lineStream(line);  // Use a stringstream for parsing

    lineStream >> m_scalor;                // Extract the scalor from the string
    std::cout << m_scalor << std::endl;    // Print it

    if(m_scalor < 1.f){ // Error handling
        throw std::invalid_argument("downscaling: Scale factor must be >= 1.f");
        return false;
    }

    return true;                         // Indicate success
}

// Creates a new image object with the specified new dimensions
Image * filterdownscaling::create(Image const * const _in)
{
    m_newW = floor(_in->width()) / m_scalor;
    m_newH = floor(_in->height()) / m_scalor;

    unsigned int d = _in->depth();       // Get the depth (number of channels) of the input image
    // Create a new image of the appropriate type based on the depth of the input image
    if (d == 1)
    {
        return new Image1UI16(m_newW, m_newH, 65535); // For single-channel images
    }
    if (d == 3)
    {
        return new Image3UI16(m_newW, m_newH, 65535); // For three-channel images
    }
    if (d == 4)
    {
        return new Image4UI8(m_newW, m_newH, 255);    // For four-channel images
    }
    else
        return nullptr; // Return nullptr if the depth is not supported
}

// Rescales the image _in and stores the result in _out
void filterdownscaling::compute(unsigned int const w, unsigned int const h, Image const * const _in, Image * const _out) const
{
    // Original dimensions
    unsigned int const w_in = _in->width();
    unsigned int const h_in = _in->height();
    unsigned int const d = _in->depth(); // Depth (number of channels)

    // New dimensions
    unsigned int w_out = _out->width();
    unsigned int h_out = _out->height();

    // Calculate the ratio of the old dimensions to the new dimensions
    float x_ratio = float((1.0 * w_in - 1) / (1.0 * w_out));
    float y_ratio = float((1.0 * h_in - 1) / (1.0 * h_out));

    // Loop over each channel
    for (unsigned int i = 0; i < d; i++)
    {
        // Calculate the position in the input image corresponding to the current pixel in the output image
        int x = floor(x_ratio * w);
        int y = floor(y_ratio * h);

        // Calculate the differences to use for interpolation
        float d_x = (x_ratio * w) - x;
        float d_y = (y_ratio * h) - y;

        // Fetch the pixel values needed for bilinear interpolation
        float A, B, C, D;
        A = _in->val(x, y, i);
        B = _in->val(x + 1, y, i);
        C = _in->val(x, y + 1, i);
        D = _in->val(x + 1, y + 1, i);

        // Perform bilinear interpolation to calculate the new pixel value
        float new_val = A * (1 - d_x) * (1 - d_y) + B * (d_x) * (1 - d_y) +
                        C * (1 - d_x) * (d_y) + D * (d_x) * (d_y);

        // Set the interpolated value in the output image
        _out->set(w, h, i, new_val);
    }
}
