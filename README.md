# Limit Order Book

A limit order book for processing and executing stock market orders and providing descriptive price statistics.

The main functionalities of this software are handling and storing buy and sell orders. Comparing buy and sell orders and executing these if necessary as well as providing a variety of trading statistics.

## Interacting with the software

All functionalities join together to produce the LOB software as a whole. All user interaction occurs in the user_interaction.cpp file, where text files are read in to be processed by numerous functions. All order processing is handled by the newOrder() and executeorder() functions. These functions call all the other separate functionalities when required. For example: when handling comparisons, the RB tree is called, when handling new orders the hash table is called etc...

To run the software run the lines of code shown below. Note that the output of the trades executed will be found in logging/exectutedOrders.txt. The test files are labelled "test-f1-i.txt", where 'i' ranges from 1 to 5:

```
g++ -std=c++11 main/user_interaction.cpp -o out
./out  main/test_files/"test-file"
```

To run the file and see functionality 3 (order statistics) uncomment line 170 (see code below) of user_interaction.cpp and run the code in the same way as above.

```
getStatistics("all", stats, orderlog);
```

## Unit-testing the software

This comprehensive testing allows you to check if all algorithms and data-structures are working correctly. To run the unit testing, compile and run the maintest.cpp file via the following commands:

```
g++ -std=c++11 testing/maintest.cpp -o out
./out --success
```

## Testing Individual Functionalities

Note: All individual functionalities use the same test files (test-f1-1.txt, test-f1-2.txt, ... , test-f1-5.txt) because they all utilise the same data.

## Order information storage - Hash-Table

The hash-table is the primary data-structure responsible for storing order information and interacting with other functionalities to make execution of orders as fast as possible (see final report for more details).

To test the full capacity of this functionality, the entire software needs to be run as a whole (see "Interacting with the software" above). However, testing the hash-table functionalities independently may be useful.

In order to test the hash table independently, a few small changes need to be made to "datastructures/hashtable.hpp". Namely lines 86 and 144 need to be commented out to prevent the red-black tree insertion being called (these lines have been marked by clear comments) and are shown below.

```
Line 86:
tree.insert_price(rbnode);
```

```
Line 144:
rbtree.delete_price(currNode->rbNode);
```

Once this has been done, the hash table can be tested via:

```
g++ -std=c++11 main/hashtable_interface.cpp -o out
./out main/test_files/"test-file"
```

If you want to view what is contained in the hash table after insertion, uncomment line 45 in main/hashtable_interface.cpp. This will print all the contents (std::cout is slow, so only do this on the first test case).

Make sure to undo all the changes to "datastructures/hashtable.hpp" when finished as these will affect the subsequent functionalities.

## Price-storage: Red-Black-Tree

The red-black tree handles price comparison as well as price storage. Testing the comparison independently cannot be done, as it also requires calling upon another functionality. To test price comparison and execution see "Interacting with the software" instructions above.

It may however be useful to view and test the storage functionality of the red-black tree. Because all orders firstly come through the hash-table, and the hash-table is also used to modify the RB tree deletions (see final-report for details), only insertion can be tested independently. Testing this will be useful, as it provides a look into the speed of the red-black tree.

To test the red-black tree run the following commands:

```
g++ -std=c++11 main/redblacktree_interface.cpp -o out
./out main/test_files/"test-file"
```

At first there will be no output, as it is simply storing prices, however, to view the tree's price storage, uncomment lines 53-58 in redblacktree_interface.cpp. These lines are clearly marked.

## Descriptive Statistics: Random Quick Sort

The software comes with an application to view descriptive statistics from all the previous orders. To test this functionality, firstly make sure line 194 of user_interaction.cpp is not commented out. MAKE SURE changes made in "Order information storage - Hash-Table" are undone. Then run the entire application as a whole using:

```
g++ -std=c++11 main/user_interaction.cpp -o out
./out  test_files/"test-file"
```

This will print out the statistics specified in the function arguments. See the getStatistics() doc-string for more information on what other statistics you can ask for.

## Other useful things to look at

The method and code used for the experimental analysis can be found in experimental/analysis as well as in the final report.
