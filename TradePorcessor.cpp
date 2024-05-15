#include "TradeProcessor.h"
void TradeProcessor::ProcessTrades(std::istream &tradeInputFile)
{

    std::vector<std::string> trades;
    std::string trade;

    while (std::getline(tradeInputFile, trade))
    {
        trades.push_back(trade);
    }

    std::vector<TradeDetails> tradeDetails;
    int lineCount = 1;
    for (const auto &trade : trades)
    {
        std::vector<std::string> tradeFields;

        std::string tradeItem;
        std::istringstream tradeStream(trade);

        while (std::getline(tradeStream, tradeItem, ','))
        {
            tradeFields.push_back(tradeItem);
        }

        if (tradeFields.size() != 3)
        {
            std::cout << "WARN: Line " << lineCount << " malformed. Only " << tradeFields.size() << " field(s) found." << std::endl;
            continue;
        }

        if (tradeFields[0].length() != 6)
        {
            std::cout << "WARN: Trade currencies on line " << lineCount << " malformed: '" << tradeFields[0] << "'" << std::endl;
            continue;
        }

        int tradeAmount;
        if (!TradeProcessorDataConverter::getIntFromString(tradeFields[1], tradeAmount))
        {
            std::cout << "WARN: Trade amount on line " << lineCount << " not a valid integer: '" << tradeFields[1] << "'" << std::endl;
        }

        double tradePrice;
        if (!TradeProcessorDataConverter::getDoubleFromString(tradeFields[2], tradePrice))
        {
            std::cout << "WARN: Trade price on line " << lineCount << " not a valid decimal: '" << tradeFields[2] << "'" << std::endl;
        }

        std::string sourceCurrency = tradeFields[0].substr(0, 3);
        std::string destinationCurrency = tradeFields[0].substr(3, 3);

        // calculate values
        TradeDetails obj;
        obj.SourceCurrency = sourceCurrency;
        obj.DestinationCurrency = destinationCurrency;
        obj.Lots = tradeAmount / LotSize;
        obj.Price = tradePrice;
        tradeDetails.push_back(obj);

        lineCount++;
    }
}

void TradeProcessor::printTradeDetails(std::vector<TradeDetails> &tradeDetails)
{
    std::ostringstream xmlStream;
    xmlStream << "<TradeRecords>" << std::endl;
    for (const auto &trade : tradeDetails)
    {
        xmlStream << "\t<TradeRecord>" << std::endl;
        xmlStream << "\t\t<SourceCurrency>" << trade.SourceCurrency << "</SourceCurrency>" << std::endl;
        xmlStream << "\t\t<DestinationCurrency>" << trade.DestinationCurrency << "</DestinationCurrency>" << std::endl;
        xmlStream << "\t\t<Lots>" << trade.Lots << "</Lots>" << std::endl;
        xmlStream << "\t\t<Price>" << trade.Price << "</Price>" << std::endl;
        xmlStream << "\t</TradeRecord>" << std::endl;
    }
    xmlStream << "</TradeRecords>";
    std::string xmlData = xmlStream.str();
    std::ofstream outFile("tradeOutput.xml");
    outFile << xmlData;
    std::cout << "INFO: " << tradeDetails.size() << " trades processed" << std::endl;
}