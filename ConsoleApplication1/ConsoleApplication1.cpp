#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Location {
    int x, y, id;
    string name;
    Location* next;
};

void addToEnd(Location*& head);
void printList(Location* head);
int countByY(Location* head, int y);
void addAfterK(Location*& head, int k);
void swapKJ(Location*& head, int k, int j);
void deleteBeforeK(Location*& head, int k);
void saveToFile(Location* head, const string& filename);
void loadFromFile(Location*& head, const string& filename);
void clearList(Location*& head);

int main() {
    Location* head = nullptr;
    int choice;
    string filename = "locations.txt";

    do {
        cout << "\nMenu:\n";
        cout << "1. Add element to the end\n";
        cout << "2. Print list\n";
        cout << "3. Count by ordinate\n";
        cout << "4. Add after k-th\n";
        cout << "5. Swap k-th and j-th\n";
        cout << "6. Delete before k-th\n";
        cout << "7. Save to file\n";
        cout << "8. Load from file\n";
        cout << "9. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addToEnd(head); break;
        case 2: printList(head); break;
        case 3: {
            int y;
            cout << "Enter ordinate: ";
            cin >> y;
            cout << "Count: " << countByY(head, y) << "\n";
            break;
        }
        case 4: {
            int k;
            cout << "Enter k: ";
            cin >> k;
            addAfterK(head, k);
            break;
        }
        case 5: {
            int k, j;
            cout << "Enter k and j: ";
            cin >> k >> j;
            swapKJ(head, k, j);
            break;
        }
        case 6: {
            int k;
            cout << "Enter k: ";
            cin >> k;
            deleteBeforeK(head, k);
            break;
        }
        case 7: saveToFile(head, filename); break;
        case 8: loadFromFile(head, filename); break;
        case 9: clearList(head); break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 9);

    return 0;
}

void addToEnd(Location*& head) {
    Location* newNode = new Location;
    cout << "Enter x, y, id, and name: ";
    cin >> newNode->x >> newNode->y >> newNode->id;
    cin.ignore();
    getline(cin, newNode->name);
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
    }
    else {
        Location* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void printList(Location* head) {
    while (head) {
        cout << "Address: " << head << " -> (" << head->x << ", " << head->y << ") "
            << "ID: " << head->id << " Name: " << head->name << "\n";
        head = head->next;
    }
}

int countByY(Location* head, int y) {
    int count = 0;
    while (head) {
        if (head->y == y) count++;
        head = head->next;
    }
    return count;
}

void addAfterK(Location*& head, int k) {
    Location* temp = head;
    for (int i = 1; i < k && temp; i++) temp = temp->next;
    if (!temp) return;

    Location* newNode = new Location;
    cout << "Enter x, y, id, and name: ";
    cin >> newNode->x >> newNode->y >> newNode->id;
    cin.ignore();
    getline(cin, newNode->name);
    newNode->next = temp->next;
    temp->next = newNode;
}

void swapKJ(Location*& head, int k, int j) {
    if (k == j) return;
    Location* prevK = nullptr, * prevJ = nullptr, * nodeK = head, * nodeJ = head;
    for (int i = 1; nodeK && i < k; i++) { prevK = nodeK; nodeK = nodeK->next; }
    for (int i = 1; nodeJ && i < j; i++) { prevJ = nodeJ; nodeJ = nodeJ->next; }
    if (!nodeK || !nodeJ) return;
    if (prevK) prevK->next = nodeJ; else head = nodeJ;
    if (prevJ) prevJ->next = nodeK; else head = nodeK;
    swap(nodeK->next, nodeJ->next);
}

void deleteBeforeK(Location*& head, int k) {
    if (k <= 1 || !head || !head->next) return;
    Location* prev = nullptr, * temp = head;
    for (int i = 1; temp->next && i < k - 1; i++) { prev = temp; temp = temp->next; }
    if (!temp->next) return;
    if (prev) prev->next = temp->next;
    else head = temp->next;
    delete temp;
}

void saveToFile(Location* head, const string& filename) {
    ofstream file(filename);
    while (head) {
        file << head->x << " " << head->y << " " << head->id << " " << head->name << "\n";
        head = head->next;
    }
    file.close();
}

void loadFromFile(Location*& head, const string& filename) {
    clearList(head);
    ifstream file(filename);
    while (!file.eof()) {
        Location* newNode = new Location;
        file >> newNode->x >> newNode->y >> newNode->id;
        file.ignore();
        getline(file, newNode->name);
        newNode->next = head;
        head = newNode;
    }
    file.close();
}

void clearList(Location*& head) {
    while (head) {
        Location* temp = head;
        head = head->next;
        delete temp;
    }
}
