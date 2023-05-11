#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <string>
// A simple phonebook created in C++ using Linked Lists

// -- Entry Object, inserts into linked list
struct Entry {
    Entry(std::string first_name, std::string last_name, std::string street_address, std::string city, std::string phone_number) {
        this->map["first_name"] = std::move(first_name);
        this->map["last_name"] = std::move(last_name);
        this->map["street_address"] = std::move(street_address);
        this->map["city"] = std::move(city);
        this->map["phone_number"] = std::move(phone_number);
    }

    void set(std::string key, std::string value) {
        auto itr = map.find(key);
        if (itr != map.end()){ (*itr).second = value; }
    }

    std::string get(std::string key) {
        auto itr = map.find(key);
        if (itr != map.end()){ return (*itr).second; }
    }


    std::map<std::string, std::string> map;

    Entry* next = nullptr;

};

// -- Linked List Class
class LinkedList {
public:
    // Adds entry to end by default
    void add_entry(Entry* entry, int index = -1) {
        // - Initialize empty list
        if (this->head == nullptr) {
            head = entry;
        // - Insert new head
        } else if (index == 0) {
            Entry* current = head;
            head = entry;
            head->next = current;
        // - Insert at any other position
        } else  {
            Entry* current = head;
            int count = 1;
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
    // - Deletes entry at given index
    void delete_entry(int index) {
        Entry* current = head;
        int count = 1;
        while(current->next != nullptr) {
            if (index <= count) { break; }
            count++;

            current = current->next;
        }
        if (count < index) { throw std::out_of_range("DELETE ENTRY FAILED: Index Out of Bounds"); }

        // Delete head or other value
        if (count > index) {
            Entry* temp = head;
            head = temp->next;
            delete temp;
        } else {
            Entry* temp = current->next;
            current->next = temp->next;
            delete temp;
        }


    }
    // - Returns entry at given index
    Entry* get_entry(int index) {
        Entry* current = head;
        int count = 0;
        while(current->next != nullptr) {
            if (index == count) { break; }
            count++;

            current = current->next;
        }
        if (count < index) { throw std::out_of_range("GET ENTRY FAILED: Index Out of Bounds"); }

        return current;
    }
    // - Returns first entry of given key-value pair
    Entry* get_entry(std::string key, std::string value) {
        Entry* current = head;
        bool found = false;
        while(current->next != nullptr) {
            if (current->get(key) == value) {
                found = true;
                break;
            }

            current = current->next;
        }
        if (!found) { throw std::out_of_range("GET ENTRY FAILED: Given Entry is not Within List"); }

        return current;
    }
    // - Returns index of given entry
    int index_of(Entry* entry) {
        Entry* current = head;
        int count = 0;
        bool found = false;
        while(current->next != nullptr) {
            if (entry == current) {
                found = true;
                break;
            }
            count++;

            current = current->next;
        }
        if (!found) { throw std::out_of_range("INDEX OF FAILED: Given Entry is not Within List"); }

        return count;
    }

    // - Returns linked lists contents as a vector of pointers
    std::vector<Entry*> list() {
        std::vector<Entry*> list;

        Entry* current = head;
        while(current->next != nullptr) {
            list.push_back(current);
            current = current->next;
        }
        list.push_back(current);
        return list;
    }

private:
    Entry* head = nullptr;
};

// -- Entry << operator overload. Allows for direct printing of Entry objects.
std::ostream& operator<<(std::ostream& os, const Entry& entry) {
    auto it = entry.map.begin();
    while (it != entry.map.end()) {
        os << it->first <<": " << it->second << "\n";
        it++;
    }
    return os;
}

std::string get_user_input(const std::string& prompt) {
    std::cout << prompt;
    std::string user_input;
    std::getline(std::cin, user_input);
    return user_input;
}

// -- Main
int main(){
    // -- Initialize Phonebook
    LinkedList phonebook;
    phonebook.add_entry(new Entry("Drake", "Pickett", "2612 James Street", "Bellingham", "3606030350"));
    phonebook.add_entry(new Entry("James", "Pickett", "2612 James Street", "Bellingham", "3606030350"));
    phonebook.add_entry(new Entry("Oliver", "Pickett", "2612 James Street", "Bellingham", "3606030350"));
    phonebook.add_entry(new Entry("Baby", "Pickett", "2612 James Street", "Bellingham", "3606030350"), 0);

    // Main loop
    std::cout << " =+=+ PHONEBOOK MANAGER +=+= \n";
    bool is_running = true;
    while (is_running) {
        std::cout << "[V]iew Phonebook\n"
                  << "[A]dd Entry\n"
                  << "[M]odify Entry\n"
                  << "[D]elete Entry\n"
                  << "[E]xit\n"
                  << "> ";

        char user_input;
        std::cin >> user_input;
        std::cin.ignore();
        std::cout << "\n";
        switch(toupper(user_input)){
            case 'V': {
                for (const Entry *e: phonebook.list()) {
                    std::cout << "=+=+=+=+=+=+=+==+=+=+=+=+=+=+=\n" << *e << "=+=+=+=+=+=+=+==+=+=+=+=+=+=+=\n";
                }
                break;
            } case 'A': {
                std::cout << "ADDING ENTRY\n"
                          << "=+=+=+=+=+=+" << std::endl;
                phonebook.add_entry(new Entry(
                        get_user_input("First Name: "), get_user_input("Last Name: "),
                        get_user_input("Street Address: "), get_user_input("City: "),
                        get_user_input("Phone Number: ")
                ));

                std::cout << "ENTRY ADDED" << std::endl;

                break;
            } case 'M': {
                std::cout << "MODIFYING ENTRY\n"
                          << "=+=+=+=+=+=+=+=" << std::endl;
                std::string user_entry = get_user_input("Search for an entry by Number or Info \n "
                                                        "Valid Info: [first_name], [last_name], [street_address], [city], [phone_number]\n "
                                                        "Valid Numbers: Between [0] and [" +
                                                        std::to_string(phonebook.list().size()) + "]"
                                                        "\n>");
                Entry *entry;
                if (isdigit(user_entry[0])) {
                    entry = phonebook.get_entry(stoi(user_entry));
                } else {
                    entry = phonebook.get_entry(user_entry, get_user_input("Value to Search For: "));
                }

                // get inputs are definined in their own lines to ensure they're called in the correct order
                std::string info = get_user_input("Info to Modify: ");
                std::string new_value = get_user_input("New Value: ");
                entry->set(info, new_value );

                std::cout << "ENTRY UPDATED" << std::endl;

                break;
            } case 'D': {
                std::cout << "DELETING ENTRY\n"
                          << "=+=+=+=+=+=+=+" << std::endl;
                std::string user_entry = get_user_input("Search for an entry by Number or Info \n "
                                                        "Valid Info: [first_name], [last_name], [street_address], [city], [phone_number]\n "
                                                        "Valid Numbers: Between [0] and [" +
                                                        std::to_string(phonebook.list().size()) + "]"
                                                      "\n>");
                Entry *entry;
                if (isdigit(user_entry[0])) {
                    entry = phonebook.get_entry(stoi(user_entry));
                } else {
                    entry = phonebook.get_entry(user_entry, get_user_input("Value to Search For: "));
                }

                phonebook.delete_entry(phonebook.index_of(entry));

                std::cout << "ENTRY DELETED" << std::endl;
                break;
            } case 'E': {
                is_running = false;
                break;
            } default:
                std::cout << "Invalid Input" << std::endl;
        }
    }

    return 0;
}
