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
    void make_member();
    bool member() const;
//    bool listen(Record* record);
    void buy(Record* record);
    static void zeroMonthlyPayments(Customer& c);
    void zeroExpanses();
    double monthlyExpanses();
    void setMonthlyExpanses(double num);




private:
    int _id;
    int _phone;
    bool _member;
    double _monthlyPayments;
};

#endif // CUSTOMER_H
