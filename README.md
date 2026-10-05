# Assignment 4: Linked Lists and Monopoly

This project was created for CS 210.

## Part 1: Linked List

I created my own linked list without using `std::list`.

The linked list supports:
- Adding items
- Searching for items
- Removing items
- Printing the list

## Part 2: Monopoly Game

I reused the linked list to create a circular Monopoly board.

The game includes:
- 10 properties
- Property name, cost, owner, and next pointer
- Two players: Mustafa and Sofia
- Circular movement around the board
- Buying unowned properties
- Blocking purchases of already owned properties
- 10 simulated turns
- Final board and player results

## Time Complexity

- Adding: O(1)
- Searching: O(n)
- Removing: O(n)
- Moving: O(k)
- Traversing: O(n)

`n` is the number of properties and `k` is the number of spaces a player moves.

## How to Run

Compile and run the C++17 program using CMake.
