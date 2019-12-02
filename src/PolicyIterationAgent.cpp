//
// Created by Chi Zhang on 8/26/19.
//

#include "PolicyIterationAgent.hpp"
#include "common.hpp"
#include "cmath"

PolicyIterationAgent::PolicyIterationAgent(const FrozenLakeMDP &mdp, double gamma, int iterations, double threshold) :
        ValueEstimateAgent(gamma, iterations, threshold), m_iterations(iterations), m_threshold(threshold), m_gamma(gamma), m_mdp(mdp) {
    MSG("Training Policy Iteration Agent on " << m_mdp.getName());
    MSG("Initializing Policy Iteration Agent");
    initialize();
    MSG("Solving...");
    solve();
}

double PolicyIterationAgent::getQValue(const GameState &state, const Action &action) {
    // TODO
    auto utilities = evaluateCurrentPolicy();
    double sum = 0.0;
	for (auto nextState : m_mdp.getTransitionStatesAndProbs(state,action)) {
        double p = nextState.second;
        double u = utilities.find(nextState.first)->second;
        double r = m_mdp.getReward(state, action, nextState.first);
        sum += p*(m_gamma*u+r);
	}	    
    return sum;//m_mdp.getCurrentReward(state) + (m_gamma*sum);
}

double PolicyIterationAgent::getValue(const GameState &state) {
    // TODO
    auto qValue = getQValue(state,getPolicy(state));
    // auto utility = m_mdp.getCurrentReward(state) + m_gamma*(qValue);
    return qValue;
}

Action PolicyIterationAgent::getPolicy(const GameState &state) {
    // TODO
    auto policyIt = m_policy.find(state);
    Action action = policyIt->second;
    return action;
}

/*
 * Evaluate the current policy by returning V(s), which is represented as a map,
 * where key is GameState and value is double.
 */
std::map<GameState, double> PolicyIterationAgent::evaluateCurrentPolicy() {
    // TODO
    auto utilities = std::map<GameState, double>();
    // Initialise utilities to zero
    for (auto policyIt = m_policy.begin(); policyIt != m_policy.end(); policyIt++) {
    	GameState currentState = policyIt->first;
    	utilities[currentState] = 0.0;
    }
    double d=0.0;
    // bellman update for utilities
    while (true) {
        d=0.0;
	    for(auto it = m_policy.begin(); it != m_policy.end(); it++) {
	        auto currentState = it->first;
	        Action currentPolicy = it->second;
	        double oldUtility = utilities.find(currentState)->second;
	        double newUtility = 0.0;

            double sum = 0.0;
            // probability of each action
            for (auto state : m_mdp.getTransitionStatesAndProbs(currentState,currentPolicy)) {
                double p = state.second;
                double u = utilities.find(state.first)->second;
                double r = m_mdp.getReward(currentState, currentPolicy, state.first);
                sum += p*(m_gamma*u+r);
            }

            newUtility = sum;//m_mdp.getCurrentReward(currentState) + (m_gamma*sum);
            // MSG("current state= [" << currentState.getLoc().x << "," << currentState.getLoc().y << "] new utility=" << sum);
            // MSG("reward: [" << currentState.getLoc().x << "," << currentState.getLoc().y << "] == " <<  m_mdp.getCurrentReward(currentState));
            utilities[currentState] = newUtility;
            if (d < abs(oldUtility-newUtility)) {
                d = abs(oldUtility-newUtility);
            }
            // MSG("new: " << newUtility << "old: " << oldUtility << "d: " << d);
	    }
	     //break if reaches threshold
        if (d < m_threshold*(1.0-m_gamma)/m_gamma) {
            // MSG("\n" << d << " is less than " << m_threshold*(1.0-m_gamma)/m_gamma);
            break;
        }
	}
	return utilities;

}

void PolicyIterationAgent::solve() {
    // TODO
    bool unchanged = false;
    int i=0;
    while(!unchanged && i<m_iterations) {
    	unchanged = true;
    	// get new policy U
    	auto policies = evaluateCurrentPolicy();

    	for (auto it = policies.begin(); it != policies.end(); it++) {
    		auto currentState = it->first;
    		double maxValue = 0.0;
    		Action maxAction = Action::LEFT;
    		double policyValue = 0.0;

    		for (Action action : m_mdp.getPossibleActions(currentState)) {
                double sum = 0.0;
                // probability of each action
                for (auto state : m_mdp.getTransitionStatesAndProbs(currentState,action)) {
                    double p = state.second;
                    double u = policies.find(state.first)->second;//getValue(state.first);
                    double r = m_mdp.getReward(currentState, action, state.first);
                    sum += p*(m_gamma*u+r);
                    // sum += p*u;
                }
                if (action == getPolicy(currentState)) {
                	policyValue = sum;
                } else {
	                if (sum > maxValue||maxValue==0.0) {
	                	maxValue = sum;
	                	maxAction = action;
	                }
	            }
			}

    		if (maxValue > policyValue) {
    			unchanged = false;
    			m_policy[currentState] = maxAction;
    		}
    	}
    	i++;
    }
}

void PolicyIterationAgent::initialize() {
    // TODO
    std::set<GameState> gameStates = m_mdp.getStates();
    auto it = gameStates.begin();
    while (it != gameStates.end()) {
        GameState currentState = *it;
        for (auto action : m_mdp.getPossibleActions(currentState)){
        	m_policy[currentState] = action;
        }
/*        MSG("Current State: " << currentState.getLoc().x << ":" << currentState.getLoc().y);
   		MSG("Current Policy: " << getPolicy(currentState));*/
        it++;
    }
}


