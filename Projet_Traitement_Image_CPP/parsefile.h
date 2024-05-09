#ifndef PARSEFILE_H
#define PARSEFILE_H

#include "resolver.h"
#include "imageio.h"
#include "filter.h"
#include <vector>

class ParseFile
{
public: // Constructors and destructor
    /** Initialize the parsing system for finding files
     */
    ParseFile();
public: // File mangement
    /** Add the path in the list of directories to search in
     */
    void prepend(filesystem::Path const & _path);
    /** Read the content of the file and store it
     */
    bool parse(std::string const & _filename);

public: // Image processing
    /** Apply the process (read the image, apply filters and save the new image)
     */
    bool apply() const;
private: // Attributes
    filesystem::Resolver  m_resolver;
    std::string           m_inimage;
    std::string           m_ouimage;
    std::vector<Filter *> m_filters;
private: // Static functions
    /** Create the loader according to the image extension
     * return nullptr when failed
     */
    static ImageIO const * createImageIO(std::string const &);
};

#endif // PARSEFILE_H
