#ifndef WALKSAT_H
#define WALKSAT_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include <random>

using namespace std;

using Variable = int;
using Literal = int;

using Clause = vector<Literal>;
using NormalForm = vector<Clause>;

using Valuation = map<Variable, bool>;

random_device rd;              
mt19937 gen(rd());   

set<Variable> getVariables(NormalForm& SAT_instance){

	set<Variable> variables;
	
	for(const auto& clause : SAT_instance){
		for(auto literal : clause){
			if(variables.find(abs(literal)) == variables.end()){
				variables.insert(abs(literal));
			}
		}
	}
	
	return variables;

}

Valuation generate_random_valuation(NormalForm& SAT_instance){
	
	set<Variable> variables = getVariables(SAT_instance);
	uniform_int_distribution<> dis(0, 1);
	
	Valuation valuation;

	for(const auto& variable : variables){	
		int p = dis(gen);
		valuation[variable] = p;
	}
	
	return valuation;
}

bool is_satisfiable(NormalForm& SAT_instance, Valuation& valuation){

	bool formula = true;
	for(const auto& clause : SAT_instance){
		
		bool clause_value = false;
		for(auto literal : clause){
			if(valuation[abs(literal)] == (literal > 0)){
				clause_value = true;
				break;
			}
		}
		
		if(!clause_value){
			return false;
		}
	}
	
	return true;
	
}

vector<Clause> find_unsatisfied_clauses(NormalForm& SAT_instance, Valuation& valuation){

	vector<Clause> unsat_clauses;

	for(const auto& clause : SAT_instance){
	
		bool clause_value = false;
		for(auto literal : clause){
			if(valuation[abs(literal)] == (literal > 0)){
				clause_value = true;
				break;
			}
		}
		
		if(!clause_value){
			unsat_clauses.push_back(clause);
		}
	}


	return unsat_clauses;
}

Clause choose_random_unsatisfied_clause(vector<Clause>& unsatisfied_clauses){
	
	int array_size = unsatisfied_clauses.size();
	
	uniform_int_distribution<> dis(0, array_size - 1);
	int p = dis(gen);
	
	return unsatisfied_clauses[p];
	
}

int calculate_breakcount(NormalForm& SAT_instance, Variable var, Valuation& valuation){
	
	valuation[var] = !valuation[var];
	int count = 0;
	
	for(const auto& clause : SAT_instance){
		bool clause_value = false;
		for(auto literal : clause){
			if(valuation[abs(literal)] == (literal > 0)){
				clause_value = true;
				break;
			}
		}
		
		if(!clause_value){
			count++;
		}
	}
	
	valuation[var] = !valuation[var];
	
	return count;
}

bool zero_breakcount_variables(map<Variable, int>& breakcounts){

	for(const auto& el : breakcounts){
	 	if(el.second == 0){
			return true;
		}
	}
	
	return false;

}

Variable choose_random_zero_breakcount_variable__to_flip(map<Variable, int>& breakcounts){
		
	vector<Variable> zeros;
	for(const auto& el : breakcounts){
		if(el.second == 0){
			zeros.push_back(el.first);
		}
	}
	
	int array_size = zeros.size();
	
	uniform_int_distribution<> dis(0, array_size - 1);
	int p = dis(gen);

	return zeros[p];
}

Variable choose_random_variable_to_flip(Clause& unsat_clause){
	
	int array_size = unsat_clause.size();
	
	uniform_int_distribution<> dis(0, array_size - 1);
	int p = dis(gen);

	return abs(unsat_clause[p]);
}

#endif
