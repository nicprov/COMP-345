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
    virtual ~PlayerStrategy(); // player strategy destructor
    PlayerStrategy(Player*, StrategyType); // player strategy constructor
    PlayerStrategy(const PlayerStrategy&); // player strategy copy constructor
    PlayerStrategy& operator= (const PlayerStrategy&); // player strategy assignment operator
    friend std::ostream& operator<< (std::ostream&, const PlayerStrategy&); // player strategy stream operator
    StrategyType getStrategy(); // get the strategy type
    void setStrategy(StrategyType); // set a new strategy type
    virtual void issueOrder(Deck*, Map*, std::vector<Player*>)=0; // abstract issueOrder method
    virtual std::vector<Territory*> toAttack(Map*)=0; // abstract toAttack method
    virtual std::vector<Territory*> toDefend(Map*)=0; // abstract toDefend method
    static constexpr std::initializer_list<StrategyType> ALL_STRATEGY_TYPES = {neutral, cheater, human, aggressive, benevolent};
    static const boost::unordered_map<StrategyType, std::string> strategyTypeMapping; // mapping of strategy type to string
protected:
    Player* player;
    StrategyType* strategyType;
};

class NeutralPlayerStrategy: public PlayerStrategy {
public:
    ~NeutralPlayerStrategy(); // neutral player destructor
    NeutralPlayerStrategy(Player*); // neutral player contructor
    NeutralPlayerStrategy(const NeutralPlayerStrategy&); // neutral player copy constructor
    NeutralPlayerStrategy& operator= (const NeutralPlayerStrategy&); // neutral player assignment operator
    friend std::ostream& operator<< (std::ostream&, const NeutralPlayerStrategy&); // neutral player stream operator
    void issueOrder(Deck*, Map*, std::vector<Player*>); // overloaded issue order method
    std::vector<Territory*> toAttack(Map*); // overloaded to attack method
    std::vector<Territory*> toDefend(Map*); // overloaded to defend method
};

class CheaterPlayerStrategy: public PlayerStrategy {
public:
    ~CheaterPlayerStrategy(); // cheater player destructor
    CheaterPlayerStrategy(Player*); // cheater player constructor
    CheaterPlayerStrategy(const CheaterPlayerStrategy&); // cheater player copy constructor
    CheaterPlayerStrategy& operator= (const CheaterPlayerStrategy&); // cheater player assignment operator
    friend std::ostream& operator<< (std::ostream&, const CheaterPlayerStrategy&); // cheater player stream operator
    void issueOrder(Deck*, Map*, std::vector<Player*>); // overloaded issue order method
    std::vector<Territory*> toAttack(Map*); // overloaded to attack method
    std::vector<Territory*> toDefend(Map*); // overloaded to defend method
};

class HumanPlayerStrategy: public PlayerStrategy {
public:
    ~HumanPlayerStrategy(); // human player destructor
    HumanPlayerStrategy(Player*); // human player constructor
    HumanPlayerStrategy(const HumanPlayerStrategy&); // human player copy constructor
    HumanPlayerStrategy& operator= (const HumanPlayerStrategy&); // human player assignment operator
    friend std::ostream& operator<< (std::ostream&, const HumanPlayerStrategy&); // human player stream operator
    void issueOrder(Deck*, Map*, std::vector<Player*>); // overloaded issue order method
    std::vector<Territory*> toAttack(Map*); // overloaded to attack method
    std::vector<Territory*> toDefend(Map*); // overloaded to defend method
};

class AggressivePlayerStrategy: public PlayerStrategy {
public:
    ~AggressivePlayerStrategy(); // aggressive player destructor
    AggressivePlayerStrategy(Player*); // aggressive player constructor
    AggressivePlayerStrategy(const AggressivePlayerStrategy&); // aggressive player copy constructor
    AggressivePlayerStrategy& operator= (const AggressivePlayerStrategy&); // aggressive player assignment operator
    friend std::ostream& operator<< (std::ostream&, const AggressivePlayerStrategy&); // aggressive player stream operator
    void issueOrder(Deck*, Map*, std::vector<Player*>); // overloaded issue order method
    std::vector<Territory*> toAttack(Map*); // overloaded to attack method
    std::vector<Territory*> toDefend(Map*); // overloaded to defend method
};

class BenevolentPlayerStrategy: public PlayerStrategy {
public:
    ~BenevolentPlayerStrategy(); // benevolent player destructor
    BenevolentPlayerStrategy(Player*); // benevolent player constructor
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy&); // benevolent player copy constructor
    BenevolentPlayerStrategy& operator= (const BenevolentPlayerStrategy&); // benevolent player assignment operator
    friend std::ostream& operator<< (std::ostream&, const BenevolentPlayerStrategy&); // benevolent player stream operator
    void issueOrder(Deck*, Map*, std::vector<Player*>); // overloaded issue order method
    std::vector<Territory*> toAttack(Map*); // overloaded to attack method
    std::vector<Territory*> toDefend(Map*); // overloaded to defend method
};

PlayerStrategy::StrategyType getStrategyType(const std::string&); // helper function to get the mapping from string to player strategy enum