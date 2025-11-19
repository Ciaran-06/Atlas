// FileLoader.cpp
#include <iostream>
#include <filesystem>

#include "FileLoader.hpp"
#include "csv.h"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

const std::string rawDataDir = "../../raw";

bool pathExists(const std::string& path) {
    if (std::filesystem::exists(path)) {
        return true;
    }
    else { throw; }
}

std::string tickerFilePath(const std::string& ticker) {
    std::string filePath = rawDataDir + "/" + ticker + ".csv"
}

std::string tickerTrimmer(std::string& ticker) {
    ticker.erase(0,15);
    ticker.erase((ticker.length() -4), ticker.length());
    return ticker;
}

// 23 chars from the start and  4 from end
CSVLoader::CSVLoader(const std::string& path) {
  std::cout << system("pwd") << std::endl; //: Debugging line to figure out paths
    std::cout << "CSV Loader Inisilased..." << std::endl;
    folderPath_ = (pathExists) ? path : throw;
    std::string  tempTicker;

   /*  for (const auto& dirEntry : recursive_directory_iterator(folderPath_)) {
        tempTicker = dirEntry.path().string();
        tempTicker = tickerTrimmer(tempTicker);

        std::cout << tempTicker << std::endl;
        tickers_.push_back(tempTicker);
    }   */    
}
/*
struct Bar {
    std::string date;
    double open;
    double high;
    double low;
    double close;
    double volume;
};
*/
void CSVLoader::loadFile(const std::string& ticker) {
   
  /* io::CSVReader<7> in(filename);
  in.read_header(io::ignore_extra_column, "Date","Open","High" "Low","Close","Adj Close","Volume");

  while(in.read_row(date, open)) */

}
