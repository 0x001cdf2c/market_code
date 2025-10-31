#ifndef PAYMENT_H
#define PAYMENT_H

#include "common/Date.h"
#include <string>

class Payment {
private:
    std::string paymentId;
    double amount;
    Date paymentDate;
    std::string status;

public:
    Payment(double amount);
    
    bool processPayment();
    bool refund();
    
    std::string getPaymentId() const { return paymentId; }
    double getAmount() const { return amount; }
    std::string getStatus() const { return status; }
};

#endif