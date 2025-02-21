#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <vector>
#include "product.h"

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);
    std::vector<Product*>& getCart();
    void addToCart(Product* p);
    void setCart(const std::vector<Product*>& newCart);

private:
    std::string name_;
    double balance_;
    int type_;
    std::vector<Product*> cart_;
};
#endif
