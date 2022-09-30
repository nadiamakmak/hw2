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
	stringstream stream;
	stream << convToLower(rawWords);
	set<string> keywords;
	string word = "";
	string temp = "";

	while(stream >> temp){ //reading in word by word (stopping at whitespaces)
		word = "";

		for(unsigned int i = 0; i<temp.size(); i++){ //for each character in the word

			if(ispunct(temp[i]) && !(temp[i]=='-')){ //if its punctuation and NOT a hyphen (to account for isbn)
				if(word.size()>=2){ //if the current word is bigger than two characters, add it to keyterms
					keywords.insert(word);
				}
			}

			else{ //if not punctuation and/or is a hyphen, continue reading in the letters
				word = word + temp[i];
			}
		}

		if(word.size()>=2){ //if the final word (at whitespace) is bigger than 2 characters, add it
			keywords.insert(word);
		}

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
