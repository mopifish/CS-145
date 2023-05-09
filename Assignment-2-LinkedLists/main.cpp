#include <iostream>
#include <utility>
// A simple phonebook created in C++ using Linked Lists


struct Entry {
    Entry(std::string first_name, std::string last_name, std::string street_address, std::string city, std::string phone_number) {
        this->first_name = std::move(first_name);
        this->last_name = std::move(last_name);
        this->street_address = std::move(street_address);
        this->city = std::move(city);
        this->phone_number = std::move(phone_number);
    }
    std::string first_name;
    std::string last_name;

    std::string street_address;
    std::string city;

    std::string phone_number;

    Entry* next = nullptr;
};

class LinkedList {
public:
    // Adds entry to end by default
    void add_entry(Entry* entry, int index = -1) {
        if (this->head == nullptr){
            head = entry;
        } else  {
            Entry* current = head;
            int count = 0;
            while(current->next != nullptr) {
                if (index == count) { break; }
                count++;

                current = current->next;
            }
            if (count < index) { throw std::out_of_range("Index Out of Bounds"); }
            if (index != -1) { entry->next = current->next; }
            current->next = entry;
        }
    }
    void delete_entry(int index) {
        Entry* current = head;
        int count = 0;
        while(current->next != nullptr) {
            if (index == count) { break; }
            count++;

            current = current->next;
        }


    }
    void modify_entry() {

    }
    void search_entry() {

    }

private:
    Entry* head = nullptr;
};

int main(){


    return 0;
}
