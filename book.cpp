#include <sstream>
#include <iomanip>
#include "book.h"
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn) :
	Product(category, name, price, qty), author_(author), isbn_(isbn)
{
}

Book::~Book(){
}

set<std::string> Book::keywords() const{
	set<string> author1 = parseStringToWords(author_);
	set<string> name1 = parseStringToWords(name_);
	set<string> kwords = setUnion(author1, name1);
	kwords.insert(isbn_);
	return kwords;
}

string Book::displayString() const{
	string info;
	stringstream priStream;
	stringstream qtyStream;
	priStream << price_;
	string price = priStream.str();
	qtyStream << qty_;
	string quantity = qtyStream.str();

	info = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + price + " " + quantity + " left.";

	return info;
}

void Book::dump(std::ostream& os) const{
	os << category_ << endl << name_ << endl << price_ << endl << qty_ << endl << isbn_ << endl << author_ << endl;
}	
