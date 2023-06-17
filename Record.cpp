#include "Record.h"

Record::Record(int r_id):
    _id(r_id),
    _copies(0),
    _buys(0),
    UF_node(nullptr) {}

int Record::id() const {
    return _id;
}

int Record::copies() const {
    return _copies;
}

int Record::buys() const {
    return _buys;
}

NodeUF<Record>* Record::UF_Node() const {
    return UF_node;
}

void Record::setNode(NodeUF<Record>* UFnode) {
    UF_node = UFnode;
}


//bool Record::listen(Record* record) {
////    if (group.size() == 0 || (vip() && !group.vip())) {
////        return false;
////    }
////    group.watch(_genre);
////    _views += group.size();
////    return true;
//}

void Record::zeroBuys() {
    _buys = 0;
}


void Record::buy() {
    _buys++;
}
