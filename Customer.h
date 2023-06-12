

#ifndef Customer_H_
#define Customer_H_

#include "Record.h"



class Customer {
public:
    Customer(int c_id, int _phone);
    Customer()                              = default;
    Customer(const Customer& other)            = default;
    Customer& operator=(const Customer& other) = default;
    ~Customer()                             = default;

    int id() const;
    bool member() const;
    bool listen(Record* record);
    void buy(Record* record);

private:
    int _c_id;
    int _phone;
    bool _member;
    int _monthlyPayments;
};

#endif