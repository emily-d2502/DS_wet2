#include "Customer.h"

Customer::Customer(int id, int phone):
    _id(id),
    _phone(phone),
    _member(false),
    _monthlyPayments(0) {}


int Customer::id() const {
    return _c_id;
}

bool Customer::member() const {
    return _member;
}


bool Customer::listen(Record* record) {
//    if (group.size() == 0 || (vip() && !group.vip())) {
//        return false;
//    }
//    group.watch(_genre);
//    _views += group.size();
//    return true;
}

void Customer::buy(Record* record) {
//    ++_number_of_ratings;
//    _tot_points += rating;
//    _rating = _tot_points / _number_of_ratings;
}

