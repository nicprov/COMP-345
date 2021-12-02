#include <boost/assign/list_of.hpp>
#include "PlayerStrategies.h"
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

const boost::unordered_map<PlayerStrategy::StrategyType, std::string> PlayerStrategy::strategyTypeMapping = boost::assign::map_list_of(PlayerStrategy::StrategyType::benevolent, "benevolent")
        (PlayerStrategy::StrategyType::aggressive, "aggressive") (PlayerStrategy::StrategyType::human, "human") (PlayerStrategy::StrategyType::cheater, "cheater") (PlayerStrategy::StrategyType::neutral, "neutral");

/* Player Strategy*/
/**
 * Player strategy destructor
 */
PlayerStrategy::~PlayerStrategy()
{
    delete this->strategyType;
}

/**
 * Player strategy constructor
 * @param player Current player
 * @param strategyType Strategy type enum
 */
PlayerStrategy::PlayerStrategy(Player *player, StrategyType strategyType)
{
    this->strategyType = new StrategyType(strategyType);
    this->player = player;
}

/**
 * Player strategy copy constructor
 * @param playerStrategy
 */
PlayerStrategy::PlayerStrategy(const PlayerStrategy &playerStrategy)
{
    this->strategyType = new StrategyType(*playerStrategy.strategyType);
    this->player = new Player(*playerStrategy.player);
}

/**
 * Player strategy assignment operator
 * @param playerStrategy
 * @return current instance of object
 */
PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &playerStrategy)
{
    if (this != &playerStrategy){
        delete this->player;
        delete this->strategyType;
        this->player = new Player(*playerStrategy.player);
        this->strategyType = new StrategyType(*playerStrategy.strategyType);
    }
    return *this;
}

/**
 * Player strategy stream operator
 * @param stream
 * @param playerStrategy
 * @return
 */
std::ostream &operator<<(std::ostream &stream, const PlayerStrategy &playerStrategy)
{
    return stream << "PlayerStrategy(" << *playerStrategy.player << ")";
}

/**
 * Get the current strategy type enum value
 * @return
 */
PlayerStrategy::StrategyType PlayerStrategy::getStrategy()
{
    return *this->strategyType;
}

/**
 * Change the current strategy type
 * @param strategy
 */
void PlayerStrategy::setStrategy(PlayerStrategy::StrategyType strategy)
{
    this->strategyType = new StrategyType(strategy);
}

/* Neutral Player Strategy */
/**
 * Neutral player strategy destructor
 */
NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
    delete this->strategyType;
}

/**
 * Neutral player strategy constructor
 * @param player
 */
NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) : PlayerStrategy(player, StrategyType::neutral){}

/**
 * Neutral player strategy copy constructor
 * @param neutralPlayerStrategy
 */
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &neutralPlayerStrategy): PlayerStrategy(neutralPlayerStrategy.player, StrategyType::neutral){}

/**
 * Neutral player strategy assignment operator
 * @param neutralPlayerStrategy
 * @return current instance of object
 */
NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &neutralPlayerStrategy)
{
    if (this != &neutralPlayerStrategy){
        delete this->player;
        delete this->strategyType;
        this->player = new Player(*neutralPlayerStrategy.player);
        this->strategyType = new StrategyType(*neutralPlayerStrategy.strategyType);
    }
    return *this;
}

/**
 * Neutral player strategy stream operator
 * @param stream
 * @param neutralPlayerStrategy
 * @return stream
 */
std::ostream &operator<<(std::ostream &stream, const NeutralPlayerStrategy &neutralPlayerStrategy)
{
    return stream << "NeutralPlayerStrategy(" << *neutralPlayerStrategy.player << ")";
}

/**
 * Automated issue order method for the neutral player strategy (does not issue orders)
 * @param deck
 * @param map
 * @param players
 */
void NeutralPlayerStrategy::issueOrder(Deck* deck, Map* map, std::vector<Player*> players){} // Neutral player doesn't issue orders

/**
 * Gets the preferred list of territories to attack for the neutral player (none)
 * @param map
 * @return
 */
std::vector<Territory *> NeutralPlayerStrategy::toAttack(Map* map)
{
    // Neutral player doesn't issue orders
    return {};
}

/**
 * Gets the preferred list of territories to defend for the neutral player (none)
 * @param map
 * @return list of territories
 */
std::vector<Territory *> NeutralPlayerStrategy::toDefend(Map* map)
{
    // Neutral player doesn't issue orders
    return {};
}

/* Cheater Player Strategy */
/**
 * Cheater player strategy destructor
 */
CheaterPlayerStrategy::~CheaterPlayerStrategy()
{
    delete this->strategyType;
}

/**
 * Cheater player strategy constructor
 * @param player
 */
CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player) : PlayerStrategy(player, StrategyType::cheater){}

/**
 * Cheater player strategy copy constructor
 * @param cheaterPlayerStrategy
 */
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy &cheaterPlayerStrategy): PlayerStrategy(cheaterPlayerStrategy.player, StrategyType::cheater){}

/**
 * Cheater player strategy assignment operator
 * @param cheaterPlayerStrategy
 * @return current instance of object
 */
CheaterPlayerStrategy &CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy &cheaterPlayerStrategy)
{
    if (this != &cheaterPlayerStrategy){
        delete this->player;
        delete this->strategyType;
        this->player = new Player(*cheaterPlayerStrategy.player);
        this->strategyType = new StrategyType(*cheaterPlayerStrategy.strategyType);
    }
    return *this;
}

/**
 * Cheater player strategy stream operator
 * @param stream
 * @param cheaterPlayerStrategy
 * @return stream
 */
std::ostream &operator<<(std::ostream &stream, const CheaterPlayerStrategy &cheaterPlayerStrategy)
{
    return stream << "CheaterPlayerStrategy(" << *cheaterPlayerStrategy.player << ")";
}

/**
 * Automated issue order method for the cheater player strategy (does not issue orders, simply conquers territories)
 * @param deck
 * @param map
 * @param players
 */
void CheaterPlayerStrategy::issueOrder(Deck* deck, Map* map, std::vector<Player*> players)
{
    // Automatically conquers all neighbouring territories
    for (Territory* territory: this->toAttack(map)){
        territory->setOwner(this->player);
    }
}

/**
 * Gets the preferred list of territories to attack for the cheater player
 * @param map
 * @return list of territories
 */
std::vector<Territory *> CheaterPlayerStrategy::toAttack(Map* map)
{
    auto neighbouringTerritories = std::vector<Territory*>();
    for (Territory* playerTerritory: map->getTerritoriesByPlayer(this->player)){
        for (Territory* neighbouringTerritory: playerTerritory->listOfAdjTerr){
            if (!(std::find(neighbouringTerritories.begin(), neighbouringTerritories.end(), neighbouringTerritory) != neighbouringTerritories.end()) && neighbouringTerritory->getOwner() != this->player) // Check if territory is already in list
                neighbouringTerritories.push_back(neighbouringTerritory);
        }
    }
    return neighbouringTerritories;
}

/**
 * Gets the preferred list of territories to defend for the cheater player (none)
 * @param map
 * @return list of territories
 */
std::vector<Territory *> CheaterPlayerStrategy::toDefend(Map* map)
{
    // Never defends any territories
    return {};
}

/* Human Player Strategy */
/**
 * Human player strategy destructor
 */
HumanPlayerStrategy::~HumanPlayerStrategy()
{
    delete this->strategyType;
}

/**
 * Human player strategy contructor
 * @param player
 */
HumanPlayerStrategy::HumanPlayerStrategy(Player *player) : PlayerStrategy(player, StrategyType::human){}

/**
 * Human player strategy copy constructor
 * @param humanPlayerStrategy
 */
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &humanPlayerStrategy): PlayerStrategy(humanPlayerStrategy.player, StrategyType::human){}

/**
 * Human player strategy assignment operator
 * @param humanPlayerStrategy
 * @return current object instance
 */
HumanPlayerStrategy &HumanPlayerStrategy::operator=(const HumanPlayerStrategy &humanPlayerStrategy)
{
    if (this != &humanPlayerStrategy){
        delete this->player;
        delete this->strategyType;
        this->player = new Player(*humanPlayerStrategy.player);
        this->strategyType = new StrategyType(*humanPlayerStrategy.strategyType);
    }
    return *this;
}

/**
 * Human player strategy stream operator
 * @param stream
 * @param humanPlayerStrategy
 * @return stream
 */
std::ostream &operator<<(std::ostream &stream, const HumanPlayerStrategy &humanPlayerStrategy)
{
    return stream << "HumanPlayerStrategy(" << *humanPlayerStrategy.player << ")";
}

/**
 * Automated issue order method for the human player strategy
 * @param deck
 * @param map
 * @param players
 */
void HumanPlayerStrategy::issueOrder(Deck* deck, Map* map, std::vector<Player*> players)
{
    // Issue deploy orders while there are armies to deploy
    std::cout << "Issuing deploy orders..." << std::endl << std::endl;
    this->player->issueDeployOrders(map);

    // Issue advance orders
    std::cout << std::endl << "Issuing advance orders and playing cards..." << std::endl << std::endl;
    this->player->issueAdvanceOrders(map, deck, players);
}

/**
 * Gets the preferred list of territories to attack for the human player
 * @param map
 * @return list of territories
 */
std::vector<Territory *> HumanPlayerStrategy::toAttack(Map* map)
{
    auto neighbouringTerritories = std::vector<Territory*>();
    for (Territory* playerTerritory: map->getTerritoriesByPlayer(this->player)){
        for (Territory* neighbouringTerritory: playerTerritory->listOfAdjTerr){
            if (!(std::find(neighbouringTerritories.begin(), neighbouringTerritories.end(), neighbouringTerritory) != neighbouringTerritories.end()) && neighbouringTerritory->getOwner() != this->player) // Check if territory is already in list
                neighbouringTerritories.push_back(neighbouringTerritory);
        }
    }
    return neighbouringTerritories;
}

/**
 * Gets the preferred list of territories to defend for the human player
 * @param map
 * @return list of territories
 */
std::vector<Territory *> HumanPlayerStrategy::toDefend(Map* map)
{
    return map->getTerritoriesByPlayer(this->player);
}

/* Aggressive Player Strategy */
/**
 * Aggressive player strategy destructor
 */
AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
    delete this->strategyType;
}

/**
 * Aggressive player strategy constructor
 * @param player
 */
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player) : PlayerStrategy(player, StrategyType::aggressive){}

/**
 * Aggressive player strategy copy constructor
 * @param aggressivePlayerStrategy
 */
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &aggressivePlayerStrategy): PlayerStrategy(aggressivePlayerStrategy.player, StrategyType::aggressive){}

/**
 * Aggressive player strategy assignment operator
 * @param aggressivePlayerStrategy
 * @return current instance of object
 */
AggressivePlayerStrategy &AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy &aggressivePlayerStrategy)
{
    if (this != &aggressivePlayerStrategy){
        delete this->player;
        delete this->strategyType;
        this->player = new Player(*aggressivePlayerStrategy.player);
        this->strategyType = new StrategyType(*aggressivePlayerStrategy.strategyType);
    }
    return *this;
}

/**
 * Aggressive player strategy stream operator
 * @param stream
 * @param aggressivePlayerStrategy
 * @return stream
 */
std::ostream &operator<<(std::ostream &stream, const AggressivePlayerStrategy &aggressivePlayerStrategy)
{
    return stream << "AggressivePlayerStrategy(" << *aggressivePlayerStrategy.player << ")";
}

/**
 * Automated issue order method for the aggressive player strategy (focuses on strongest territory)
 * @param deck
 * @param map
 * @param players
 */
void AggressivePlayerStrategy::issueOrder(Deck* deck, Map* map, std::vector<Player*> players)
{
    // Get the strongest countries
    std::vector<Territory*> strongTerritories = this->toDefend(map);

    // Issue deploy orders by focusing army pool on strongest territory
    if (!strongTerritories.empty()){
        Order* deploy = new Deploy(this->player, strongTerritories.at(0), this->player->armyPool);
        this->player->attachExistingObservers(deploy, this->player->orderList->getObservers());
        this->player->orderList->add(deploy);
    }

    // Issue advance orders if possible
    if (!strongTerritories.empty()){
        Territory* sourceTerritory = strongTerritories.at(0);
        for (Territory* targetTerritory: strongTerritories.at(0)->listOfAdjTerr){
            if (targetTerritory->getOwner() != this->player){
                Order* advance = new Advance(deck, this->player, sourceTerritory, targetTerritory, sourceTerritory->getNumberOfArmies());
                this->player->attachExistingObservers(advance, this->player->orderList->getObservers());
                this->player->orderList->add(advance);
                break;
            }
        }
    }

    // Play first card in hand
    Order* order;
    if (!this->player->hand->getCards().empty()){
        Card* card = this->player->hand->getCards().at(0);
        switch (card->getType()) {
            case Card::CardType::bomb:
                if (!this->toAttack(map).empty()){
                    order = new Bomb(this->toAttack(map).at(0)->getOwner(), this->toAttack(map).at(0));
                    this->player->attachExistingObservers(order, this->player->orderList->getObservers());
                    card->play(deck, this->player, order);
                }
                break;
            case Card::CardType::blockade:
                if (!this->toDefend(map).empty()) {
                    order = new Blockade(this->player, this->toDefend(map).at(0), players);
                    this->player->attachExistingObservers(order, this->player->orderList->getObservers());
                    card->play(deck, this->player, order);
                }
                break;
            case Card::CardType::airlift:
            case Card::CardType::diplomacy:
                // Nothing to airlift, all armies are already concentrated in one area
                // No time for diplomacy when you're aggressive
                this->player->hand->removeCard(card);
                break;
            case Card::CardType::reinforcement:
                this->player->armyPool += 5;
                this->player->hand->removeCard(card);
                break;
        }
    }
}

/**
 * Gets the preferred list of territories to attack for the aggressive player
 * @param map
 * @return list of territories
 */
std::vector<Territory *> AggressivePlayerStrategy::toAttack(Map* map)
{
    auto neighbouringTerritories = std::vector<Territory*>();
    for (Territory* playerTerritory: map->getTerritoriesByPlayer(this->player)){
        for (Territory* neighbouringTerritory: playerTerritory->listOfAdjTerr){
            if (!(std::find(neighbouringTerritories.begin(), neighbouringTerritories.end(), neighbouringTerritory) != neighbouringTerritories.end()) && neighbouringTerritory->getOwner() != this->player) // Check if territory is already in list
                neighbouringTerritories.push_back(neighbouringTerritory);
        }
    }
    // Sort by weakest territories
    std::sort(neighbouringTerritories.begin(), neighbouringTerritories.end(),[](Territory* t1, Territory* t2){
        return t1->getNumberOfArmies() < t2->getNumberOfArmies();
    });
    return neighbouringTerritories;
}

/**
 * Gets the preferred list of territories to defend for the aggressive player
 * @param map
 * @return list of territories
 */
std::vector<Territory *> AggressivePlayerStrategy::toDefend(Map* map)
{
    // Always attacks, but useful for reinforcements
    std::vector<Territory*> playerTerritories = map->getTerritoriesByPlayer(this->player);
    // Sort territories by number of armies in decreasing order
    std::sort(playerTerritories.begin(), playerTerritories.end(),[](Territory* t1, Territory* t2){
        return t1->getNumberOfArmies() > t2->getNumberOfArmies();
    });
    return playerTerritories;
}

/* Benevolent Player Strategy */
/**
 * Benevolent player strategy destructor
 */
BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
    delete this->strategyType;
}

/**
 * Benevolent player strategy constructor
 * @param player
 */
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player) : PlayerStrategy(player, StrategyType::benevolent){}

/**
 * Benevolent player strategy copy constructor
 * @param benevolentPlayerStrategy
 */
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy &benevolentPlayerStrategy): PlayerStrategy(benevolentPlayerStrategy.player, StrategyType::benevolent){}

/**
 * Benevolent player strategy assignment operator
 * @param benevolentPlayerStrategy
 * @return current instance of object
 */
BenevolentPlayerStrategy &BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy &benevolentPlayerStrategy)
{
    if (this != &benevolentPlayerStrategy){
        delete this->player;
        delete this->strategyType;
        this->player = new Player(*benevolentPlayerStrategy.player);
        this->strategyType = new StrategyType(*benevolentPlayerStrategy.strategyType);
    }
    return *this;
}

/**
 * Benevolent player strategy stream operator
 * @param stream
 * @param benevolentPlayerStrategy
 * @return stream
 */
std::ostream &operator<<(std::ostream &stream, const BenevolentPlayerStrategy &benevolentPlayerStrategy)
{
    return stream << "BenevolentPlayerStrategy(" << *benevolentPlayerStrategy.player << ")";
}

/**
 * Automated issue order method for the benevolent player strategy (focuses on weakest territory)
 * @param deck
 * @param map
 * @param players
 */
void BenevolentPlayerStrategy::issueOrder(Deck* deck, Map* map, std::vector<Player*> players)
{
    // Get the most vulnerable countries
    std::vector<Territory*> weakTerritories = this->toDefend(map);

    // Issue deploy orders by distributing army pool equally between all vulnerable countries
    if (!weakTerritories.empty()){
        int armyCount = 0;
        while (armyCount < this->player->armyPool){
            for (Territory* territory: weakTerritories){
                if (this->player->armyPool == armyCount)
                    break;
                Order* order = new Deploy(this->player, territory, 1);
                armyCount++;

                // Attach log observer to order
                this->player->attachExistingObservers(order, this->player->orderList->getObservers());

                // Add order to orderList
                this->player->orderList->add(order);
            }
        }
    }

    // Issue advance order from the strongest territory, to the weakest
    Territory* from;
    Territory* to;
    if (!this->toDefend(map).empty()) {
        from = this->toDefend(map).at(this->toDefend(map).size()-1); // strongest territory
        for (Territory* adjacentTerritory: from->listOfAdjTerr){
            if (adjacentTerritory->getNumberOfArmies() < from->getNumberOfArmies() && adjacentTerritory->getOwner() == this->player){
                to = this->toDefend(map).at(0); // weakest territory
                Order* advance = new Advance(deck, this->player, from, to, from->getNumberOfArmies() % 5);
                this->player->attachExistingObservers(advance, this->player->orderList->getObservers());
                this->player->orderList->add(advance);
                break;
            }
        }
    }

    // Play card
    Order* order;
    if (!this->player->hand->getCards().empty()){
        Card* card = this->player->hand->getCards().at(0);
        switch (card->getType()) {
            case Card::CardType::bomb: {
                // Benevolent player does not attack enemy
                this->player->hand->removeCard(card);
                break;
            }
            case Card::CardType::blockade: {
                if (!this->toDefend(map).empty()){
                    order = new Blockade(this->player, this->toDefend(map).at(0), players);
                    this->player->attachExistingObservers(order, this->player->orderList->getObservers());
                    card->play(deck, this->player, order);
                }
                break;
            }
            case Card::CardType::airlift: {
                if (!this->toDefend(map).empty()) {
                    from = this->toDefend(map).at(this->toDefend(map).size()-1);
                    to = this->toDefend(map).at(0);
                    order = new Airlift(this->player, from, to, from->getNumberOfArmies() % 5);
                    this->player->attachExistingObservers(order, this->player->orderList->getObservers());
                    card->play(deck, this->player, order);
                }
                break;
            }
            case Card::CardType::reinforcement: {
                this->player->armyPool += 5;
                this->player->hand->removeCard(card);
                break;
            }
            case Card::CardType::diplomacy: {
                Player *enemy = nullptr;
                do {
                    player = players.at(rand()%(players.size()-1));
                } while (enemy == this->player); // Ensure that random player isn't yourself
                order = new Negotiate(this->player, enemy);
                this->player->attachExistingObservers(order, this->player->orderList->getObservers());
                card->play(deck, this->player, new Negotiate(this->player, enemy));
                break;
            }
        }
    }
}

/**
 * Gets the preferred list of territories to attack for the benevolent player
 * @param map
 * @return list of territories
 */
std::vector<Territory *> BenevolentPlayerStrategy::toAttack(Map* map)
{
    // Never advances onto enemy territories
    return {};
}

/**
 * Gets the preferred list of territories to defend for the benevolent player
 * @param map
 * @return list of territories
 */
std::vector<Territory*> BenevolentPlayerStrategy::toDefend(Map* map)
{
    std::vector<Territory*> playerTerritories = map->getTerritoriesByPlayer(this->player);
    // Sort territories by number of armies in increasing order
    std::sort(playerTerritories.begin(), playerTerritories.end(),[](Territory* t1, Territory* t2){
                  return t1->getNumberOfArmies() < t2->getNumberOfArmies();
    });
    return playerTerritories;
}

/**
 * Gets the strategy type from the boost map
 * @param _strategy
 * @return strategy type
 */
PlayerStrategy::StrategyType getStrategyType(const std::string& _strategy)
{
    for (auto& it: PlayerStrategy::strategyTypeMapping){
        if (it.second == _strategy)
            return it.first;
    }
    throw std::runtime_error("Strategy type (" + _strategy + ") does not exist");
}