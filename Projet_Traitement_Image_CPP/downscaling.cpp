#include "downscaling.h"

#include <iostream>
#include <assert.h>
#include <cmath>
#include <string>
#include <sstream>
// #include <omp.h>

#include "image1i16.h"
#include "image3ui16.h"
#include "image4ui8.h"

Downscaling::Downscaling()
{

}

bool
Downscaling::setParameters(std::string const & _line)
{
    std::string line = _line;
    std::stringstream lineStream(line);

    lineStream >> m_newW;
    std::cout << m_newW << std::endl;

    lineStream >> m_newH;
    std::cout << m_newH << std::endl;

    return true;
}

Image *
Downscaling::create(Image const * const _in) const
{
    unsigned int d = _in->depth();
    if (d==1)
    {
        return new Image1UI16(m_newW,m_newH,65535);
    }
    if (d==3)
    {
        return new Image3UI16(m_newW,m_newH,65535);
    }
    if (d==4)
    {
        return new Image4UI8(m_newW,m_newH,255);
    }
    else
        return nullptr;
}


/** apply the filter on pixel w,h of image _in and store the resulting pixel in an other existing image _out
 */
void
Downscaling::compute(unsigned int const w,unsigned int const h, Image const * const _in, Image * const _out) const
{
    unsigned int const w_in = _in->width();
    unsigned int const h_in = _in->height();
    unsigned int const d = _in->depth();

    unsigned int w_out = _out->width();
    unsigned int h_out = _out->height();

    float x_ratio = float((1.0*w_in-1)/(1.0*w_out));
    float y_ratio = float((1.0*h_in-1)/(1.0*h_out));

    for (unsigned int i = 0; i < d; i++)
    {
        int x = floor(x_ratio*w);
        int y = floor(y_ratio*h);

        float d_x = (x_ratio*w)-x;
        float d_y = (y_ratio*h)-y;
        float A,B,C,D;
        A = _in->val(x,y,i);
        B = _in->val(x+1,y,i);
        C = _in->val(x,y+1,i);
        D = _in->val(x+1,y+1,i);

        float new_val = A*(1-d_x)*(1-d_y) + B*(d_x)*(1-d_y) + C*(1-d_x)*(d_y) + D*(d_x)*(d_y);

        _out->set(w,h,i,new_val);

    }

}
