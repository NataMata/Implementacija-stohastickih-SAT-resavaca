#include "WalkSAT.h"
#include <optional>
#include <iostream>

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

int main(){

	double probability = 0.4;

	NormalForm formula = {
	    {1, 2, 3}, {-1, -2, 4}, {1, -3, 5}, {-2, 3, -4}, {2, 4, -5},
	    {-1, 3, 5}, {1, -4, -5}, {-3, 4, 5}, {2, -3, -5}, {-1, -2, 3},
	    {1, 4, -5}, {-2, -4, 5}, {3, -4, -5}, {-1, 3, -4}, {2, 3, 4},
	    {1, 5, -2}, {-3, -5, 2}, {4, -1, -3}, {-5, 1, 4}, {2, -4, 6}
	};
	
	if(WalkSAT(formula, 10, probability)){
		cout << "SAT" << endl;
	} else{
		cout << "Unknown" << endl;
	}

	return 0;
}
