#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <string>
#include <set>

class Movie : public Product {
  public:
    Movie(const std::string &name, double price, int qty, const std::string &genre, const std::string &rating);
    virtual ~Movie();
    //returns set of keywords to index this product
    virtual std::set<std::string> keywords() const;
    //returns a string to display for this product
    virtual std::string displayString() const;
    //dumps product info in database to stream
    virtual void dump(std::ostream &os) const;

  private:
    std::string genre_;
    std::string rating_;
};

#endif