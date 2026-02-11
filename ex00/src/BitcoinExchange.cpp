#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const std::string &inputFileName)
{
    std::ifstream inputFile;
    inputFile.open(inputFileName.c_str());
    if (!inputFile.is_open())
        throw CouldNotOpenFile();
    inputFile.close();
    this->_inputFileName = inputFileName.c_str();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    this->_inputFileName = other._inputFileName;
    this->_inputDataBase = other._inputDataBase;
    this->_csvDataBase = other._csvDataBase;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        this->_inputFileName = other._inputFileName;
        this->_inputDataBase = other._inputDataBase;
        this->_csvDataBase = other._csvDataBase;
    }
    return *this;
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
            throw EmptyLine();
        this->_inputDataBase[strNum] = line;
        strNum++;
    }
    inputFile.close();
}

void BitcoinExchange::getDataFromCsvFile()
{
    std::ifstream inputFile;
    inputFile.open("data.csv");
    if (!inputFile.is_open())
        throw CouldNotOpenFile();
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
            throw EmptyLine();
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
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (isdigit(date[i]) == 0)
			return (false);
	}
	if (date[5] == '0' && date[6] == '0') 
		return (false);
	if ((date[5] == '1' && date[6] > '2') || date[5] > '1')
		return (false);

	if (date[8] == '0' && date[9] == '0')
		return (false);
	if ((date[8] == '3' && date[9] > '1') || date[8] > '3')
		return (false);
	return (true);
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
        if (x > 1000)
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
		if (date < this->_csvDataBase.begin()->first || date > this->_csvDataBase.rbegin()->first)
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