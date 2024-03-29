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
	stringstream priStream;
	stringstream qtyStream;
	priStream << price_;
	string price = priStream.str();
	qtyStream << qty_;
	string quantity = qtyStream.str();

	info = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + price + " " + quantity + " left.";

	return info;
}

void Movie::dump(std::ostream& os) const{
	os << category_ << endl << name_ << endl << std::fixed << setprecision(2) << price_ << endl << qty_ << endl << genre_ << endl << rating_ << endl;
}	
