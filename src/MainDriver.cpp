#include "CardsDriver.cpp"
#include "GameEngineDriver.cpp"
#include "OrdersDriver.cpp"
#include "PlayerDriver.cpp"
#include "MapDriver.cpp"

int main(){
    cout << "Running Map Driver" << endl;
    cout << "-----------------------" << endl;
  //  mapDriver();
    cout << endl << endl << "Running Player Driver" << endl;
    cout << "-----------------------" << endl;
    PlayerDriver();
    cout << endl << endl << "Running Orders Driver" << endl;
    cout << "-----------------------" << endl;
    ordersDriver();
    cout << endl << endl << "Running Cards Driver" << endl;
    cout << "-----------------------" << endl;
    cardsDriver();
    cout << endl << endl << "Running Game Engine Driver" << endl;
    cout << "-----------------------" << endl;
  //  gameEngineDriver();
}