#include "mydatastore.h"
#include "util.h"
#include <fstream>
#include <iostream>

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore(){
  //deletes all products and users
  for(size_t i = 0; i < products_.size(); ++i){
    delete products_[i];
  }
  for(size_t i = 0; i < users_.size(); ++i){
    delete users_[i];
  }
}

void MyDataStore::addProduct(Product* p) {
  products_.push_back(p);
  updateKeywordMap(p);
}

void MyDataStore::addUser(User* u) {
  users_.push_back(u);
}

void MyDataStore::updateKeywordMap(Product* p) {
  //get the set of keywords for this product
  std::set<std::string> keys = p->keywords();
  //for each keyword, insert the product into the mapping
  for(std::set<std::string>::iterator it = keys.begin(); it != keys.end(); ++it) {
    //convert keyword to lowercase
    std::string key = *it;
    key = convToLower(key);
    keywordToProducts_[key].insert(p);
  }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  std::set<Product*> finalSet;

  //if no search terms, return an empty result
  if(terms.empty()) {
    return std::vector<Product*>();
  }

  //Vector of sets to hold the results for each term
  std::vector<std::set<Product*>> sets;
  for(size_t i = 0; i < terms.size(); i++) {
    std::string term = convToLower(terms[i]);
    //looks up the term in the keyword mapping
    if(keywordToProducts_.find(term) != keywordToProducts_.end()) {
      sets.push_back(keywordToProducts_[term]);
    } else {
      //if the term is not found, using intersection, return empty
      if(type == 0) {
        return std::vector<Product*>();
      }
    }
  }
  if(sets.empty()) {
    //none of the terms were found
    return std::vector<Product*>();
  }

  //combine the sets based on search type
  if(type == 0) { //intersection of all sets
    finalSet = sets[0];
    for(size_t i = 1; i < sets.size(); i++) {
      finalSet = setIntersection(finalSet, sets[i]);
    }
  } else { //union of all sets
    finalSet = sets[0];
    for(size_t i = 1; i < sets.size(); i++){
      finalSet = setUnion(finalSet, sets[i]);
    }
  }

  //convert the resulting set into a vector
  std::vector<Product*> results(finalSet.begin(), finalSet.end());
  return results;
}

void MyDataStore::dump(std::ostream& ofile) {
  ofile << "<products>\n";
  for(size_t i = 0; i < products_.size(); ++i){
    products_[i]->dump(ofile);
  }
  ofile << "</products>\n";
  ofile << "<users>\n";
  for(size_t i = 0; i < users_.size(); ++i){
    users_[i]->dump(ofile);
  }
  ofile << "</users>";
}

//cart functions
  //add product from hits vector at position hitIndex to the user's cart.
  void MyDataStore::addToCart(const std::string& username, int hitIndex, const std::vector<Product*>& hits) {
    User* targetUser = 0;
    std::string userLower = convToLower(username);
    for(size_t i = 0; i < users_.size(); ++i) {
      if(convToLower(users_[i] -> getName()) == userLower) {
        targetUser = users_[i];
        break;
      }
    }
    if(targetUser == 0) {
      std::cout << "Invalid request" << std::endl;
      return;
    }    
    if(hitIndex < 1 || hitIndex > static_cast<int>(hits.size())) {
      std::cout << "Invalid request" << std::endl;
      std::fflush(stdout);
      return;
    }
    targetUser->addToCart(hits[hitIndex - 1]);
    std::cout << "Product added to cart." << std::endl;
  }

//View the cart for a user: list each item with an ascending index.
void MyDataStore::viewCart(const std::string& username) {
  User* targetUser = 0;
  std::string userLower = convToLower(username);
  for(size_t i = 0; i < users_.size(); ++i) {
    if(convToLower(users_[i]->getName()) == userLower) {
      targetUser = users_[i];
      break;
    }
  }
  if(targetUser == 0) {
    std::cout << "Invalid username" << std::endl;
    return;
  }
  std::vector<Product*>& cart = targetUser->getCart();
  if(cart.empty()) {
    std::cout << "Cart is empty." << std::endl;
    return;
  }
  for(size_t i = 0; i < cart.size(); i++) {
    std::cout << "Item " << (i + 1) << "\n" << cart[i]->displayString() << "\n\n";
}
}

//process the purchase of items in a user's cart
//remove from cart and reduce qty by 1 if purchased
void MyDataStore::buyCart(const std::string& username) {
  User* targetUser = 0;
  std::string userLower = convToLower(username);
  for(size_t i = 0; i < users_.size(); ++i) {
    if(convToLower(users_[i]->getName()) == userLower) {
      targetUser = users_[i];
      break;
    }
  }
  if(targetUser == 0) {
    std::cout << "Invalid username" << std::endl;
    return;
  }
  std::vector<Product*>& cart = targetUser ->getCart();
  std::vector<Product*> newCart; //to store items that were not purchased
  for(size_t i = 0; i < cart.size(); ++i){
    Product* prod = cart[i];
    double price = prod->getPrice();
    int qty = prod->getQty();
    if(qty > 0 && targetUser->getBalance() >= price) {
      //purchase reduces quantity and deducts from user's balance
      prod->subtractQty(1);
      targetUser->deductAmount(price);
    }else {
      newCart.push_back(prod);
    }
  }
  //replace the user's cart with the items that were not purchased
  targetUser->setCart(newCart);
}