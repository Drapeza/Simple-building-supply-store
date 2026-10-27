#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include "items.h"

void UncountItem::setUncountItemAmount()
{
    double amount;
    while (true)
    {
        std::cout << "\nВведите количество в метрах/литрах кубических: ";
        std::cin >> amount;

        if (std::cin.good())
        {
            std::cin.ignore(1000, '\n');
            break;
        }

        std::cin.clear();
        std::cout << "\nОшибка ввода данных!\n";
        std::cin.ignore(1000, '\n');
    }

    UncountItem::uncountItemAmount = amount;
}

double UncountItem::inputAmount(double maxAmount)
{
    double amount;
    while (true)
    {
        std::cout << "\nВведите количество (в единицах из названия товара, доступно " << maxAmount << "): ";
        std::cin >> amount;

        if (std::cin.good() && amount > 0 && amount <= maxAmount)
        {
            std::cin.ignore(1000, '\n');
            break;
        }

        std::cin.clear();
        std::cout << "\nОшибка ввода данных! Количество должно быть больше нуля и не больше остатка.\n";
        std::cin.ignore(1000, '\n');
    }

    return amount;
}

void CountItem::setCountItemAmount()
{
    int amount;
    while (true)
    {
        std::cout << "\nВведите количество в штуках: ";
        std::cin >> amount;

        if (std::cin.good())
        {
            std::cin.ignore(1000, '\n');
            break;
        }

        std::cin.clear();
        std::cout << "\nОшибка ввода данных!";
        std::cin.ignore(1000, '\n');
    }

    CountItem::countItemAmount = amount;
}

double CountItem::inputAmount(double maxAmount)
{
    int amount;
    while (true)
    {
        std::cout << "\nВведите количество в штуках (доступно " << maxAmount << "): ";
        std::cin >> amount;

        if (std::cin.good() && amount > 0 && amount <= maxAmount)
        {
            std::cin.ignore(1000, '\n');
            break;
        }

        std::cin.clear();
        std::cout << "\nОшибка ввода данных! Количество должно быть целым, больше нуля и не больше остатка.\n";
        std::cin.ignore(1000, '\n');
    }

    return amount;
}
std::ostream &operator<<(std::ostream &os, const Item &obj)
{
    os << obj.getName() << " " << obj.getPrice()<<" "<<obj.getAmount();
    return os;
}
std::istream &operator>>(std::istream &is, Item &obj)
{
    std::string name;
    double price=0;
    std::cout << "Введите название: \n";
    std::getline(is, name);
    std::cout << "Введите цену: \n";
    is >> price;
    is.ignore(1000, '\n');
    obj.setName(name.c_str());
    obj.setPrice(price);
    return is;
}

ItemStruct itemToStruct (const Item& item)
{
   
        ItemStruct newItem={};
        newItem.price = item.getPrice();
        newItem.amount = item.getAmount();
        newItem.itemType = item.getType();

        strncpy(newItem.name, item.getName().c_str(), sizeof(newItem.name)-1);
        newItem.name[39]='\0';
    return newItem;
}

Item *itemFromStruct(const ItemStruct &rec)
{

    Item *newItem = nullptr;

    if (rec.itemType == 0)
    {
        newItem = new CountItem(rec.name, rec.price, static_cast<int>(rec.amount));
    }

    if (rec.itemType ==1)
    {
        newItem = new UncountItem(rec.name, rec.price, rec.amount);
    }

    if (newItem != nullptr)
    {
        return newItem;
    }
    return nullptr;
}

void saveItemsToBinary(const std::vector<Item *> &items, const std::string& fileName)
{
    std::ofstream f(fileName, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!f)
    {
        std::cerr << "Ошибка записи в файл!\n";
        return;
    }

    for (size_t i = 0; i < items.size(); i++)
    {
        ItemStruct newItem= itemToStruct(*items[i]);
        f.write(reinterpret_cast<const char *>(&newItem), sizeof(newItem));
        if (f.fail())
        {
            std::cerr << "ОШибка сохранения в файл.\n";
            return;
        }
       
    }
    f.close();
}


void readItemsFromBinary(std::vector<Item *> &items, const std::string& fileName)
{
    std::ifstream f(fileName, std::ios::in | std::ios::binary);
    if (!f)
    {
        std::cerr << "Невозможно прочитать файл!\n";
        return;
    }

    for (auto item : items)
    {
        delete item;
    }
    items.clear();

   
    
        ItemStruct newItemStruct;
      
        while (true)
        {  f.read(reinterpret_cast<char *>(&newItemStruct), sizeof(ItemStruct));
            if (f.eof())
            {
                break;
            }
            if (!f)
            {
                std::cerr << "Ошибка чтения данных!\n";break;
            }
            Item* newItem=itemFromStruct(newItemStruct);

            if(newItem!=nullptr){
                items.push_back(newItem);
            }
        }
    

    f.close();
}