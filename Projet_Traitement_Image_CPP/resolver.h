// Copyright 2015 Wenzel Jakob. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the filesystem/LICENSE file.

#if !defined(__FILESYSTEM_Resolver_H)
#define __FILESYSTEM_Resolver_H

#include "path.h"

namespace filesystem
{

/** Simple class for manipulating paths on Linux/Windows/Mac OS
 * This class is just a temporary workaround to avoid the heavy boost
 * dependency until boost::filesystem is integrated into the standard template
 * library at some point in the future.
 */
class Resolver
{
public:
    /** Default constructor to an empty set of paths
     */
    Resolver();
    /** Copy constructor
     */
    Resolver(Resolver const &);
    /** Number of paths
     */
    size_t size() const;
    /** add the path in front of the set
     */
    void prepend(Path const &path) ;
    /** add the path at the end of the set
     */
    void append(Path const &path)  ;
    /** check if value exist in the set of path and return the correct absolute path
     */
    Path resolve(Path const &value) const;
public: // Iterators
    typedef std::vector<Path>::iterator iterator;
    typedef std::vector<Path>::const_iterator const_iterator;
    iterator begin();
    iterator end()  ;
    const_iterator begin() const ;
    const_iterator end()   const ;
    /** suppress the path pointed by it
     */
    void erase(iterator & it) ;
private:
    std::vector<Path> m_paths;
};

} /* namespace filesystem */

#endif /* __FILESYSTEM_Resolver_H */
