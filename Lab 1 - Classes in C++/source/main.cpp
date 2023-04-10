// Drake Pickett
// 4.10.2023
// CS 145 - Lab 1
// A simple Rectangle class based off of exercise 9.11 in the book.
// Seeks to show headers vs implementation, and encapsulation of data using classes.

#include <iostream>
#include "Rectangle.h"

int main(){
    std::pair<int, int> dimensions = std::make_pair(17, 3);
    std::pair<int, int> position = std::make_pair(10, 10);

    Rectangle new_rect(dimensions, position);

    std::cout << new_rect;

    return 0;
}