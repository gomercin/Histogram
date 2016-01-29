//
//  FileIOManagerCls.hpp
//  Histogram
//
//  Created by Omer Karaduman on 24.01.2016.
//

#ifndef FileIOManagerCls_hpp
#define FileIOManagerCls_hpp

#include "ErrorLoggerCls.hpp"
#include "IOManagerBaseCls.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

const std::string INTERVAL_BEGIN_STR = "Intervals:";
const std::string ENTRY_BEGIN_STR = "Entries:";

///FBUIM-LLR-1 Class is inherited from IOManagerBaseCls and implements the virtual functions
template <typename T>
class FileIOManagerCls : public IOManagerBaseCls<T> {
private:
    std::string inputFileName;
    std::ifstream inputStream;
    
    bool isReadingIntervals;
    bool isEndOfInput;
    bool hasFoundIntervalBeginStr;
    
    bool isLineWhiteSpace(std::string line);
    
    int lineCounter;
public:
    ///FBUIM-LLR-3
    FileIOManagerCls(std::string fileName);
    ~FileIOManagerCls() {inputStream.close();};
    
    ///IOM-LLR-3
    bool IsReadingIntervals();
    
    ///IOM-LLR-4
    IntervalCls<T>* ReadInterval();
    
    ///IOM-LLR-7
    bool ReadEntry(T&);
    
    ///IOM-LLR-11
    bool Initialize();
    
    ///IOM-LLR-12
    bool IsEndOfInput();
    
    ///IOM-LLR-13
    void PrintHistogram(HistogramManagerCls<T>* histogram);
    
};

template <typename T>
FileIOManagerCls<T>::FileIOManagerCls(std::string fileName)
{
    inputFileName = fileName;
    
    isReadingIntervals = true;
    isEndOfInput = false;
    hasFoundIntervalBeginStr = false;
    lineCounter = 0;
}

template <typename T>
bool FileIOManagerCls<T>::IsReadingIntervals()
{
    return isReadingIntervals;
}

template <typename T>
bool FileIOManagerCls<T>::isLineWhiteSpace(std::string line)
{
    return line.find_first_not_of (" \t") == line.npos;
}

template <typename T>
IntervalCls<T>* FileIOManagerCls<T>::ReadInterval()
{
    IntervalCls<T>* output = NULL;
    
    if (!inputStream.is_open() || !inputStream.good())
    {
        if (!inputStream.eof())
        {
            ERROR_LOG("File cannot be read in FileIOManagerCls.ReadInterval");
        }
        
        isEndOfInput = true;
    }
    else if (IsReadingIntervals() == true)
    {
        std::string line;
        bool continueReading = true;
        
        while (continueReading == true)
        {
            if (std::getline(inputStream, line))
            {
                lineCounter++;
                
                if (isLineWhiteSpace(line) == true)
                {
                    //skip the line, try the next line
                    //no error will be reported
                    continueReading = true;
                }
                else if (line == INTERVAL_BEGIN_STR)
                {
                    // input file should start with the interval begin str
                    // and that must be the only instance of that string
                    if (hasFoundIntervalBeginStr == false)
                    {
                        hasFoundIntervalBeginStr = true;
                    }
                    else
                    {
                        //entering here means there are multiple INTERVAL_BEGIN_STR in the input file
                        //we  will report it as an error
                        
                        std::stringstream ss;
                        ss << "Incorrect instance of " << INTERVAL_BEGIN_STR << " in input file, at line " << lineCounter;
                        ERROR_LOG(ss.str());
                    }
                    
                    //in any case the line will be skipped
                    continueReading = true;
                }
                else if (line == ENTRY_BEGIN_STR)
                {
                    //we have come to the end of the intervals, will return null
                    isReadingIntervals = false;
                    continueReading = false;
                    output = NULL;
                }
                else
                {
                    //we might have a valid interval line
                    std::istringstream lineAsStream(line);
                    
                    T lowerBound;
                    T upperBound;
                    
                    //trying to read the line into two variables of our template type
                    //error handling is shifted to stream>> operator
                    if ((lineAsStream >> lowerBound >> upperBound))
                    {
                        output = new IntervalCls<T>(lowerBound, upperBound);
                        continueReading = false;
                    }
                    else
                    {
                        //the line may not contain an interval,
                        //or the interval may not be parsed
                        //we will skip the line as right now, we should have intervals
                        continueReading = true;
                        
                        std::stringstream ss;
                        ss << "Line cannot be parsed as interval \"" << line << "\" in input file, at line " << lineCounter;
                        ERROR_LOG(ss.str());
                    }
                }
            }
            else
            {
                //the line could not be read, we do not need to try to further read the input file
                //we may be in the end of file, if we aren't, an error will be logged
                
                if (!inputStream.eof())
                {
                    std::stringstream ss;
                    ss << "Line could not be read from the input file at line number \"" << lineCounter;
                    ERROR_LOG(ss.str());
                }
                
                isEndOfInput = true;
                continueReading = false;
                output = NULL;
            }
        }
    }
    else
    {
        ERROR_LOG("ReadInterval was called while entries should be reading");
    }
    
    return output;
}

template <typename T>
bool FileIOManagerCls<T>::ReadEntry(T& entryVal)
{
    bool readSuccesful = false;
    
    if (!inputStream.is_open() || !inputStream.good())
    {
        if (!inputStream.eof())
        {
            ERROR_LOG("File cannot be read in FileIOManagerCls.ReadEntry");
        }
        isEndOfInput = true;
    }
    else if (IsReadingIntervals() == false)
    {
        std::string line;
        bool continueReading = true;
        
        while (continueReading == true)
        {
            if (std::getline(inputStream, line))
            {
                lineCounter++;
                
                if (isLineWhiteSpace(line) == true)
                {
                    //skip the line, try the next line
                    continueReading = true;
                }
                else if (line == INTERVAL_BEGIN_STR)
                {
                    //will report and skip the line
                    std::stringstream ss;
                    ss << "Incorrect instance of " << INTERVAL_BEGIN_STR << " in input file, at line " << lineCounter;
                    ERROR_LOG(ss.str());
                    
                    continueReading = true;
                }
                else if (line == ENTRY_BEGIN_STR)
                {
                    //will report and skip the line
                    std::stringstream ss;
                    ss << "Incorrect instance of " << ENTRY_BEGIN_STR << " in input file, at line " << lineCounter;
                    ERROR_LOG(ss.str());
                    
                    continueReading = true;
                }
                else
                {
                    //we might have a valid interval line
                    std::istringstream lineAsStream(line);
                    
                    //trying to read the line into the parameter
                    //error handling is shifted to stream>> operator
                    if (lineAsStream >> entryVal)
                    {
                        readSuccesful = true;
                        continueReading = false;
                    }
                    else
                    {
                        //the line may not contain an entry,
                        //we will report and skip the line
                        std::stringstream ss;
                        ss << "Line cannot be parsed as entry: \"" << line << "\" in input file, at line " << lineCounter;
                        ERROR_LOG(ss.str());
                        
                        continueReading = true;
                    }
                }
            }
            else
            {
                //the line could not be read, we do not need to try to further read the input file
                //we may be in the end of file, if we aren't, an error will be logged
                
                if (!inputStream.eof())
                {
                    std::stringstream ss;
                    ss << "Line could not be read from the input file at line number " << lineCounter;
                    ERROR_LOG(ss.str());
                }
                
                isEndOfInput = true;
                continueReading = false;
                readSuccesful = false;
            }
        }
    }
    else
    {
        ERROR_LOG("ReadEntry was called while intervals should be reading");
        readSuccesful = false;
    }
    
    return readSuccesful;
}

template <typename T>
bool FileIOManagerCls<T>::Initialize()
{
    bool result = true;
    
    //try to open the set input file
    inputStream.open(inputFileName, std::ios::in);
    
    if (!inputStream.is_open() || !inputStream.good())
    {
        result = false;
        
        std::stringstream ss;
        ss << "Input file " << inputFileName << " could not be opened for reading. Error detail: "<< strerror(errno);
        ERROR_LOG(ss.str());
    }
    
    return result;
}

template <typename T>
bool FileIOManagerCls<T>::IsEndOfInput()
{
    return isEndOfInput;
}

template <typename T>
void FileIOManagerCls<T>::PrintHistogram(HistogramManagerCls<T>* histogram)
{
    std::ofstream output;
    output.open("output.txt", std::ofstream::trunc);
    
    if (!output.is_open() || !output.good())
    {
        ERROR_LOG("output.txt cannot be opened for writing!");
    }
    else
    {
        std::map<T, IntervalCls<T>* > hist = histogram->GetHistogram();
        
        typename std::map<T, IntervalCls<T>* >::iterator it;
        
        //iterating in map items and printing the results
        for ( it = hist.begin(); it != hist.end(); it++ )
        {
            output << "[" << it->second->Lower << ", " << it->second->Upper << "):\t" << it->second->EntryCount << std::endl;
        }
        
        //printing the outlier count
        std::list<T> outliers = histogram->GetOutlierList();
        output << "Outlier count:\t"<<outliers.size();
        
        output.close();
    }
}

#endif /* FileIOManagerCls_hpp */
