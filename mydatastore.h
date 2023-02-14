#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "util.h"
#include "datastore.h"

class MyDataStore : public DataStore {
  public :
    MyDataStore();
    
    virtual ~MyDataStore();
  
    void addProduct(Product* p);

    void addUser(User* u);

    User* getUserFromUsername(std::string username);

    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    void dump(std::ostream& ofile);

    void add_to_cart(std::string username, Product* p);

    void view_cart(std::string username);

    void buy_cart(std::string username);

    std::map<User*, std::vector<Product*>> usersToCart_;

  private : 
    std::vector<User*> users_;
    std::vector<Product*> products_;
    std::map<std::string, std::set<Product*>> keywordsToProducts_;
    
};


#endif

