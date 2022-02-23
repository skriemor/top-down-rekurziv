#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
class nonterminals{
private:
	vector<string>* alters;
	void addAlter(string Alter);
public:
	string* sym;
	static vector<nonterminals>initRules(vector<string> g);
	static void processRules(vector<nonterminals>& g, vector<string> rules);
	nonterminals(string base) {
		sym = new string(base);
		alters = new vector<string>;
	}
	string getSym();
	vector<string> getAlters();
};

