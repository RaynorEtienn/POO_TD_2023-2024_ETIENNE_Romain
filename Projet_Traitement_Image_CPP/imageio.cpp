#include "imageio.h"
#include <iostream>

ImageIO::~ImageIO()
{
}

std::map<std::string, ImageIO::Constructor> * ImageIO::m_constructors = nullptr;

void
ImageIO::registerClass(std::string const &name, ImageIO::Constructor const &constr)
{
    if(m_constructors == nullptr)
    {
        m_constructors = new std::map<std::string, ImageIO::Constructor>;
    }
    (*m_constructors)[name] = constr;
}

ImageIO *
ImageIO::createInstance( std::string const &name)
{
    if(m_constructors == nullptr)
    {
        std::cerr << "No image file format has been registered!" << std::endl;
        return nullptr;
    }
    else if(m_constructors->find(name) == m_constructors->end())
    {
        std::cerr << "A constructor image extension " << name << " could not be found!" << std::endl;
        return nullptr;
    }
    else
    {
        return (*m_constructors)[name]();
    }
}

