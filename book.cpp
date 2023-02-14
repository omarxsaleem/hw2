#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <map>
#include "util.h"
#include "book.h"
#include "product.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) : Product(category, name, price, qty)
{
  isbn_ = isbn;
  author_ = author;
  
  set<string> names = parseStringToWords(name_);
  set<string> authors = parseStringToWords(author_);
  
  for(set<string>::iterator it = names.begin(); it != names.end(); ++it){
    keywords_.insert(*it);
  }

  for(set<string>::iterator it1 = authors.begin(); it1 != authors.end(); ++it1){
    keywords_.insert(*it1);
  }
  keywords_.insert(isbn_);
}

std::set<std::string> Book::keywords() const
{
  return keywords_;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
  return false;
}

string Book::displayString() const
{
  string s = name_ + 
  "\nAuthor: " + author_ + " ISBN: " + isbn_ +
  "\n" + (std::to_string(price_).substr(0,5)) + " " + to_string(qty_) + " left." ;
  return s;
}

void Book::dump(std::ostream& os) const
{
  Product::dump(os);
  os << isbn_ << endl;
  os << author_ << endl;
}