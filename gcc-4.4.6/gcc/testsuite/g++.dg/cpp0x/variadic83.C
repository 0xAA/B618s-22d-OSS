// PR c++/31441
// { dg-options "-std=gnu++0x" }

template<typename> struct A;

template<typename... T> struct A<T...> { }; // { dg-bogus "cannot expand" "" { xfail *-*-* } }

A<int> a; // { dg-bogus "incomplete type" "" { xfail *-*-* } }
