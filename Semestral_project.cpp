#include <stdio.h>
#include <iostream>
#include "Btree.h"

using namespace std;

int main()
{
	// Tvorba prazdneho B-stromu
	Btree* MujStrom = new Btree(6);
	// Vkladani klicu
	MujStrom->insertion(55);
	std::cout << "\nStav stromu\n\n";
	MujStrom->insertion(27);
	std::cout << "\nStav stromu\n\n";
	MujStrom->insertion(1);
	std::cout << "\nStav stromu\n\n";
	MujStrom->insertion(67);
	std::cout << "\nStav stromu\n\n";
	MujStrom->insertion(55);
	std::cout << "\nStav stromu\n\n";
	// Hledani klice
	MujStrom->searching(57, MujStrom->getRoot());
	std::cout << "\nHledani stromu\n\n";
	// Pocet klicu
	MujStrom->numofkeys(MujStrom->getRoot());
	std::cout << "\nPocet klicu\n\n";

	// Odtraneni klicu
	MujStrom->deletion(55, MujStrom->getRoot());
	std::cout << "\nStav stromu\n\n";
	MujStrom->deletion(27, MujStrom->getRoot());
	std::cout << "\nStav stromu\n\n";
	MujStrom->deletion(420, MujStrom->getRoot());
	std::cout << "\nStav stromu\n\n";
	MujStrom->deletion(67, MujStrom->getRoot());
	std::cout << "\nStav stromu\n\n";

	MujStrom->numofkeys(MujStrom->getRoot());
	std::cout << "\nPocet klicu\n\n";
	// Vypis stromu
	MujStrom->traversal(MujStrom->getRoot());

	



	return 0;
}

