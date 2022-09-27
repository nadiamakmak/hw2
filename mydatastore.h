#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "datastore.h"
#include "product.h"
#include "review.h"
#include "user.h"
#include "util.h"

class MyDataStore : public DataStore {
	public:
		MyDataStore();
		~MyDataStore();

		//virtual datastore functions
		void addProduct(Product* p);
		void addUser(User* u);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);

		//
		void addToCart(std::string user, int itemNum, std::vector<Product*> hits);
		void viewCart(std::string user);
	private:
		std::vector<Product*> allProducts;
		std::vector<User*> allUsers;
		std::map<std::string, std::set<Product*>> keywordProducts; //a map of different words and their corresponding products
		std::map<std::string, std::vector<Product*>> cart; //map of different users and their personal carts
}