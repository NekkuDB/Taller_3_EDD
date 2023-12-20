#include "CSVReader.h"
#include <fstream>
#include <sstream>

CSVReader::CSVReader(const std::string &filename) : filename(filename) {}

std::vector<std::vector<std::string>> CSVReader::readData() {
    std::ifstream file(filename);
    std::vector<std::vector<std::string>> dataList;
    std::string line, cell;

    while (getline(file, line)) {
        std::stringstream lineStream(line);
        std::vector<std::string> row;

        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        dataList.push_back(row);
    }
    file.close();
    return dataList;
}
