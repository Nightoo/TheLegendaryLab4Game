#include <iostream>

class Object{
public:
    std::string symbol;
    std::string set_object(){
        return symbol;
    };
};

class Wall: public Object{
public:
    std::string symbol = "#";
};

class Door: public Object{
public:
    std::string symbol = "0";
};

class Rock: public Object{
public:
    std::string symbol = "*";
};

class Key: public Object{
public:
    std::string symbol = "K";
};

class Empty: public Object{
public:
    std::string symbol = " ";
};
