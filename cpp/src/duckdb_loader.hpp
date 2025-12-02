#pragma once
#include <string>
#include <memory>
#include "duckdb.hpp"
#include <arrow/api.h>

class DuckDBLoader {
    private:
    std::unique_ptr<duckdb::DuckDB> db;
    std::unique_ptr<duckdb::Connection> conn;
    std::string dbPath;
    public:
        DuckDBLoader(const std::string& db_Path);
        bool registerTicker(const std::string& folderPath,
                            const std::string& ticker);
        duckdb::unique_ptr<duckdb::QueryResult> runQuery(const std::string& sql);
        std::shared_ptr<arrow::Table> toArrow(duckdb::QueryResult* result);
};

/*
need to open duckdb conn
need to load paraquet file into duckdb
need to run sql query to extract data but have the query engine inheri from this class
return arrow table
*/