#include <sstream>
#include <iomanip>
#include "movie.h"
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
	Product(category, name, price, qty), genre_(genre), rating_(rating)
{
}

Movie::~Movie(){
}

set<std::string> Movie::keywords() const{
	set<string> genre1 = parseStringToWords(genre_);
	set<string> name1 = parseStringToWords(name_);
	set<string> kwords = setUnion(genre1, name1);
	return kwords;
}

string Movie::displayString() const{
	string info;
	stringstream temp;
	temp << price_;
	string price = temp.str();
	temp.clear();
	temp << qty_;
	string quantity = temp.str();

	info = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + price + " " + quantity + " left.\n";

	return info;
}

void Movie::dump(std::ostream& os) const{
	os << category_ << endl << name_ << endl << price_ << endl << qty_ << endl << genre_ << endl << rating_ << endl;
}	
