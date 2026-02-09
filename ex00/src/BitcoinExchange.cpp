#include "../inc/BitcoinExchange.hpp"

// BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const std::string &inputFileName)
{
    std::ifstream inputFile;
    inputFile.open(inputFileName.c_str());
    if (!inputFile.is_open())
        throw std::runtime_error("Error: could not open file.");
    inputFile.close();
    this->_inputFileName = inputFileName.c_str();
}

BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::getDataFromInputFile()
{
    std::ifstream inputFile;
    inputFile.open(this->_inputFileName.c_str());
    std::string line;
    int strNum = 0;
    while (std::getline(inputFile, line))
    {
        if (line.empty())
            throw std::runtime_error("Error: empty line in input file.");
        if (line == "date | value" && strNum == 0)
            continue;
        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos)
            throw std::runtime_error("bad input => " + line);
        std::string date = line.substr(0, pipePos - 1);
        std::cout << "date: ' '" << date << std::endl;
        strNum++;
    }
}