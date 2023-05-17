//
// Created by picke on 5/15/2023.
//

#include "WordSearch.h"

WordSearch::WordSearch(const std::vector<std::string>& words) {
    srand (time(NULL));

    this->grid = std::vector<std::vector<char>>(this->SIZE, std::vector<char> (this->SIZE, '-'));
    for (std::string word : words){
        int x, y, dy, dx, x_end_position, y_end_position;

        do {
            // X and Y positions, determine where the word will be drawn
            x = rand() % this->SIZE;
            y = rand() % this->SIZE;
            // X and Y Directions, determine which way the word will be drawn
            dx = get_random_sign();
            dy = get_random_sign();

            x_end_position = std::max(x + (dx*word.size()), x+word.size());
            y_end_position = std::max(y + (dy*word.size()), x+word.size());
        }while (!is_in_range(x_end_position, 0, this->SIZE-1) || !is_in_range(y_end_position, 0, this->SIZE-1));

        for (int i = 0; i < word.size(); i++){
            this->grid[y+(i*dy)][x + (i*dx)] = word[i];
        }

    }
}

std::ostream& operator<<(std::ostream& os, const WordSearch& ws) {
    for (const std::vector<char>& row : ws.grid){
        for (char c : row){
            os << c << "  ";
        }
        os << "\n";
    }
    return os;
}

// Returns random lowercase letter of alphabet
char WordSearch::get_random_letter() {
    return 'a' + rand()%26;
}

// Returns -1, 0, or 1
int WordSearch::get_random_sign() {
    return rand()%3 -1;
}

// Returns true if value is between min and max
bool WordSearch::is_in_range(int value, int min, int max) {
    return value <= max && value >= min;
}
