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
	convToLower(rawWords);
	stringstream stream;
	set<string> keywords;
	string word = "";
	string temp = "";
	int charNum = 0;

	while(stream >> temp){ //reading in word by word (stopping at whitespaces)

		while(charNum<(int)temp.size()){ //goes through the entire first "word"
			if(temp[charNum]=='-'){ //if it's a hyphen, add it to the first word and keep going
				word += temp[charNum];
				charNum++;
				continue;
			}

			else if(ispunct(temp[charNum])){ //if there is punctuation (not a hyphen)
				if(word.size()>=2){ //see if what we have so far is greater than 2 characters
					keywords.insert(word); //if yes, add it to keywords
				}
				word = ""; //discard everything before punctuation (either added or not added)
			}

			else{ //if not punctuation, add the character to the word
				word += temp[charNum];
				charNum++;
			}

		}

		if(word.size()>=2){ //if the final word (at whitespace) is bigger than 2 characters, add it
			keywords.insert(word);
		}

		word.clear(); //discard the word to start over

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
