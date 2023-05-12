#include<algorithm>
#include <iostream>
#include <string>
#include <vector>

struct LetterInventory{
    LetterInventory(std::string letters){
        this->inventory = std::move(letters);
        sort(this->inventory.begin(), this->inventory.end());
    }

    void set(char letter, int num){
        for (int i = 0; i < num; i++){
            this->inventory.push_back(tolower(letter));
        }
        sort(this->inventory.begin(), this->inventory.end());
    }
    int get(char letter){
        int num_char = 0;
        for (char c : this->inventory){
            if (c == letter) {num_char++;}
        }
        return num_char;
    }

    bool is_empty(){
        return (this->inventory.size() == 0);
    }
    int size(){
        return this->inventory.size();
    }

    LetterInventory operator+(const LetterInventory& other) const {
        return {this->inventory + other.inventory};
    }
    LetterInventory operator-(const LetterInventory& other) const {
        std::string result;
        int i = 0, j = 0;
        while (i < this->inventory.length() && j < other.inventory.length()) {
            if (this->inventory[i] < other.inventory[j]) {
                result += this->inventory[i];
                i++;
            } else if (this->inventory[i] > other.inventory[j]) {
                j++;
            } else {
                i++;
                j++;
            }
        }

        while (i < this->inventory.length()) {
            result += this->inventory[i];
            i++;
        }

        return {result};
    }
    LetterInventory operator*(const int& num) const {
        std::string result;
        for (char c : this->inventory){
            for(int i = 0; i < num; i++){ result += c; }
        }

        return {result};
    }
    friend std::ostream& operator<<(std::ostream& os, const LetterInventory& obj) {
        os << obj.inventory;
        return os;
    }
private:
    std::string inventory;
};


int main() {
    // Creating Inventories
    LetterInventory inventory1 = LetterInventory("banana");
    LetterInventory inventory2 = LetterInventory("bonoboa");
    std::cout << "Initial Inventories: \n" << inventory1 << "\n" << inventory2 << "\n\n";

    // Showing Subtraction
    std::cout << "Subtracting: \n";
    std::cout << inventory2 - inventory1 << "\n";
    std::cout << inventory1 - inventory2 << "\n";
    LetterInventory inventory3 = inventory1 - inventory2;
    std::cout << inventory3 << "\n\n";

    // Showing Addition
    std::cout << "Adding: \n";
    std::cout << inventory2 + inventory1 << "\n";
    std::cout << inventory1 + inventory2 << "\n";
    LetterInventory inventory4 = inventory1 + inventory2;
    std::cout << inventory4 << "\n\n";

    // Other Features
    LetterInventory inventory5 = inventory1 - inventory1;
    std::cout << "Inventory: " << inventory5 << "\n";
    std::cout << "Is Empty: " << (inventory5.is_empty() ? "true" : "false") << "\n";
    inventory5.set('a', 5);
    std::cout << "Inventory: " << inventory5 << "\n";
    std::cout << "Is Empty: " << (inventory5.is_empty() ? "true" : "false") << "\n";
    std::cout << "Num of a: " << inventory5.get('a') << "\n\n";

    // Bonus Features
    LetterInventory inventory6 = inventory1 + inventory2 - inventory3;
    std::cout << inventory6 << "\n";
    LetterInventory inventory7 = inventory1 * 3 - inventory1;
    std::cout << inventory7 << "\n";


    return 0;
}
