#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "orderLine.h"
#include "customer.h"

class Receipt
{
protected:
    int number;
    static int orderNumber;

public:
    Receipt() : number(0) {}

    void createReceipt()
    {
        orderNumber++;
        number = orderNumber;
    }

    void printReceipt(const Customer *customer, const std::vector<OrderLine> &lines) const;

    bool saveReceiptToFile(const char *fileName, const Customer *customer, const std::vector<OrderLine> &lines) const;

    ~Receipt() {}
};
