#include <iostream>
#include <vector>
#include <list>
#include <fstream>
using namespace std;

const int TABLE_SIZE = 100;

struct Item {
    string id;
    string name;
    string category;
    string date;
    string location;
};

class HashTable {
    vector<list<Item>> table;

    int hashFunction(string key) {
        int hash = 0;
        for (char ch : key)
            hash = (hash + int(ch)) % TABLE_SIZE;
        return hash;
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
    }

    void addItem(const Item& item) {
        int index = hashFunction(item.id);
        table[index].push_back(item);
        saveToFile(item);
    }

    Item* searchItem(string id) {
        int index = hashFunction(id);
        for (auto& item : table[index]) {
            if (item.id == id)
                return &item;
        }
        return nullptr;
    }

    void displayAll() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            for (auto& item : table[i]) {
                cout << "ID: " << item.id << ", Name: " << item.name
                     << ", Category: " << item.category << ", Date: " << item.date
                     << ", Location: " << item.location << endl;
            }
        }
    }

    void saveToFile(const Item& item) {
        ofstream fout("lost_found_data.txt", ios::app);
        fout << item.id << "," << item.name << "," << item.category << ","
             << item.date << "," << item.location << endl;
        fout.close();
    }

    void loadFromFile() {
        ifstream fin("lost_found_data.txt");
        string line;
        while (getline(fin, line)) {
            Item item;
            size_t pos = 0;
            int field = 0;
            while ((pos = line.find(',')) != string::npos) {
                string token = line.substr(0, pos);
                switch (field) {
                    case 0: item.id = token; break;
                    case 1: item.name = token; break;
                    case 2: item.category = token; break;
                    case 3: item.date = token; break;
                }
                line.erase(0, pos + 1);
                field++;
            }
            item.location = line;
            int index = hashFunction(item.id);
            table[index].push_back(item);
        }
        fin.close();
    }
};

int main() {
    HashTable tracker;
    tracker.loadFromFile();

    int choice;
    while (true) {
        cout << "\n1. Add Item\n2. Search Item\n3. Display All\n4. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Item i;
            cout << "Enter ID: "; getline(cin, i.id);
            cout << "Enter Name: "; getline(cin, i.name);
            cout << "Enter Category: "; getline(cin, i.category);
            cout << "Enter Date (YYYY-MM-DD): "; getline(cin, i.date);
            cout << "Enter Location: "; getline(cin, i.location);
            tracker.addItem(i);
        } else if (choice == 2) {
            string id;
            cout << "Enter ID to search: "; cin >> id;
            Item* found = tracker.searchItem(id);
            if (found)
                cout << "Item Found: " << found->name << ", " << found->category << ", " << found->date << ", " << found->location << endl;
            else
                cout << "Item not found!" << endl;
        } else if (choice == 3) {
            tracker.displayAll();
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
