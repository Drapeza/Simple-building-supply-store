#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include "customer.h"

void Customer::setAge()
{
    int age;
    while (true)
    {
        std::cout << "\nВведите ваш возраст: ";
        std::cin >> age;

        if (std::cin.good() && age >= 18 && age <= 100)
        {
            std::cin.ignore(1000, '\n');
            break;
        }

        std::cin.clear();
        std::cout << "\nУказано невозможное значение возраста. Возраст клиента должен быть в диапазоне от 18 до 100.\n";
        std::cin.ignore(1000, '\n');
    }

    Customer::customerAge = age;
}

void Customer::setNumber()
{
    std::string number;
    while (true)
    {
        std::cout << "\nВведите ваш телефон(375XXXXXXXXX): ";
        std::getline(std::cin, number);
        int size = number.size();

        bool onlyDigits = true;
        for (int i = 0; i < size; i++)
        {
            if (number[i] < '0' || number[i] > '9')
            {
                onlyDigits = false;
            }
        }

        if (std::cin.good() && onlyDigits && size == 12 && number.rfind("375", 0) == 0)
        {
            break;
        }

        std::cin.clear();
        std::cout << "\nУказан несуществующий номер. Повторите ввод.\n";
    }

    Customer::customerNumber = '+' + number;
}