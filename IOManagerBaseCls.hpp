//
//  IOManagerBaseCls.hpp
//  Histogram
//
//  Created by Omer Karaduman on 24.01.2016.
//

#ifndef IOManagerBaseCls_hpp
#define IOManagerBaseCls_hpp

#include "ErrorLoggerCls.hpp"
#include "IntervalCls.hpp"
#include "HistogramManagerCls.hpp"

///IOM-LLR-1 Class is created using a template
template <typename T>
class IOManagerBaseCls {
    
protected:
    ///IOM-LLR-2 protected base constructor to ensure derived classes will need to implement
    ///their custom constructors.
    IOManagerBaseCls() {};
    
public:
    virtual ~IOManagerBaseCls() {};
    
    ///IOM-LLR-3
    virtual bool IsReadingIntervals() = 0;
    
    ///IOM-LLR-4
    virtual IntervalCls<T>* ReadInterval() = 0;
    
    ///IOM-LLR-7
    virtual bool ReadEntry(T&) = 0;
    
    ///IOM-LLR-11
    virtual bool Initialize() = 0;
    
    ///IOM-LLR-12
    virtual bool IsEndOfInput() = 0;
    
    ///IOM-LLR-13
    virtual void PrintHistogram(HistogramManagerCls<T>* histogram) = 0;
};

#endif /* IOManagerBaseCls_hpp */
