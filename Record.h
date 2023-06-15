#ifndef RECORD_H
#define RECORD_H


#include "NodeUF.h"

class Record {
public:
    explicit Record(int r_id);
    Record(const Record& other)            = default;
    Record& operator=(const Record& other) = default;
    ~Record()                              = default;

    int id() const;
    int copies() const;
    int buys() const;


    NodeUF<Record>* UF_Node() const;

    void setNode(NodeUF<Record>* UFnode);
    bool listen(Record* record);
    void buy();
    void zeroBuys();


private:
    int _id;
    int _copies;
    int _buys;
    NodeUF<Record>* UF_node;
};

#endif
