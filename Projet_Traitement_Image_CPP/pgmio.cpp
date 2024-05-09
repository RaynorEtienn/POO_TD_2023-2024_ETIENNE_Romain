#include "pgmio.h"
#include "image1i16.h"

#include <fstream>
#include <iostream>
#include <cmath>

// skip all lines starting by #. _line contains the first non-comment line if the end of file was not reached
inline void
skipcomments(std::ifstream & _file, std::string & _line)
{
    while(!_file.eof())
    { // the end of the file is not reached
        std::getline(_file,_line);
        if(_line[0]=='#')
        {//skip a comment
            continue;
        }
        else
        { // no more a comment
            return;
        }
    }
}

Image *
PGMIO::load(std::string const & _file) const
{

    std::ifstream infile(_file); // create a file input stream from filename

    if(!infile.is_open())
    {
        std::cerr << "We can't open " << _file << std::endl;
        return nullptr;
    }

    std::string line; // current line
    // skip comments
    skipcomments(infile,line);
    //looking for P2: check the type of image (2)
    if((line.size() >= 2 ) and (line[0]=='P') and (line[1] == '2'))
    {//P2 exist
        if((line.size() >= 3) and (line[2] !=' '))
        {//but not followed by a space
            std::cerr << _file << " is not an ASCII PGM file" << std::endl;
            infile.close();
            return nullptr;
        }
    }
    else
    {
        std::cerr << _file << " does not start with P2" << std::endl;
        infile.close();
        return nullptr;
    }
    //skip comments
    skipcomments(infile,line);
    //read dimensions in latest line
    std::size_t indexofnextinteger;
    unsigned int const width = std::stoi(line,&indexofnextinteger);//get width
    if((indexofnextinteger == 0) or (indexofnextinteger == line.size()))
    {// no width or no width and height
        std::cerr << "no width height found in " << _file << std::endl;
        infile.close();
        return nullptr;
    }
    //we found a value and there are some remaining characters in the line
    line.erase(0,indexofnextinteger);
    unsigned int const heigth = std::stoi(line,&indexofnextinteger);//get height

    //skip comments
    skipcomments(infile,line);
    // get max value
    unsigned int max = std::stoi(line,&indexofnextinteger);

    Image1UI16 * res = new Image1UI16(width,heigth,max);

    unsigned int counter = 0;
    while( (!infile.eof()) and (counter < width*heigth))
    {
        unsigned int val;
        infile >> val; // read value
        res->set(counter % width,counter/width,0,float(val)/float(max));
        counter++;
    }
    infile.close();
    if(counter == width*heigth)
    {// we read everything
        return res;
    }
    else
    {// something went wrong
        std::cerr << "Not enough pixels in " << _file << std::endl;
        delete res;
        return nullptr;
    }

}

bool
PGMIO::save(std::string const & _file, Image const * const  _image) const
{
    std::ofstream outfile(_file); // create a file output stream from filename

    if(!outfile.is_open())
    {
        std::cerr << "We can't open " << _file << std::endl;
        return false;
    }
    outfile << "P2\n";
    outfile << _image->width() << " " << _image->height() << "\n";
    Image1UI16 const * const image = dynamic_cast<Image1UI16 const * const>(_image);//try to convert to Image1UI16
    unsigned short const max = (image!=nullptr)?image->max():65535;
    outfile << max << "\n";
    for(unsigned int h = 0; h < _image->height(); h++)
    {
        for(unsigned int w = 0; w < _image->width() ; w ++)
        {
            unsigned short val = std::round(_image->val(w,h,0)*float(max));
            outfile << val << " ";
        }
        outfile << "\n";
    }
    outfile.close();
    return true;
}

static ImageIO::Register<PGMIO> registerPGMIO1("PGM");
static ImageIO::Register<PGMIO> registerPGMIO2("pgm");
