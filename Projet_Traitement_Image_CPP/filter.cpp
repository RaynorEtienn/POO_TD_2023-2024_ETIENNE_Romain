#include "filter.h"
#include <assert.h>

// #include <omp.h>

Image *
Filter::create(Image const * const _in)
{
    return _in->duplicate();
}

void
Filter::apply(Image const * const _in, Image * const _out) const
{
    //check if the images exist and have the same size
    assert((_in != nullptr)   and (_out != nullptr));
    assert((_in->width() > 0) and (_out->width() > 0));
    assert((_in->height()> 0) and (_out->height()> 0));
    assert((_in->depth() > 0) and (_out->depth() > 0));
    for(unsigned int i =0; i < _out->width()*_out->height() ; i++)
    {
        compute(i%_out->width(),i/_out->width(),_in,_out);
    }
}
