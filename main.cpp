#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "items.h"
#include "catalog.h"
#include "customer.h"
#include "order.h"
#include "orderLine.h"
#include "receipt.h"
#include "menu.h"

int main()
{
    system("chcp 1251 > nul");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Catalog newCatalog;
    std::cout << "Добро пожаловать в наш каталог!\n";

    const std::string shopFile = "ShopData.bin";

    if (newCatalog.loadFromBinary(shopFile) < 0)
    {
        newCatalog.addItem(new CountItem("Цемент (мешок)", 15.5, 50));
        newCatalog.addItem(new CountItem("Кирпич красный (шт)", 0.85, 1000));
        newCatalog.addItem(new UncountItem("Краска белая (л)", 45.2, 25.5));
        newCatalog.addItem(new UncountItem("Грунтовка (л)", 12.0, 50.0));
        newCatalog.addItem(new CountItem("Блок газосиликатный (шт)", 4.8, 300));
        newCatalog.addItem(new UncountItem("Песок строительный (т)", 22.5, 15.0));
        newCatalog.addItem(new CountItem("Лист гипсокартона (шт)", 18.0, 40));
        newCatalog.addItem(new UncountItem("Кабель медный (м)", 3.2, 150.0));
        newCatalog.addItem(new CountItem("Пенопласт лист (шт)", 9.5, 60));
        newCatalog.addItem(new UncountItem("Штукатурка гипсовая (кг)", 1.1, 250.0));
        newCatalog.saveToBinary(shopFile);
    }

    while (true)
    {
        newCatalog.showCatalog();
        std::cout << "[1] - Поиск по названию товара\n"
                  << "[2] - Сортировать товары по цене(по возрастанию)\n"
                  << "[3] - Сделать заказ\n"
                  << "[4] - Сохранить каталог в файл\n"
                  << "[5] - Работа с файлом каталога\n"
                  << "[0] - ВЫХОД\n";

        int choice = inputChoice(0, 5);

        switch (choice)
        {
        case 1:
        {
            std::cout << "Введите название товара: ";
            std::string name;
            std::getline(std::cin, name);
            Item *findItem = newCatalog.findItem(name);
            if (findItem == nullptr)
            {
                std::cout << "Такого товара нет.\n";
            }
            else
            {
                findItem->showInfo();
            }
            break;
        }

        case 2:
        {
            std::cout << "Отсортированный каталог: \n";
            newCatalog.sortCatalogList();
            break;
        }

        case 3:
        {
            makeOrder(newCatalog);
            newCatalog.saveToBinary(shopFile); 
            break;
        }

        case 4:
        {
            if (newCatalog.saveCatalogToFile("catalog.txt"))
            {
                std::cout << "Каталог сохранен в файл catalog.txt\n";
            }
            else
            {
                std::cout << "Не удалось сохранить каталог в файл!\n";
            }
            break;
        }

        case 5:
        {
            editFile();
            newCatalog.loadFromBinary(shopFile); 
            break;
        }

        case 0:
        {
            return 0;
        }
        }
    }

    return 0;
}