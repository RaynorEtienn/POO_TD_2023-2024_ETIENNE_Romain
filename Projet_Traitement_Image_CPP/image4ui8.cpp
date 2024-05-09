#include "image4ui8.h" // Include the class declaration

#include <cmath>       // For mathematical operations
#include <algorithm>   // For std::copy to duplicate image data

// Constructor: Initializes an image with the specified width, height, and maximum value per channel
Image4UI8::Image4UI8(unsigned int const width, unsigned int const height, unsigned short const max)
    : Image(width, height), // Initialize base class with width and height
      m_data(new unsigned short[width * height * 4]), // Allocate memory for pixel data, 4 channels per pixel
      m_max(max) // Set the maximum value for any channel
{
}

// Destructor: Frees the allocated memory for the image data
Image4UI8::~Image4UI8()
{
    if(m_data != nullptr) // Check if data was allocated
    {
        delete[] m_data; // Free the allocated memory
    }
}

// Creates a duplicate of the current image and returns a pointer to the new image
Image * Image4UI8::duplicate() const
{
    // Create a new Image4UI8 instance with the same width, height, and max value
    Image4UI8 * res = new Image4UI8(width(), height(), m_max);
    // Duplicate the pixel data from the current image to the new one
    std::copy(m_data, m_data + width() * height() * 4, res->m_data);
    return res; // Return the new image
}

// Returns the depth (number of channels) of the image, which is 4 for RGBA
unsigned int Image4UI8::depth() const
{
    return 4;
}

// Returns the maximum possible value for any channel in the image
unsigned int Image4UI8::max() const
{
    return m_max;
}

// Accesses the normalized value of a specific pixel's channel
float Image4UI8::val(unsigned int const w, unsigned int const h, unsigned int const d) const
{
    if((d < depth()) && (w < width()) && (h < height())) // Ensure the indices are within the image boundaries
    {
        // Calculate the index for the requested pixel's channel and retrieve its value
        return float(m_data[depth() * (h * width() + w) + d]) / float(m_max);
    }
    else
    {
        return 0.f; // Return 0 for out-of-bounds indices
    }
}

// Sets the value for a specific pixel's channel
void Image4UI8::set(unsigned int const w, unsigned int const h, unsigned int const d, float const f)
{
    if((d < depth()) && (w < width()) && (h < height())) // Ensure the indices are within the image boundaries
    {
        // Scale the floating-point input to the appropriate range
        float scaled = f * float(m_max);
        // Clamp the value to the maximum and set the pixel's channel
        m_data[depth() * (h * width() + w) + d] = (scaled > float(m_max)) ? float(m_max) : std::round(scaled);
    }
}
