#include <fstream>
#include <iostream>

#include "parsefile.h"
#include "pgmio.h"
#include "ppmio.h"
#include "bmpio.h"
#include "filtergaussian.h"
#include "filterbilateral.h"
#include "filterrescaling.h"
#include "filterdownscaling.h"
#include "filterupscaling.h"

ParseFile::ParseFile()
{
}

void
ParseFile::prepend(filesystem::Path const & _path)
{
    m_resolver.prepend(_path); // add _path in the list of available directories
}

bool
ParseFile::parse(std::string const & _filename)
{
    filesystem::Path l_filename = m_resolver.resolve(_filename); // find the file

    if(l_filename.empty())
    {
        std::cerr << "We didn't find " << _filename << std::endl;
        return false;
    }

    std::ifstream infile(l_filename.str()); // create a file input stream from filename

    if(!infile.is_open())
    {
        std::cerr << "We can't open " << l_filename << std::endl;
        return false;
    }

    filesystem::Resolver l_resolver(m_resolver);//resolver to look for a file in a set of path

    std::string line;
    //read first line with inimg
    std::getline(infile,line);
    std::size_t found = line.find("inimg ");
    if((found != std::string::npos) and (found == 0))
    { //we find the line starting by inimg
        line.erase(line.begin(),line.begin()+6); // we remove inimg
        if(filesystem::Path(line).is_absolute())
        {
            l_resolver.prepend(filesystem::Path(line).parent_path()); // add path if absolute filename was used
        }
        filesystem::Path l_inimg = l_resolver.resolve(line); // find file
        if(l_inimg.empty())
        {
            std::cerr << "We didn't find image " << line << std::endl;
            return false;
        }
        else
        {
            m_inimage=l_inimg.str();
        }
    }
    //read second line with ouimg
    std::getline(infile,line);
    found = line.find("ouimg ");
    if((found != std::string::npos) and (found == 0))
    { //we find the line starting by inimg
        line.erase(line.begin(),line.begin()+6); // we remove ouimg
        if(filesystem::Path(line).is_absolute())
        {
            m_ouimage = line;
        }
        else
        {
            m_ouimage = (*(l_resolver.begin())/filesystem::Path(line)).str();//create an absolute path
        }
    }
    while(!infile.eof())
    { // the end of the file is not reached
        std::getline(infile,line);
        std::size_t found = line.find("filter ");
        // if found, find the name of the parameters, create the corresponding filter and initialize it with the corresponding parameters
        if ((found != std::string::npos) and (found == 0))
        {
            line.erase(line.begin(),line.begin()+6); // we remove filter
            try
            {
                std::size_t found = line.find("rescaling");
                if (found != std::string::npos)
                // we find the filter rescaling
                {
                    std::cout << "filter rescaling found" << std::endl;
                    Rescaling * mfilt = new Rescaling(); // we create the filter
                    m_filters.push_back(mfilt); // we push the filter in the list of the filter we have to apply
                    line.erase(line.begin(),line.begin()+10); // we remove rescaling
                    mfilt->setParameters(line); // we initialize the parameters of the filter
                }

                found = line.find("downscaling");
                if (found != std::string::npos)
                // we find the filter downscaling
                {
                    std::cout << "filter downscaling found" << std::endl;
                    filterdownscaling * mfilt = new filterdownscaling(); // we create the filter
                    m_filters.push_back(mfilt); // we push the filter in the list of the filter we have to apply
                    line.erase(line.begin(),line.begin()+12); // we remove downscaling
                    mfilt->setParameters(line); // we initialize the parameters of the filter
                }

                found = line.find("upscaling");
                if (found != std::string::npos)
                // we find the filter upscaling
                {
                    std::cout << "filter upscaling found" << std::endl;
                    filterupscaling * mfilt = new filterupscaling(); // we create the filter
                    m_filters.push_back(mfilt); // we push the filter in the list of the filter we have to apply
                    line.erase(line.begin(),line.begin()+10); // we remove upscaling
                    mfilt->setParameters(line); // we initialize the parameters of the filter
                }

                found = line.find("gaussian");
                if (found != std::string::npos)
                // we find the filter gaussian
                {
                    std::cout << "filter gaussian found" << std::endl;
                    Gaussian * mfilt = new Gaussian(); // we create the filter
                    m_filters.push_back(mfilt); // we push the filter in the list of the filter we have to apply
                    line.erase(line.begin(),line.begin()+9); // we remove gaussian
                    mfilt->setParameters(line); // we initialize the parameters of the filter
                }

                found = line.find("bilateral");
                if (found != std::string::npos)
                // we find the filter bilateral
                {
                    std::cout << "filter bilateral found" << std::endl;
                    Bilateral * mfilt = new Bilateral(); // we create the filter
                    m_filters.push_back(mfilt); // we push the filter in the list of the filter we have to apply
                    line.erase(line.begin(),line.begin()+10); // we remove bilateral
                    mfilt->setParameters(line); // we initialize the parameters of the filter
                }
            }
            catch (std::invalid_argument& e)
            {
                std::cout << e.what() << std::endl;
                return -1;
            }
        }

    }
    return true;
}

bool
ParseFile::apply() const
{
    ImageIO const * const inio = createImageIO(filesystem::Path(m_inimage).extension());
    if(inio==nullptr)
    {//loader unavailable
        return false;
    }
    ImageIO const * const outio = createImageIO(filesystem::Path(m_ouimage).extension());
    if(outio==nullptr)
    {//writer unavailable
        delete inio;
        return false;
    }
    //load the input image
    Image * imgin = inio->load(m_inimage);
    delete inio; //used, no more needed
    if(imgin==nullptr)
    {//failed reading image
        delete outio;
        return false;
    }
    //for each filters, if there is an input image
    for(unsigned int i =0; (imgin!=nullptr) and (i < m_filters.size()); i++ )
    {
        // create the output image (Filter::create) : out = filter->create(in)
        Image * resimg = m_filters[i]->create(imgin);
        if(resimg==nullptr)
        {//the creation of input image failed
            std::cerr << "Unable to create output image for filter" << std::endl;
        }
        else
        {//apply the filter
            m_filters[i]->apply(imgin,resimg);
        }
        delete imgin;//delete input image: no more needed
        imgin=resimg;//next input image is the current result: it will stop the loop if resimg==nullptr
    }
    //save the result
    bool res=false;
    if(imgin!=nullptr)
    {// everything seems to be oK
        res = outio->save(m_ouimage,imgin);
        delete imgin;//delete input image: no more needed
    }
    delete outio; // no more needed
    if(res==false)
    {//failed in writing the image
        std::cerr << "Failed to save " << m_ouimage << std::endl;
    }
    return res;
}

ImageIO const *
ParseFile::createImageIO(std::string const & _extension)
{
    ImageIO const * res = ImageIO::createInstance(_extension);
    if(res == nullptr)
    {
        std::cerr << "Unknown extension " << _extension << std::endl;
    }
    return res;
}
