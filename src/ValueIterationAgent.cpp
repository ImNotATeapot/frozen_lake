//
// Created by Chi Zhang on 8/24/19.
//

#include "common.hpp"
#include "ValueIterationAgent.hpp"
#include <tuple>
#include <functional>

ValueIterationAgent::ValueIterationAgent(FrozenLakeMDP const &mdp, double gamma, int iterations, double threshold) :
        ValueEstimateAgent(iterations, gamma, threshold), m_iterations(iterations), m_threshold(threshold), m_gamma(gamma), m_mdp(mdp) {

    MSG("Training Value Iteration Agent on " << m_mdp.getName());
    MSG("Initializing Value Iteration Agent");
    initialize();
    MSG("Solving...");
    solve();

//Print
    // for (auto it = states.begin(); it != states.end();) {
    //     auto t = it->second;
    //     auto currentState = it->first;

    //     MSG("Current state: ["<<currentState.getLoc().x<<"]["<<currentState.getLoc().y<<"]");
    //     MSG("Value: "<<getValue(currentState)<<", Policy: "<<getPolicy(currentState));
    //     it++;
    // }
}

double ValueIterationAgent::getValue(const GameState &state) {
    // TODO
    auto stateIt = states.find(state);
    auto t = stateIt->second;

    std::vector<double> values;
    std::vector<Action> actions = m_mdp.getPossibleActions(stateIt->first);
    if(actions.size() == 0) {
        values.push_back(0.0);
    }
    for (Action action : actions) {
        switch (action) {
            case UP:
            values.push_back(std::get<0>(t));
            break;
            case DOWN:
            values.push_back(std::get<1>(t));
            break;
            case LEFT:
            values.push_back(std::get<2>(t));
            break;
            case RIGHT:
            values.push_back(std::get<3>(t));
            break;
            default:
            values.push_back(0.0);
        }
    }

    return *max_element(values.begin(), values.end()); 
    // return std::max(std::max(up,down), std::max(left,right)); 
}

double ValueIterationAgent::getQValue(const GameState &state, const Action &action) {
    // TODO
    auto stateIt = states.find(state);
    auto t = stateIt->second;

    switch(action) {
        case UP:
        return std::get<0>(t);
        case DOWN:
        return std::get<1>(t);
        case LEFT:
        return std::get<2>(t);
        case RIGHT:
        return std::get<3>(t);
        default: return 0.0;
    }
}

Action ValueIterationAgent::getPolicy(const GameState &state) {
    // TODO
    auto stateIt = states.find(state);
    auto t = stateIt->second;
    double max = getValue(state);

    if (max == 0) {
        std::vector<Action> actions = m_mdp.getPossibleActions(stateIt->first);
        for (Action action : actions){
            return action;
        } 
    }

    if (max == std::get<0>(t)) {
        return Action::UP;
    } else if (max == std::get<1>(t)) {
        return Action::DOWN;
    } else if (max == std::get<2>(t)) {
        return Action::LEFT;
    } else {
        return Action::RIGHT;
    }
}


void ValueIterationAgent::solve() {
    // TODO. Implement Value Iteration here

    double d = 0.0;
    int iterations = 0;
    while (iterations <= m_iterations) {
        iterations++;
        //iterate through sets
        d=0.0;
        // auto it = states.begin();

        int stateNum = 0;
        for(auto it = states.begin(); it != states.end();) {
            auto t = it->second;
            auto currentState = it->first;
            double oldValue = getValue(currentState);
            //update values
            for (Action action : m_mdp.getPossibleActions(currentState)) {

                double sum = 0.0;
                // probability of each action
                for (auto state : m_mdp.getTransitionStatesAndProbs(currentState,action)) {
                    double p = state.second;
                    double u = getValue(state.first);
                    double r = m_mdp.getReward(currentState, action, state.first);
                    sum += p*(m_gamma*u+r);
                }

                double utility = sum;


                // double pu = 0.0;
                // double r = m_mdp.getCurrentReward(currentState);
                // for (auto state : m_mdp.getTransitionStatesAndProbs(currentState,action)) {
                //     double p = state.second;
                //     double u = getValue(state.first);
                //     pu += p*u;
                // }
                // double utility = r+m_gamma*pu;


                ValueTuple currTuple;
                ValueTuple tuple;
                t = states[currentState];
                //update tuple
                switch (action) {
                    case UP:
                     tuple = std::make_tuple(utility, std::get<1>(t), std::get<2>(t), std::get<3>(t)); 
                    states[currentState] = tuple;
                    break;
                    case DOWN:
                     tuple = std::make_tuple(std::get<0>(t), utility, std::get<2>(t), std::get<3>(t)); 
                    states[currentState] = tuple;
                    break;
                    case LEFT:
                     tuple = std::make_tuple(std::get<0>(t), std::get<1>(t), utility, std::get<3>(t)); 
                    states[currentState] = tuple;
                    break;
                    case RIGHT:
                     tuple = std::make_tuple(std::get<0>(t), std::get<1>(t), std::get<2>(t), utility); 
                    states[currentState] = tuple;
                    break;
                    default: break;
                }
            }
            double newValue = getValue(currentState);
            //change maximum d
            if (d < abs(oldValue-newValue)) {
                d = abs(oldValue-newValue);
            }
            it++;
        }
        //break if reaches threshold
        if (d < m_threshold*(1.0-m_gamma)/m_gamma) {
            // MSG("\n" << d << " is less than " << m_threshold*(1.0-m_gamma)/m_gamma);
            // MSG("\n new value = " << getValue(currentState));
            break;
        }
    }
}

void ValueIterationAgent::initialize() {
    // TODO. Initialize your data structure.
    std::set<GameState> gameStates = m_mdp.getStates();
    auto it = gameStates.begin();
    while (it != gameStates.end()) {
        GameState currentState = *it;
        ValueTuple tuple = std::make_tuple(0.0,0.0,0.0,0.0); 
        states[currentState] = tuple;
        it++;
    }
}




