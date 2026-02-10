#ifndef BITCOINEXCHANGE_CLASS_HPP
#define BITCOINEXCHANGE_CLASS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <stdexcept>

class BitcoinExchange
{
    private:
        std::string _inputFileName;
        std::map<size_t, std::string> _inputDataBase;
        std::map<std::string, std::string> _csvDataBase;

    public:
        BitcoinExchange();
        BitcoinExchange(const std::string &inputFileName);
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange& operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void getDataFromInputFile();
        void getDataFromCsvFile();
        void printCsvDataBase() const;
        void isCsvDataValid() const;
        bool isDateValid(const std::string &date) const;
        bool isFloatValid(const std::string &value) const;
        std::string isFloatOrUnsignedIntValid(const std::string &value) const;
        void calculateExchangeRate();

    class CouldNotOpenFile : public std::exception
    {
        public:
            virtual const char *what() const throw()
            {
                return ("Error: Could not open file");
            }
    };

    class EmptyLine : public std::exception
    {
        public:
            virtual const char *what() const throw()
            {
                return ("Error: Empty line in file");
            }
    };
};

#endif