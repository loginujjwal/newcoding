#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
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

    const string DATA_FILE = "items.txt";

public:
    HashTable() {
        table.resize(TABLE_SIZE);
        loadFromFile();
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

    vector<Item> getAllItems() {
        vector<Item> items;
        for (auto& bucket : table) {
            for (auto& item : bucket) {
                items.push_back(item);
            }
        }
        return items;
    }

private:
    void saveToFile(const Item& item) {
        ofstream fout(DATA_FILE, ios::app);
        fout << item.id << "|" << item.name << "|" << item.category << "|"
             << item.date << "|" << item.location << "\n";
        fout.close();
    }

    void loadFromFile() {
        ifstream fin(DATA_FILE);
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            string id, name, category, date, location;
            if (getline(ss, id, '|') &&
                getline(ss, name, '|') &&
                getline(ss, category, '|') &&
                getline(ss, date, '|') &&
                getline(ss, location)) {
                Item item = {id, name, category, date, location};
                int index = hashFunction(id);
                table[index].push_back(item);
            }
        }
        fin.close();
    }
};

#endif
