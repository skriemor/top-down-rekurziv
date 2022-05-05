#include <iostream>
#include <vector>
#include <list>
#include "nonterminals.h"



using namespace std;
vector<nonterminals> ruleVector;
vector<string> NonTerminalInput = { "S","A","B" };
vector<string> input = {"S -> A", "S -> AB", "A -> a","A -> AA","B -> BB" , "S -> ABB", "S -> bba", "S -> SS"};
string inputstring = "bbaa";

bool evaluate(string jj) {
	return jj == inputstring;
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
	if (s.length() > inputstring.length()) return false;
	if (evaluate(s)) {
		cout << s << endl;
		return true; 
	}
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
bool bottom_up(string s, int charpointer, int extenderpointer, int sympointer) {
	bool setter = false;
	string copyOfS = s;
	if (s == "S") return true;
	cout << s <<endl;
	auto parentSyms = nonterminals::ParentSymsOfTerminal(s.substr(charpointer, charpointer + extenderpointer),ruleVector);

	if (parentSyms.size()>sympointer +1 && bottom_up(s, charpointer, extenderpointer, sympointer + 1)) return true;
	//
	
		cout << "[";
		if (parentSyms.size() > 0) for (auto v : parentSyms) cout << v << " ";

		cout << "]" << "Between "<<charpointer <<" and "<< charpointer+extenderpointer << endl;
	
	
	//
	
	if (parentSyms.size() > 0 && sympointer>=0) {
		copyOfS.replace(charpointer, charpointer + extenderpointer, parentSyms[sympointer]);
		setter = true;
	}
	if (copyOfS == "S") return true;
	
	if (charpointer + extenderpointer < copyOfS.length()) {
		if (bottom_up(copyOfS, setter?0:charpointer, setter?0:extenderpointer + 1, -1))return true;
	}
	
	if (charpointer < copyOfS.length()) {
		if (bottom_up(copyOfS, setter?0:charpointer + 1, 0, -1)) return true ;
	}

	return false;
}

//A string megforditasa az indexeles erdekeben




//--------------------------------------------------------------------------------------------------------------------------------
int main(){
	
	ruleVector = nonterminals::initSyms(NonTerminalInput);
	nonterminals::processRules(ruleVector, input);

	for (auto g = ruleVector.begin(); g != ruleVector.end(); g++){
		cout << g->getSym() << (!(g + 1 == ruleVector.end()) ? " | " : "");
	}
	nonterminals::illustrateRules(ruleVector);
	//cout << (solve("S", 0, 0, {}) ? "Talalt" : "Nem talalt");
	cout << bottom_up(inputstring, 0, 0, -1);

}

