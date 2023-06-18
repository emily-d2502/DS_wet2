#include "Customer.h"

Customer::Customer(int id, int phone):
    _id(id),
    _phone(phone),
    _member(false),
    _monthlyPayments(0) {}


int Customer::id() const {
    return _id;
}

int Customer::phone() const {
    return _phone;
}

bool Customer::member() const {
    return _member;
}

void Customer::make_member(){
    _member = true;
}

 void Customer::zeroMonthlyPayments(Customer& c) {
    c.zeroExpanses();
}

void Customer::zeroExpanses(){
    _monthlyPayments = 0;
}

double Customer::monthlyExpanses() {
    return _monthlyPayments;
}

void Customer::setMonthlyExpanses(double num){
    _monthlyPayments = num;
}

void Customer::buy(Record* record) {
    if (this->member()) {
        this->_monthlyPayments += 100 + record->buys();
    }
}

