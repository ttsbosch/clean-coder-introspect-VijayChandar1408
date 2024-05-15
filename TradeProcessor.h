#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#pragma once

constexpr float LotSize = 100000;

struct TradeDetails
{
    std::string SourceCurrency;      // SourceCurrency
    std::string DestinationCurrency; // DestinationCurrency
    float Lots;
    double Price;
};

class TradeProcessor
{
public:
    void ProcessTrades(std::istream &stream);

private:
    void storeTradeDetailsAsXML(std::vector<TradeDetails>& tradeDetails);
};


class TradeProcessorDataConverter
{
public:
    static bool getIntFromString(const std::string &str, int &value)
    {
        try
        {
            value = std::stoi(str);
            return true;
        }
        catch (const std::exception &)
        {
            return false;
        }
    }

    static bool getDoubleFromString(const std::string &str, double &value)
    {
        try
        {
            value = std::stod(str);
            return true;
        }
        catch (const std::exception &)
        {
            return false;
        }
    }
};

// int main()
// {
//     TradeProcessor processor;
//     std::ifstream file("trades.txt");
//     if (file.is_open())
//     {
//         processor.ProcessTrades(file);
//         file.close();
//     }
//     else
//     {
//         std::cout << "Failed to open file" << std::endl;
//     }
//     return 0;
// }
