#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <map>
#include "util.h"
#include "movie.h"
#include "product.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating) : Product(category, name, price, qty)
{
  genre_ = genre;
  rating_ = rating;

  keywords_.insert(genre_);
  keywords_.insert(rating_);
  set<string> names = parseStringToWords(name_);
  set<string> genres = parseStringToWords(genre_);
  
  for(set<string>::iterator it = names.begin(); it != names.end(); ++it){
    keywords_.insert(*it);
  }

  for(set<string>::iterator it = genres.begin(); it != genres.end(); ++it){
    keywords_.insert(*it);
  }

}

std::set<std::string> Movie::keywords() const
{
  return keywords_;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
  return false;
}

std::string Movie::displayString() const
{
  string s = name_ + 
  "\nGenre: " + genre_ + " Rating: " + rating_ +
  "\n" + (std::to_string(price_).substr(0,5)) + " " + to_string(qty_) + " left." ;
  return s;
}

void Movie::dump(std::ostream& os) const
{
  Product::dump(os);
  os << genre_ << endl;
  os << rating_ << endl;
}