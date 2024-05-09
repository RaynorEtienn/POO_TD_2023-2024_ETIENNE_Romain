#include "image3ui16.h"  // Include the declaration for Image3UI16

#include <cmath>         // For mathematical operations
#include <algorithm>     // For std::copy function

// Constructor to initialize an Image3UI16 object with specified dimensions and max color value
Image3UI16::Image3UI16(unsigned int const width, unsigned int const height, unsigned short const max)
    : Image(width, height),  // Initialize the base Image class with width and height
      m_data(new unsigned short[width * height * 3]),  // Allocate memory for pixel data
      m_max(max)  // Initialize the maximum color value (for normalization)
{
}

// Destructor to free the allocated memory for pixel data
Image3UI16::~Image3UI16()
{
    if(m_data != nullptr)  // Check if the data pointer is not null
    {
        delete[] m_data;  // Free the allocated memory
    }
}

// Create a duplicate of the current image and return a pointer to it
Image * Image3UI16::duplicate() const
{
    Image3UI16 * res = new Image3UI16(width(), height(), m_max);  // Create a new Image3UI16 object
    std::copy(m_data, m_data + width() * height() * 3, res->m_data);  // Copy the pixel data to the new object
    return res;  // Return the new object as an Image pointer
}

// Return the depth (number of color channels) of the image, which is 3
unsigned int Image3UI16::depth() const
{
    return 3;
}

// Return the maximum color value
unsigned int Image3UI16::max() const
{
    return m_max;
}

// Access the value of a pixel (w, h) for a specific channel (d) and normalize it
float Image3UI16::val(unsigned int const w, unsigned int const h, unsigned int const d) const
{
    if((d < depth()) && (w < width()) && (h < height()))  // Check if indices are within bounds
    {
        // Calculate the index in the data array and normalize the value
        return float(m_data[h * width() * 3 + w * 3 + d]) / float(m_max);
    }
    else
    {
        return 0.f;  // Return 0 if indices are out of bounds
    }
}

// Set the value of a pixel (w, h) for a specific channel (d)
void Image3UI16::set(unsigned int const w, unsigned int const h, unsigned int const d, float const f)
{
    if((d < depth()) && (w < width()) && (h < height()))  // Check if indices are within bounds
    {
        float scaled = f * float(m_max);  // Scale the floating-point value to the 16-bit range
        // Clamp the value to the maximum and round it, then set it in the data array
        m_data[h * width() * 3 + w * 3 + d] = (scaled > float(m_max)) ? m_max : std::round(scaled);
    }
}
