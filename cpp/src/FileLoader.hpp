#pragma once

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <thread>
#include <memory>
#include <functional>
#include <iostream>

namespace arrow {
    class Table;
}
namespace duckdb {
    class Connection;
    class DuckDB;
}

struct Bar {
    std::string date;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

class CSVLoader {
public:
    // Constructor: folder path containing CSVs
    explicit CSVLoader(const std::string& folderPath);

    // Load a single CSV file
    void loadFile(const std::string& filename);

    // Load all CSV files in folder, optionally using multithreading
    void loadAllFiles(bool multithreaded = true);

    // Retrieve parsed data for a specific ticker
    const std::vector<Bar>& getData(const std::string& ticker) const;

    // Retrieve list of tickers loaded
    const std::vector<std::string>& getTickers() const;

    // Logging interface (simple console logging, can extend to file)
    void setLogger(std::function<void(const std::string&)> logger);

    // Arrow Table integration: returns an in-memory Arrow table for a ticker
    std::shared_ptr<arrow::Table> getArrowTable(const std::string& ticker);

    // DuckDB integration: load CSV into DuckDB table
    void loadIntoDuckDB(duckdb::Connection& conn, const std::string& tableName);

private:
    std::string folderPath_;
    std::vector<std::string> tickers_;

    // Map ticker → parsed bars
    std::map<std::string, std::vector<Bar>> data_;

    // Mutex for thread-safe writes
    mutable std::mutex dataMutex_;

    // Optional logging function
    std::function<void(const std::string&)> logger_;

    // Helper: parse CSV file into vector of Bar structs
    void parseCSV(const std::string& fullPath, const std::string& ticker);

    // Helper: validate a row, throws or logs error if invalid
    void validateRow(const std::vector<std::string>& row);

    // Helper: thread worker for multithreaded loading
    void loadWorker(const std::string& filename);

    // Internal helpers for Arrow/DuckDB conversions
    std::shared_ptr<arrow::Table> convertToArrow(const std::vector<Bar>& bars);
    void insertIntoDuckDB(duckdb::Connection& conn, const std::string& tableName,
                          const std::vector<Bar>& bars);
};