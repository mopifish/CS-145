#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>

using std::string;

struct PhonebookEntry {
    int ID = -1;
    string first_name;
    string last_name;
    string street_address;
    string city_name;
    string zip_code;
    string email;
    string phone_number;

    PhonebookEntry() = default;
    PhonebookEntry(string first_name, string last_name, string street_address, string city_name, string zip_code, string email, string phone_number) {
        this->first_name = std::move(first_name);
        this->last_name = std::move(last_name);
        this->street_address = std::move(street_address);
        this->city_name = std::move(city_name);
        this->zip_code = std::move(zip_code);
        this->email = std::move(email);
        this->phone_number = std::move(phone_number);
    }
};

struct Node {
    int ID;
    int height;

    PhonebookEntry data;

    Node* left = nullptr;
    Node* right = nullptr;

    Node(int id, PhonebookEntry data){
        this->ID = id;
        this->height = 1;
        this->data = std::move(data);
    }

    void update_height(){
        int left_height = (this->left != nullptr) ? this->left->height + 1 : 0;
        int right_height = (this->right != nullptr) ? this->right->height + 1 : 0;
        this->height = std::max(left_height, right_height);
    }
};

class BinarySearchTree {
private:
    Node* root = nullptr;
    // -- Insertion Functions --
    Node* insert_node(Node* new_node, Node* current_node) {

        // Base Case
        if (current_node == nullptr){
            return new_node;
        }

        if (new_node->ID < current_node->ID) {
            current_node->left = this->insert_node(new_node, current_node->left);
        } else if (new_node->ID > current_node->ID) {
            current_node->right = this->insert_node(new_node, current_node->right);
        } else {
            std::cout << "FAILED: " << new_node->ID << " == " << current_node->ID << "\n";
            return current_node;
        }

        // ---------- AVL Sorting, Sourced from https://www.geeksforgeeks.org/insertion-in-an-avl-tree/ ----------

        current_node->update_height();
        int root_balance = this->get_balance(current_node);
        return this->balance(current_node, new_node, root_balance);
   }
    Node* balance(Node* subroot, Node* new_node, int node_balance) {
        if (node_balance > 1 ) {
            /* Left Left
             *            z                                      y
             *           / \                                   /   \
             *          y   T4      Right Rotate (z)          x      z
             *         / \          - - - - - - - - ->      /  \    /  \
             *        x   T3                               T1  T2  T3  T4
             *       / \
             *     T1   T2
             */
            /* z = subroot = current_node->left
             * y = current_node->left->left
             */
            if (new_node->ID < subroot->left->ID) {
                return this->rotate_right(subroot);

                /* Left Right
                 *           c                              c                           c
                 *         /                               /                           /
                 *        z                               z                           x
                 *       / \                            /   \                        /  \
                 *      y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
                 *     / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
                 *   T1   x                          y    T3                    T1  T2 T3  T4
                 *       / \                        / \
                 *     T2   T3                    T1   T2
                 */
                /* c = current_node
                 * z = subroot = current_node->left
                 * y = current_node->left->left
                 */
            } else if (new_node->ID > subroot->left->ID) {
                subroot->left = this->rotate_left(subroot->left);
                return this->rotate_right(subroot);
            }
        }
        // Right Cases
        else if (node_balance < -1) {

            /* Right Right Case
             *    c                               c
             *     \                               \
             *     z                                y
             *    /  \                            /   \
             *   T1   y     Left Rotate(z)       z      x
             *       /  \   - - - - - - - ->    / \    / \
             *      T2   x                     T1  T2 T3  T4
             *          / \
             *        T3  T4
             */
            /* c = current_node
             * z = subroot = current_node->right
             * y = current_node->right->right
             */
            if (new_node->ID > subroot->right->ID) {
                return this->rotate_left(subroot);

                /* Right Left Case
                 *         c                            c                            c
                 *          \                            \                            \
                 *           z                            z                            x
                 *          / \                          / \                          /  \
                 *        T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
                 *            / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
                 *           x   T4                      T2   y                  T1  T2  T3  T4
                 *          / \                              /  \
                 *        T2   T3                           T3   T4
                 */
                /* c = current_node
                 * z = subroot = current_node->right
                 * y = current_node->right->right
                 */
            } else if (new_node->ID < subroot->right->ID) {
                subroot->right = this->rotate_right(subroot->right);
                return rotate_left(subroot);
            }
        }

        return subroot;
    }
    Node* rotate_right(Node* y) {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->update_height();
        x->update_height();

        // Return new root
        return x;
    }
    Node* rotate_left(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update node heights
        x->update_height();
        y->update_height();

        // Return new subtree root
        return y;
    }
    int height(Node* node){
        return (node == nullptr) ? 0 : node->height;
    }
    int get_balance(Node* node) {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }


    Node* delete_node(int ID, Node* current_node){
        if (current_node->ID > ID) {
            current_node->right = (ID, current_node->right);
        } else if (current_node->ID < ID) {
            current_node->left = (ID, current_node->left);
        } else if (current_node->ID == ID) {
            if (current_node->left == nullptr and current_node->right == nullptr){
                delete current_node;
                current_node = nullptr;
            } else if (current_node->left == nullptr) {
                Node* temp = current_node;
                current_node = current_node->right;
                delete temp;
            } else if (current_node->right == nullptr) {
                Node* temp = current_node;
                current_node = current_node->left;
                delete temp;
            } else {
                Node* min_node = get_minimum_node(current_node->right);\
                current_node->data = min_node->data;
                current_node->right = delete_node(min_node->ID, current_node->right);
            }
        }

        return current_node;
    }
    Node* get_minimum_node(Node* current_node){
        while (current_node->left != nullptr){
            current_node = current_node->left;
        }
        return current_node;
    }

    // ---------------- Recursive printing, Sourced from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
    void print(string prefix, Node* current_node, bool is_left){

        std::cout << prefix;
        std::cout << (is_left ? "|--" : "L--" );

        // print the value of the node
        std::cout << ((current_node != nullptr) ? std::to_string(current_node->ID) : " ") << std::endl;

        if(current_node != nullptr) {
            // enter the next tree level - left and right branch
            this->print(prefix + (is_left ? "|   " : "    "), current_node->left, true);
            this->print(prefix + (is_left ? "|   " : "    "), current_node->right, false);
        }
    }

public:
    void insert_node(Node* new_node) {
         if (this->root == nullptr){
            this->root = new_node;
         } else {
             this->root = this->insert_node(new_node, this->root);
         }
    }
    void delete_node(int ID){
        this->root = this->delete_node(ID, this->root);
    }

    void print(){
        this->print("", this->root, false);
    }
};


int main() {
    BinarySearchTree BST = BinarySearchTree();

    std::vector<PhonebookEntry> phonebook_entrys = {
            PhonebookEntry("Jane", "Seymore", "157 Jone St", "Jerseyham", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Fillip", "Write", "157 Jone St", "Jonesberg", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Hammer", "Seymore", "157 Jone St", "Jerseyham", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Crock", "Socter", "157 Jone St", "Shorton", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Bob", "Seymore", "157 Jone St", "Jonesberg", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Bill", "Socter", "157 Jone St", "Shorton", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Blip", "Lillip", "157 Jone St", "Ohio", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Jik", "Write", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Jord", "Glurpis", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Foop", "Socter", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Snurp", "Seymore", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Illip", "Write", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Goop", "Glurpis", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Gryuck", "Socter", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Gorch", "Glurpis", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Snook", "Write", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Ticker", "Socter", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Richie", "Glurpis", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Lolop", "Socter", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Franet", "Seymore", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Frolp", "Write", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Grint", "Socter", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Snurk", "Glurpis", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Hugh", "Socter", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),
            PhonebookEntry("Eyes", "Seymore", "157 Jone St", "Maneves", "78644", "janey@gmail.com", "555-555-5555"),

    };

    for (int i = 0; i < phonebook_entrys.size(); i++){
        phonebook_entrys[i].ID = i;
        Node* new_node = new Node(i, phonebook_entrys[i]);
        BST.insert_node(new_node);
    }

    BST.print();
    BST.delete_node(1);
    BST.print();

    return 0;
}
