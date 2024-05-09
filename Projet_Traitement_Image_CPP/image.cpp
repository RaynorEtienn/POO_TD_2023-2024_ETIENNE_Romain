#include "image.h"

Image::Image()
    :m_width(0),m_height(0)
{

}

Image::~Image()
{

}

Image::Image(unsigned int const width, unsigned int const height)
    :m_width(width),m_height(height)
{

}
