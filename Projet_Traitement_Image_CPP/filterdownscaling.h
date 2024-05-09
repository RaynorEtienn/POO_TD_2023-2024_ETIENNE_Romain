#ifndef FILTERDOWNSCALING_H
#define FILTERDOWNSCALING_H

#include "filter.h"

class filterdownscaling : public Filter
{
public:
    filterdownscaling();

    virtual bool setParameters(std::string const & _line);
    /** create the output image according the input Image and the expected format of the resulting image
     */
    virtual Image * create(Image const * const _in);
protected:
    /** apply the filter on pixel w,h of image _in and store the resulting pixel in an other existing image _out
     */
    virtual void compute(unsigned int const w,unsigned int const h, Image const * const _in, Image * const _out) const;
private:
    float m_scalor;
    unsigned int m_newW;
    unsigned int m_newH;
};

#endif // FILTERDOWNSCALING_H
