#include <string>

class DuckDBLoader {
    private:
    std::string dbPath;
    public:
        DuckDBLoader(const std::string& db_Path);
};