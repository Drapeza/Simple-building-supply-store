#include <iostream>
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

int inputChoice(int minValue, int maxValue)
{
    int choice;
    while (true)
    {
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        if (std::cin.good() && choice <= maxValue && choice >= minValue)
        {
            std::cin.ignore(1000, '\n');
            return choice;
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

void makeOrder(Catalog &newCatalog)

{
    Customer newCustomer("None", 18, "+375000000000");
    std::string customerName;
    while (true)
    {
        std::cout << "Введите имя покупателя: ";
        std::getline(std::cin, customerName);

        if (std::cin.good() && !customerName.empty())
        {
            break;
        }

        std::cin.clear();
        std::cout << "Имя не может быть пустым.\n";
    }
    newCustomer.setName(customerName);
    newCustomer.setAge();
    newCustomer.setNumber();

    Order newOrder;
    newOrder.setCustomer(&newCustomer);

    while (true)
    {
        newCatalog.showCatalog();
        std::cout << "[1] - Добавить товар в корзину\n"
                  << "[2] - Удалить товар из корзины\n"
                  << "[3] - Просмотреть заказ\n"
                  << "[4] - Совершить заказ\n"
                  << "[5] - Изменить количество товара в корзине\n"
                  << "[0] - Отменить заказ\n";

        int choiceOrder = inputChoice(0, 5);

        switch (choiceOrder)
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
                double available = findItem->getAmount() - newOrder.getItemQuantity(findItem);
                if (available <= 0)
                {
                    std::cout << "Весь остаток этого товара уже лежит в вашей корзине.\n";
                }
                else
                {
                    double quantity = findItem->inputAmount(available);
                    newOrder.addItem(findItem, quantity);
                    std::cout << "Товар добавлен в корзину!\n";
                }
            }
            break;
        }

        case 2:
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
                if (newOrder.dellItem(findItem))
                {
                    std::cout << "Товар успешно убран из заказа!\n";
                }
                else
                {
                    std::cout << "Этот товар не был добавлен в ваш заказ.\n";
                }
            }
            break;
        }

        case 3:
        {
            newOrder.showOrder();
            break;
        }

        case 4:
        {
            if (newOrder.confirmOrder())
            {
                newOrder.printReceipt();
                if (newOrder.saveReceiptToFile("receipts.txt"))
                {
                    std::cout << "Чек сохранен в файл receipts.txt\n";
                }
                else
                {
                    std::cout << "Не удалось сохранить чек в файл!\n";
                }
                return;
            }
            std::cout << "Корзина пуста. Заказ оформить нельзя.\n";
            break;
        }

        case 5:
        {
            std::cout << "Введите название товара: ";
            std::string name;
            std::getline(std::cin, name);

            Item *findItem = newCatalog.findItem(name);
            if (findItem == nullptr)
            {
                std::cout << "Такого товара нет.\n";
            }
            else if (newOrder.getItemQuantity(findItem) == 0.0)
            {
                std::cout << "Этого товара нет в вашем заказе.\n";
            }
            else
            {
                double quantity = findItem->inputAmount(findItem->getAmount());
                newOrder.editItem(findItem, quantity);
                std::cout << "Количество изменено!\n";
            }
            break;
        }

        case 0:
        {
            std::cout << "Заказ отменен.\n";
            return;
        }
        }
    }
}
