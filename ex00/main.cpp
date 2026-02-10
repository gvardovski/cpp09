#include "inc/BitcoinExchange.hpp"

int main(int gc, char **gv)
{
    if (gc != 2)
    {
        std::cerr << "It should be: ./btc [file]" << std::endl;
        return (1);
    }
    try
    {
        BitcoinExchange btc(gv[1]);
        btc.getDataFromInputFile();
        btc.getDataFromCsvFile();
        btc.isCsvDataValid();
        btc.calculateExchangeRate();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return (0);
}