#include <iostream>
#include <string>

using namespace std;

// =========================
// Property
// =========================

struct Property {
    string name;
    int cost;
    string owner;
    Property* next;
};

// =========================
// Linked List
// =========================

class LinkedList {
private:
    Property* head;
    Property* tail;
    int size;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void add(string name, int cost) {
        Property* newProperty = new Property{name, cost, "Unowned", nullptr};

        if (head == nullptr) {
            head = newProperty;
            tail = newProperty;
            newProperty->next = head;
        } else {
            tail->next = newProperty;
            tail = newProperty;
            tail->next = head;
        }

        size++;
    }

    Property* search(string name) {
        if (head == nullptr) return nullptr;

        Property* current = head;

        do {
            if (current->name == name) return current;
            current = current->next;
        } while (current != head);

        return nullptr;
    }

    bool remove(string name) {
        if (head == nullptr) return false;

        Property* current = head;
        Property* previous = tail;

        do {
            if (current->name == name) {
                if (current == head && current == tail) {
                    head = nullptr;
                    tail = nullptr;
                } else {
                    previous->next = current->next;

                    if (current == head) head = current->next;
                    if (current == tail) tail = previous;

                    tail->next = head;
                }

                delete current;
                size--;
                return true;
            }

            previous = current;
            current = current->next;

        } while (current != head);

        return false;
    }

    void print() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Property* current = head;

        do {
            cout << current->name
                 << " | Cost: $" << current->cost
                 << " | Owner: " << current->owner
                 << endl;

            current = current->next;

        } while (current != head);
    }

    Property* move(Property* position, int spaces) {
        for (int i = 0; i < spaces; i++) {
            position = position->next;
        }

        return position;
    }

    Property* getHead() {
        return head;
    }

    int getSize() {
        return size;
    }

    ~LinkedList() {
        if (head == nullptr) return;

        tail->next = nullptr;

        while (head != nullptr) {
            Property* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// =========================
// Player
// =========================

struct Player {
    string name;
    int money;
    Property* position;
};

// =========================
// Buy Property
// =========================

void buyProperty(Player& player) {
    Property* property = player.position;

    if (property->owner != "Unowned") {
        cout << property->name << " is already owned by "
             << property->owner << "." << endl;
        return;
    }

    if (player.money < property->cost) {
        cout << player.name << " cannot afford "
             << property->name << "." << endl;
        return;
    }

    property->owner = player.name;
    player.money -= property->cost;

    cout << player.name << " bought "
         << property->name << " for $"
         << property->cost << "." << endl;
}

// =========================
// Part 1 Test
// =========================

void testLinkedList() {
    cout << "PART 1 - MY LINKED LIST" << endl;
    cout << "===================================" << endl;

    LinkedList testList;

    testList.add("Property A", 100);
    testList.add("Property B", 200);
    testList.add("Property C", 300);

    cout << "\nAfter adding:" << endl;
    testList.print();

    cout << "\nSearching for Property B: ";

    if (testList.search("Property B") != nullptr) {
        cout << "Found" << endl;
    } else {
        cout << "Not found" << endl;
    }

    cout << "\nRemoving Property B: ";

    if (testList.remove("Property B")) {
        cout << "Removed" << endl;
    } else {
        cout << "Not found" << endl;
    }

    cout << "\nAfter removing:" << endl;
    testList.print();

    cout << endl;
}

// =========================
// Main
// =========================

int main() {

    // Part 1
    testLinkedList();

    // Part 2
    cout << "PART 2 - MONOPOLY GAME" << endl;
    cout << "======================" << endl;

    LinkedList board;

    board.add("Mediterranean Avenue", 60);
    board.add("Baltic Avenue", 80);
    board.add("Oriental Avenue", 100);
    board.add("Vermont Avenue", 120);
    board.add("Connecticut Avenue", 140);
    board.add("St. Charles Place", 160);
    board.add("States Avenue", 180);
    board.add("Virginia Avenue", 200);
    board.add("Park Place", 350);
    board.add("Boardwalk", 400);

    cout << "\nStarting Board:" << endl;
    board.print();

    Player mustafa{"Mustafa", 1500, board.getHead()};
    Player sofia{"Sofia", 1500, board.getHead()};

    int moves[10] = {2, 2, 4, 3, 4, 5, 3, 3, 6, 1};

    cout << "\n10 TURN SIMULATION" << endl;
    cout << "==================" << endl;

    for (int turn = 0; turn < 10; turn++) {
        Player* currentPlayer;

        if (turn % 2 == 0) {
            currentPlayer = &mustafa;
        } else {
            currentPlayer = &sofia;
        }

        string oldPosition = currentPlayer->position->name;

        currentPlayer->position =
            board.move(currentPlayer->position, moves[turn]);

        cout << "\nTurn " << turn + 1 << ": "
             << currentPlayer->name
             << " moved " << moves[turn]
             << " spaces from " << oldPosition
             << " to " << currentPlayer->position->name
             << "." << endl;

        buyProperty(*currentPlayer);

        cout << currentPlayer->name
             << " has $" << currentPlayer->money
             << " left." << endl;
    }

    cout << "\nFINAL BOARD" << endl;
    cout << "===========" << endl;
    board.print();

    cout << "\nFINAL PLAYERS" << endl;
    cout << "=============" << endl;

    cout << mustafa.name << ": $" << mustafa.money
         << " | Position: " << mustafa.position->name << endl;

    cout << sofia.name << ": $" << sofia.money
         << " | Position: " << sofia.position->name << endl;

    return 0;
}