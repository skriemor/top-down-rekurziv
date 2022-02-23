#include <vector>
#include <iostream>
#include "nonterminals.h"

using namespace std;

class vector_plus :public vector<nonterminals> {
public:
	bool Contains(string& g);
};