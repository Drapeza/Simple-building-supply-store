#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "items.h"
#include "customer.h"
#include "receipt.h"
#include "orderLine.h"

class Order
{
protected:
    Receipt receipt;
    Customer *customer;
    std::vector<OrderLine> lines;

public:
    Order() : customer(nullptr) {}

    void setCustomer(Customer *newCustomer)
    {
        customer = newCustomer;
    }

    double getItemQuantity(Item *item) const;
    void addItem(Item *newItem, double quantity);
    bool dellItem(Item *itemToDelete);
    bool editItem(Item *itemToEdit, double newQuantity);
    void showOrder() const;
    bool confirmOrder();
    void printReceipt() const;
    bool saveReceiptToFile(const char *fileName) const;

    ~Order() {}
};
