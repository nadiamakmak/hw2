#include "mydatastore.h"
#include <iostream>
using namespace std;

MyDataStore::MyDataStore(){

}
MyDataStore::~MyDataStore(){
	//deleting store products
	vector<Product*>::iterator productIt;
	for(productIt = allProducts.begin(); productIt < allProducts.end(); ++productIt){
		delete *productIt;
	}

	//deleting users + users' checkout carts
	vector<User*>::iterator userIt;
	for(userIt = allUsers.begin(); userIt < allUsers.end(); ++userIt){
		delete *userIt;
	}

}

void MyDataStore::addProduct(Product* p){
	allProducts.push_back(p);
	set<string> kwords = p->keywords();
	set<string>::iterator kwordsIt = kwords.begin();
	
	while(kwordsIt != kwords.end()){ //for all the keywords of a certain product

		if(keywordProducts.find(*kwordsIt) == keywordProducts.end()){ //if this is a new word
			//create a new set of products that correspond to this word, and add this word (and its corresponding products) to the list of all words
			set<Product*> results;
			results.insert(p);
			keywordProducts.insert(make_pair(*kwordsIt, results));
			++kwordsIt;
		}

		else{ //if this isn't a new word
			//find the word in the list of all words, and then add this product to its results
			(keywordProducts.find(*kwordsIt)->second).insert(p);
			++kwordsIt;
		}

	}

}

void MyDataStore::addUser(User* u){
	allUsers.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	set<Product*> tempResults;
	vector<Product*> results;

	if(terms.empty() == true){ //if nothing is searched, return no products
		return results;
	}

	if(type == 0){ //AND
		set<Product*> andSearch;

		for(unsigned int i=0; i<terms.size(); i++){ //for every searched term
			if(andSearch.empty() == true){ //for the first term, add all the products that correspond to that term 
				andSearch = keywordProducts[terms[i]];
			}
			//make result the intersection of the current keyword's products and the existing products 
			andSearch = setIntersection(keywordProducts[terms[i]], andSearch);
		}
		tempResults = andSearch;
	}

	else if(type == 1){ //OR
		set<Product*> orSearch;

		for(unsigned int i=0; i<terms.size(); i++){ //for every searched term
			orSearch = setUnion(keywordProducts[terms[i]], orSearch); //union function twice (first and empty, second and first)
		}
		tempResults = orSearch;
	}

	set<Product*>::iterator tempsIt = tempResults.begin();
	while(tempsIt!=tempResults.end()){ //put from set into vector (as per function signature)
		results.push_back(*tempsIt);
		++tempsIt;
	}
	cout << endl;
	return results;
}

void MyDataStore::dump(std::ostream& ofile){
	vector<Product*>::iterator product = allProducts.begin();
	vector<User*>::iterator user = allUsers.begin();

	ofile << "<products>" << endl;

	while(product != allProducts.end()){ //go through all products, dumping each one into the given format
		(*product)->dump(ofile);
		++product;
	}
	ofile << "</products>" << endl << "<users>" << endl;

	while(user != allUsers.end()){ //go through all users, dumping each one into the given format
		(*user)->dump(ofile);
		++user;
	}

	ofile << "</users>" << endl;
}

void MyDataStore::addToCart(std::string user, int itemNum, std::vector<Product*> hits){
	//checking to see if the user exists
	bool exist = false;
	for(unsigned int i=0; i<allUsers.size(); i++){ //find the actual user and make that the account
		if(allUsers[i]->getName() == user){
			exist = true;
		}
	}
	if(exist == false){ //if that user doesn't exist, invalid request
		cout << endl << "Invalid request" << endl;
		return;
	}

	if(cart.find(user) != cart.end()){ //valid inputs and user has a cart
		(cart.find(user)->second).push_back(hits[itemNum-1]); //add the item to the product vector representing the user's cart
	}

	else{ //user doesn't already have a cart (so first item to be added?)
		vector<Product*> newCart; //make a new cart, and the item to that cart, and then add a new pair to the map of that user and that cart
		newCart.push_back(hits[itemNum-1]);
		cart.insert(make_pair(user, newCart));
	}

}

void MyDataStore::viewCart(std::string user){
	//checking to see if the user exists
	bool exist = false;
	for(unsigned int i=0; i<allUsers.size(); i++){ //find the actual user
		if(allUsers[i]->getName() == user){
			exist = true;
		}
	}

	if(exist == false){ //if that user doesn't exist, invalid request
		cout << endl << "Invalid username" << endl;
		return;
	}

	else if((cart.find(user)->second.size() == 0) || (cart.find(user) == cart.end())){ //if the cart is empty or nothing has been added yet
		cout << endl << "No items in cart" << endl;
	}

	else if(cart.find(user) != cart.end()){ //if the user exists and the user's cart is not empty 
		vector<Product*> currentCart;
		currentCart = (cart.find(user))->second;
		vector<Product*>::iterator whichProduct = currentCart.begin();

		int index = 1;
		cout << endl;
		while(whichProduct != currentCart.end()){
			cout << index << "." << (*whichProduct)->displayString() << endl <<endl;
			++whichProduct;
			index++;
		}
	}


}

void MyDataStore::buyCart(std::string user){
	//checking to see if the user exists
	bool exist = false;
	for(unsigned int i=0; i<allUsers.size(); i++){
		if(allUsers[i]->getName() == user){
			exist = true;
		}
	}
	if(exist == false){ //if that user doesn't exist, invalid username
		cout << endl << "Invalid username" << endl;
		return;
	}

	map<string, vector<Product*>>::iterator userCartIt = cart.find(user);
	User* account;

	for(unsigned int i=0; i<allUsers.size(); i++){ //find the user (if it exists)
		if(allUsers[i]->getName() == user){
			account = allUsers[i];
		}
	}

	if(cart.find(account->getName()) == cart.end()){ //if the user doesn't have a cart (nothing has been added)
		cout << endl << "No items in cart" << endl;
	}
	
	else{ //cart has stuff and the user exists
		vector<Product*> &usersCart = (userCartIt->second); //PBR the cart so we can erase the stuff as we go
		vector<Product*>::iterator whichProduct = usersCart.begin();
		unsigned int index = 0;

		while(index<usersCart.size()){
			double price = usersCart[index]->getPrice();
			if((account->getBalance() >= price) && (usersCart[index]->getQty())>0){ //user has enough money and there is enough in stock
				account->deductAmount(price); //lower their balance, take one out of stock, remove that item from their cart
				usersCart[index]->subtractQty(1);
				for(unsigned int j=0; j<index; j++){ //gets whichProduct to be the item in the list
					++whichProduct;
				}
				usersCart.erase(whichProduct);
			}
			else{ //either no money or not in stock
				index++; //go on to the next item
			}

		}

	}

}