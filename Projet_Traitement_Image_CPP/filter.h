#ifndef FILTER_H
#define FILTER_H

#include "image.h"
#include <string>

class Filter
{
public:
    /** the following function parse the line _line to read the parameters
     */
    virtual bool setParameters(std::string const & _line) = 0;
    /** create the output image according the input Image and the expected format of the resulting image
     * by default, duplicate the input image
     */
    virtual Image * create(Image const * const _in);
    /** apply the filter on image _in and output the result in an other existing image _out with same size and depth
     */
    void apply(Image const * const _in, Image * const _out) const;
protected:
    /** apply the filter on pixel w,h of image _in and store the resulting pixel in an other existing image _out
     */
    virtual void compute(unsigned int const w,unsigned int const h, Image const * const _in, Image * const _out) const = 0;
};

#endif // FILTER_H
