//
//  HistogramApplicationCls.hpp
//  Histogram
//
//  Created by Omer Karaduman on 24.01.2016.
//

#ifndef HistogramApplicationBaseCls_hpp
#define HistogramApplicationBaseCls_hpp

#include "ErrorLoggerCls.hpp"
#include "IOManagerBaseCls.hpp"
#include "HistogramManagerCls.hpp"

template <typename T>
class HistogramApplicationBaseCls {
    IOManagerBaseCls<T>* ioManager;
    HistogramManagerCls<T>* histogramManager;
    
public:
    HistogramApplicationBaseCls();
    ~HistogramApplicationBaseCls();
    
    void SetIOManager(IOManagerBaseCls<T>* _ioManager);
    void SetHistogramManager(HistogramManagerCls<T>* _histogramManager);
    void CreateHistogram();
    void ReportHistogram();
    void CreateAndReportHistogram();
};


template <typename T>
HistogramApplicationBaseCls<T>::HistogramApplicationBaseCls()
{
    
}

template <typename T>
HistogramApplicationBaseCls<T>::~HistogramApplicationBaseCls()
{
    delete ioManager;
    delete histogramManager;
}

template <typename T>
void HistogramApplicationBaseCls<T>::SetIOManager(IOManagerBaseCls<T>* _ioManager)
{
    ioManager = _ioManager;
    
    if (ioManager != NULL)
    {
        ioManager->Initialize();
    }
    else
    {
        ERROR_LOG("NULL argument to HistogramApplicationBaseCls.SetIOManager");
    }
}

template <typename T>
void HistogramApplicationBaseCls<T>::SetHistogramManager(HistogramManagerCls<T>* _histogramManager)
{
    histogramManager = _histogramManager;
    
    if (histogramManager == NULL)
    {
        ERROR_LOG("NULL argument to HistogramApplicationBaseCls.SetHistogramManager");
    }
}

template <typename T>
void HistogramApplicationBaseCls<T>::CreateHistogram()
{
    if (ioManager != NULL && histogramManager != NULL)
    {
        while (ioManager->IsEndOfInput() == false)
        {
            if (ioManager->IsReadingIntervals() == true)
            {
                IntervalCls<T>* interval = ioManager->ReadInterval();
                
                if (interval != NULL)
                {
                    histogramManager->AddInterval(interval);
                }
                //error handling is made in the ioManager
            }
            else
            {
                T entry;
                
                if (ioManager->ReadEntry(entry) == true)
                {
                    histogramManager->AddEntry(entry);
                }
                //error handling is made in the ioManager
            }
        }
    }
}

template <typename T>
void HistogramApplicationBaseCls<T>::ReportHistogram()
{
    if (ioManager != NULL && histogramManager != NULL)
    {
        ioManager->PrintHistogram(histogramManager);
    }
    else
    {
       ERROR_LOG("Histogram could not be reported, object had null fields");
    }
}

template <typename T>
void HistogramApplicationBaseCls<T>::CreateAndReportHistogram()
{
    CreateHistogram();
    ReportHistogram();
}


#endif /* HistogramApplicationCls_hpp */
