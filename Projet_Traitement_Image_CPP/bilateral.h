#ifndef BILATERAL_H  // Prevents the bilateral header file from being included multiple times
#define BILATERAL_H

#include "filter.h"  // Includes the base class 'Filter' header for inheritance

/**
 * The Bilateral class inherits from the Filter class. This class is specifically designed to apply a bilateral filter
 * to an image. A bilateral filter is a non-linear, edge-preserving, and noise-reducing smoothing filter for images.
 * It replaces the intensity of each pixel with a weighted average of intensity values from nearby pixels. The weight
 * depends on the spatial distance and the radiometric difference (e.g., intensity difference), allowing it to preserve edges.
 */
class Bilateral : public Filter
{
public:
    Bilateral();  // Constructor declaration

    /**
     * Parses the input string to read the parameters necessary for the bilateral filter. The parameters typically include
     * the spatial (distance) and range (color/intensity) sigma values for the Gaussian functions used in the filter.
     *
     * @param _line The input string containing the parameters.
     * @return Returns true if the parameters could be successfully parsed and set; otherwise, false.
     */
    virtual bool setParameters(std::string const & _line);
protected:
    /**
     * Applies the bilateral filter to a specific pixel located at (w, h) in the input image '_in' and stores
     * the result in the corresponding pixel of the output image '_out'. This function is called for each pixel
     * in the image to apply the filter across the entire image.
     *
     * @param w The width coordinate (column index) of the pixel to be processed.
     * @param h The height coordinate (row index) of the pixel to be processed.
     * @param _in Pointer to the input image.
     * @param _out Pointer to the output image where the result is stored.
     */
    virtual void compute(unsigned int const w,unsigned int const h, Image const * const _in, Image * const _out) const;
private:
    float m_sigmaD;  // The spatial (distance) sigma value for the Gaussian function, controls how far away pixels influence each other.
    float m_sigmaR;  // The range (color/intensity) sigma value for the Gaussian function, controls how similar in color pixels need to be to influence each other.
};

#endif // BILATERAL_H
