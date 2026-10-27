#include "order.h"

double Order::getItemQuantity(Item *item) const
{
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].getItem() == item)
        {
            return lines[i].getQuantity();
        }
    }
    return 0.0;
}

void Order::addItem(Item *newItem, double quantity)
{
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].getItem() == newItem)
        {
            lines[i].setQuantity(lines[i].getQuantity() + quantity);
            return;
        }
    }
    lines.push_back(OrderLine(newItem, quantity));
}

bool Order::dellItem(Item *itemToDelete)
{
    for (auto it = lines.begin(); it != lines.end(); ++it)
    {
        if (it->getItem() == itemToDelete)
        {
            lines.erase(it);
            return true;
        }
    }
    return false;
}

bool Order::editItem(Item *itemToEdit, double newQuantity)
{
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].getItem() == itemToEdit)
        {
            lines[i].setQuantity(newQuantity);
            return true;
        }
    }
    return false;
}

void Order::showOrder() const
{
    if (lines.empty())
    {
        std::cout << "\nКорзина пуста.\n";
        return;
    }
    receipt.printReceipt(customer, lines);
}

bool Order::confirmOrder()
{
    if (lines.empty())
    {
        return false;
    }

    for (int i = 0; i < lines.size(); i++)
    {
        lines[i].getItem()->decreaseAmount(lines[i].getQuantity());
    }
    receipt.createReceipt();
    return true;
}

void Order::printReceipt() const
{
    receipt.printReceipt(customer, lines);
}

bool Order::saveReceiptToFile(const char *fileName) const
{
    return receipt.saveReceiptToFile(fileName, customer, lines);
}
