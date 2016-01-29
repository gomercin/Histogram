//
//  HistogramManagerCls.hpp
//  Histogram
//
//  Created by Omer Karaduman on 24.01.2016.
//

#ifndef HistogramManagerCls_hpp
#define HistogramManagerCls_hpp
#include "ErrorLoggerCls.hpp"
#include "IntervalCls.hpp"
#include <map>
#include <list>

///HM-LLR-1 Class is designed to use templates
template <class T>
class HistogramManagerCls {
private:
    std::map<T, IntervalCls<T>* >* histogramMap;
    std::list<T>* outlierList;
    
public:
    HistogramManagerCls();
    ~HistogramManagerCls();
    
    void AddInterval(IntervalCls<T>* _interval);
    void AddEntry(T _entry);
    
    //HM-LLR-6 Public getters for internal data structures
    std::map<T, IntervalCls<T>* > GetHistogram();
    std::list<T> GetOutlierList();
    
};

template <typename T>
HistogramManagerCls<T>::HistogramManagerCls()
{
    histogramMap = new std::map<T, IntervalCls<T>* >();
    outlierList = new std::list<T>();
}

template <typename T>
HistogramManagerCls<T>::~HistogramManagerCls()
{
    delete histogramMap;
    delete outlierList;
}

///HM-LLR-2, HM-LLR-3
///This function will be used to insert interval values using the lower bounds as keys
template <typename T>
void HistogramManagerCls<T>::AddInterval(IntervalCls<T>* _interval)
{
    (*histogramMap)[_interval->Lower] = _interval;
}

///HM-LLR-4, HM-LLR-5
///This function is used to find the interval the entry resides on and increment the entry count
///if the entry cannot be found, it will be stored in the outlier list
template <typename T>
void HistogramManagerCls<T>::AddEntry(T _entry)
{
    IntervalCls<T>* potentialInterval = NULL;
    
    //find the largest key smaller than the parameter
    typename std::map<T, IntervalCls<T>* >::iterator itlow= histogramMap->lower_bound(_entry);
    
    if(itlow->first == _entry)
    {
        //if there is a key with the value of _entry, we will be here
        potentialInterval = itlow->second;
    }
    else if(itlow != histogramMap->begin())
    {
        //if the key is not equal to the entry and we are not already at the beginning
        //lower bound will be the previous item in map
        itlow--;
        potentialInterval = itlow->second;
    }
    else
    {
        //entry should be an outlier
        outlierList->push_back(_entry);
    }
    
    //the function will return false if the _entry does not belong to that interval
    if (potentialInterval != NULL)
    {
        if (potentialInterval->AddElement(_entry) == false)
        {
            //if the parameter does not fit in the interval, insert it into the outlier list
            outlierList->push_back(_entry);
        }
    }
}

template <typename T>
std::map<T, IntervalCls<T>* > HistogramManagerCls<T>::GetHistogram()
{
    return *histogramMap;
}

template <typename T>
std::list<T> HistogramManagerCls<T>::GetOutlierList()
{
    return *outlierList;
}
#endif /* HistogramManagerCls_hpp */
