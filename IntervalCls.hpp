//
//  IntervalCls.hpp
//  Histogram
//
//  Created by Omer Karaduman on 24.01.2016.
//

#ifndef IntervalCls_hpp
#define IntervalCls_hpp
#include "ErrorLoggerCls.hpp"

//IW-LLR-2 Class is created using a template
template <typename T>
class IntervalCls {
public:
    
    T Lower;
    T Upper;
    unsigned int EntryCount;

    IntervalCls() {};
    
    ///IW-LLR-1 Constructor that initializes the class members
    IntervalCls(T _lower, T _upper) :
        Lower(_lower),
        Upper(_upper),
        EntryCount(0)
    {
        if (_lower > _upper)
        {
            std::stringstream ss;
            ss << "Invalid lower and upper boundaries: " << _lower << ", " << _upper;
            ERROR_LOG(ss.str());
        }
    };
    
    IntervalCls(const IntervalCls& other) :
        Lower(other.Lower),
        Upper(other.Upper),
        EntryCount(other.EntryCount) {};
    
    bool AddElement(T _element);
};

///Checks if the entry parameter is in the interval range
///and increments the counter if it is
///an epsilon check is not added as the input is not
///expected to be an output of a calculation
template <typename T>
bool IntervalCls<T>::AddElement(T _entry) {
    bool elementWasAdded = false;
    
    if (_entry >= Lower && _entry < Upper) {
        EntryCount++;
        elementWasAdded = true;
    }
    
    return elementWasAdded;
}

#endif /* IntervalCls_hpp */
