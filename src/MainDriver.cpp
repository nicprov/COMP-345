#include "CardsDriver.cpp"
#include "GameEngineDriver.cpp"
#include "OrdersDriver.cpp"
#include "PlayerDriver.cpp"

int main(){
    cout << "Running Orders Driver" << endl;
    cout << "-----------------------" << endl;
    ordersDriver();
    cout << endl << endl << "Running Cards Driver" << endl;
    cout << "-----------------------" << endl;
    cardsDriver();
    cout << "Running Player Driver" << endl;
    cout << "-----------------------" << endl;
    PlayerDriver();
    cout << endl << endl << "Running Game Engine Driver" << endl;
    cout << "-----------------------" << endl;
    gameEngineDriver();
}