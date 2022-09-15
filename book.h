#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include "util.h"
#include <sstream>
#include <string>
#include <iostream>

class Book : public Product{
	public:

		Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn);

    ~Book();

		std::set<std::string> keywords() const;

		std::string displayString() const;

		void dump(std::ostream& os) const;

	private:
		std::string author_;
		std::string isbn_;

};
#endif