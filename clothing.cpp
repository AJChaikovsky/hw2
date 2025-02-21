#include "clothing.h"
#include "util.h"
#include <sstream>

Clothing::Clothing(const std::string &name, double price, int qty, const std::string &brand, const std::string &size) : Product("clothing", name, price, qty), brand_(brand), size_(size) {

}

Clothing::~Clothing() {

}

std::set<std::string> Clothing::keywords() const {
  //get keywords from product name
  std::set<std::string> result = parseStringToWords(name_);
  //get keywords from the brand
  std::set<std::string> brandKeywords = parseStringToWords(brand_);
  //combine brand and product name
  for(const std::string &word : brandKeywords){
    result.insert(word);
  }
  return result;
}

std::string Clothing::displayString() const {
  std::stringstream ss;
  ss << name_ << "\n";
  ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
  ss << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Clothing::dump(std::ostream &os) const {
  //dumps data in database format
  os << "clothing" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n";
}