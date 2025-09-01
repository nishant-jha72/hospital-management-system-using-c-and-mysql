#ifndef ADMIN_H
#define ADMIN_H

#include "HMS.h"
#include <string>

class Admin : protected HMS {
public:
    // Patient methods
    void show_patient_list();
    void show_patient(int p_id);
    void remove_patient(int p_id);
    int print_fee(int p_id);
    void pay_bill(int p_id);

    // Doctor methods
    void add_doctor();
    void remove_doctor(int doc_id);
    void doctors_info(int doc_id);

    // Appointments
    void check_appoint();
    void cancel_appointement();
    void reshudule_appointement(int app_id, string date);

    // Feedback
    void show_feedback();
    void show_feedback_personal(int doc_id);

    // View disease
    void view_disease(int p_id);
};

#endif
