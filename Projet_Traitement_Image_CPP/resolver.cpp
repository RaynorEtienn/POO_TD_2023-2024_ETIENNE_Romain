// Copyright 2015 Wenzel Jakob. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the filesystem/LICENSE file.

#include "resolver.h"

#include <iostream>

namespace filesystem
{

Resolver::Resolver()
{
    m_paths.push_back(Path::getcwd());
}

Resolver::Resolver(Resolver const & res)
{
    m_paths = res.m_paths;
}

size_t
Resolver::size() const
{
    return m_paths.size();
}

Resolver::iterator
Resolver::begin()
{
    return m_paths.begin();
}

Resolver::iterator
Resolver::end()
{
    return m_paths.end();
}

Resolver::const_iterator
Resolver::begin() const
{
    return m_paths.begin();
}

Resolver::const_iterator
Resolver::end()   const
{
    return m_paths.end();
}

void
Resolver::erase(iterator & it)
{
    m_paths.erase(it);
}

void
Resolver::prepend(Path const &path)
{
    m_paths.insert(m_paths.begin(), path);
}

void
Resolver::append(Path const &path)
{
    m_paths.push_back(path);
}


Path
Resolver::resolve(Path const &value) const
{
    for (const_iterator it = m_paths.begin(); it != m_paths.end(); ++it)
    {
        Path combined = *it / value;
        if (combined.exists())
        {
            return combined;
        }
    }
    return Path();
}

}
