#include "Record.h"

Record::Record(int r_id):
    _id(r_id),
    _copies(0),
    _buys(0),
    _stackHeight(0),
    _column(r_id) {}


Record::Record():
        _id(-1),
        _copies(0),
        _buys(0),
        _stackHeight(0),
        _column(-1) {}

int Record::id() const {
    return _id;
}

int Record::copies() const {
    return _copies;
}

int Record::buys() const {
    return _buys;
}
void Record::setColumn(int Column){
    _column = Column;
}
int Record::getColumn() const{
    return _column;
}

void Record::setCopies(int copies) {
    _copies = copies;
}

void Record::setHeight(int height) {
    _stackHeight = height;
}

int Record::getHeight() const{
    return _stackHeight;
}

void Record::zeroBuys() {
    _buys = 0;
}


void Record::buy() {
    _buys = _buys + 1;
}
