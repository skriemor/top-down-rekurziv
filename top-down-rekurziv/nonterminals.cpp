#include "nonterminals.h"
#include <iterator>


string nonterminals::getSym() {
	return *sym;
}

vector<string> nonterminals::getAlters() {
	return *alters;
}

void nonterminals::addAlter(string Alter) {
	this->alters->push_back(Alter);
}

bool contains(vector<nonterminals>& convec, string s) {
	return find_if(convec.begin(), convec.end(), [&](nonterminals& V) {return V.getSym()==s; })==convec.end()?false:true;

}


vector<nonterminals> nonterminals::initSyms(vector<string> g){
	vector<nonterminals>* tempVec = new vector<nonterminals>();
	
	for (auto it = g.begin(); it != g.end(); it++) {
		if (!contains(*tempVec,*it)) {
			tempVec->push_back(nonterminals(*it));
		}
	}
	//std::cout << tempVec->size() << std::endl;
	
	return *tempVec;
}

void nonterminals::processRules(vector<nonterminals>& rV,vector<string> rules) {
	for (auto it1:rules) {
		for (auto it2 : rV) {
			if (it2.getSym()[0] == it1[0]) {
				it1.erase(0,5);
				it2.addAlter(it1);
				break;
			}
		}
	}
	
}


void nonterminals::illustrateRules(vector<nonterminals> nv) {
	string ruleList;
	cout << endl;
	for (auto v : nv) {
		for (auto b : v.getAlters()) {
			ruleList += b + " | ";
		}
		ruleList.erase(ruleList.end() - 3, ruleList.end() - 1);
		cout << v.getSym() << " -> " << ruleList << endl;
		ruleList = "";
	}
}

bool nonterminals::hasTerminal(string f) {
	auto alties = this->getAlters();
	return find(alties.begin(), alties.end(), f) != alties.end();
}

vector<string> nonterminals::ParentSymsOfTerminal(string f, vector<nonterminals>& rulez) {
	vector<string> SymbolsOfTerminal = vector<string>();
	for (auto s : rulez) if (s.hasTerminal(f)) SymbolsOfTerminal.push_back(s.getSym());
	return SymbolsOfTerminal;
}
