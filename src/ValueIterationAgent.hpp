//
// Created by Chi Zhang on 8/24/19.
//

#ifndef FROZEN_LAKE_VALUEITERATIONAGENT_HPP
#define FROZEN_LAKE_VALUEITERATIONAGENT_HPP


#include "LearningAgent.hpp"
#include "FrozenLake.hpp"

class ValueIterationAgent : public ValueEstimateAgent {
    typedef std::tuple<double, double, double, double> ValueTuple; //UP DOWN LEFT RIGHT
public:

    ValueIterationAgent(FrozenLakeMDP const &mdp, double gamma, int iterations, double threshold);

    double getValue(const GameState &state) override;

    double getQValue(const GameState &state, const Action &action) override;

    Action getPolicy(const GameState &state) override;

    std::string getName() const override {
        return "ValueIterationAgent";
    }

private:
    void initialize() override;

    void solve();

    const FrozenLakeMDP &m_mdp;

    double m_gamma;

    double m_threshold;

    int m_iterations;

    std::map<GameState, ValueTuple> states;

};


#endif //FROZEN_LAKE_VALUEITERATIONAGENT_HPP
