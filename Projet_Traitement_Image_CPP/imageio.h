#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <string>
#include <functional>
#include <map>
#include "image.h"

/** Generic Class to load an image
 */
class ImageIO
{
public:
    /** Default destructor (do nothing) required for pure virtual class
     */
    virtual ~ImageIO();
    /** load the image in _file
     *    if failed, return  nullprt
     *    if succeed, return  the pointer on the newly created images
     */
    virtual Image * load(std::string const & _file) const =0;
    /** Save image in _file
     *    _image and *_image always remain unchanged
     *    return the success of the failure of the process
     */
    virtual bool save(std::string const & _file, Image const * const  _image) const =0;
public:// mechanism to find the correct loader according to an file format extension
    /** define a type of function without any parameters by which return a pointer to new ImageIO
     */
    typedef std::function<ImageIO *(void)> Constructor;
    /** Register an Filter constructor with the object factory
     * extension   : A string containing the file extension that is associated with this class.
     * constructor : A function to an anonymous function that is able to call the constructor of the class.
     */
    static void registerClass(std::string const &extension, Constructor const &constructor);
    /** Construct an instance from the class of the given extension
     */
    static ImageIO *createInstance(const std::string &extension);
    /** Constructor function templated by a class derived from ImageIO.
     * It will be the constructor function for registerClass
     */
    template<typename _derivedfromImageIO>
    static ImageIO * create()
    {
        return new _derivedfromImageIO;
    }
    /** Class used to associate (register) a file extension with the previous function
     * Each class C derived from ImageIO must contains in the declaration files (.cpp) at least the line where "name" is user-defined
     * static ImageIO::Register<C> name("extension");
     */
    template <typename _derivedfromImageIO>
    class Register
    {
    public:
        /** Constructor with the name of the extension
         *  Its only rule is to associate the extension with the constructor
         */
        Register(std::string const & extension)
        {
            ImageIO::registerClass(extension,create<_derivedfromImageIO>);
        }
    private:
        /** Default constructor in private to prevent such a declaration
         */
        Register()
        {
        }
    };
private:
    static std::map<std::string, Constructor> * m_constructors;
};

#endif // IMAGEIO_H
