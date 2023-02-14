#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <map>
#include "util.h"
#include "clothing.h"
#include "product.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, string size, string brand) : Product(category, name, price, qty)
{
  size_ = size;
  brand_ = brand;
  
  keywords_.insert(size_);
  set<string> names = parseStringToWords(name_);
  set<string> brands = parseStringToWords(brand_);
  
  for(set<string>::iterator it = names.begin(); it != names.end(); ++it){
    keywords_.insert(*it);
  }

  for(set<string>::iterator it1 = brands.begin(); it1 != brands.end(); ++it1){
    keywords_.insert(*it1);
  }

}

std::set<std::string> Clothing::keywords() const
{
  return keywords_;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
  return false;
}

std::string Clothing::displayString() const
{
  string s = name_ + 
  "\nSize: " + size_ + " Brand: " + brand_ +
  "\n" + (std::to_string(price_).substr(0,5)) + " " + to_string(qty_) + " left." ;
  return s;
}

void Clothing::dump(std::ostream& os) const
{
  Product::dump(os);
  os << size_ << endl;
  os << brand_ << endl;
}