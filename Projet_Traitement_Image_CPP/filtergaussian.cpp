#include "filtergaussian.h"   // Include the header file for the Gaussian class

#include <iostream>     // For input and output operations
#include <assert.h>     // For the assert macro used for internal error checking
#include <cmath>        // For mathematical operations, such as exp() and round()
#include <string>       // For string manipulation
#include <sstream>      // For string stream operations
// #include <omp.h>     // Commented out, potentially for parallel operations with OpenMP

Gaussian::Gaussian()
{
    // Default constructor: initializes a new instance of the Gaussian class
}

/**
 * Set the standard deviation parameter (sigma) of the Gaussian filter from a string
 */
bool Gaussian::setParameters(std::string const & _line)
{
    std::string line = _line;                // Copy the input string to a local variable
    std::stringstream lineStream(line);      // Use stringstream for parsing the string

    lineStream >> m_sigma;                   // Extract the sigma value from the string
    std::cout << m_sigma << std::endl;       // Output the sigma value for verification

    return true;                             // Always returns true (consider adding error checking)
}


/**
 * Apply the Gaussian filter on a specific pixel (w, h) of the input image _in
 * and store the resulting pixel in another existing image _out.
 */
void Gaussian::compute(unsigned int const w, unsigned int const h, Image const * const _in, Image * const _out) const
{
    unsigned int D = _in->depth(); // Get the depth (number of color channels) of the input image
    int L = round(3*m_sigma);      // Calculate the kernel size based on sigma (3 sigma rule)

    for(unsigned int d = 0; d < D; d++) // Iterate over each color channel
    {
        float res = 0;                 // Initialize the result of the filtering to 0
        float total_weight = 0;        // Initialize total weight for normalization
        for(int u = -L; u <= L; u++)   // Iterate over the kernel
        {
            for(int v = -L; v <= L; v++)
            {
                int x = w - u;        // Corrected to use subtraction correctly
                int y = h - v;

                // Check if the pixel position is within the image boundaries
                if (x >= 0 && x < _in->width() && y >= 0 && y < _in->height())
                {
                    float weight = exp(-(u*u + v*v) / (2*m_sigma*m_sigma)) / (2 * 3.14 * m_sigma * m_sigma);
                    res += _in->val(x, y, d) * weight;
                    total_weight += weight; // Accumulate the weight for normalization
                }
            }
        }

        if(total_weight > 0) // Avoid division by zero
        {
            res /= total_weight; // Normalize the accumulated result by the total weight
        }

        _out->set(w, h, d, res); // Set the filtered value in the output image
    }
}
