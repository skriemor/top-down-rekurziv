#include <iostream>
#include "nonterminals.h"
#include <vector>

using namespace std;
vector<nonterminals> ruleVector;
vector<string> NonTerminalInput = { "S","A","B" };
vector<string> input = {"S -> A", "S -> AB", "A -> a", "B -> b", "B -> a", "A -> c", "A -> B"};
string inputstring = "bb";

bool evaluate(string jj) {
	return jj == inputstring;
}
void illustrateRules(vector<nonterminals> nv) {
	string ruleList;
	cout<<endl;
	for (auto v : nv) {
		for (auto b : v.getAlters()) {
			ruleList += b + " | ";
		}
		ruleList.erase(ruleList.end() - 3, ruleList.end() - 1);
		cout << v.getSym() << " -> " << ruleList << endl;
		ruleList = "";
	}
}

/*
Itt kezdodhet a megoldas rekurzioval -------------------------------------------------------------------------------------------
Kiegeszitendo: az S->SS tipusu szabalyokhoz kell irnom egy feltetelt,
hogy ne lepje tul a VART stringinput meretet, ezzel elkerulve a vegtelen memoriafoglalast

A --- jelzések közötti algoritmus rekurzióra épül,
a szoftver többi része teljesen moduláris,
felhasználható iterációs megoldásra is
*/

vector<nonterminals>::iterator SS;
string tempstring;
bool solve(string s, int altpointer, int charpointer, vector<string> alts) {
	if(evaluate(s)) return true;
	SS = find_if(ruleVector.begin(), ruleVector.end(), [&](nonterminals& V) {return V.getSym()[0] == s[charpointer]; });
	if (SS != ruleVector.end()) {
		alts = SS->getAlters();

		tempstring = s;
		cout << tempstring << endl;

		tempstring.replace(charpointer, 1, alts[altpointer]);
		if (solve(tempstring, 0, charpointer, {}))return true;


		if (altpointer+1 < alts.size()) if (solve(s, altpointer + 1, charpointer, alts)) return true;


	}
	if (charpointer < s.length()) if (solve(tempstring, 0, charpointer + 1, {}))return true;
	
	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------
int main(){
	
	ruleVector = nonterminals::initRules(NonTerminalInput);
	

	for (auto g = ruleVector.begin(); g != ruleVector.end(); g++){
		cout << g->getSym() << (!(g + 1 == ruleVector.end()) ? " | " : "");
	}


	nonterminals::processRules(ruleVector, input);

	illustrateRules(ruleVector);
	std::cout << (solve("S", 0, 0, {}) ? "Talált" : "Nem talált");

}

