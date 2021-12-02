#include <vector>
#include "Map.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "PlayerStrategies.h"

//Player methods

/**
 * Destructor
 */
Player::~Player()
{
    delete this->hand;
    hand = nullptr;
    delete this->orderList;
    orderList = nullptr;
}

/**
 * Player constructor
 */
Player::Player()
{
    this->playerStrategy = new HumanPlayerStrategy(this);
    this->name = "No name";
    this->hand = new Hand();
    this->orderList = new OrderList();
    this->armyPool = 0;
}

/**
 * Player default constructor
 * Provides default values to the Player object
 * @param name string
 */
Player::Player(const std::string &name, PlayerStrategy::StrategyType strategyType)
{
    switch (strategyType) {
        case PlayerStrategy::neutral:
            this->playerStrategy = new NeutralPlayerStrategy(this);
            break;
        case PlayerStrategy::cheater:
            this->playerStrategy = new CheaterPlayerStrategy(this);
            break;
        case PlayerStrategy::human:
            this->playerStrategy = new HumanPlayerStrategy(this);
            break;
        case PlayerStrategy::aggressive:
            this->playerStrategy = new AggressivePlayerStrategy(this);
            break;
        case PlayerStrategy::benevolent:
            this->playerStrategy = new BenevolentPlayerStrategy(this);
            break;
    }
    this->name = name;
    this->hand = new Hand();
    this->orderList = new OrderList();
    this->armyPool = 0;
}

/**
 * Player Constructor
 * @param hand Hand
 * @param orderlist OrderList
 * @param name string
 * @param territoryList vector of pointers to pointers
 */
Player::Player(PlayerStrategy::StrategyType strategyType, const Hand &hand, const OrderList &orderlist, const std::string &name)
{
    switch (strategyType) {
        case PlayerStrategy::neutral:
            this->playerStrategy = new NeutralPlayerStrategy(this);
            break;
        case PlayerStrategy::cheater:
            this->playerStrategy = new CheaterPlayerStrategy(this);
            break;
        case PlayerStrategy::human:
            this->playerStrategy = new HumanPlayerStrategy(this);
            break;
        case PlayerStrategy::aggressive:
            this->playerStrategy = new AggressivePlayerStrategy(this);
            break;
        case PlayerStrategy::benevolent:
            this->playerStrategy = new BenevolentPlayerStrategy(this);
            break;
    }
    this->armyPool = 0;
    this->hand = new Hand(hand);
    this->orderList = new OrderList(orderlist);
    this->name = name;
}

/**
 * Player copy constructor
 * Makes a copy of Player
 * @param player Player
 */
Player::Player(const Player &player)
{
    switch (player.playerStrategy->getStrategy()) {
        case PlayerStrategy::neutral:
            this->playerStrategy = new NeutralPlayerStrategy(*dynamic_cast<NeutralPlayerStrategy*>(player.playerStrategy));
            break;
        case PlayerStrategy::cheater:
            this->playerStrategy = new CheaterPlayerStrategy(*dynamic_cast<CheaterPlayerStrategy*>(player.playerStrategy));
            break;
        case PlayerStrategy::human:
            this->playerStrategy = new HumanPlayerStrategy(*dynamic_cast<HumanPlayerStrategy*>(player.playerStrategy));
            break;
        case PlayerStrategy::aggressive:
            this->playerStrategy = new AggressivePlayerStrategy(*dynamic_cast<AggressivePlayerStrategy*>(player.playerStrategy));
            break;
        case PlayerStrategy::benevolent:
            this->playerStrategy = new BenevolentPlayerStrategy(*dynamic_cast<BenevolentPlayerStrategy*>(player.playerStrategy));
            break;
    }
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    this->name = player.name;
    this->armyPool = player.armyPool;
}

/**
 * Player assignment operator
 * @param player Player
 * @return Player reference
 */
Player& Player::operator= (const Player& player)
{
    if (this != &player){
        switch (this->playerStrategy->getStrategy()) {
            case PlayerStrategy::neutral:
                delete dynamic_cast<NeutralPlayerStrategy*>(playerStrategy);
                break;
            case PlayerStrategy::cheater:
                delete dynamic_cast<CheaterPlayerStrategy*>(playerStrategy);
                break;
            case PlayerStrategy::human:
                delete dynamic_cast<HumanPlayerStrategy*>(playerStrategy);
                break;
            case PlayerStrategy::aggressive:
                delete dynamic_cast<AggressivePlayerStrategy*>(playerStrategy);
                break;
            case PlayerStrategy::benevolent:
                delete dynamic_cast<BenevolentPlayerStrategy*>(playerStrategy);
                break;
        }
        switch (player.playerStrategy->getStrategy()) {
            case PlayerStrategy::neutral:
                this->playerStrategy = new NeutralPlayerStrategy(*dynamic_cast<NeutralPlayerStrategy*>(playerStrategy));
                break;
            case PlayerStrategy::cheater:
                this->playerStrategy = new CheaterPlayerStrategy(*dynamic_cast<CheaterPlayerStrategy*>(playerStrategy));
                break;
            case PlayerStrategy::human:
                this->playerStrategy = new HumanPlayerStrategy(*dynamic_cast<HumanPlayerStrategy*>(playerStrategy));
                break;
            case PlayerStrategy::aggressive:
                this->playerStrategy = new AggressivePlayerStrategy(*dynamic_cast<AggressivePlayerStrategy*>(playerStrategy));
                break;
            case PlayerStrategy::benevolent:
                this->playerStrategy = new BenevolentPlayerStrategy(*dynamic_cast<BenevolentPlayerStrategy*>(playerStrategy));
                break;
        }
        delete this->hand;
        this->hand = new Hand(*player.hand);
        delete this->orderList;
        this->orderList = new OrderList(*player.orderList);
        this->name = player.name;
        this->armyPool = player.armyPool;
    }
    return *this;
}

/**
 * Stream insertion operator for Player
 * @param stream Output stream
 * @param player Player
 * @return output stream
 */
std::ostream &operator<<(std::ostream &stream, const Player &player)
{
    return stream << "Player(name:" << player.name << ", strategy:" << PlayerStrategy::strategyTypeMapping.at(player.playerStrategy->getStrategy()) << "): " << *player.hand << ", " << *player.orderList << ", Army pool:" << player.armyPool;
}

/**
 * Create orders for execution
 * @param deck Deck
 * @param map Map
 * @param players vector of pointers to pointers
 */
void Player::issueOrder(Deck* deck, Map* map, std::vector<Player*>& players)
{
    this->playerStrategy->issueOrder(deck, map, players);
}

/**
 * Comparison of player by looking at its type
 * @param player Player compared to
 * @return bool value of true (match) or false (does not match)
 */
bool Player::operator==(const Player &player) const
{
    return this->name == player.name && *this->orderList == *player.orderList && *this->hand == *player.hand;
}

/**
 * Create and display territories to defend
 * based on territories owned
 * @return list of territories to defend
 */
std::vector<Territory*> Player::toDefend(Map* map)
{
    return this->playerStrategy->toDefend(map);
}

/**
 * Create and display territories to attack
 * based on adjacent territories
 * @return list of territories to attack
 */
std::vector<Territory* > Player::toAttack(Map* map)
{
    return this->playerStrategy->toDefend(map);
}

/**
 * Get Player name
 * @return name of player
 */
std::string &Player::getName()
{
    return this->name;
}

/**
 * Get Orderlist
 * @return orderList of player
 */
OrderList &Player::getOrderList()
{
    return *this->orderList;
}

/**
 * Verifies if players have negotiation with eachother
 * @param enemy Player
 * @return true if negotiation is needed, false otherwise
 */
bool Player::hasNegotiationWith(Player* enemy)
{
    for (int i = 0; i < orderList->getOrders().size(); i++)
        if (orderList->getOrders().at(i)->getOrderType() == 6)
            if (dynamic_cast<Negotiate*>(orderList->getOrders().at(i))->getEnemy() == enemy)
                return true;
    return false;
}

/**
 * Prompts human player to enter information for a particular advance order
 * @param map current map
 * @param deck current deck of cards
 * @return created order
 */
Order* Player::advance(Map* map, Deck* deck)
{
    Order* order;
    int index = 1;
    int territoryFromIndex;
    int territoryToIndex;
    int armiesToDeploy;
    Territory* territoryFrom;
    Territory* territoryTo;
    int choice;

    std::cout << std::endl << "Choose which kind of mobilization you would like:" << std::endl;
    std::cout << "1. Move armies to defend" << std::endl;
    std::cout << "2. Move armies to attack" << std::endl;
    std::cout << "Select an option: ";

    getValidatedInput(choice, 1, 2);

    for (Territory* territory: this->toDefend(map))
        std::cout << index++ << ": " << territory->getTerrName() << " (armies: " << territory->getNumberOfArmies() << ")" << std::endl;

    std::cout << "Select a territory to mobilize armies from: ";
    getValidatedInput(territoryFromIndex, 1, this->toDefend(map).size());
    territoryFrom = this->toDefend(map).at(territoryFromIndex-1);

    if (choice == 1) {
        index = 1;
        for (Territory* territory: this->toDefend(map))
            std::cout << index++ << ": " << territory->getTerrName() << " (armies: " << territory->getNumberOfArmies() << ")" << std::endl;

        std::cout << "Select a territory to mobilize armies to: ";
        getValidatedInput(territoryToIndex, 1, this->toDefend(map).size());
        territoryTo = this->toDefend(map).at(territoryToIndex-1);
    } else {
        index = 1;
        for (Territory* territory: this->toAttack(map))
            std::cout << index++ << ": " << territory->getTerrName() << " (armies: " << territory->getNumberOfArmies() << ")" << std::endl;

        std::cout << "Select a territory to mobilize armies to: " << std::endl;
        getValidatedInput(territoryToIndex, 1, this->toAttack(map).size());
        territoryTo = this->toDefend(map).at(territoryToIndex-1);
    }

    std::cout << "Select the number of armies to deploy to " << territoryTo->getTerrName() << ": ";
    getValidatedInput(armiesToDeploy, 1, territoryFrom->getNumberOfArmies());

    order = new Advance(deck, this, territoryFrom, territoryTo, armiesToDeploy);
    attachExistingObservers(order, this->orderList->getObservers());
    return order;
}

/**
 * Prompts the human player to issue deploy orders and validates them
 * @param map current map
 */
void Player::issueDeployOrders(Map* map)
{
    Order* order;
    Territory* territoryToDeployTo;
    int armiesDeployed = 0;

    // Issue deploy orders
    while (armiesDeployed < this->armyPool){
        int numArmiesToDeploy = 0;
        int territoryToDeployArmies = 0;

        // List territories available to deploy orders on
        int index = 1;
        for (Territory* ownedTerr : this->toDefend(map))
            std::cout << index++ << ": " << ownedTerr->getTerrName() << std::endl;

        std::cout << std::endl << "Select a territory to deploy armies to: ";
        getValidatedInput(territoryToDeployArmies, 1, (this->toDefend(map).size()));

        territoryToDeployTo = this->toDefend(map).at(territoryToDeployArmies-1);

        std::cout << "Select the number of armies (" << (this->armyPool-armiesDeployed) << " armies left to deploy) to deploy to " << territoryToDeployTo->getTerrName() << " : ";
        getValidatedInput(numArmiesToDeploy, 1, (this->armyPool-armiesDeployed));

        // Create new order
        order = new Deploy(this, territoryToDeployTo, numArmiesToDeploy);

        // Attach log observer to order
        attachExistingObservers(order, this->orderList->getObservers());

        // Add order to orderList
        this->orderList->add(order);

        armiesDeployed += numArmiesToDeploy;
    }
}

/**
 * Prompts the user to issue advance orders and validates them
 * @param map current map
 * @param deck current deck of card
 * @param players list of current players
 */
void Player::issueAdvanceOrders(Map* map, Deck* deck, std::vector<Player*> players){
    Order* order;
    bool isCardPlayed = false;
    while (true) {
        std::string choice;
        if (!isCardPlayed && this->hand->getCards().size() > 0)
            std::cout << "Card <card>, Advance <advance> or End Turn <endturn>?: ";
        else
            std::cout << "Advance <advance> or End Turn <endturn>?: ";
        std::cin >> choice;
        if (choice == "card"){
            if (!this->hand->getCards().empty()) {
                isCardPlayed = true;
                int index = 1;
                int cardIndex;
                std::cout << std::endl << "Cards available to play: " << std::endl;
                for (Card* card: this->hand->getCards())
                    std::cout << index++ << ": " << *card << std::endl;
                std::cout << "Select a card to play: ";
                getValidatedInput(cardIndex, 1, this->hand->getCards().size());
                Card* card = this->hand->getCards().at(cardIndex-1);
                card->play(deck, this, getCardOrderDetails(card, map, players));
            } else
                std::cout << "\x1B[31m" << "No cards to play" << "\033[0m" << std::endl;
        } else if (choice == "advance") {
            order = advance(map,deck);
            orderList->add(order);
        } else if (choice == "endturn") {
            break;
        } else
            std::cout << "\x1B[31m" << "Invalid choice." << "\033[0m" << std::endl;
    }
}

/**
 * Prompts the human player to enter the information to create an order from a card
 * @param card Card being played
 * @param map current map
 * @param players list of players
 * @return created order from card
 */
Order* Player::getCardOrderDetails(Card* card, Map* map, std::vector<Player*>& players) {
    Order *order = nullptr;
    Territory* territoryTo;
    Territory* territoryToAttack;
    Territory* territoryFrom;
    Territory* territoryToBlockade;
    Player* enemy;
    int index = 0;

    switch (card->getType()) {
        case Card::CardType::bomb:
            std::cout << "Playing bomb card..." << std::endl;

            // Display territories available for bombing
            index = 1;
            std::cout << "List of available territories to bomb: " << std::endl;
            for (Territory* canAttack : this->toAttack(map)) {
                std::cout << index++ << ". " << canAttack->getTerrName() << std::endl;
            }

            // Ask for territory to bomb
            std::cout << "Select territory to bomb: ";
            int territoryToAttackIndex;
            getValidatedInput(territoryToAttackIndex, 1, this->toAttack(map).size());
            territoryToAttack = this->toAttack(map).at(territoryToAttackIndex-1);

            // Create order and add to order list
            order = new Bomb(territoryToAttack->getOwner(), territoryToAttack);
            this->orderList->add(order);
            break;
        case Card::CardType::blockade:
            std::cout << "Playing blockade card..." << std::endl;

            // List owned territories
            index = 1;
            std::cout << "List of available territories to blockade: " << std::endl;
            for (Territory* canAttack : this->toDefend(map)) {
                std::cout << index++ << ". " << canAttack->getTerrName() << std::endl;
            }

            //Ask territory to blockade
            std::cout << "Select territory to blockade: ";
            int territoryToBlockadeIndex;
            getValidatedInput(territoryToBlockadeIndex, 1, this->toDefend(map).size());
            territoryToBlockade = this->toDefend(map).at(territoryToBlockadeIndex-1);

            order = new Blockade(this, territoryToBlockade, players);
            attachExistingObservers(order, this->orderList->getObservers());
            this->orderList->add(order);
            break;
        case Card::CardType::airlift:
            std::cout << "Playing airlift card..." << std::endl;

            // List owned territories
            index = 1;
            std::cout << "List of available territories owned: " << std::endl;
            for (Territory* canAttack : this->toDefend(map)) {
                std::cout << index++ << ". " << canAttack->getTerrName() << " (armies: " << canAttack->getNumberOfArmies() << ")" << std::endl;
            }

            // Ask source territory
            std::cout << "Select a territory to mobilize armies from: " << std::endl;
            int territoryFromIndex;
            getValidatedInput(territoryFromIndex, 1, this->toDefend(map).size());
            territoryFrom = this->toDefend(map).at(territoryFromIndex-1);

            // Ask destination territory
            std::cout << "Select a territory to mobilize armies to: " << std::endl;
            int territoryToIndex;
            getValidatedInput(territoryToIndex, 1, this->toDefend(map).size());
            territoryTo = this->toDefend(map).at(territoryToIndex-1);

            // Ask for number of armies to deploy
            std::cout << "Select the number of armies to deploy: ";
            int armiesToDeploy;
            getValidatedInput(armiesToDeploy, 1, territoryFrom->getNumberOfArmies());

            order = new Airlift(this, territoryFrom, territoryTo, armiesToDeploy);
            attachExistingObservers(order, this->orderList->getObservers());
            this->orderList->add(order);
            break;
        case Card::CardType::diplomacy:
            std::cout << "Playing diplomacy card..." << std::endl;

            // Display players in the game
            index = 0;
            for (Player* player: players) {
                std::cout << index++ << ". " << this->getName() << std::endl;
            }

            // Ask player to negotiate with
            std::cout << "Select player with whom to negotiate (cannot negotiate with oneself): ";
            int enemyIndex;
            getValidatedInput(enemyIndex, 1, players.size());
            enemy = players.at(enemyIndex-1);

            order = new Negotiate(this, enemy);
            attachExistingObservers(order, this->orderList->getObservers());
            this->orderList->add(order);
            break;
        case Card::CardType::reinforcement:
            std::cout << "Playing reinforcement card..." << std::endl;
            // Immediately adds 5 armies in the reinforcement pool
            this->armyPool += 5;
            this->hand->removeCard(card);
            break;
    }
    return order;
}

/**
 * Add observers to subject from the passed list of observers
 * @param subject
 * @param observerList
 */
void Player::attachExistingObservers(Subject *subject, const std::vector<Observer*>& observerList)
{
    for (Observer* observer: observerList)
        subject->attach(observer);
}

/**
 * Get the current strategy type object
 * @return
 */
PlayerStrategy::StrategyType Player::getStrategyType()
{
    return this->playerStrategy->getStrategy();
}

/**
 * Set the strategy type
 * @param strategyType
 */
void Player::setStrategyType(PlayerStrategy::StrategyType strategyType)
{
    this->playerStrategy->setStrategy(strategyType);
}

/**
 * Helper function to validate a choice in a given rance
 * @param choice Choice being selected
 * @param min Minimum value
 * @param max Maximum value
 */
void getValidatedInput(int& choice, int min, int max)
{
    while (choice < min or choice > max){
        if(!(std::cin >> choice)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\x1B[31m" << "Invalid input, try again: " << "\033[0m";
        } else if (choice < min or choice > max)
            std::cout << "\x1B[31m" << "Choice out of range, must be between " << min << ", and " << max << " : " << "\033[0m";
    }
}