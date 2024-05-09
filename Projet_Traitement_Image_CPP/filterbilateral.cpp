#include "filterbilateral.h" // Include the header file for the Bilateral filter class.

#include <iostream> // For input and output.
#include <assert.h> // For assertions in the code.
#include <cmath> // For mathematical functions, such as round().
#include <string> // For string manipulations.
#include <sstream> // For string stream operations.

// Constructor definition for the Bilateral class.
Bilateral::Bilateral()
{
    // Empty constructor body - currently not initializing anything.
}

// Set the parameters of the bilateral filter from a string.
bool
Bilateral::setParameters(std::string const & _line)
{
    std::string line = _line; // Make a copy of the input string.
    std::stringstream lineStream(line); // Use stringstream for parsing.
    lineStream >> m_sigmaD; // Parse and set the spatial-domain standard deviation.
    std::cout << m_sigmaD << std::endl; // Output m_sigmaD for debugging.
    lineStream >> m_sigmaR; // Parse and set the range-domain standard deviation.
    std::cout << m_sigmaR << std::endl; // Output m_sigmaR for debugging.
    return true; // Always returns true - consider adding validation of input.
}

/**
 * Apply the bilateral filter on a specific pixel (w, h) of an input image (_in) and store the resulting pixel in another existing image (_out).
 * This method computes the filtered value of a pixel based on its spatial and intensity distance from its neighbors.
 */
void
Bilateral::compute(unsigned int const w, unsigned int const h, Image const * const _in, Image * const _out) const
{
    unsigned int D = _in->depth(); // Get the depth of the input image.
    int L = round(3*m_sigmaD); // Calculate the kernel size based on the spatial standard deviation.

    for(unsigned int d = 0; d < D; d++) // Iterate over each depth.
    {
        float pixel_intensity = _in->val(w, h, d); // Get the intensity of the current pixel.
        float result_intensity = 0; // Initialize the result intensity for the pixel.
        float total_weight = 0; // Initialize the total weight to normalize the result.

        for(int u = -L; u <= L; u++) // Iterate over the kernel width.
        {
            for(int v = -L; v <= L; v++) // Iterate over the kernel height.
            {
                int neighbor_x = w + u;
                int neighbor_y = h + v;

                // Ensure the neighbor pixel is within image bounds.
                if (neighbor_x >= 0 && neighbor_x < _in->width() && neighbor_y >= 0 && neighbor_y < _in->height())
                {
                    float neighbor_intensity = _in->val(neighbor_x, neighbor_y, d); // Get the intensity of the neighbor pixel.

                    // Calculate the weight based on spatial and intensity distance.
                    float weight = exp(-(u*u + v*v)/(2*m_sigmaD*m_sigmaD) - (pixel_intensity - neighbor_intensity)*(pixel_intensity - neighbor_intensity)/(2*m_sigmaR*m_sigmaR)) / (2 * 3.14 * m_sigmaD * m_sigmaD * sqrt(2 * 3.14) * m_sigmaR);
                    result_intensity += neighbor_intensity * weight; // Accumulate the weighted neighbor pixel intensity.
                    total_weight += weight; // Accumulate the total weight.
                }
            }
        }

        if (total_weight > 0) // Avoid division by zero.
        {
            result_intensity /= total_weight; // Normalize the result intensity by the total weight.
        }

        _out->set(w, h, d, result_intensity); // Set the filtered intensity of the pixel in the output image.
    }
}
