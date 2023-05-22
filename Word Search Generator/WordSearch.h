//
// Created by picke on 5/15/2023.
//


#ifndef WORD_SEARCH_GENERATOR_WORDSEARCH_H
#define WORD_SEARCH_GENERATOR_WORDSEARCH_H

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>


class WordSearch {
public:
    WordSearch(const std::vector<std::string>& words);

    friend std::ostream& operator<<(std::ostream& os, const WordSearch& ws);

private:
    const int SIZE = 15;

    std::vector<std::vector<char>> grid;

    // Placement data type. Contains all info needed to place a word (x pos, y pos, x direction, y direction, score being number of letters it intersects)
    struct Placement {
        int x, y, dx, dy, score;

        Placement(int, int, int, int, int);
    };

    static char get_random_letter() ;
    //std::vector<Placement> place_next_word(const std::vector<std::string>&, int, std::vector<Placement>);
    void place_word(std::string word);
    int place_next_letter(std::string, int, int, Placement);

    bool is_in_range(int, int, int);
};


#endif //WORD_SEARCH_GENERATOR_WORDSEARCH_H
