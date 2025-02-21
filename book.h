#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <string>
#include <set>

class Book : public Product {
  public:
    Book(const std::string &name, double price, int qty, const std::string &isbn, const std::string &author);
    virtual ~Book();
    //returns set of keywords to index this product
    virtual std::set<std::string> keywords() const;
    //returns a string to display for this product
    virtual std::string displayString() const;
    //dumps product info in database to string
    virtual void dump(std::ostream &os) const;

  private:
    std::string isbn_;
    std::string author_;
};

#endif