#include <sstream>
#include <iomanip>
#include "clothing.h"
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
	Product(category, name, price, qty), size_(size), brand_(brand)
{
}

Clothing::~Clothing(){
}

set<std::string> Clothing::keywords() const{
	set<string> brand1 = parseStringToWords(brand_);
	set<string> name1 = parseStringToWords(name_);
	set<string> kwords = setUnion(brand1, name1);
	return kwords;
}

string Clothing::displayString() const{
	string info;
	stringstream temp;
	temp << price_;
	string price = temp.str();
	temp.clear();
	temp << qty_;
	string quantity = temp.str();

	info = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + price + " " + quantity + " left.\n";

	return info;
}

void Clothing::dump(std::ostream& os) const{
	os << category_ << endl << name_ << endl << price_ << endl << qty_ << endl << size_ << endl << brand_ << endl;
}	
