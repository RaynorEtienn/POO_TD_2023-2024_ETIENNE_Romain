#ifndef FILTERGAUSSIAN_H  // Prevents multiple inclusions of this header file
#define FILTERGAUSSIAN_H

#include "filter.h"  // Includes the definition of the base Filter class

/**
 * The Gaussian class, derived from the Filter base class, implements a Gaussian blur filter.
 * A Gaussian blur is a filter that applies a Gaussian function to blur an image, helping reduce noise and detail.
 */
class Gaussian : public Filter
{
public:
    Gaussian();  // Constructor for the Gaussian class

    /**
     * Interprets a given line of text to extract and set the necessary parameters for the Gaussian filter.
     * This typically involves parsing the sigma value, which defines the spread of the blur effect.
     *
     * @param _line A string containing the parameters to be set.
     * @return Returns true if the parameters are successfully parsed and set, false otherwise.
     */
    virtual bool setParameters(std::string const & _line);
protected:
    /**
     * Applies the Gaussian blur to a specific pixel (w, h) in the input image '_in' and writes the
     * blurred result to the corresponding location in another image '_out'. This process is repeated for
     * every pixel in the image to achieve the full blur effect.
     *
     * @param w The x-coordinate (width) of the pixel to be processed.
     * @param h The y-coordinate (height) of the pixel to be processed.
     * @param _in Pointer to the input image where pixels are read from.
     * @param _out Pointer to the output image where the blurred pixels are written to.
     */
    virtual void compute(unsigned int const w,unsigned int const h, Image const * const _in, Image * const _out) const;
private:
    float m_sigma;  // The sigma value for the Gaussian function, controlling the extent of the blur.
};

#endif // GAUSSIAN_H
