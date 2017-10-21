#ifndef _STRINGTRIVIAL_H
#define _STRINGTRIVIAL_H

#include <iostream>
#include <cstring>
#include <utility>

namespace trivial
{

class String
{
public:
    String()
    : m_dataptr(new char[1])
    {
        std::cout << "constructor()" << std::endl;
        *m_dataptr = '\0';
    }
    String(const char *str)
    : m_dataptr(new char[strlen(str) + 1])
    {
        std::cout << "constructor(char *)" << std::endl;
        strcpy(m_dataptr, str);
    }
    String(const String &rhs)
    : m_dataptr(new char[rhs.size() + 1])
    {
        std::cout << "copy constructor" << std::endl;
        strcpy(m_dataptr, rhs.c_str());
    }

    ~String() noexcept
    {
        std::cout << "destructor" << std::endl;
        delete[] m_dataptr;
    }

    String& operator=(const String& rhs)
    {
      std::cout << "copy operator=" << std::endl;

      char* tmp = rhs.m_dataptr;
      m_dataptr = new char[rhs.size() + 1];
      strcpy(m_dataptr, rhs.c_str());
      delete[] tmp;
      //String tmp(rhs);
      //swap(tmp);
      return *this;
    }
/*
    String(String&& rhs) noexcept
    : m_dataptr(rhs.m_dataptr)
    {
        std::cout << "move constructor" << std::endl;
        rhs.m_dataptr = nullptr;
    }

    String& operator=(String&& rhs)
    {
      std::cout << "move operator=" << std::endl;

      delete[] m_dataptr;
      m_dataptr = rhs.m_dataptr;
      rhs.m_dataptr = nullptr;

      return *this;
    }
*/

private:
    size_t size() const
    {
        return strlen(m_dataptr);
    }

    const char* c_str() const
    {
        return m_dataptr;
    }
    void swap(String& rhs)
    {
      std::swap(m_dataptr, rhs.m_dataptr);
    }

private:
    char *m_dataptr;
};

String getString()
{
    String str("string");
    return str;    //return "string";
}

}
#endif // STRINGTRIVIAL_H
