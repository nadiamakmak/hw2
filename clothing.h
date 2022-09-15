#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include "util.h"
#include <sstream>
#include <string>
#include <iostream>

class Clothing : public Product{
	public:

		Clothing(const std::string category, const std::string name, double price, int qty, std::string brand, std::string size);
    ~Clothing();

		std::set<std::string> keywords() const;

		std::string displayString() const;

		void dump(std::ostream& os) const;

	private:
		std::string size_;
		std::string brand_;

};
#endif