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
  //declare a set to hold the keywords
set<string> keywords;
//convert entire string to lowercase
string lowerStr = convToLower(rawWords);

string word;
//process each character in the lowercase string
for(char c : lowerStr){
  if(isspace(c) || ispunct(c)){
    if(word.size() >= 2){ //add the word if its length is greater than or equal to 2
      keywords.insert(word);
    }
    word.clear();
  } else {
    word.push_back(c);//append character to the current word
  }
}
if(word.size() >= 2){ //after loop, check if there is a remaining word
    keywords.insert(word);
  }
return keywords;

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
