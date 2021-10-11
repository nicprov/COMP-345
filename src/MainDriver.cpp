#include "CardsDriver.cpp"
#include "GameEngineDriver.cpp"
#include "OrdersDriver.cpp"

int main(){
    cout << "Running Orders Driver" << endl;
    cout << "-----------------------" << endl;
    ordersDriver();
    cout << endl << endl << "Running Cards Driver" << endl;
    cout << "-----------------------" << endl;
    cardsDriver();
    cout << endl << endl << "Running Game Engine Driver" << endl;
    cout << "-----------------------" << endl;
    gameEngineDriver();
}