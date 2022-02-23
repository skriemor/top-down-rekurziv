#include "vector_plus.h"


bool vector_plus::Contains(string& g) {
	return find_if(this->begin(), this->end(), [&](nonterminals& V) {return V.getSym() == g; }) ==this->end() ? false : true;
}
