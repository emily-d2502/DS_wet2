#include "recordsCompany.h"

RecordsCompany::RecordsCompany() {

}

RecordsCompany::~RecordsCompany() {

}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
    if (number_of_records < 0) {
        return StatusType::INVALID_INPUT;
    }

    // reset records order
    // reset expenses for costumers
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

    } catch (int e) {
        return StatusType::ALREADY_EXISTS;
    }
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount) {
    if (c_id1 < 0 || c_id2 < 0 || amount <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {

    } catch (int e) {
        return StatusType::ALREADY_EXISTS;
    }
    return StatusType::SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id) {
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Customer &customer = _customers.find(c_id);

    } catch (const HashTable<Customer>::KeyNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2) {
    if (r_id1 < 0 || r_id2 < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {

    } catch (int e) {
        return StatusType::ALREADY_EXISTS;
    }
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight) {
    if (r_id < 0 || hight == nullptr || column == nullptr) {
        return StatusType::INVALID_INPUT;
    }

    try {

    } catch (int e) {
        return StatusType::ALREADY_EXISTS;
    }
    return StatusType::SUCCESS;
}
