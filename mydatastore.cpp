#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <set>
#include "mydatastore.h"
#include "product.h"
#include "util.h"
#include "user.h"

using namespace std;

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
  for(size_t i = 0 ; i < users_.size(); i++){
    delete users_[i];
  }

  for(size_t i = 0 ; i < products_.size(); i++){
    delete products_[i];
  }
  
}

void MyDataStore::addProduct(Product* p)
{
  // store product locally
  products_.push_back(p);
  
  std::set<std::string> prodKeywords = p->keywords();

  for(set<string>::iterator it = prodKeywords.begin(); it != prodKeywords.end(); ++it){
    keywordsToProducts_[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u)
{
  users_.push_back(u);
  // adding user to cart map
  vector<Product*> cart;
  usersToCart_.insert({u, cart});
}

/**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
  // cout << "search function" << endl;
  vector<Product*> common;
  string firstTerm = terms[0];
  // set<string> searching = {convToLower(firstTerm)};
  set<Product*> result = keywordsToProducts_[firstTerm];

  // case for if there is only one term (no AND or OR)
  if(terms.size() == 1){
    for(set<Product*>::iterator it = result.begin(); it != result.end(); ++it){
      common.push_back(*it);
    }
    }else{
    if(type == 1){
      for(size_t i = 1; i < terms.size(); i++){
        result = setUnion(result, keywordsToProducts_[terms[i]]);
      }
      }else if(type == 0){
        for(size_t i = 1; i < terms.size(); i++){
          result = setIntersection(result, keywordsToProducts_[terms[i]]);
        }
      }
    }

  for(set<Product*>::iterator it = result.begin(); it != result.end(); ++it){
    common.push_back(*it);
  }
  return common;
}

/**
* Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile)
{
  ofile << "<products>" << endl;
  for(size_t i = 0; i < products_.size(); i++){
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;

  ofile << "<users>" << endl;
  for(size_t i = 0; i < users_.size(); i++){
    users_[i]->dump(ofile);
  }
  ofile << "</users>" << endl;
}

User* MyDataStore::getUserFromUsername(string username)
{
  for(size_t i = 0; i < users_.size(); i++){
    if(users_[i]->getName() == username){
      return users_[i];
    }
  }
  return NULL;
}

void MyDataStore::add_to_cart(std::string username, Product* p)
{
  User* selectedUser = getUserFromUsername(username);

  if(selectedUser == NULL){
    cout << "Invalid request" << endl;
    return;
  }

  if(usersToCart_.find(selectedUser) == usersToCart_.end()){
    vector<Product*> currentCart = usersToCart_[selectedUser];
    currentCart.push_back(p);
    usersToCart_[selectedUser] = currentCart;
  }else{
    usersToCart_.find(selectedUser)->second.push_back(p);
  }
}

void MyDataStore::view_cart(std::string username)
{
  User* selectedUser = getUserFromUsername(username);

  if(selectedUser == NULL){
    cout << "Invalid username" << endl;
    return;
  }

  vector<Product*> cart = usersToCart_[selectedUser];

  for(size_t i = 0; i < cart.size(); i++){
    cout << "Item " << i+1 << endl;
    cout << cart[i]->displayString() << endl;
    cout << endl;
  }
}

void MyDataStore::buy_cart(string username)
{
  User* selectedUser = getUserFromUsername(username);

  if(selectedUser == NULL){
    cout << "Invalid username" << endl;
    return;
  }

  if(usersToCart_.find(selectedUser) == usersToCart_.end()){
    cout << "Invalid Request" << endl;
    return;
  }

  vector<Product*> cart = usersToCart_[selectedUser];
  
  for(size_t i = 0; i < cart.size(); i++){
    double prodPrice = cart[i]->getPrice();
    // cout << "enters buycart for loop" << endl;
    if(cart[i]->getQty() != 0 && selectedUser->getBalance() >= prodPrice){
      cart[i]->subtractQty(1);
      selectedUser->deductAmount(prodPrice);
      cart.erase(cart.begin()+i);
      i--;
    }
  }
  usersToCart_[selectedUser] = cart;
}
