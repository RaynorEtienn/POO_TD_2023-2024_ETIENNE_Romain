#include "image1i16.h"

#include <cmath>
#include <algorithm>    // std::copy

Image1UI16::Image1UI16(unsigned int const width, unsigned int const height, unsigned short const max)
    :Image(width,height),m_data(new unsigned short[width*height]),m_max(max)
{
}

Image1UI16::~Image1UI16()
{
    if(m_data!=nullptr)
    {
        delete[] m_data;
    }
}

// create a copy of the current image
Image *
Image1UI16::duplicate() const
{
    Image1UI16 * res = new Image1UI16(width(),height(),m_max);
    std::copy(m_data,m_data+width()*height(),res->m_data);
    return res;
}

unsigned int
Image1UI16::depth()  const
{
    return 1;
}

unsigned int
Image1UI16::max() const
{
    return m_max;
}

// access to the value of pixel (w,h) and for component d
float
Image1UI16::val(unsigned int const w, unsigned int const h, unsigned int const d) const
{
    if( (d==0) and (w < width()) and (h < height()))
    {
        return float(m_data[h*width()+w])/float(m_max);
    }
    else
    {
        return 0.f;
    }
}

// set the value f to pixel (w,h) and its component d
void
Image1UI16::set(unsigned int const w, unsigned int const h, unsigned int const d, float const f)
{
    if( (d==0) and (w < width()) and (h < height()))
    {
        float scaled = f*float(m_max);
        m_data[h*width()+w]=(scaled>float(m_max))?float(m_max):std::round(scaled);
    }

}
