

# Introduction

There are a lot of tips telling us that some fruits must not be eaten with some other fruits, or we might get ourselves in serious trouble. For example, bananas can not be eaten with cantaloupe, otherwise it will lead to kidney deficiency.

Now you are given a long list of such tips, and a big basket of fruits. You are supposed to pick up those fruits so that it is safe to eat any of them.

The core of this problem is to find a maximal clique of the given graph, which has the most vertexes but least total price.

### Input Specification:



Each input file contains one test case. For each case, the first line gives two positive integers: N, the number of tips, and M, the number of fruits in the basket. both numbers are no more than 100.

Then two blocks follow. The first block contains N pairs of fruits which must not be eaten together, each pair occupies a line and there is no duplicated tips; and the second one contains M fruits together with their prices, again each pair in a line. To make it simple, each fruit is represented by a 3-digit ID number. A price is a positive integer which is no more than 1000. All the numbers in a line are separated by spaces.

### Output Specification:

For each case, first print in a line the maximum number of safe fruits. Then in the next line list all the safe fruits, in increasing order of their ID's. The ID's must be separated by exactly one space, and there must be no extra space at the end of the line. Finally in the third line print the total price of the above fruits. Since there may be many different solutions, you are supposed to output the one with a maximum number of safe fruits. In case there is a tie, output the one with the lowest total price. It is guaranteed that such a solution is unique.