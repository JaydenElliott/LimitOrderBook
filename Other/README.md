# README
### u6680348

## Limit order book (LOB) user interaction:

This software requires input from a text file. This text file contains order information in the following format:

```
n
order-type price ID
```
**n**: number of orders in text file

**Order-type options**:
 * buy
 * sell
 * delete


**Price**:
* if making a delete order, set price to 0

**ID**:
* if making a buy or sell order, set ID to 0. An order ID will be generated for you.

**Example text file**:
```
8
buy 13 0
sell 30 0
buy 20 0
buy 23 0
delete 13 1235123
sell 40 0
delete 13 1235123
sell 32 0
```


**Compile**:
To compile this program run:
```
g++ -std=c++11 skeleton.cpp -o out
```
And then add the orders.txt file as an input to the out file, i.e.
```
./out orders.txt
```


For future reference, if you want to print out the the trees after making the orders, uncomment the last 3 lines in the skeleton file. This functionality not currently implemented so print will be empty.