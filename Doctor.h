#ifndef DOCTOR_H
#define DOCTOR_H

#include "Admin.h"
#include <string>

class Doctor : protected Admin {
public:
    void doctors_request();
    void doc_details();
    void cancel_appointment();
    void patient_details();
    void show_patient_disease();
    void show_appointment();
};

#endif
