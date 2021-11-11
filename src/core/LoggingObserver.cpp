#include "LoggingObserver.h"
#include <iostream>
#include <fstream>


ILoggable::ILoggable() {};
ILoggable::~ILoggable() {};

Observer::Observer(){
};
Observer::~Observer(){
};

LogObserver::LogObserver(){

};

LogObserver::LogObserver(Subject* s) {
    _subject = s;
    _subject->Attach(this);
};

LogObserver::~LogObserver() {
    _subject->Detach(this);
};

void LogObserver::Update(ILoggable* I) {
    std::ofstream file("gamelog.txt", std::ofstream::out | std::ofstream::app);
    if(file.is_open()){
        std::string logOut= _subject->stringToLog();
        file << logOut << std::endl;
    }

};

Subject::Subject(){
    _observers = new std::vector<Observer*>;
}
Subject::~Subject(){
    delete _observers;
}
void Subject::Attach(Observer* o){
    _observers->push_back(o);
};
void Subject::Detach(Observer* o){
    int count = 0;
    for(Observer* observer : *_observers){
        if(observer == o){
            _observers->erase(_observers->begin()+count);
            break;
        }
        count++;
    }
};

void Subject::Notify(ILoggable* i){
   std::vector<Observer *>::iterator l = _observers->begin();
   for (; l != _observers->end(); ++l)
      (*l)->Update(i);
};
