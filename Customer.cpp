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



//bool Customer::listen(Record* record) {
////    if (group.size() == 0 || (vip() && !group.vip())) {
////        return false;
////    }
////    group.watch(_genre);
////    _views += group.size();
////    return true;
//}


 void Customer::zeroMonthlyPayments(Customer& c) {
    c.zeroExpanses();
}

void Customer::zeroExpanses(){
    _monthlyPayments = 0;
}

double Customer::monthlyExpanses() {
    return _monthlyPayments;
}



void Customer::buy(Record* record) {
    if (this->member())
    {
        this->_monthlyPayments += 100 + record->buys();
    }
}

