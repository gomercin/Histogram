//
//  ErrorLoggerCls.hpp
//  Histogram
//
//  Created by Omer Karaduman on 25.01.2016.
//

#ifndef ErrorLoggerCls_hpp
#define ErrorLoggerCls_hpp

#define ERROR_LOG(x) ErrorLoggerCls::GetInstance()->Log(x)
#define CLEAR_ERRORS ErrorLoggerCls::GetInstance()->ClearLog()

#include "ErrorLoggerCls.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

class ErrorLoggerCls {
private:
    std::ofstream logStream;
    
    ErrorLoggerCls();
public:
    
    static ErrorLoggerCls* GetInstance()
    {
        static ErrorLoggerCls instance;
        
        return &instance;
    }
    
    void Log(std::string logStr);
    
    void ClearLog();
};

#endif /* ErrorLoggerCls_hpp */
