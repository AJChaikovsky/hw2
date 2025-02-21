#include "book.h"
#include "util.h"
#include <sstream>

Book::Book(const std::string &name, double price, int qty, const std::string &isbn, const std::string &author) : Product("book", name, price, qty), isbn_(isbn), author_(author) {

}

Book::~Book() {

}

std::set<std::string> Book::keywords() const {
  //get keywords from product name and author of book
  std::set<std::string> result = parseStringToWords(name_);
  std::set<std::string> authorKeywords = parseStringToWords(author_);
  //add all keywords from authorKeywords
  for(const std::string &word : authorKeywords){
    result.insert(word);
  }

  //insert ISBN
  result.insert(isbn_);
  return result;
}

std::string Book::displayString() const {
  std::stringstream ss;
  ss << name_ << "\n";
  ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
  ss << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Book::dump(std::ostream &os) const {
  //dumps data in database format
  os << "book" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << "\n";
}