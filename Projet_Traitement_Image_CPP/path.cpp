// Copyright 2015 Wenzel Jakob. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the filesystem/LICENSE file.
#include "path.h"

#include <stdexcept>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#if !defined(WIN32)
# include <sys/stat.h>
# include <unistd.h>
#endif

#if defined(__linux)
# include <linux/limits.h>
#endif

namespace filesystem
{

Path::Path()
    : m_type(native_path), m_absolute(false)
{
}

Path::Path(Path const &path)
    : m_type(path.m_type), m_path(path.m_path), m_absolute(path.m_absolute)
{
}

Path::Path(char const * const string)
{
    set(string);
}

Path::Path(std::string const  &string)
{
    set(string);
}
#if defined(WIN32)
Path::Path(std::wstring const &wstring)
{
    set(wstring);
}

Path::Path(wchar_t const * const wstring)
{
    set(wstring);
}
#endif

size_t
Path::size() const
{
    return m_path.size();
}

bool
Path::empty() const
{
    return m_path.empty();
}

bool
Path::is_absolute() const
{
    return m_absolute;
}

Path
Path::make_absolute() const
{
#if !defined(WIN32)
    char temp[PATH_MAX];
    if (realpath(str().c_str(), temp) == NULL)
    {
        throw std::runtime_error("Internal error in realpath(): " + std::string(strerror(errno)));
    }
    return Path(temp);
#else
    std::wstring value = wstr(), out(MAX_PATH, '\0');
    DWORD length = GetFullPathNameW(value.c_str(), MAX_PATH, &out[0], NULL);
    if (length == 0)
    {
        throw std::runtime_error("Internal error in realpath(): " + std::to_string(GetLastError()));
    }
    return Path(out.substr(0, length));
#endif
}

bool
Path::exists() const
{
#if defined(WIN32)
    return GetFileAttributesW(wstr().c_str()) != INVALID_FILE_ATTRIBUTES;
#else
    struct stat sb;
    return stat(str().c_str(), &sb) == 0;
#endif
}

bool
Path::is_directory() const
{
#if defined(WIN32)
    DWORD result = GetFileAttributesW(wstr().c_str());
    if (result == INVALID_FILE_ATTRIBUTES)
    {
        return false;
    }
    return (result & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
    struct stat sb;
    if (stat(str().c_str(), &sb))
    {
        return false;
    }
    return S_ISDIR(sb.st_mode);
#endif
}

bool
Path::is_file() const
{
#if defined(WIN32)
    DWORD result = GetFileAttributesW(wstr().c_str());
    if (result == INVALID_FILE_ATTRIBUTES)
    {
        return false;
    }
    return (result & FILE_ATTRIBUTE_NORMAL) != 0;
#else
    struct stat sb;
    if (stat(str().c_str(), &sb))
    {
        return false;
    }
    return S_ISREG(sb.st_mode);
#endif
}

std::string
Path::extension() const
{
    if (empty())
    {
        return "";
    }
    std::string const  &last = m_path[m_path.size()-1];
    size_t pos = last.find_last_of(".");
    if (pos == std::string::npos)
    {
        return "";
    }
    return last.substr(pos+1);
}

Path
Path::parent_path() const
{
    Path result;
    result.m_absolute = m_absolute;

    if (m_path.empty())
    {
        if (!m_absolute)
        {
            result.m_path.push_back("..");
        }
    }
    else
    {
        size_t until = m_path.size() - 1;
        for (size_t i = 0; i < until; ++i)
        {
            result.m_path.push_back(m_path[i]);
        }
    }
    return result;
}

Path
Path::operator/(Path const &other) const
{
    if (other.m_absolute)
    {
        throw std::runtime_error("Path::operator/(): expected a relative path!");
    }
    if (m_type != other.m_type)
    {
        throw std::runtime_error("Path::operator/(): expected a path of the same type!");
    }

    Path result(*this);

    for (size_t i=0; i<other.m_path.size(); ++i)
    {
        result.m_path.push_back(other.m_path[i]);
    }

    return result;
}

std::string
Path::str(path_type type) const
{
    std::ostringstream oss;

    if (m_type == posix_path && m_absolute)
    {
        oss << "/";
    }

    for (size_t i=0; i<m_path.size(); ++i)
    {
        oss << m_path[i];
        if (i+1 < m_path.size())
        {
            if (type == posix_path)
            {
                oss << '/';
            }
            else
            {
                oss << '\\';
            }
        }
    }

    return oss.str();
}

Path
Path::getcwd()
{
#if !defined(WIN32)
    char temp[PATH_MAX];
    if (::getcwd(temp, PATH_MAX) == NULL)
    {
        throw std::runtime_error("Internal error in getcwd(): " + std::string(strerror(errno)));
    }
    return Path(temp);
#else
    std::wstring temp(MAX_PATH, '\0');
    if (!_wgetcwd(&temp[0], MAX_PATH))
    {
        throw std::runtime_error("Internal error in getcwd(): " + std::to_string(GetLastError()));
    }
    return Path(temp.c_str());
#endif
}

void
Path::set(std::string const  &str, path_type type)
{
    m_type = type;
    if (type == windows_path)
    {
        m_path = tokenize(str, "/\\");
        m_absolute = str.size() >= 2 && std::isalpha(str[0]) && str[1] == ':';
    }
    else
    {
        m_path = tokenize(str, "/");
        m_absolute = !str.empty() && str[0] == '/';
    }
}

Path &
Path::operator=(std::string const  &str)
{
    set(str);
    return *this;
}

Path &
Path::operator=(Path const &path)
{
    m_type = path.m_type;
    m_path = path.m_path;
    m_absolute = path.m_absolute;
    return *this;
}

std::ostream &operator<<(std::ostream &os, Path const &path)
{
    os << path.str();
    return os;
}

#if defined(WIN32)
std::wstring
Path::wstr() const
{
    std::string temp = str();
    int size = MultiByteToWideChar(CP_UTF8, 0, &temp[0], (int)temp.size(), NULL, 0);
    std::wstring result(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, &temp[0], (int)temp.size(), &result[0], size);
    return result;
}


void
Path::set(std::wstring const &wstring, path_type type)
{
    std::string string;
    if (!wstring.empty())
    {
        int size = WideCharToMultiByte(CP_UTF8, 0, &wstring[0], (int)wstring.size(),NULL, 0, NULL, NULL);
        string.resize(size, 0);
        WideCharToMultiByte(CP_UTF8, 0, &wstring[0], (int)wstring.size(),&string[0], size, NULL, NULL);
    }
    set(string, type);
}

Path &
Path::operator=(std::wstring const &str)
{
    set(str);
    return *this;
}
#endif


std::vector<std::string>
Path::tokenize(std::string const  &string, std::string const  &delim)
{
    std::string::size_type lastPos = 0, pos = string.find_first_of(delim, lastPos);
    std::vector<std::string> tokens;

    while (lastPos != std::string::npos)
    {
        if (pos != lastPos)
        {
            tokens.push_back(string.substr(lastPos, pos - lastPos));
        }
        lastPos = pos;
        if ((lastPos == std::string::npos) or ((lastPos + 1) == string.length()))
        {
            break;
        }
        pos = string.find_first_of(delim, ++lastPos);
    }

    return tokens;
}

}
