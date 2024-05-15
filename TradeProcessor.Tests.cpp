#include <gtest/gtest.h>
#include "TradeProcessor.h"
#include <fstream>

// Demonstrate some basic assertions.
TEST(TradeProcessorTestSuite, BasicAssertions)
{

    TradeProcessor tradeProcessor{};

    std::ifstream file("trades.txt");
    if (file.is_open())
    {
        tradeProcessor.ProcessTrades(file);
        file.close();
    }
    else
    {
        // std::cout << "Failed to open file" << std::endl;
    }
}

TEST(TradeProcessorDataConverter, getIntFromString)
{
    int value{0};

    EXPECT_TRUE(TradeProcessorDataConverter::getIntFromString("1", value));

    EXPECT_EQ(value, 1);

    EXPECT_FALSE(TradeProcessorDataConverter::getIntFromString("A", value));
}

TEST(TradeProcessorDataConverter, getDoubleFromString)
{
    double value{0.0};

    EXPECT_TRUE(TradeProcessorDataConverter::getDoubleFromString("1000", value));

    EXPECT_EQ(value, 1000);

    EXPECT_FALSE(TradeProcessorDataConverter::getDoubleFromString("A", value));
}