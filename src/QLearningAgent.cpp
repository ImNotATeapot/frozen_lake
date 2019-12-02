//
// Created by Chi Zhang on 8/27/19.
//

#include "common.hpp"
#include "third_party/random.hpp"
#include "QLearningAgent.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>

QLearningAgent::QLearningAgent(FrozenLakeEnv &env, double gamma, int iterations, double alpha, double epsilon) :
        ValueEstimateAgent(gamma, iterations, 0.0), m_alpha(alpha), m_epsilon(epsilon), m_env(env) {
    MSG("Training Q Learning Agent on " << m_env.getName());
    MSG("Initializing Q Learning Agent");
    initialize();
    MSG("Solving...");
    solve();
}

double QLearningAgent::getValue(const GameState &state) {
    // TODO
    auto stateIt = utilities.find(state);
    auto t = stateIt->second;

    std::vector<double> values;
    std::vector<Action> actions = m_env.getPossibleActions(stateIt->first);
    for (Action action : actions){
        values.push_back(getQValue(state, action));
    }
    if(actions.size() == 0) {
        values.push_back(0.0);
    }

    return *max_element(values.begin(), values.end()); 
}

double QLearningAgent::getQValue(const GameState &state, const Action &action) {
    // TODO
    //Q(s,a) = R(s) + gamma * sum(p*max(Q(s',a')))
    auto stateIt = utilities.find(state);
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

// The final policy without exploration. Used for evaluation.
Action QLearningAgent::getPolicy(const GameState &state) {
    // TODO
    auto stateIt = utilities.find(state);
    auto t = stateIt->second;
    double min = getValue(state);

    if (min == 0) {
        std::vector<Action> actions = m_env.getPossibleActions(stateIt->first);
        for (Action action : actions){
            return action;
        } 
    }

    if (min == std::get<0>(t)) {
        return Action::UP;
    } else if (min == std::get<1>(t)) {
        return Action::DOWN;
    } else if (min == std::get<2>(t)) {
        return Action::LEFT;
    } else if (min == std::get<3>(t)){
        return Action::RIGHT;
    } else {
        return Action::UP;
    }
}

// you should use getAction in solve instead of getPolicy and implement your exploration strategy here.
Action QLearningAgent::getAction(const GameState &state) {
    // TODO
    double rand = (std::rand() % 100 + 1)/100; 
    if (rand <= m_epsilon) {
        std::vector<Action> actions;
        int num=0;
        for (Action action : m_env.getPossibleActions(state)) {
            actions.push_back(action);
            num++;
        }
        if (num != 0 ) {
            double index = (std::rand()%num);
            return actions[index];
        } else {
            return Action::UP;
        }
    } else {
        return getPolicy(state);
    }
}

void QLearningAgent::update(const GameState &state, const Action &action, const GameState &nextState, double reward) {
    // TODO
    // Q(s,a) = Q(s,a)+a*(R(s(s) + gamma(Q(s',a')) - Q(s,a)) 
    double oldValue = getQValue(state, action);
    double nextValue = getValue(nextState);
    double newValue = oldValue + m_alpha*(reward + m_gamma*(nextValue) - oldValue);

    ValueTuple t = utilities[state];
    switch (action) {
        case UP:
         t = std::make_tuple(newValue, std::get<1>(t), std::get<2>(t), std::get<3>(t)); 
        break;
        case DOWN:
         t = std::make_tuple(std::get<0>(t), newValue, std::get<2>(t), std::get<3>(t)); 
        break;
        case LEFT:
         t = std::make_tuple(std::get<0>(t), std::get<1>(t), newValue, std::get<3>(t)); 
        break;
        case RIGHT:
         t = std::make_tuple(std::get<0>(t), std::get<1>(t), std::get<2>(t), newValue); 
        break;
        default: break;
    }
    utilities[state] = t;
    return;
}

void QLearningAgent::solve() {
    // output a file for plotting
    std::ofstream outFile;
    outFile.open("result.csv");
    outFile << "Episode,Reward" << std::endl;

    int maxEpisodeSteps = 100;
    // collect m_iterations trajectories for update
    for (int i = 0; i < m_iterations; i++) {
        int numSteps = 0;
        GameState state = m_env.reset();
        while (!m_env.isTerminal(state)) {
            Action action = getAction(state);
            GameState nextState = m_env.getNextState(state, action);
            double reward = m_env.getReward(state, action, nextState);

            update(state, action, nextState, reward);
            state = nextState;
            numSteps += 1;
            if (numSteps >= maxEpisodeSteps) break;  // avoid infinite loop in some cases.
        }
        // evaluate for 100 episodes using the current optimal policy. You can't change this line.
        double episodeReward = m_env.runGame(*this, 1000, m_gamma, false).first;
        std::cout << "Evaluating episode reward at learning iteration " << i << " is " << episodeReward << std::endl;
        outFile << i << "," << episodeReward << std::endl;
    }
    outFile.close();
}

void QLearningAgent::initialize() {
    // TODO
    std::set<GameState> gameStates = m_env.getAllStates();
    auto it = gameStates.begin();
    while (it != gameStates.end()) {
        GameState currentState = *it;
        ValueTuple tuple = std::make_tuple(0.0,0.0,0.0,0.0); 
        utilities[currentState] = tuple;
        it++;
    }
    return;
}
