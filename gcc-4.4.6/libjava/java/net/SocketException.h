
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __java_net_SocketException__
#define __java_net_SocketException__

#pragma interface

#include <java/io/IOException.h>
extern "Java"
{
  namespace java
  {
    namespace net
    {
        class SocketException;
    }
  }
}

class java::net::SocketException : public ::java::io::IOException
{

public:
  SocketException();
  SocketException(::java::lang::String *);
private:
  static const jlong serialVersionUID = -5935874303556886934LL;
public:
  static ::java::lang::Class class$;
};

#endif // __java_net_SocketException__