#include "WalkSAT.h"
#include <optional>
#include <iostream>
#include <fstream>

uniform_real_distribution<> dis(0.0, 1.0); 

optional<Valuation> WalkSAT(NormalForm& SAT_instance, int condition, double probability){

	Valuation valuation = generate_random_valuation(SAT_instance);
	Variable var_to_flip;

	while(condition > 0){
	
		if(is_satisfiable(SAT_instance, valuation)){
			return valuation;
		}
		
		vector<Clause> unsatisfied_clauses = find_unsatisfied_clauses(SAT_instance, valuation);
		
		Clause unsat_clause = choose_random_unsatisfied_clause(unsatisfied_clauses);
		
		map<Variable, int> breakcounts;
		for(auto literal : unsat_clause){
			int var = abs(literal);
			breakcounts[var] = calculate_breakcount(SAT_instance, var, valuation);
		}
		
		if(zero_breakcount_variables(breakcounts)){
			var_to_flip = choose_random_zero_breakcount_variable__to_flip(breakcounts);
		} else{
			double p = dis(gen);
			
			if(p < probability){
				var_to_flip = choose_random_variable_to_flip(unsat_clause);
			} else{
				auto it = min_element(breakcounts.begin(), breakcounts.end(), [](const auto& p1, const auto& p2) { return p1.second < p2.second;});
    				var_to_flip = it->first;	
			}
		}
		
		valuation[var_to_flip] = !valuation[var_to_flip];
		condition--;
	}
	
	return nullopt;
}

NormalForm parse(std::istream& input) {

    string buffer;
    do {
        input >> buffer;
        if(buffer == "c")
            input.ignore(1000, '\n');
    } while(buffer != "p");

    input >> buffer;

    int atomCount;
    int clauseCount;
    input >> atomCount >> clauseCount;

    NormalForm res;
    for(int i = 0; i < clauseCount; i++) {
        Clause clause;
        Literal literal;
        input >> literal;
        while(literal != 0) {
            clause.push_back(literal);
            input >> literal;
        }
        res.push_back(clause);
    }
    return res;
}

int main(int argc, char* argv[]){

	if(argc == 1){
		cout << "Unesite naziv fajla."<< endl;
		return 1;
	}
	
	string filename = argv[1];
        ifstream inputFile(filename);

        NormalForm formula = parse(inputFile);
	
	double probability = 0.4;
	auto res = WalkSAT(formula, 10, probability);
	
	if(res){
		cout << "SAT" << endl;
		
		Valuation val = res.value();
		for(auto pair : val){
			cout << pair.first << ": " << pair.second << endl;
		}
		 
	} else{
		cout << "Unknown" << endl;
	}

	return 0;
}
