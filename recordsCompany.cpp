#include "recordsCompany.h"


RecordsCompany::RecordsCompany() :
        _customers(),
        _records(nullptr),
        _prizes(nullptr)
{}



RecordsCompany::~RecordsCompany() {

}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
    if (number_of_records < 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        for (int i = 0; i<number_of_records; i++)
        {
            _records = new UnionFind<Record>(number_of_records);
            Record * tmp = new Record(i);
            _records->Makeset(tmp);
        }
    } catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }

    _records->removeAllRecords();


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
        Customer &customer = _customers.find(c_id);
        return customer.phone();
    } catch (const HashTable<Customer>::KeyNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::makeMember(int c_id) {
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Customer &customer = _customers.find(c_id);
        if (!customer.member()) {
            return StatusType::ALREADY_EXISTS;
        }
        customer.make_member();
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
        Customer &customer = _customers.find(c_id);
        return customer.member();
    } catch (const HashTable<Customer>::KeyNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id) {
    if (c_id < 0 || r_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {

        Record* record = _records->ReturnObject(r_id);
        Customer customer = _customers.find(c_id);
        customer.buy(record);
        record->buy();
    } catch (const HashTable<Customer>::KeyNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    } catch (const Array<NodeUF<Record>*>::OutOfRange& e) {
        return StatusType::DOESNT_EXISTS;
    }

    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount) {
    if (c_id1 < 0 || c_id2 < c_id1 || amount <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        _prizes->insert(c_id1-1);
    } catch (const Tree<int>::KeyExists& e) {}
    try {
        _prizes->insert(c_id2);
    } catch (const Tree<int>::KeyExists& e) {}
    _prizes->add(c_id2,amount);
    _prizes->add(c_id1-1,-amount);

    return StatusType::SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id) {
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Customer &customer = _customers.find(c_id);
        return customer.monthlyExpanses();
    } catch (const HashTable<Customer>::KeyNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2) {
    if (r_id1 < 0 || r_id2 < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Record* B = _records->Find(r_id1);
        Record* A = _records->Find(r_id2);
        if (A == B)
            return StatusType::FAILURE;
        _records->stackBonA(A,B);
    } catch (const Array<NodeUF<Record>*>::OutOfRange& e) {
        return StatusType::DOESNT_EXISTS;
    }
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight) {
    if (r_id < 0 || hight == nullptr || column == nullptr) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Record* record = _records->ReturnObject(r_id);
        *hight = _records->SumHeight(record) - record->copies();
        Record* headStack = _records->Find(r_id);
        *column = headStack->UF_Node()->_column;
    } catch (const Array<NodeUF<Record>*>::OutOfRange& e) {
        return StatusType::DOESNT_EXISTS;
    }
    return StatusType::SUCCESS;
}
