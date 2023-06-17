#include "recordsCompany.h"


RecordsCompany::RecordsCompany() :
        _records(nullptr),
        _customers(),
        _prizes(nullptr)
{}



RecordsCompany::~RecordsCompany() {

}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
    if (number_of_records < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        if(_records)
        {
            delete _records;
        }
        _records = new UnionFind<Record>(number_of_records);
        for (int i = 0; i<number_of_records; i++)
        {
            Record* tmp = new Record(i);
            tmp->setCopies(records_stocks[i]);
            tmp->setHeight(records_stocks[i]);
            _records->MakeSet(i, tmp);
        }


    } catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }

    _customers.apply(Customer::zeroMonthlyPayments);

    if(_prizes)
    {
        delete _prizes;
    }
    _prizes = new Tree<int>;

    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone) {
    if (c_id < 0 || phone < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Customer *customer = new Customer(c_id, phone);
        _customers.insert(c_id, customer);
    } catch (const HashTable<Customer>::KeyExists& e) {
        return StatusType::ALREADY_EXISTS;
    } catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id) {
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Customer * customer = _customers.find(c_id);
        return customer->phone();
    } catch (const HashTable<Customer>::KeyNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::makeMember(int c_id) {
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Customer * customer = _customers.find(c_id);
        if (customer->member()) {
            return StatusType::ALREADY_EXISTS;
        }
        _prizes->insert(c_id);
        double debt = _prizes->prizeSum(c_id);
        customer->setMonthlyExpanses(customer->monthlyExpanses()+debt);
        customer->make_member();
//        int i = 0;
    } catch (const HashTable<Customer>::KeyNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    }
    return StatusType::SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id) {
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Customer * customer = _customers.find(c_id);
        return customer->member();
    } catch (const HashTable<Customer>::KeyNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id) {
    if (c_id < 0 || r_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Record record = _records->ReturnObject(r_id);
        Customer * customer = _customers.find(c_id);
        customer->buy(&record);
        record.buy();
    } catch (const HashTable<Customer>::KeyNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    } catch (const Array<Record>::OutOfRange& e) {
        return StatusType::DOESNT_EXISTS;
    }

    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount) {
    if (c_id1 < 0 || c_id2 < c_id1 || amount <= 0) {
        return StatusType::INVALID_INPUT;
    }
    _prizes->add(c_id2,amount);
    _prizes->add(c_id1-1,-amount);

    return StatusType::SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id) {
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Customer *customer = _customers.find(c_id);
        if (!customer->member())
            return StatusType::DOESNT_EXISTS;
        return customer->monthlyExpanses() - _prizes->prizeSum(c_id);
    } catch (const HashTable<Customer>::KeyNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2) {
    if (r_id1 < 0 || r_id2 < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        int B = _records->Find(r_id1);
        int A = _records->Find(r_id2);
        if (A == B)
            return StatusType::FAILURE;
        _records->stackBonA(A,B);
    } catch (const Array<Record>::OutOfRange& e) {
        return StatusType::DOESNT_EXISTS;
    }
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight) {
    if (r_id < 0 || hight == nullptr || column == nullptr) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Record tmp = _records->ReturnObject(r_id);
        *hight = _records->SumHeight(r_id) - tmp.copies();

        int headStack = _records->Find(r_id);
        Record tmp2 = _records->ReturnObject(headStack);
        *column = tmp2.getColumn();
    } catch (const Array<Record>::OutOfRange& e) {
        return StatusType::DOESNT_EXISTS;
    }
    return StatusType::SUCCESS;
}
