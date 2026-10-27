#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "items.h"
#include "menu.h"

static const char *FILE_NAME = "ShopData.bin";

static int countRecords()
{
    std::ifstream f(FILE_NAME, std::ios::binary);
    if (!f.is_open())
    {
        return 0;
    }

    f.seekg(0, std::ios::end);
    std::streamoff size = f.tellg();
    f.close();

    if (size < 0)
    {
        return 0;
    }
    return static_cast<int>(size / static_cast<std::streamoff>(sizeof(ItemStruct)));
}

static int inputNumber(const char *text, int minValue, int maxValue)
{
    int number;
    while (true)
    {
        std::cout << text;
        std::cin >> number;

        if (std::cin.good() && number >= minValue && number <= maxValue)
        {
            std::cin.ignore(1000, '\n');
            return number;
        }

        if (std::cin.eof() || std::cin.bad())
        {
            return minValue;
        }

        std::cin.clear();
        std::cout << "Ошибка ввода данных! Повторите попытку.\n";
        std::cin.ignore(1000, '\n');
    }
}

static double inputDouble(const char *text, double minValue)
{
    double value;
    while (true)
    {
        std::cout << text;
        std::cin >> value;

        if (std::cin.good() && value >= minValue)
        {
            std::cin.ignore(1000, '\n');
            return value;
        }

        if (std::cin.eof() || std::cin.bad())
        {
            return minValue;
        }

        std::cin.clear();
        std::cout << "Ошибка ввода данных! Повторите попытку.\n";
        std::cin.ignore(1000, '\n');
    }
}

static void printItem(int number, const Item &item)
{
    std::cout << number << ". " << item;
    if (item.getType() == ItemType::countItem)
    {
        std::cout << " [штучный]\n";
    }
    else
    {
        std::cout << " [весовой]\n";
    }
}

static void showFile()
{
    if (countRecords() == 0)
    {
        std::cout << "Файл пуст или ещё не создан.\n";
        return;
    }

    std::ifstream f(FILE_NAME, std::ios::binary);
    if (!f.is_open())
    {
        std::cerr << "Ошибка открытия файла!\n";
        return;
    }

    std::cout << "Товары в файле (название, цена, остаток): \n";
    f.seekg(0);

    ItemStruct rec;
    int number = 0;
    while (true)
    {
        f.read(reinterpret_cast<char *>(&rec), sizeof(rec));
        if (f.eof())
        {
            break;
        }
        if (f.fail() || f.bad())
        {
            std::cerr << "Ошибка чтения данных.\n";
            break;
        }

        number++;
        Item *item = itemFromStruct(rec);
        if (item != nullptr)
        {
            printItem(number, *item);
            delete item;
        }
    }
    f.close();
}

static void addToFile()
{
    std::cout << "Выберите тип товара:\n"
              << "[1] - Штучный (CountItem)\n"
              << "[2] - Весовой / мерный (UncountItem)\n";
    int choiceType = inputNumber("Ваш выбор: ", 1, 2);

    CountItem *countPtr = nullptr;
    UncountItem *uncountPtr = nullptr;
    Item *newItem = nullptr;

    if (choiceType == 1)
    {
        countPtr = new CountItem("None", 0.0, 0);
        newItem = countPtr;
    }
    else
    {
        uncountPtr = new UncountItem("None", 0.0, 0.0);
        newItem = uncountPtr;
    }
    
        std::cin >> *newItem;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Ошибка ввода данных! Товар не добавлен.\n";
        delete newItem;
        return;
    }

    if (newItem->getName().empty() || newItem->getPrice() <= 0.0)
    {
        std::cout << "Название не должно быть пустым, а цена должна быть больше нуля. Товар не добавлен.\n";
        delete newItem;
        return;
    }

    if (newItem->getName().size() > sizeof(ItemStruct::name) - 1)
    {
        std::cout << "Название длиннее 39 символов, оно будет обрезано.\n";
    }

    if (countPtr != nullptr)
    {
        countPtr->setCountItemAmount();
    }
    else
    {
        uncountPtr->setUncountItemAmount();
    }

    if (newItem->getAmount() < 0.0)
    {
        std::cout << "Остаток не может быть отрицательным. Товар не добавлен.\n";
        delete newItem;
        return;
    }

    ItemStruct rec = itemToStruct(*newItem);
    delete newItem;

    std::ofstream out(FILE_NAME, std::ios::binary | std::ios::app);
    if (!out.is_open())
    {
        std::cerr << "Ошибка открытия файла!\n";
        return;
    }

    out.write(reinterpret_cast<const char *>(&rec), sizeof(rec));
    if (!out.good())
    {
        std::cerr << "Ошибка записи в файл!\n";
    }
    else
    {
        std::cout << "Товар добавлен в файл.\n";
    }
    out.close();
}

static void findInFile()
{
    if (countRecords() == 0)
    {
        std::cout << "Файл пуст или ещё не создан.\n";
        return;
    }

    std::cout << "[1] - Поиск по части названия\n"
              << "[2] - Поиск по диапазону цены\n";
    int mode = inputNumber("Выберите вид поиска: ", 1, 2);

    std::string query;
    double minPrice = 0.0;
    double maxPrice = 0.0;

    if (mode == 1)
    {
        std::cout << "Введите часть названия: ";
        std::getline(std::cin, query);
        if (query.empty())
        {
            std::cout << "Пустой запрос.\n";
            return;
        }
    }
    else
    {
        minPrice = inputDouble("Цена от: ", 0.0);
        maxPrice = inputDouble("Цена до: ", 0.0);
        if (maxPrice < minPrice)
        {
            std::cout << "Верхняя граница цены меньше нижней.\n";
            return;
        }
    }

    std::ifstream f(FILE_NAME, std::ios::binary);
    if (!f.is_open())
    {
        std::cerr << "Ошибка открытия файла!\n";
        return;
    }

    std::cout << "\n=== Результаты поиска ===\n";
    f.seekg(0);

    ItemStruct rec;
    int number = 0;
    int found = 0;
    while (true)
    {
        f.read(reinterpret_cast<char *>(&rec), sizeof(rec));
        if (f.eof())
        {
            break;
        }
        if (f.fail() || f.bad())
        {
            std::cerr << "Ошибка чтения данных.\n";
            break;
        }

        number++;

        bool match;
        if (mode == 1)
        {
            match = std::string(rec.name).find(query) != std::string::npos;
        }
        else
        {
            match = rec.price >= minPrice && rec.price <= maxPrice;
        }

        if (match)
        {
            Item *item = itemFromStruct(rec);
            if (item != nullptr)
            {
                printItem(number, *item);
                delete item;
                found++;
            }
        }
    }
    f.close();

    if (found == 0)
    {
        std::cout << "Ничего не найдено.\n";
    }
}

static void editInFile()
{
    int count = countRecords();
    if (count == 0)
    {
        std::cout << "Файл пуст или ещё не создан.\n";
        return;
    }

    showFile();
    int number = inputNumber("Введите номер записи для редактирования: ", 1, count);

    std::fstream f(FILE_NAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!f.is_open())
    {
        std::cerr << "Ошибка открытия файла!\n";
        return;
    }

    std::streamoff pos = static_cast<std::streamoff>(number - 1) * static_cast<std::streamoff>(sizeof(ItemStruct));

    f.seekg(pos);
    ItemStruct rec;
    f.read(reinterpret_cast<char *>(&rec), sizeof(rec));
    if (f.fail() || f.bad())
    {
        std::cerr << "Ошибка чтения данных.\n";
        f.close();
        return;
    }

    std::cout << "Выбрана запись:\n";
    Item *oldItem = itemFromStruct(rec);
    if (oldItem != nullptr)
    {
        printItem(number, *oldItem);
        delete oldItem;
    }

    std::string newName;
    std::cout << "Новое название (Enter - оставить прежнее): ";
    std::getline(std::cin, newName);
    if (!newName.empty())
    {
        std::strncpy(rec.name, newName.c_str(), sizeof(rec.name) - 1);
        rec.name[sizeof(rec.name) - 1] = '\0';
    }

    double newPrice = inputDouble("Новая цена (0 - оставить прежнюю): ", 0.0);
    if (newPrice > 0.0)
    {
        rec.price = newPrice;
    }

    double newAmount = inputDouble("Новый остаток (-1 - оставить прежний): ", -1.0);
    if (newAmount >= 0.0)
    {
        if (rec.itemType == ItemType::countItem)
        {
            rec.amount = static_cast<int>(newAmount);
        }
        else
        {
            rec.amount = newAmount;
        }
    }

    f.seekp(pos);
    f.write(reinterpret_cast<const char *>(&rec), sizeof(rec));
    if (!f.good())
    {
        std::cerr << "Ошибка записи в файл!\n";
    }
    else
    {
        std::cout << "Запись изменена.\n";
    }
    f.close();
}

static void deleteFromFile()
{
    int count = countRecords();
    if (count == 0)
    {
        std::cout << "Файл пуст или ещё не создан.\n";
        return;
    }

    showFile();
    int number = inputNumber("Введите номер записи для удаления: ", 1, count);

    std::cout << "Удалить запись №" << number << "? (y/n): ";
    char answer;
    std::cin >> answer;
    std::cin.ignore(1000, '\n');
    if (answer != 'y')
    {
        std::cout << "Удаление отменено.\n";
        return;
    }

    std::vector<Item *> items;
    readItemsFromBinary(items, FILE_NAME);

    // если прочитали не всё, файл перезаписывать нельзя - потеряем данные
    if (static_cast<int>(items.size()) != count)
    {
        std::cerr << "Не удалось прочитать все записи. Удаление отменено.\n";
        for (size_t i = 0; i < items.size(); i++)
        {
            delete items[i];
        }
        return;
    }

    delete items[number - 1];
    items.erase(items.begin() + (number - 1));

    saveItemsToBinary(items, FILE_NAME);

    for (size_t i = 0; i < items.size(); i++)
    {
        delete items[i];
    }
    items.clear();

    if (countRecords() == count - 1)
    {
        std::cout << "Запись удалена.\n";
    }
    else
    {
        std::cerr << "Не удалось удалить запись!\n";
    }
}

void editFile()
{
    while (true)
    {
        std::cout << "\n[1] - Добавить данные в файл\n"
                  << "[2] - Удалить данные из файла\n"
                  << "[3] - Редактировать данные в файле\n"
                  << "[4] - Просмотр данных в файле\n"
                  << "[5] - Поиск товара в файле\n"
                  << "[0] - ВЫХОД в главное меню\n";

        switch (inputChoice(0, 5))
        {
        case 1:
        {
            addToFile();
            break;
        }

        case 2:
        {
            deleteFromFile();
            break;
        }

        case 3:
        {
            editInFile();
            break;
        }

        case 4:
        {
            showFile();
            break;
        }

        case 5:
        {
            findInFile();
            break;
        }

        case 0:
        {
            return;
        }
        }
    }
}
