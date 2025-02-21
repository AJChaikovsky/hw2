#include "movie.h"
#include "util.h"
#include <sstream>

Movie::Movie(const std::string &name, double price, int qty, const std::string &genre, const std::string &rating) : Product("movie", name, price, qty), genre_(genre), rating_(rating) {

}

Movie::~Movie() {

}

std::set<std::string> Movie::keywords() const {
  //get keywords from product name and author of book
  std::set<std::string> result = parseStringToWords(name_);
  //get genre as keyword
  result.insert(convToLower(genre_));
  return result;
}

std::string Movie::displayString() const {
 std::stringstream ss;
  ss << name_ << "\n";
  ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
  ss << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Movie::dump(std::ostream &os) const {
  //dumps data in database format
  os << "movie" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n";
}