//
//  TestMain.cpp
//  Histogram
//
//  Created by Omer Karaduman on 25.01.2016.
//
#include "FileHistogramApplicationCls.hpp"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>


//got from stackoverflow
template<typename InputIterator1, typename InputIterator2>
bool
range_equal(InputIterator1 first1, InputIterator1 last1,
            InputIterator2 first2, InputIterator2 last2)
{
    while(first1 != last1 && first2 != last2)
    {
        if(*first1 != *first2) return false;
        ++first1;
        ++first2;
    }
    return (first1 == last1) && (first2 == last2);
}

bool CompareFiles(const std::string& filename1, const std::string& filename2)
{
    std::ifstream file1(filename1);
    std::ifstream file2(filename2);
    
    std::istreambuf_iterator<char> begin1(file1);
    std::istreambuf_iterator<char> begin2(file2);
    
    std::istreambuf_iterator<char> end;
    
    return range_equal(begin1, end, begin2, end);
}

void CopyFileToTestDirectory(std::string sourcePath, std::string targetPath)
{
    std::ifstream  src(sourcePath, std::ios::binary);
    std::ofstream  dst(targetPath, std::ios::binary);
    
    dst << src.rdbuf();
}
//end of premade code :)

///Gets the input file (if any)
///Runs the histogram application by giving this file as input
///compares the result files with expected outputs in the given path
bool RunTestsUnderDirectory(std::string dirPath)
{
    std::ifstream expectedErrorsStream;
    std::ifstream expectedOutputStream;
    
    //trying to open expected_errors file
    std::string expectedErrorsPath = dirPath + "/expected_errors.txt";
    expectedErrorsStream.open(expectedErrorsPath);
    
    if (!expectedErrorsStream.is_open() || !expectedErrorsStream.good())
    {
        return false;
    }
    
    //trying to open expected output file
    std::string expectedOutputPath = dirPath + "/expected_output.txt";
    expectedOutputStream.open(expectedOutputPath);
    
    if (!expectedOutputStream.is_open() || !expectedOutputStream.good())
    {
        return false;
    }
    
    //running the application with input.txt under given folder
    FileHistogramApplicationCls<float>* app = new FileHistogramApplicationCls<float>(dirPath + "/input.txt");
    app->CreateAndReportHistogram();
    delete app;
    
    std::string receivedErrorsPath = dirPath + "/received_errors.txt";
    std::string receivedOutputPath = dirPath + "/received_output.txt";
    CopyFileToTestDirectory("error.txt", receivedErrorsPath);
    CopyFileToTestDirectory("output.txt", receivedOutputPath);
    
    //compares outputs with expected results
    bool hasTestPassed = CompareFiles(receivedErrorsPath, expectedErrorsPath) && CompareFiles(receivedOutputPath, expectedOutputPath);
    
    //prints the test results
    std::cout << "Test result for input under " << dirPath << " is " << (hasTestPassed ? "PASS" : "FAIL") << std::endl;
        
    return true;
}


int main(int argc, const char * argv[]) {
    
    std::stringstream ss;
    int testDirectoryCounter = 1;
    
    //try to use Tests/# folders as test directories
    //stop when a necessary file could not be found
    do
    {
        ss.str("");
        ss.clear();
        
        ss << "Tests/" << testDirectoryCounter;
        //std::cout << "running tests under " << ss.str() << std::endl;
        testDirectoryCounter++;
        
    } while (RunTestsUnderDirectory(ss.str()) == true);
    
    
    
    return 0;
}
