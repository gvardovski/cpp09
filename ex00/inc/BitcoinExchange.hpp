#ifndef BITCOINEXCHANGE_CLASS_HPP
#define BITCOINEXCHANGE_CLASS_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

class BitcoinExchange
{
    private:
        std::string _inputFileName;
        std::map<std::string, int> _inputDataBase;
    public:
        // BitcoinExchange();
        BitcoinExchange(const std::string &inputFileName);
        // BitcoinExchange(const BitcoinExchange &other);
        // BitcoinExchange& operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void getDataFromInputFile();
};

#endif