#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Record.h"

class Customer {
public:
    Customer(int id, int phone);
    Customer(const Customer& other)             = default;
    Customer& operator=(const Customer& other)  = default;
    ~Customer()                                 = default;

    int id() const;
    int phone() const;
    bool make_member();
    bool member() const;
    bool listen(Record* record);
    void buy(Record* record);
    void zeroMonthlyPayments();

private:
    int _id;
    int _phone;
    bool _member;
    int _monthlyPayments;
};

#endif // CUSTOMER_H
