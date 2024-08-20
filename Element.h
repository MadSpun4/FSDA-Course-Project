#ifndef ELEMENT_H
#define ELEMENT_H
#pragma once
#include "Fields/Date.h"

class Element {
public:
    Element();
    Element(string articul, string nameSupplier, string nameProduct, const Date &date);

    std::string getArticul() const;
    std::string getNameSupplier() const;
    std::string getNameProduct() const;
    Date getDate() const;

    void setArticul(const std::string &articul);
    void setNameSupplier(const std::string &nameSupplier);
    void setNameProduct(const std::string &nameProduct);
    void setDate(const Date &date);

    bool lessKeyHT(const Element &element);

    bool operator < (const Element &element) const;
    bool operator > (const Element &element) const;
    bool operator == (const Element &element) const;
    bool operator != (const Element &element) const;

    friend ostream& operator << (ostream& out, const Element &element);


private:
    std::string _articul;
    std::string _nameSupplier;
    std::string _nameProduct;
    Date _date;
};



#endif //ELEMENT_H
