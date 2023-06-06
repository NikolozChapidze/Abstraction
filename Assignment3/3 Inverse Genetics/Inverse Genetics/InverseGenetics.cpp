/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "foreach.h"
#include "simpio.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	//test
	cout<<"Please input protein: ";
	listAllRNAStrandsFor(getLine(""),codons);
	///
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}

Set<string> getAllRNAStandsFor(string protein, Map<char, Set<string> >& codons){
	if(protein.length() == 1){
		return codons[protein[protein.size()-1]]; 
	}
	Set<string> result;
	foreach(string second in getAllRNAStandsFor(protein.substr(1),codons)){
		foreach(string first in codons[protein[0]]){
			result.add(first+second);
		}
	}
	return result;
}

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	Set<string> result = getAllRNAStandsFor(protein,codons);
	foreach(string r in result){
		cout<<r<<endl;
	}
}