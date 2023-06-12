
#include "Record.h"

Record::Record(int r_id):
    _r_id(r_id),
    _copies(0),
    _buys(0),
    _UF_node(nullptr) {}

int Record::id() const {
    return _r_id;
}

NodeUF<Record>* Record::node() {
    return _UF_node;
}


bool Record::listen(Record* record) {
//    if (group.size() == 0 || (vip() && !group.vip())) {
//        return false;
//    }
//    group.watch(_genre);
//    _views += group.size();
//    return true;
}

void Record::buy(Record* record) {
//    ++_number_of_ratings;
//    _tot_points += rating;
//    _rating = _tot_points / _number_of_ratings;
}
