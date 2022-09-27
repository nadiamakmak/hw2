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
			//make a new set of products that correspond to this word, and add this word (and its corresponding products) to the list of all words
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

	if(terms.empty() == true){ //if nothing is searched, return no products
		return results;
	}

	if(type == 0){ //AND
		set<Product*> and;

		for(unsigned int i=0; i<terms.size(); i++){ //for every searched term
			if(and.empty() == true){ //for the first term, add all the products that correspond to that term 
				and = keywordProducts[terms[i]];
			}
			//make result the intersection of the current keyword's products and the existing products 
			and = setIntersection(keywordProducts[terms[i]], and);
		}
		tempResults = and;
	}

	else if(type == 1){ //OR
		set<Product*> or;

		for(unsigned int i=0; i<terms.size(); i++){ //for every searched term
			if(or.empty() == true){ //for the first term, add all the products that correspond to that term 
				or = keywordProducts[terms[i]];
			}
			//make result the union of the current keyword's products and the existing products 
			or = setUnion(keywordProducts[terms[i]], or);
		}
		tempResults = or;
	}

	vector<Product*> results;
	set<Product*>::iterator tempsIt = tempResults.begin();

	while(tempsIt!=tempResults.end()){
		results.push_back(*tempsIt);
		++tempsIt;
	}

	return results;

}

void MyDataStore::dump(std::ostream& ofile){

}

void MyDataStore::addToCart(std::string user, int itemNum, std::vector<Product*> hits){

	if(cart.find(user) != cart.end()){ //valid inputs and user has a cart
		(cart.find(user)->second).push_back(hits[itemNum-1]); //add the item to the product vector representing the user's cart
	}

	else{ //user doesn't already have a cart (so first item to be added?)
		vector<Product*> newCart; //make a new cart, and the item to that cart, and then add a new pair to the map of that user and that cart
		newCart.push_back(hits[itemNum-1]);
		cart.insert(make_pair(user, newCart));
	}

}

void viewCart(std::string user){
	if(cart.find(user) != cart.end()){ //if the user's cart is not empty
		vector<Product*> currentCart;
		currentCart = (cart.find(user))->second;
		vector<Product*>::iterator whichProduct = cart.begin();

		int index = 1;

		while(whichProduct != cart.end()){
			cout << index << "." << (*whichProduct)->displayString() << endl;
			++whichProduct;
			index++;
		}
		
	}
}