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
    size_t strNum = 0;
    while (std::getline(inputFile, line))
    {
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (strNum == 0 && line != "date|value")
            throw std::runtime_error("Error: 'date | value' line should be the first line in input file.");
        else if (strNum == 0 && line == "date|value")
        {
            strNum++;
            continue;
        }
        if (line.empty())
            throw std::runtime_error("Error: empty line in input file.");  
        this->_inputDataBase[strNum] = line;
        strNum++;
    }
    inputFile.close();
}

void BitcoinExchange::getDataFromCsvFile()
{
    std::ifstream inputFile;
    inputFile.open("data/data.csv");
    std::string line;
    size_t strNum = 0;
    while (std::getline(inputFile, line))
    {
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (strNum == 0 && line != "date,exchange_rate")
            throw std::runtime_error("Error: 'date,exchange_rate' line should be the first line in csv file.");
        else if (strNum == 0 && line == "date,exchange_rate")
        {
            strNum++;
            continue;
        }
        if (line.empty())
            throw std::runtime_error("Error: empty line in csv file.");
        size_t commaPos = line.find(',');
        std::string date = line.substr(0, commaPos);
        std::string value = "";
        if (commaPos != std::string::npos)
            value = line.substr(commaPos + 1);
        this->_csvDataBase[date] = value;
        strNum++;
    }
    inputFile.close();
}

void BitcoinExchange::isCsvDataValid() const
{
    for (std::map<std::string, std::string>::const_iterator it = this->_csvDataBase.begin(); it != this->_csvDataBase.end(); it++)
    {
        if (!isDateValid(it->first))
            throw std::runtime_error("Error: invalid date in csv file. " + it->first);
        if (!isFloatValid(it->second))
            throw std::runtime_error("Error: invalid float value in csv file. " + it->second);
    }
}

bool BitcoinExchange::isDateValid(const std::string &date) const
{
    struct tm tm;
    if (strptime(date.c_str(), "%Y-%m-%d", &tm) == NULL)
        return false;
    return true;
}

bool BitcoinExchange::isFloatValid(const std::string &value) const
{
    std::istringstream ss(value);
    float f;
    ss >> f;
    if (ss.fail() || !ss.eof())
        return false;
    return true;
}

std::string BitcoinExchange::isFloatOrUnsignedIntValid(const std::string &value) const
{
    size_t pointPos = value.find('.');
    if (pointPos == std::string::npos)
    {
        std::istringstream ss(value);
        long int x;
        ss >> x;
        if (ss.fail() || !ss.eof())
            return "Error: bad input => " + value;
        if (x > std::numeric_limits<int>::max())
            return "Error: too large a number.";
        if (x < 0)
            return "Error: not a positive number.";
    }
    else
    {
        if (isFloatValid(value))
        {
            float f = std::atof(value.c_str());
            if (f < 0)
                return "Error: not a positive number.";
        }
        else
            return "Error: bad input => " + value;
    }
    return "";
}

void BitcoinExchange::calculateExchangeRate()
{
    for (std::map<size_t, std::string>::const_iterator it = this->_inputDataBase.begin(); it != this->_inputDataBase.end(); it++)
    {
        size_t pipePos = it->second.find('|');
        std::string date = it->second.substr(0, pipePos);
        if (!isDateValid(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        std::string value = "";
        if (pipePos != std::string::npos)
            value = it->second.substr(pipePos + 1);
        else
        {
            std::cerr << "Error: bad input => " << value << std::endl;
            continue;
        }
        std::string msg = isFloatOrUnsignedIntValid(value);
        if (!msg.empty())
        {
            std::cerr << msg << std::endl;
            continue;
        }
        std::map<std::string, std::string>::const_iterator csvIt = this->_csvDataBase.lower_bound(date);
        if (csvIt == this->_csvDataBase.end())
            csvIt--;
        else if (csvIt != this->_csvDataBase.begin() && csvIt->first != date)
            csvIt--;
        float exchangeRate = std::atof(csvIt->second.c_str());
        float flvalue = std::atof(value.c_str());
        float result = flvalue * exchangeRate;
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
}