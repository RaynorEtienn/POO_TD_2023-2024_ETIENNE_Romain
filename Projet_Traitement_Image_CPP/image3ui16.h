#ifndef Image3UI16_H
#define Image3UI16_H

#include "image.h"

/** Colored images with 3*16 bits unsigned int
 */
class Image3UI16 : public Image
{
public:
    /** Intialize with the width, height, and the max grayscaled value
     */
    Image3UI16(unsigned int const width, unsigned int const height, unsigned short const max);
    /** Destructor
     */
    ~Image3UI16();
public: // accessing to dimensions
    /** Return 3 for the depth
     */
    virtual unsigned int depth()  const;
    /** Return max value
     */
    unsigned int max() const ;
public: // implementation of other pure virtual members
    /** Create a copy of the current image
     */
    virtual Image * duplicate() const;
    /** Access to the value of pixel (w,h) and for component d
     */
    virtual float val(unsigned int const width, unsigned int const height, unsigned int const depth) const;
    /** Set the value f to pixel (w,h) and its component d
     */
    virtual void  set(unsigned int const width, unsigned int const height, unsigned int const depth, float const f);
private:
    unsigned short * m_data;
    unsigned short   m_max;
};

#endif // Image3UI16_H
