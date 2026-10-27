#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "items.h"

class Catalog
{
protected:
    std::vector<Item *> catalogList;

public:
    Catalog() {}
    void addItem(Item *newItem)
    {
        catalogList.push_back(newItem);
    }
    Item *findItem(const std::string &name);
    void sortCatalogList() const;
    void showCatalog() const;
    bool saveCatalogToFile(const char *fileName) const;
    int loadFromBinary(const std::string &fileName);
    void saveToBinary(const std::string &fileName) const;

    ~Catalog();
};
