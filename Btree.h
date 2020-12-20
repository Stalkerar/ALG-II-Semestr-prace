#include <stdio.h>
#include <iostream>

using namespace std;



/// Popis tridy B-strom
class Btree
{
protected:
	/// Pocitadlo klicu B-stromu
	int count;
	/// Rad stromu
	int Max;
	/// Minimalmi pocet potomku 
	int Min;
	/// Pole hodnot pro uzel
	int* value;
	/// Pole potomku uzle
	Btree** link;
	/// Koren B-stromu
	Btree* root;
public:
	/// Konstruktor B-stromu, pro inicializaci prazdneho stromu
	/// @param _Max Tento paramater predstavuje rad vytvoreneho stromu
	Btree(int _Max)
	{
		Max = _Max;
		Min = _Max / 2;
		count = 0;
		value = new int[_Max];
		link = new Btree * [_Max + 1];
		root = NULL;
	}
	~Btree()
	{
		free(value);
		free(link);
	}
	/// Metoda pro vraceni korene B-stromu
	/// @return Koren B-stromu
	Btree* getRoot();
	/// Metoda pro inicializaci uzle
	/// @param val Klic uzlu, ktery se ma vlozit
	/// @param child Odkaz na navazujici uzel
	/// @return Novy uzel
	Btree* initNode(int val, Btree* child);
	///Metoda pro nastaveni hodnoty uzle na spravnem miste
	///@param val Klic uzlu, ktery se ma vlozit
	///@param pos Pozice uzlu v B-strome
	///@param node Spravovany uzel
	///@param child Nasledujici uzel v B-strome
	void setNode(int val, int pos, Btree* node, Btree* child);
	///Metoda pro rozdeleni uzle
	///@param val Klic uzlu, ktery se ma vlozit
	///@param pval Buffer pro klic uzlu
	///@param pos Pozice uzlu
	///@param node Spracovavany uzel
	///@param child Potomek spracovavaneho uzlu
	///@param newNode Ukazatel pro vytvoreni noveho uzlu
	void splitNode(int val, int* pval, int pos, Btree* node, Btree* child, Btree** newNode);
	///Metoda pro vlozeni hodnoty do uzle
	///@param val Klic uzlu, ktery se ma vlozit
	///@param pval Buffer pro klic uzlu
	///@param node Spracovavany uzel
	///@param child Potomci spracovavaneho uzlu
	int valueNode(int val, int* pval, Btree* node, Btree** child);
	///Metoda pro vlozeni hodnoty a vypsani soucasneho stavu B-stromu
	///@param val Klic uzlu, ktery se ma vlozit
	void insertion(int val);
	///Metoda pro kopirovani nasledujiciho uzle pro mazani
	///@param myNode Spracovavany uzel
	///@param pos Pozice spracovavaneho uzlu
	void copySuccessor(Btree* myNode, int pos);
	///Metoda pro odstraneni hodnoty z vybraneho uzle a posunuti pozic uzlu
	///@param myNode Spracovavny uzel
	///@param pos Pozice spracovavaneho uzlu
	void removeVal(Btree* myNode, int pos);
	///Metoda pro posunuti hodnot z rodice do praveho potomka
	///@param myNode Spracovavny uzel
	///@param pos Pozice spracovavaneho uzlu
	void shiftRight(Btree* myNode, int pos);
	///Metoda pro posunuti hodnot z rodice do levého potomka
	///@param myNode Spracovavny uzel
	///@param pos Pozice spracovavaneho uzlu
	void shiftLeft(Btree* myNode, int pos);
	///Metoda pro spojeni uzlu
	///@param myNode Spracovavny uzel
	///@param pos Pozice spracovavaneho uzlu
	void mergeNodes(Btree* myNode, int pos);
	///Metoda pro setrizeni uzle v ramci stromu
	///@param myNode Spracovavny uzel
	///@param pos Pozice spracovavaneho uzlu
	void adjustNode(Btree* myNode, int pos);
	///Metoda pro vymazani hodnoty v uzlu
	///@param val Klic, ktery se ma vymazat
	///@parma myNode Spracovavany uzel
	int delValFromNode(int val, Btree* myNode);
	///Metoda pro odstraneni klice a vypsani stavu B-stromu
	///@param val Klic, ktery se ma vymazat
	///@parma myNode Spracovavany uzel
	void deletion(int val, Btree* myNode);
	///Metoda pro vyhledani zadane hodnoty v B-stromu
	///@param val Klic, ktery se ma vyhledat
	///@parma myNode Spracovavany uzel
	void searching(int val, Btree* myNode);
	///Metoda pro vraceni poctu klicu v B-stromu
	///@param myNode Spracovavany uzel
	void numofkeys(Btree* myNode);
	///Metoda pro vypis hodnot B-stromu
	///@param myNode Spracovavany uzel
	void traversal(Btree* myNode);
};

	Btree* Btree :: getRoot()
	{
		return root;
	}

	Btree* Btree :: initNode(int val, Btree* child) 
	{
		Btree* newNode = new Btree(Max);
		newNode->value[1] = val;
		newNode->count = 1;
		newNode->link[0] = root;
		newNode->link[1] = child;
		return newNode;
	}

	void Btree :: setNode(int val, int pos, Btree* node, Btree* child) 
	{
		int j = node->count;
		while (j > pos) 
		{
			node->value[j + 1] = node->value[j];
			node->link[j + 1] = node->link[j];
			j--;
		}
		node->value[j + 1] = val;
		node->link[j + 1] = child;
		node->count++;
	}

	void Btree :: splitNode(int val, int* pval, int pos, Btree* node, Btree* child, Btree** newNode) 
	{
		int median, j;
		// Rozhodnuti o pozici uzlu
		if (pos > Min)
		{
			median = Min + 1;
		}
		else
		{
			median = Min;
		}
		// Pripadne vytvoreni noveho uzle
		*newNode = new Btree(Max);
		j = median + 1;
		while (j <= Max) 
		{
			(*newNode)->value[j - median] = node->value[j];
			(*newNode)->link[j - median] = node->link[j];
			j++;
		}
		node->count = median;
		(*newNode)->count = Max - median;

		if (pos <= Min) 
		{
			setNode(val, pos, node, child);
		}
		else 
		{
			setNode(val, pos - median, *newNode, child);
		}
		*pval = node->value[node->count];
		(*newNode)->link[0] = node->link[node->count];
		node->count--;
	}

	int Btree :: valueNode(int val, int* pval, Btree* node, Btree** child) 
	{

		int pos;
		// Overeni zda se jedna o posledni uzel
		if (!node) 
		{
			*pval = val;
			*child = NULL;
			return 1;
		}

		if (val < node->value[1]) 
		{
			pos = 0;
		}
		else 
		{
			// Pruchod polem hodnot aby se nevlozil duplikat
			for (pos = node->count;(val < node->value[pos] && pos > 1); pos--);
			if (val == node->value[pos]) 
			{
				cout << "Duplikaty nejsou povoleny\n";
				return 0;
			}
		}// Overeni pokud je treba rozdelit uzly
		if (valueNode(val, pval, node->link[pos], child)) 
		{
			if (node->count < Max) 
			{
				setNode(*pval, pos, node, *child);
			}
			else 
			{
				splitNode(*pval, pval, pos, node, *child, child);
				return 1;
			}
		}
		return 0;
	}

	void Btree :: insertion(int val)
	{
		int flag, i;
		Btree* child;
		flag = valueNode(val, &i, root, &child);
		// Rozhodnuti pokud se jedna o koren
		if (flag)
		{
			root = initNode(i, child);
		}
		traversal(root);
	}

	void Btree :: copySuccessor(Btree* myNode, int pos) 
	{
		Btree* buffer;
		buffer = myNode->link[pos];

		for (; buffer->link[0] != NULL;)
		{
			buffer = buffer->link[0];
			myNode->value[pos] = buffer->value[1];
		}

	}

	void Btree :: removeVal(Btree* myNode, int pos) 
	{
		int i = pos + 1;
		while (i <= myNode->count) 
		{
			myNode->value[i - 1] = myNode->value[i];
			myNode->link[i - 1] = myNode->link[i];
			i++;
		}
		myNode->count--;
	}

	void Btree :: shiftRight(Btree* myNode, int pos) 
	{
		Btree* x = myNode->link[pos];
		int j = x->count;

		while (j > 0) 
		{
			x->value[j + 1] = x->value[j];
			x->link[j + 1] = x->link[j];
		}
		x->value[1] = myNode->value[pos];
		x->link[1] = x->link[0];
		x->count++;

		x = myNode->link[pos - 1];
		myNode->value[pos] = x->value[x->count];
		myNode->link[pos] = x->link[x->count];
		x->count--;
		return;
	}

	void Btree :: shiftLeft(Btree* myNode, int pos) 
	{
		int j = 1;
		Btree* x = myNode->link[pos - 1];

		x->count++;
		x->value[x->count] = myNode->value[pos];
		x->link[x->count] = myNode->link[pos]->link[0];

		x = myNode->link[pos];
		myNode->value[pos] = x->value[1];
		x->link[0] = x->link[1];
		x->count--;

		while (j <= x->count) 
		{
			x->value[j] = x->value[j + 1];
			x->link[j] = x->link[j + 1];
			j++;
		}
		return;
	}

	void Btree :: mergeNodes(Btree* myNode, int pos) 
	{
		int j = 1;
		Btree* x1 = myNode->link[pos], * x2 = myNode->link[pos - 1];

		x2->count++;
		x2->value[x2->count] = myNode->value[pos];
		x2->link[x2->count] = myNode->link[0];

		while (j <= x1->count) 
		{
			x2->count++;
			x2->value[x2->count] = x1->value[j];
			x2->link[x2->count] = x1->link[j];
			j++;
		}

		j = pos;
		while (j < myNode->count)
		{
			myNode->value[j] = myNode->value[j + 1];
			myNode->link[j] = myNode->link[j + 1];
			j++;
		}
		myNode->count--;
		free(x1);
	}

	void Btree :: adjustNode(Btree* myNode, int pos) 
	{

		if (!pos) 
		{
			if (myNode->link[1]->count > Min)
			{
				shiftLeft(myNode, 1);
			}
			else 
			{
				mergeNodes(myNode, 1);
			}
		}
		else 
		{
			if (myNode->count != pos)
			{
				if (myNode->link[pos - 1]->count > Min) 
				{
					shiftRight(myNode, pos);
				}
				else 
				{
					if (myNode->link[pos + 1]->count > Min) 
					{
						shiftLeft(myNode, pos + 1);
					}
					else 
					{
						mergeNodes(myNode, pos);
					}
				}
			}
			else 
			{
				if (myNode->link[pos - 1]->count > Min)
				{
					shiftRight(myNode, pos);
				}
				else
				{
					mergeNodes(myNode, pos);
				}
			}
		}
	}

	int Btree :: delValFromNode(int val, Btree* myNode) 
	{
		int pos, flag = 0;
		// Kontrola jestli se uzel vubec vyskytuje v pameti
		if (myNode) 
		{
			// Kontrola pozice Klice
			if (val < myNode->value[1]) 
			{
				pos = 0;
				flag = 0;
			}
			else 
			{
				for (pos = myNode->count;
					(val < myNode->value[pos] && pos > 1); pos--);
				if (val == myNode->value[pos]) {
					flag = 1;
				}
				else {
					flag = 0;
				}

				
			}
			if (flag) 
			{
				if (myNode->link[pos - 1]) 
				{
					copySuccessor(myNode, pos);
					flag = delValFromNode(myNode->value[pos], myNode->link[pos]);
					if (flag == 0) 
					{
						cout << "Data nejsou v B-stromu\n";
					}
				}
				else 
				{
					removeVal(myNode, pos);
				}
			}
			else 
			{
				flag = delValFromNode(val, myNode->link[pos]);
			}
			if (myNode->link[pos]) 
			{
				if (myNode->link[pos]->count < Min)
				{
					adjustNode(myNode, pos);
				}
			}
		}
		return flag;
	}

	void Btree :: deletion(int val, Btree* myNode) 
	{
		Btree* tmp;
		if (!delValFromNode(val, myNode)) 
		{
			cout << "Data se nenachazeji v B-Stromu\n";
			return;
		}
		else 
		{
			if (myNode->count == 0) 
			{
				tmp = myNode;
				myNode = myNode->link[0];
				free(tmp);
			}
		}
		root = myNode;
		traversal(root);
		return;
	}

	void Btree :: searching(int val, Btree* myNode) 
	{
		int pos;
		if (!myNode) {
			return;
		}

		if (val < myNode->value[1]) {
			pos = 0;
		}
		else {
			for (pos = myNode->count;
				(val < myNode->value[pos] && pos > 1); (pos)--);
			if (val == myNode->value[pos]) 
			{
				cout << "Data nalezena\n";
				return;
			}
			else
			{
				cout << "Data chybi \n";
				return;
			}
		}
		searching(val, myNode->link[pos]);
		return;
	}

	void Btree :: numofkeys(Btree* myNode)
	{
		cout << myNode->count;
	}

	void Btree :: traversal(Btree* myNode) 
	{
		int i;
		if(myNode)
		{
			for (i = 0; i < myNode->count; i++)
			{
				if (i == 0)
				{
					cout << myNode->value[i + 1] << ' ';
					cout << "\n";
				}
				else
				{
					traversal(myNode->link[i]);
					cout << myNode->value[i + 1] << ' ';
				}
			}
			traversal(myNode->link[i]);
		}
	}


