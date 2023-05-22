//
// Created by picke on 5/15/2023.
//

#include "WordSearch.h"

WordSearch::WordSearch(const std::vector<std::string>& words) {
    srand(time(NULL));
    this->grid = std::vector<std::vector<char>>(this->SIZE, std::vector<char> (this->SIZE, '-'));



    for (int j = 0; j < words[i].size(); j++){
        this->grid[ + (j*placements[i].dy)][placements[i].x + (j*placements[i].dx)] = words[i][j];
    }
//    std::vector<Placement> placements = place_next_word(words, 0, std::vector<Placement>{});
//    for (int i = 0; i < words.size(); i++) {
//        for (int j = 0; j < words[i].size(); j++){
//            this->grid[placements[i].y + (j*placements[i].dy)][placements[i].x + (j*placements[i].dx)] = words[i][j];
//        }
//    }
}

std::ostream& operator<<(std::ostream& os, const WordSearch& ws) {
    for (const std::vector<char>& row : ws.grid){
        for (char c : row){
            os << (c == '!' ? WordSearch::get_random_letter() : (char)toupper(c)) << "  ";
        }
        os << "\n";
    }
    return os;
}

// Returns random lowercase letter of alphabet
char WordSearch::get_random_letter() {
    return 'a' + rand()%26;
}

//std::vector<WordSearch::Placement> WordSearch::place_next_word(const std::vector<std::string>& words, int i, std::vector<Placement> placements) {
//    if (i > words.size()-1) { return placements; }
//
//    std::vector<Placement> best_placements = {Placement(0, 0, 0, 0, -1)};
//
//    // For every grid space
//    for (int y = 0; y < this->SIZE; y++) {
//        for (int x = 0; x < this->SIZE; x++) {
//            // For every possible direction
//            for (int dy = -1; dy <= 1; dy++) {
//                for (int dx = -1; dx <= 1; dx++) {
//                    if (dx == 0 && dy == 0) { continue; }
//
//                    Placement new_placement = Placement(x, y, dx, dy, 0);
//                    new_placement.score = place_next_letter(words[i], 0, 0, new_placement);
//                    if (new_placement.score > -1) {
//                        placements.push_back(new_placement);
//                        std::vector<Placement> new_placements = place_next_word(words, i + 1, placements);
//
//                        int total_score = 0;
//                        int best_score = 0;
//                        for (Placement p : new_placements) {
//                            total_score += p.score;
//                        }
//                        for (Placement p : best_placements) {
//                            best_score += p.score;
//                        }
//
//                        if (total_score > best_score) {
//                            best_placements = new_placements;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return best_placements;
//}

// Recursive wrapper
void WordSearch::place_word(std::string word){
    Placement best_placement = Placement(0, 0, 0, 0);
    int best_score = -1;

    // For every possible x and y
    for (int y = 0; y < this->SIZE; y++) {
        for (int x = 0; x < this->SIZE; x++) {

            // For every possible direction
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    // Prevents words that go nowhere
                    if (dy == 0 and dx == 0) { continue; }

                    Placement new_placement = Placement(x, y, dx, dy);
                    // Use recursive function to get score of placement
                    int new_placement_score = place_next_letter(word, 0, 0, new_placement);
                    if (new_placement_score > best_score) {
                        best_placement = new_placement;
                        best_score = new_placement_score;
                    }
                }
            }
        }
    }

    // If no intersections possible)
    if(best_score == 0) {
        // Instead places word in random position
        do {
            best_placement = Placement(rand()%SIZE, rand()%SIZE, rand()%3-1, rand()%3-1);

        } while (place_next_letter(word, 0, 0, best_placement) == -1);
    }

    std::cout << word << ": "<< best_score << "\n";
    // Places best word

}
//// Recursive function that places a word onto the grid with aims of overlapping as many characters as possible
int WordSearch::place_next_letter(std::string word, int i, int score, Placement p) {
    // Base case, indicates we've successfully placed every letter in word
    if (i > word.size()) { return score; }
    // Fail case, if placement is out of range
    if (not is_in_range(p.x + p.dx, 0, this->SIZE-1) or not is_in_range(p.y + p.dy, 0, this->SIZE-1)) { return -1; }

    bool space_is_empty = this->grid[p.y][p.x] == '-';
    bool letters_match = tolower(this->grid[p.y][p.x]) == tolower(word[i]);

    if (space_is_empty or letters_match){
        if (letters_match){score++;}
        p.x += p.dx;
        p.y += p.dy;
        return place_next_letter(word, i +1, score, p);
    }

    // Placement failed, negating score
    return -1;

}

// Returns true if value is between min and max
bool WordSearch::is_in_range(int value, int min, int max) {
    return value <= max && value >= min;
}


WordSearch::Placement::Placement(int x, int y, int dx, int dy, int score) {
    this->x = x;
    this->y = y;
    this->dx = dx;
    this->dy = dy;
    this->score = score;
}
