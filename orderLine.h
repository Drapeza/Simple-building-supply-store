#pragma once
#include "items.h"
class OrderLine
{
protected:
    Item *item;
    double quantity;

public:
    OrderLine(Item *item, double quantity) : item(item), quantity(quantity) {}
    Item *getItem() const { return item; }
    double getQuantity() const { return quantity; }
    void setQuantity(double quantity) { this->quantity = quantity; }
    double getSum() const { return item->getPrice() * quantity; }
    ~OrderLine() {}
};
