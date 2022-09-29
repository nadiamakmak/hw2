#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	typename std::set<T>::iterator it = s1.begin();
	std::set<T> intersections;

	while(it != s1.end()){
		if(s2.find(*it)!=s2.end()){
			intersections.insert(*it);
		}

		++it;

	}

	return intersections;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	typename std::set<T>::iterator it = s1.begin();
	std::set<T> unions = s2;

	while(it != s1.end()){
		if(unions.find(*it)==unions.end()){
			unions.insert(*it);
		}

		++it;

	}

	return unions;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
