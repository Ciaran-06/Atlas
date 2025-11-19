// FileLoader.hpp
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>

class CSVLoader {
private:
    std::string filePath;
    std::vector<std::string> ticker_;
    std::map<std::string, std::vector<std::map<std::string, double>>> data;

    void paraseCSV(const std::string& fullPath, const std::string& ticker);
    void validateRow(const std::vector<std::string>& row);
public:
    CSVLoader(const std::string& folderPath);
    void loadFile(const std::string& fileName);
    void loadAllFiles ();

    const std::vector<std::string>& getTickers();
    const std::vector<std::map<std::string, double>>& getData();
};