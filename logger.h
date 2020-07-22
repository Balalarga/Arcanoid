#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace Logger{
    template <class T>
    void log(T data){
        std::cout<<"INFO: ";
        std::cout<<data<<std::endl;
    }

    template <class T>
    void error(T data){
        std::cout<<"ERROR: ";
        std::cout<<data<<std::endl;
    }
};

#endif // LOGGER_H
