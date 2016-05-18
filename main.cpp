//
//  main.cpp
//  Histogram
//
//  Created by Omer Karaduman on 24.01.2016.
//

#include "FileHistogramApplicationCls.hpp"

int main(int argc, const char * argv[]) {
    
    std::string inputFileName = "test.txt";
    
    if (argc > 1)
    {
        inputFileName = argv[1];
    }
    
    FileHistogramApplicationCls<float>* app = new FileHistogramApplicationCls<float>(inputFileName);
    app->CreateAndReportHistogram();
    
    delete app;
    return 0;
}
