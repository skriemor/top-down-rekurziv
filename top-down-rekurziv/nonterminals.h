#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
class nonterminals{
private:
	vector<string>* alters;
	void addAlter(string Alter);
	bool hasTerminal(string f);

public:
	string* sym;
	static vector<nonterminals>initSyms(vector<string> g);
	static void processRules(vector<nonterminals>& g, vector<string> rules);
	static void illustrateRules(vector<nonterminals> nv);
	nonterminals(string base) {
		sym = new string(base);
		alters = new vector<string>;
	}
	string getSym();
	vector<string> getAlters();
	static vector<string> ParentSymsOfTerminal(string s, vector<nonterminals>& rulez);
};

