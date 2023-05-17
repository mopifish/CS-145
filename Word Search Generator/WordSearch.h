//
// Created by picke on 5/15/2023.
//


#ifndef WORD_SEARCH_GENERATOR_WORDSEARCH_H
#define WORD_SEARCH_GENERATOR_WORDSEARCH_H

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


class WordSearch {
public:
    WordSearch(const std::vector<std::string>& words);

    friend std::ostream& operator<<(std::ostream& os, const WordSearch& ws);

private:
    const int SIZE = 15;

    std::vector<std::vector<char>> grid;

    char get_random_letter();
    int get_random_sign();

    bool is_in_range(int value, int min, int max);
};


#endif //WORD_SEARCH_GENERATOR_WORDSEARCH_H
