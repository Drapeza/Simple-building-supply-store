#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

class Customer
{
    std::string customerName;
    int customerAge;
    std::string customerNumber;

public:
    Customer(const char *name, int age = 18, const char *number = "") : customerName(name), customerAge(age), customerNumber(number) {}
    std::string getName() const { return customerName; }
    int getAge() const { return customerAge; }
    std::string getNumber() const { return customerNumber; }
    void setAge();
    void setName(std::string name)
    {
        this->customerName = name;
    }
    void setNumber();
    ~Customer() {}
};
