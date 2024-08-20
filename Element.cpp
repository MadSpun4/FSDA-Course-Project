#include "Element.h"
#include <utility>

Element::Element() = default;

Element::Element(string articul, string nameSupplier, string nameProduct, const Date &date) :_articul(std::move(articul)),
_nameSupplier(std::move(nameSupplier)),_nameProduct(std::move(nameProduct)), _date(date){}

std::string Element::getArticul() const{
    return _articul;
}

std::string Element::getNameSupplier() const{
    return _nameSupplier;
}

std::string Element::getNameProduct() const{
    return _nameProduct;
}

Date Element::getDate() const{
    return _date;
}

void Element::setArticul(const std::string &articul) {
    _articul = articul;
}

void Element::setNameSupplier(const std::string &nameSupplier) {
    _nameSupplier = nameSupplier;
}

void Element::setNameProduct(const std::string &nameProduct) {
    _nameProduct = nameProduct;
}

void Element::setDate(const Date &date) {
    _date = date;
}


bool Element::operator<(const Element &element) const{
    if(_articul < element._articul)
        return true;
    if(_articul == element._articul && _date < element._date)
        return true;

    return false;
}

bool Element::operator>(const Element &element) const{
    if(_articul > element._articul)
        return true;
    if(_articul == element._articul && _date > element._date)
        return true;

    return false;
}

bool Element::operator==(const Element &element) const {
    return element._articul == _articul && _date == element._date && element._nameProduct == _nameProduct && element._nameSupplier == _nameSupplier;
}

bool Element::operator!=(const Element &element) const {
    return !(*this == element);
}

ostream & operator<<(ostream& out, const Element &element){
    out << " | " << element.getArticul() << " " << element.getDate().toString() << " " << element.getNameSupplier() << " " << element.getNameProduct() << " |";
    return out;
}
