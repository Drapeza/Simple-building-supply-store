#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "catalog.h"

Item *Catalog::findItem(const std::string &name)
{
    if (name.empty())
    {
        return nullptr;
    }

    for (int i = 0; i < catalogList.size(); i++)
    {
        if (catalogList[i]->getName().rfind(name, 0) == 0)
        {
            return catalogList[i];
        }
    }
    return nullptr;
}

void Catalog::sortCatalogList() const
{
    std::vector<Item *> sortedList = catalogList;
    int size = sortedList.size();
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (sortedList[j]->getPrice() > sortedList[j + 1]->getPrice())
            {
                Item *temp;
                temp = sortedList[j];
                sortedList[j] = sortedList[j + 1];
                sortedList[j + 1] = temp;
            }
        }
    }
    std::cout << std::endl
              << std::setw(21) << std::setfill('=') << "" << " ÊÀÒÀËÎÃ ÌÀÃÀÇÈÍÀ ÑÒÐÎÉÌÀÒÅÐÈÀËÎÂ " << std::setw(22) << std::setfill('=') << "" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << std::left << std::setw(40) << "Íàèìåíîâàíèå" << " | ";
    std::cout << std::right << std::setw(15) << "Öåíà (ðóá.)" << " | ";
    std::cout << std::right << std::setw(15) << "Îñòàòîê" << "|\n";
    std::cout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;

    for (int i = 0; i < sortedList.size(); i++)
    {
        std::cout << std::left << std::setw(40) << sortedList[i]->getName() << " | ";

        std::cout.setf(std::ios::fixed | std::ios::showpoint);
        std::cout.precision(2);
        std::cout << std::right << std::setw(15) << sortedList[i]->getPrice() << " | ";
        std::cout.unsetf(std::ios::fixed | std::ios::showpoint);
        std::cout.precision(6);

        std::cout << std::right << std::setw(15) << sortedList[i]->getAmount() << "|\n";
    }
    std::cout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;
}

void Catalog::showCatalog() const
{
    std::cout << std::endl
              << std::setw(21) << std::setfill('=') << "" << " ÊÀÒÀËÎÃ ÌÀÃÀÇÈÍÀ ÑÒÐÎÉÌÀÒÅÐÈÀËÎÂ " << std::setw(22) << std::setfill('=') << "" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << std::left << std::setw(40) << "Íàèìåíîâàíèå" << " | ";
    std::cout << std::right << std::setw(15) << "Öåíà (ðóá.)" << " | ";
    std::cout << std::right << std::setw(15) << "Îñòàòîê" << "|\n";
    std::cout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;

    for (int i = 0; i < catalogList.size(); i++)
    {
        std::cout << std::left << std::setw(40) << catalogList[i]->getName() << " | ";

        std::cout.setf(std::ios::fixed | std::ios::showpoint);
        std::cout.precision(2);
        std::cout << std::right << std::setw(15) << catalogList[i]->getPrice() << " | ";
        std::cout.unsetf(std::ios::fixed | std::ios::showpoint);
        std::cout.precision(6);

        std::cout << std::right << std::setw(15) << catalogList[i]->getAmount() << "|\n";
    }
    std::cout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;
}

bool Catalog::saveCatalogToFile(const char *fileName) const
{
    std::ofstream fout(fileName);
    if (fout.fail())
    {
        return false;
    }

    fout << std::endl
         << std::setw(21) << std::setfill('=') << "" << " ÊÀÒÀËÎÃ ÌÀÃÀÇÈÍÀ ÑÒÐÎÉÌÀÒÅÐÈÀËÎÂ " << std::setw(22) << std::setfill('=') << "" << std::endl;
    fout << std::setfill(' ');
    fout << std::left << std::setw(40) << "Íàèìåíîâàíèå" << " | ";
    fout << std::right << std::setw(15) << "Öåíà (ðóá.)" << " | ";
    fout << std::right << std::setw(15) << "Îñòàòîê" << "|\n";
    fout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;

    for (int i = 0; i < catalogList.size(); i++)
    {
        fout << std::left << std::setw(40) << catalogList[i]->getName() << " | ";

        fout.setf(std::ios::fixed | std::ios::showpoint);
        fout.precision(2);
        fout << std::right << std::setw(15) << catalogList[i]->getPrice() << " | ";
        fout.unsetf(std::ios::fixed | std::ios::showpoint);
        fout.precision(6);

        fout << std::right << std::setw(15) << catalogList[i]->getAmount() << "|\n";
    }
    fout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;
    return fout.good();
}

int Catalog::loadFromBinary(const std::string &fileName)
{
    std::ifstream check(fileName, std::ios::binary);
    if (!check.is_open())
    {
        return -1;
    }
    check.close();

    readItemsFromBinary(catalogList, fileName);
    return static_cast<int>(catalogList.size());
}

void Catalog::saveToBinary(const std::string &fileName) const
{
    saveItemsToBinary(catalogList, fileName);
}

Catalog::~Catalog()
{
    for (int i = 0; i < catalogList.size(); i++)
    {
        delete catalogList[i];
    }
}
