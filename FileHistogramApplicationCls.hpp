//
//  FileHistogramApplicationCls.hpp
//  Histogram
//
//  Created by Omer Karaduman on 24.01.2016.
//

#ifndef FileHistogramApplicationCls_hpp
#define FileHistogramApplicationCls_hpp

#include "ErrorLoggerCls.hpp"
#include "HistogramApplicationBaseCls.hpp"
#include "HistogramManagerCls.hpp"
#include "FileIOManagerCls.hpp"

template <typename T>
class FileHistogramApplicationCls : public HistogramApplicationBaseCls<T> {
private:
    FileHistogramApplicationCls() {};
    
public:
    FileHistogramApplicationCls (std::string fileName)
    {
        CLEAR_ERRORS;
        this->SetHistogramManager(new HistogramManagerCls<T>());
        this->SetIOManager(new FileIOManagerCls<T>(fileName));
    }
};

#endif /* FileHistogramApplicationCls_hpp */
