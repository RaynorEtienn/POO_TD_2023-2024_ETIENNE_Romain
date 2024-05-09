#ifndef BMPIO_H  // Prevents the BMPIO header file from being included multiple times
#define BMPIO_H

#include "imageio.h"  // Includes the base class 'ImageIO' header for inheritance

/**
 * The BMPIO class inherits from the ImageIO class and is specifically designed for handling the input/output operations
 * of BMP (Bitmap) image files. It provides functionalities to load BMP images from disk and to save images to disk in BMP format.
 */
class BMPIO : public ImageIO
{
public:
    /**
     * Loads an image from a specified BMP file. If the loading process succeeds, it returns a pointer to the newly loaded
     * image object. If the loading fails, it returns a nullptr, indicating that no image could be loaded.
     *
     * @param _file The path to the BMP file to be loaded.
     * @return A pointer to the loaded Image object on success, or nullptr on failure.
     */
    virtual Image * load(std::string const & _file) const;
    /**
     * Saves an image to a specified BMP file. The function does not modify the input image object; it only writes the image
     * data to the disk. It returns a boolean value indicating the success or failure of the save operation.
     *
     * @param _file The path where the BMP file should be saved.
     * @param _image A pointer to the Image object to be saved.
     * @return True if the image was successfully saved, false if the save operation failed.
     */
    virtual bool save(std::string const & _file, Image const * const  _image) const;
};

#endif // BMPIO_H
