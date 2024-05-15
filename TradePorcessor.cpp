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
    std::ostringstream xStream;
    xStream << "<TradeRecords>" << std::endl;
    for (const auto &record : tradeDetails)
    {
        xStream << "\t<TradeRecord>" << std::endl;
        xStream << "\t\t<SourceCurrency>" << record.SourceCurrency << "</SourceCurrency>" << std::endl;
        xStream << "\t\t<DestinationCurrency>" << record.DestinationCurrency << "</DestinationCurrency>" << std::endl;
        xStream << "\t\t<Lots>" << record.Lots << "</Lots>" << std::endl;
        xStream << "\t\t<Price>" << record.Price << "</Price>" << std::endl;
        xStream << "\t</TradeRecord>" << std::endl;
    }
    xStream << "</TradeRecords>";
    std::string xData = xStream.str();
    std::ofstream outFile("output.xml"); // Output XML file
    outFile << xData;
    std::cout << "INFO: " << tradeDetails.size() << " trades processed" << std::endl;
}