#include "receipt.h"
int Receipt::orderNumber = 0;

void Receipt::printReceipt(const Customer *customer, const std::vector<OrderLine> &lines) const
{
    if (lines.empty())
    {
        std::cout << "\nÊîðçèíà ïóñòà. ×åê íå ìîæåò áûòü ñôîðìèðîâàí.\n";
        return;
    }

    std::cout << std::endl;
    if (number == 0)
    {
        std::cout << std::setw(30) << std::setfill('=') << "" << " ×ÅÐÍÎÂÈÊ ÇÀÊÀÇÀ " << std::setw(30) << std::setfill('=') << "" << std::endl;
    }
    else
    {
        std::cout << std::setw(30) << std::setfill('=') << "" << " ÊÀÑÑÎÂÛÉ ×ÅÊ #" << number << " " << std::setw(30) << std::setfill('=') << "" << std::endl;
    }
    std::cout << std::setfill(' ');

    if (customer != nullptr)
    {
        std::cout << "Ïîêóïàòåëü: " << customer->getName() << '\n';
        std::cout << "Òåëåôîí: " << customer->getNumber() << '\n';
    }

    std::cout << std::left << std::setw(30) << "Íàèìåíîâàíèå òîâàðà" << " | ";
    std::cout << std::right << std::setw(12) << "Öåíà (ðóá.)" << " | ";
    std::cout << std::right << std::setw(10) << "Êîë-âî" << " | ";
    std::cout << std::right << std::setw(15) << "Ñóììà (ðóá.)" << "|\n";
    std::cout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;

    double totalSum = 0.0;

    for (int i = 0; i < lines.size(); i++)
    {
        std::cout << std::left << std::setw(30) << lines[i].getItem()->getName() << " | ";

        std::cout.setf(std::ios::fixed);
        std::cout.precision(2);
        std::cout << std::right << std::setw(12) << lines[i].getItem()->getPrice() << " | ";
        std::cout.unsetf(std::ios::fixed);
        std::cout.precision(6);

        std::cout << std::right << std::setw(10) << lines[i].getQuantity() << " | ";

        std::cout.setf(std::ios::fixed | std::ios::showpos);
        std::cout.precision(2);
        std::cout << std::right << std::setw(15) << lines[i].getSum() << "|\n";

        std::cout.unsetf(std::ios::fixed | std::ios::showpos);
        std::cout.precision(6);

        totalSum += lines[i].getSum();
    }

    std::cout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;
    std::cout << std::left << std::setw(58) << "ÈÒÎÃÎ Ê ÎÏËÀÒÅ:" << " | ";

    std::cout.setf(std::ios::fixed | std::ios::showpos);
    std::cout.precision(2);
    std::cout << std::right << std::setw(15) << totalSum;
    std::cout.unsetf(std::ios::fixed | std::ios::showpos);
    std::cout.precision(6);

    std::cout << "|\n";
    std::cout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;
}

bool Receipt::saveReceiptToFile(const char *fileName, const Customer *customer, const std::vector<OrderLine> &lines) const
{
    std::ofstream fout(fileName, std::ios::app);
    if (fout.fail())
    {
        return false;
    }

    if (lines.empty())
    {
        return false;
    }

    fout << std::endl;
    if (number == 0)
    {
        fout << std::setw(30) << std::setfill('=') << "" << " ×ÅÐÍÎÂÈÊ ÇÀÊÀÇÀ " << std::setw(30) << std::setfill('=') << "" << std::endl;
    }
    else
    {
        fout << std::setw(30) << std::setfill('=') << "" << " ÊÀÑÑÎÂÛÉ ×ÅÊ #" << number << " " << std::setw(30) << std::setfill('=') << "" << std::endl;
    }
    fout << std::setfill(' ');

    if (customer != nullptr)
    {
        fout << "Ïîêóïàòåëü: " << customer->getName() << '\n';
        fout << "Òåëåôîí: " << customer->getNumber() << '\n';
    }

    fout << std::left << std::setw(30) << "Íàèìåíîâàíèå òîâàðà" << " | ";
    fout << std::right << std::setw(12) << "Öåíà (ðóá.)" << " | ";
    fout << std::right << std::setw(10) << "Êîë-âî" << " | ";
    fout << std::right << std::setw(15) << "Ñóììà (ðóá.)" << "|\n";
    fout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;

    double totalSum = 0.0;

    for (int i = 0; i < lines.size(); i++)
    {
        fout << std::left << std::setw(30) << lines[i].getItem()->getName() << " | ";

        fout.setf(std::ios::fixed);
        fout.precision(2);
        fout << std::right << std::setw(12) << lines[i].getItem()->getPrice() << " | ";
        fout.unsetf(std::ios::fixed);
        fout.precision(6);

        fout << std::right << std::setw(10) << lines[i].getQuantity() << " | ";

        fout.setf(std::ios::fixed | std::ios::showpos);
        fout.precision(2);
        fout << std::right << std::setw(15) << lines[i].getSum() << "|\n";

        fout.unsetf(std::ios::fixed | std::ios::showpos);
        fout.precision(6);

        totalSum += lines[i].getSum();
    }

    fout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;
    fout << std::left << std::setw(58) << "ÈÒÎÃÎ Ê ÎÏËÀÒÅ:" << " | ";

    fout.setf(std::ios::fixed | std::ios::showpos);
    fout.precision(2);
    fout << std::right << std::setw(15) << totalSum;
    fout.unsetf(std::ios::fixed | std::ios::showpos);
    fout.precision(6);

    fout << "|\n";
    fout << std::setw(77) << std::setfill('=') << "" << std::setfill(' ') << std::endl;

    return fout.good();
}
