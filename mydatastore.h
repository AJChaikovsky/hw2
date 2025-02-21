#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <map>

class MyDataStore : public DataStore {
  public:
  MyDataStore();
  virtual ~MyDataStore();

  //adds a product to the store
  virtual void addProduct(Product* p);

  //adds a user to the store
  virtual void addUser(User* u);

  //performs a search for products using the given keywords.
  //type 0 (intersection) and type 1 (union)
  virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

  //dumps the current database to the given ostream
  virtual void dump(std::ostream& ofile);

  //cart functions
  void addToCart(const std::string& username, int hitIndex, const std::vector<Product*>& hits);
  void viewCart(const std::string& username);
  void buyCart(const std::string& username);

  private:
  //stores products and users
  std::vector<Product*> products_;
  std::vector<User*> users_;
  //mapping from keyword to the set of products containing that keyword
  std::map<std::string, std::set<Product*>> keywordToProducts_;

  //helper function to update the keyword mapping for a product
  void updateKeywordMap(Product* p);
};

#endif