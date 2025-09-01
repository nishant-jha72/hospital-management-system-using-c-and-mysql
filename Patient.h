#ifndef PATIENT_H
#define PATIENT_H

#include "Admin.h"
#include <string>

class Patient : protected Admin {
public:
    int registration();
    void view_patient_details(int p_id);
    void payBill();
    void book_appointment();
    void cancel_appointment();
    void reshudule_appointment(int app_id, std::string date);
    void view_disease(int p_id);
    void give_rating_to_doctor();
};

#endif
