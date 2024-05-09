#include "ppmio.h"         // Include the class declaration
#include "image3ui16.h"    // Include the declaration for Image3UI16, representing an image with 3 channels of 16 bits each

#include <fstream>         // For file I/O operations
#include <iostream>        // For standard I/O operations
#include <cmath>           // For mathematical operations, e.g., std::round

// Function to skip comment lines in a PPM file
inline void skipcomments(std::ifstream & _file, std::string & _line)
{
    while(!_file.eof()) // Loop until the end of the file
    {
        std::getline(_file, _line); // Read a line from the file
        if(_line[0] == '#') // If the line starts with '#', it's a comment
        {
            continue; // Skip this line and read the next one
        }
        else // If the line is not a comment
        {
            return; // Return with _line containing the first non-comment line
        }
    }
}

// Function to load a PPM image from a file
Image * PPMIO::load(std::string const & _file) const
{
    std::ifstream infile(_file); // Open the file for reading

    // If the file cannot be opened
    if(!infile.is_open())
    {
        std::cerr << "We can't open " << _file << std::endl;
        return nullptr; // Return nullptr indicating failure
    }

    std::string line; // Variable to store lines read from the file
    skipcomments(infile, line); // Skip initial comments

    // Check for the P3 magic number, indicating an ASCII PPM file
    if(line.size() >= 2 && line[0] == 'P' && line[1] == '3')
    {
        // Check if 'P3' is not properly followed by a space (indicating a malformed header)
        if(line.size() >= 3 && line[2] != ' ')
        {
            std::cerr << _file << " is not an ASCII PPM file" << std::endl;
            infile.close();
            return nullptr;
        }
    }
    else // If the file does not start with 'P3'
    {
        std::cerr << _file << " does not start with P3" << std::endl;
        infile.close();
        return nullptr;
    }

    skipcomments(infile, line); // Skip more comments if present

    // Read image dimensions from the line
    std::size_t indexofnextinteger;
    unsigned int const width = std::stoi(line, &indexofnextinteger); // Get width

    // If width is not found or the line doesn't contain more data for height
    if(indexofnextinteger == 0 || indexofnextinteger == line.size())
    {
        std::cerr << "no width height found in " << _file << std::endl;
        infile.close();
        return nullptr;
    }

    line.erase(0, indexofnextinteger); // Remove the width part from the line
    unsigned int const height = std::stoi(line, &indexofnextinteger); // Get height

    skipcomments(infile, line); // Skip comments before the max value
    unsigned int max = std::stoi(line, &indexofnextinteger); // Get the max value (pixel value range)

    // Create an image object with the read dimensions and max value
    Image3UI16 * res = new Image3UI16(width, height, max);

    // Read pixel values and fill the image
    unsigned int counter = 0;
    while(!infile.eof() && counter < width * height * 3)
    {
        unsigned int val;
        infile >> val; // Read a pixel value
        // Set the pixel value in the image, adjusting for the channel index
        res->set((counter / 3) % width, (counter / 3) / width, counter % 3, float(val) / float(max));
        counter++;
    }
    infile.close();

    // Check if all expected pixels were read
    if(counter == width * height * 3)
    {
        return res; // Return the loaded image
    }
    else // If not all pixels were read
    {
        std::cerr << "Not enough pixels in " << _file << std::endl;
        delete res;
        return nullptr; // Return nullptr indicating failure
    }
}

// Function to save an image in PPM format
bool PPMIO::save(std::string const & _file, Image const * const  _image) const
{
    std::ofstream outfile(_file); // Open the file for writing

    // If the file cannot be opened
    if(!outfile.is_open())
    {
        std::cerr << "We can't open " << _file << std::endl;
        return false; // Return false indicating failure
    }

    // Write the PPM header
    outfile << "P3\n"; // Magic number for ASCII PPM
    outfile << _image->width() << " " << _image->height() << "\n"; // Image dimensions

    // Try to dynamic cast the image to Image3UI16 to ensure it's the correct type
    Image3UI16 const * const image = dynamic_cast<Image3UI16 const * const>(_image);
    unsigned short const max = (image != nullptr) ? image->max() : 65535; // Get the max value or default to 65535

    outfile << max << "\n"; // Write the max value

    // Write the pixel values
    for(unsigned int h = 0; h < _image->height(); h++)
    {
        for(unsigned int w = 0; w < _image->width(); w++)
        {
            for(unsigned int d = 0; d < 3; d++) // For each color channel
            {
                unsigned short val = std::round(_image->val(w, h, d) * float(max)); // Scale and round the pixel value
                outfile << val << " "; // Write the pixel value
            }
        }
        outfile << "\n"; // New line after each row
    }
    outfile.close(); // Close the file
    return true; // Return true indicating success
}

// Static registration of PPMIO for handling PPM files
static ImageIO::Register<PPMIO> registerPPMIO1("PPM");
static ImageIO::Register<PPMIO> registerPPMIO2("ppm");
