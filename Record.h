#ifndef RECORD_H
#define RECORD_H


#include "NodeUF.h"

class Record {
public:
    Record(int r_id);
    Record(const Record& other)            = default;
    Record& operator=(const Record& other) = default;
    ~Record()                              = default;

    int id() const;
    NodeUF<Record>* node();
    bool listen(Record* record);
    void buy(Record* record);

private:
    int _r_id;
    int _copies;
    int _buys;
    NodeUF<Record>* _UF_node;
};

#endif
