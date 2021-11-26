#pragma once

#include <iostream>
#include <vector>
#include <boost/unordered_map.hpp>

class Territory;
class Player;
class Deck;
class Map;

class PlayerStrategy {
public:
    enum StrategyType {
        neutral = 1,
        cheater = 2,
        human = 3,
        aggressive = 4,
        benevolent = 5
    };
    PlayerStrategy(Player*, StrategyType);
    PlayerStrategy(const PlayerStrategy&);
    PlayerStrategy& operator= (const PlayerStrategy&);
    friend std::ostream& operator<< (std::ostream&, const PlayerStrategy&);
    StrategyType getStrategy();
    void setStrategy(StrategyType);
    virtual void issueOrder(Deck*, Map*, std::vector<Player*>)=0;
    virtual std::vector<Territory*> toAttack(Map*)=0;
    virtual std::vector<Territory*> toDefend(Map*)=0;
    static constexpr std::initializer_list<StrategyType> ALL_STRATEGY_TYPES = {neutral, cheater, human, aggressive, benevolent};
    static const boost::unordered_map<StrategyType, std::string> strategyTypeMapping;
protected:
    Player* player;
    StrategyType* strategyType;
};

class NeutralPlayerStrategy: public PlayerStrategy {
public:
    NeutralPlayerStrategy(Player*);
    NeutralPlayerStrategy(const NeutralPlayerStrategy&);
    NeutralPlayerStrategy& operator= (const NeutralPlayerStrategy&);
    friend std::ostream& operator<< (std::ostream&, const NeutralPlayerStrategy&);
    void issueOrder(Deck*, Map*, std::vector<Player*>);
    std::vector<Territory*> toAttack(Map*);
    std::vector<Territory*> toDefend(Map*);
};

class CheaterPlayerStrategy: public PlayerStrategy {
public:
    CheaterPlayerStrategy(Player*);
    CheaterPlayerStrategy(const CheaterPlayerStrategy&);
    CheaterPlayerStrategy& operator= (const CheaterPlayerStrategy&);
    friend std::ostream& operator<< (std::ostream&, const CheaterPlayerStrategy&);
    void issueOrder(Deck*, Map*, std::vector<Player*>);
    std::vector<Territory*> toAttack(Map*);
    std::vector<Territory*> toDefend(Map*);
};

class HumanPlayerStrategy: public PlayerStrategy {
public:
    HumanPlayerStrategy(Player*);
    HumanPlayerStrategy(const HumanPlayerStrategy&);
    HumanPlayerStrategy& operator= (const HumanPlayerStrategy&);
    friend std::ostream& operator<< (std::ostream&, const HumanPlayerStrategy&);
    void issueOrder(Deck*, Map*, std::vector<Player*>);
    std::vector<Territory*> toAttack(Map*);
    std::vector<Territory*> toDefend(Map*);
};

class AggressivePlayerStrategy: public PlayerStrategy {
public:
    AggressivePlayerStrategy(Player*);
    AggressivePlayerStrategy(const AggressivePlayerStrategy&);
    AggressivePlayerStrategy& operator= (const AggressivePlayerStrategy&);
    friend std::ostream& operator<< (std::ostream&, const AggressivePlayerStrategy&);
    void issueOrder(Deck*, Map*, std::vector<Player*>);
    std::vector<Territory*> toAttack(Map*);
    std::vector<Territory*> toDefend(Map*);
};

class BenevolentPlayerStrategy: public PlayerStrategy {
public:
    BenevolentPlayerStrategy(Player*);
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy&);
    BenevolentPlayerStrategy& operator= (const BenevolentPlayerStrategy&);
    friend std::ostream& operator<< (std::ostream&, const BenevolentPlayerStrategy&);
    void issueOrder(Deck*, Map*, std::vector<Player*>);
    std::vector<Territory*> toAttack(Map*);
    std::vector<Territory*> toDefend(Map*);
};

PlayerStrategy::StrategyType getStrategyType(const std::string&);