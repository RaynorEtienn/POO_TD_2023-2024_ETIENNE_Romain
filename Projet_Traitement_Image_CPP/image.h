#ifndef IMAGE_H
#define IMAGE_H

//Generic class for Images
class Image
{
public:
    /** Initialize an image with width, height and depth
     */
    Image(unsigned int const width, unsigned int const height);
    /** virtual desctructor
     */
    virtual ~Image();
public: // accessing to dimensions
            unsigned int width()  const    {return m_width;}
            unsigned int height() const    {return m_height;}
    virtual unsigned int depth()  const =0 ;
public: // other pure virtual members
    /** Create a copy of the current image
     */
    virtual Image * duplicate() const = 0;
    /** Access to the value of pixel (w,h) and for component d
     * if d >= depth(), return 0
     * if w >= width() or h >= height(), return 0
     */
    virtual float val(unsigned int const w, unsigned int const h, unsigned int const depth) const = 0;
    /** Set the value f to pixel (w,h) and its component d
     */
    virtual void  set(unsigned int const w, unsigned int const h, unsigned int const depth, float const f) = 0;
private:
    /** Initialize an image with width = 0, height = 0 and depth = 0 (forbidden)
     */
    Image();
    unsigned int m_width;
    unsigned int m_height;
};

#endif // IMAGE_H
