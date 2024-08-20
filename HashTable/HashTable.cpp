#include "HashTable.h"

#include <string>
#include <iomanip>
#include <regex>

HashTable::HashTable(const unsigned size)
{
    table = vector<Key *>(size);
    for (int i = 0; i < size; i++)
        table[i] = new Key(new Tree());
}

Element HashTable::getElement(unsigned index) const {
    if (index < table.size() && table[index]) {
        return table[index]->getTree()->getRoot()->getElement();
    }
    throw std::out_of_range("Index out of range");
}

const std::vector<Key*>& HashTable::getKeys() const {
    return table;
}

bool HashTable::insert(const Element &element)
{
    if (validateData(element.getNameSupplier(), element.getArticul(), element.getNameProduct())) {
        if (const unsigned index = hashFunction(element) % table.size(); table[index]->getStatus() != 1)
        {
            table[index]->getTree()->insert(element);
            table[index]->setStatus(1);
            countElements++;
            return true;
        }
        else
        {
            if (table[index]->getTree()->insert(element)) {
                countElements++;
                return true;
            } else {
                cerr << "Element already exists in the tree." << endl;
                return false;
            }
        }
    } else {
        cerr << "Invalid data, skipping element." << endl;
        return false;
    }

}

bool HashTable::remove(const Element &element)
{

    if (const auto index = hashFunction(element) % table.size(); table[index]->getStatus() == 1)
    {
        if (table[index]->getTree()->remove(element))
        {
            if (table[index]->getTree()->isEmpty())
            {
                table[index]->setStatus(2);
                countElements--;
            }
            return true;
        }
    }
    return false;
}

unsigned HashTable::find(const Element &element) const
{
    if (const auto index = hashFunction(element) % table.size(); table[index]->getStatus() == 1)
    {
        if (table[index]->getTree()->find(element))
            return index;
    }

    return -1;
}

void HashTable::print(std::ostream& os) const {
    for (size_t i = 0; i < table.size(); i++) {
        os << setw(3) << i + 1 << ": ";
        table[i]->getTree()->print(os);
        os << std::endl;
    }
}

void HashTable::print() const {
    print(std::cout);
}

void HashTable::printTree(std::ostream& os, unsigned short index) const {
    table[index]->getTree()->printTree(os);
}

void HashTable::printTree(unsigned short index) const {
    printTree(std::cout, index);
}

bool HashTable::validateData(const std::string &nameSupplier, const std::string &articul, const std::string &nameProduct) {
    regex articulRegex("^[a-z0-9-]+$");
    regex nameSupplierRegex("^[A-Z]+( [A-Za-z0-9]+)*$");
    regex nameProductRegex("^[a-z0-9]+( [a-z0-9]+)*$");

    if (!regex_match(articul, articulRegex)) {
        cerr << "Invalid articul: " << articul << endl;
        return false;
    }

    if (!regex_match(nameSupplier, nameSupplierRegex)) {
        cerr << "Invalid nameSupplier: " << nameSupplier << endl;
        return false;
    }

    if (!regex_match(nameProduct, nameProductRegex)) {
        cerr << "Invalid nameProduct: " << nameProduct << endl;
        return false;
    }

    return true;
}

void HashTable::inputFile(const std::string &path)
{
    if (table.empty())
        return;

    std::ifstream in(path);
    if (in.is_open())
    {
        while (!in.eof())
        {
            Element el;
            std::string company;
            std::string str;

            in >> str;
            if (in.eof()) break; // Проверка, достигнут ли конец файла
            company += str + " ";
            in >> str;
            company += str;
            el.setNameSupplier(company);

            in >> str;
            el.setArticul(str);

            in >> str;
            el.setDate(Date(str));

            std::getline(in, str);
            str.erase(0, 1); // Удаление начального пробела
            el.setNameProduct(str);

            insert(el);
        }
        std::cerr << "Data was inputted!\n";
    }
    else
    {
        std::cout << "Error opening file\n";
    }
    in.close();
}


unsigned HashTable::hashFunction(const Element &element) const
{
    int sum = 0;
    for (const auto &c : element.getArticul())
    {
        sum += c;
    }
    int mod = 10;
    int count = 1;

    while (static_cast<int>(table.size() / mod) != 0)
    {
        mod *= 10;
        count++;
    }

    sum += element.getDate().getDay() + element.getDate().getMonth() + element.getDate().getYear();
    const string str_sum = to_string(sum);

    int result = 0;
    const size_t str_sum_size = str_sum.size();

    for (int i = 0; i < static_cast<int>(str_sum_size / count); i++)
    {
        result += stoi(str_sum.substr(i * count, count));
    }

    result *= result;
    const string result_str = to_string(result);
    return stoi(result_str.substr(result_str.size() / 2, count));
}
