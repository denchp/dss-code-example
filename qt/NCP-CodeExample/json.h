#ifndef JSON_H
#define JSON_H
#include <iostream>

using namespace std;

class json
{
public:
    json();
    template<class T>
    T parse(string data);
};
#endif // JSON_H
