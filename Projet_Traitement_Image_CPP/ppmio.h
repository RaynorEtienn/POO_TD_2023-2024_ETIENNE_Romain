#ifndef PPMIO_H
#define PPMIO_H

#include "imageio.h"
/** Class dedicated to read and write PPM images
 */
class PPMIO : public ImageIO
{
public:
    /** load the image in _file
     *    if failed, return  nullprt
     *    if succeed, return  the pointer on the newly created images
     */
    virtual Image * load(std::string const & _file) const;
    /** Save image in _file
     *    _image and *_image always remain unchanged
     *    return the success of the failure of the process
     */
    virtual bool save(std::string const & _file, Image const * const  _image) const;
};

#endif // PPMIO_H

