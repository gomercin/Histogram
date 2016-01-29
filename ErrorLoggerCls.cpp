//
//  ErrorLoggerCls.cpp
//  Histogram
//
//  Created by Omer Karaduman on 25.01.2016.
//

#include "ErrorLoggerCls.hpp"

ErrorLoggerCls::ErrorLoggerCls()
{
    logStream.open("error.txt", std::ofstream::trunc);
    
    if (!logStream.is_open() || !logStream.good())
    {
        std::cout << "Couldn't open error.txt file for writing" << std::endl;
    }
}

void ErrorLoggerCls::Log(std::string logStr)
{
    if (!logStream.is_open() || !logStream.good())
    {
        std::cout << logStr << std::endl;
    }
    else
    {
        logStream << logStr << std::endl;
    }
}

void ErrorLoggerCls::ClearLog()
{
    if (logStream.is_open())
    {
        logStream.close();
    }
    
    logStream.open("error.txt", std::ofstream::trunc);
    
    if (!logStream.is_open() || !logStream.good())
    {
        std::cout << "Couldn't open error.txt file for writing" << std::endl;
    }
}