#include <iostream>
#include "assert.h"

#include "parsefile.h"


int
main(int argc, char *argv[])
{
    if(argc !=2 )
    {
        std::cerr << argv[0] << " must be followed by a unique arguement, a file" << std::endl;
        return 1;
    }

    ParseFile parser; // create the mechanism to look for a file
    parser.prepend(PROJECT_DIR); // add the project directory into the path
    if(filesystem::Path(argv[1]).is_absolute())
    {
        parser.prepend(filesystem::Path(argv[1]).parent_path()) ; // add the parent path of the file when absolute definition
    }
    //parse the script file precised in the command line
    if(!parser.parse(argv[1]))
    {//failed reading script
        return 1;
    }
    //run the script
    if(parser.apply())
    {//failed apply
        return 1;
    }

    return 0;
}
