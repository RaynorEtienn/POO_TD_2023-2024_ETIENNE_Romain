// Copyright 2015 Wenzel Jakob. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the filesystem/LICENSE file.

#if !defined(__FILESYSTEM_PATH_H)
#define __FILESYSTEM_PATH_H

#include <string>
#include <vector>

#if defined(WIN32)
# include <windows.h>
#endif

namespace filesystem {

/**
 * \brief Simple class for manipulating paths on Linux/Windows/Mac OS
 *
 * This class is just a temporary workaround to avoid the heavy boost
 * dependency until boost::filesystem is integrated into the standard template
 * library at some point in the future.
 */
class Path
{
public: //subtypes
    enum path_type
    {
        windows_path = 0,
        posix_path = 1,
#if defined(WIN32)
        native_path = windows_path
#else
        native_path = posix_path
#endif
    };
public: // Constructors
    /** create an absolute path which type is native_path
     */
    Path();
    /** create a copy of the Path path
     */
    Path(Path const &path);
    /** create a Path containing the path in string
     */
    Path(char const * const string);
    /** create a Path containing the path in string
     */
    Path(std::string const  &string);
#if defined(WIN32)
    /** create a Path containing the path in wstring
     */
    Path(std::wstring const &wstring);
    /** create a Path containing the path in wstring
     */
    Path(wchar_t const * const wstring);
#endif
public: // Access and other functionnalites
    /** Length of the path
     */
    size_t size() const;
    /** Check if the path is empty
     */
    bool empty() const;
    /** Check if the path is an absolute one
     */
    bool is_absolute() const;
    /** Convert local path to absolute path
     */
    Path make_absolute() const;
    /** Check if the path  / file exist
     */
    bool exists() const;
    /** Check if the path point to a directory
     */
    bool is_directory() const;
    /** Check if the path point to a file
     */
    bool is_file() const;
    /** Get the extension of a file
     */
    std::string extension() const;
    /** Get parent path of a file
     */
    Path parent_path() const;
public: // Set values
    /** Set the values of a path
     */
    void set(std::string const  &str, path_type type = native_path);
#if defined(WIN32)
    void set(std::wstring const &wstring, path_type type = native_path);
#endif
    /** Affectation
     */
    Path &operator=(std::string const  &str);
    Path &operator=(Path const &path);
#if defined(WIN32)
    Path &operator=(std::wstring const &str);
#endif
public: // Operators, manipulate and convert
    /** Concatenate two relative path of same type
     */
    Path operator/(Path const &other) const;
    /** convert path to string
     */
    std::string str(path_type type = native_path) const;
#if defined(WIN32)
    std::wstring wstr() const;
#endif
    /**
     */
    static Path getcwd();
    /** Display the path in an output stream
     */
    friend std::ostream &operator<<(std::ostream &os, Path const &path);
protected:
    path_type m_type;
    std::vector<std::string> m_path;
    bool m_absolute;
protected:
    static std::vector<std::string> tokenize(std::string const  &string, std::string const  &delim);
};

} /* namespace filesystem */

#endif /* __FILESYSTEM_PATH_H */
