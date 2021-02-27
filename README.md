# Limit Order Book

A limit order book for processing, executing and logging stock market orders.

The main functionalities of this software are handling and storing buy and sell orders. Comparing buy and sell orders and executing these if necessary as well as providing a trading log and a variety of trading statistics.

## Interacting with the software

Interactions with the software can be done in the user_interaction.cpp file, where text files are read in to be processed by numerous functions. All order processing is handled by the newOrder() and executeorder() functions. These functions call all the other separate functionalities when required. For example: when handling comparisons, the RB tree is called, when handling new orders the hash table is called etc...

To run the software run the lines of code shown below. Note that the output of the trades executed will be found in logging/exectutedOrders.txt. The test files are labelled "test-f1-i.txt", where 'i' ranges from 1 to 5:

```
g++ -std=c++11 main/user_interaction.cpp -o out
./out  main/test_files/"test-file"
```

Obtain trading statistics through the getStatistics() function:

```
getStatistics("all", stats, orderlog);
```

## Unit-testing the software

This comprehensive testing allows you to check if all algorithms and data-structures are working correctly. To run the unit testing, compile and run the testing/maintest.cpp file via the following commands:

```
g++ -std=c++11 testing/maintest.cpp -o out
./out --success
```
