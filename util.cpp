#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  set <string> parsedWords;

  for(int i = 0; i < rawWords.length(); i++){
    if((int(rawWords[i]) > 31 && int(rawWords[i]) < 48) || (int(rawWords[i]) > 57 && int(rawWords[i]) < 65) || (int(rawWords[i]) > 90 && int(rawWords[i]) < 97) || (int(rawWords[i]) > 123 && int(rawWords[i]) < 127)){
      rawWords[i] = ' ';
    }
  }

  stringstream strstrm(rawWords);
  string word;
  while(strstrm >> word){
    if(word.length() >= 2){
      parsedWords.insert(convToLower(word));
    }
  }
//   for(set<string>::iterator it=parsedWords.begin(); it != parsedWords.end(); ++it){
//     cout << "Word: " << *it << endl;
// }
  return parsedWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
