#include "CardsDriver.cpp"
#include "GameEngineDriver.cpp"
#include "OrdersDriver.cpp"

int main(){
    cout << "Running Cards Driver" << endl;
    cout << "-----------------------" << endl;
    cardsDriver();
    cout << endl << endl << "Running Game Engine Driver" << endl;
    cout << "-----------------------" << endl;
    gameEngineDriver();
    cout << endl << endl << "Running Orders Driver" << endl;
    cout << "-----------------------" << endl;
    ordersDriver();
}
