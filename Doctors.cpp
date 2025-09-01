#include "Doctor.h"
#include <iostream>
using namespace std;

void Doctor::doctors_request() {
    int doc_id; string feedback;
    cout << "Enter Your Doctor ID: "; cin >> doc_id;
    cin.ignore();
    cout << "Enter Your Feedback About Hospital (max 1000 chars): "; getline(cin, feedback);

    if (feedback.empty() || feedback.size() > 1000) {
        cout << "Invalid feedback length!" << endl; return;
    }

    string safe_feedback;
    for (char c : feedback) safe_feedback += (c == '\'') ? "\\'" : string(1, c);

    string query = "INSERT INTO feedback_hospital(doc_id,feedback) VALUES (" + to_string(doc_id) + ",'" + safe_feedback + "')";
    if (mysql_query(conn, query.c_str())) cout << "Error submitting feedback: " << mysql_error(conn) << endl;
    else cout << "Feedback submitted successfully!" << endl;
}

void Doctor::doc_details() {
    int doc_id;
    cout << "Enter Doctor ID: "; cin >> doc_id;
    doctors_info(doc_id);
}

void Doctor::cancel_appointment() {
    Admin::cancel_appointement();
}

void Doctor::patient_details() {
    int p_id;
    cout << "Enter Patient ID: "; cin >> p_id;
    show_patient(p_id);
}

void Doctor::show_patient_disease() {
    int p_id;
    cout << "Enter Patient ID: "; cin >> p_id;
    view_disease(p_id);
}
void Doctor::show_appointment() {
    int doc_id;
    cout << "Enter Doctor ID: "; 
    cin >> doc_id;

    string query = "SELECT app_id, p_id, app_date FROM appoint_table WHERE doc_id = " + to_string(doc_id);

    if(mysql_query(conn, query.c_str())){
        cout << "Error in Doctor::show_appointment: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if(!res){
        cout << "No appointments found or error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_ROW row;
    cout << "Appointments for Doctor ID " << doc_id << ":\n";
    cout << "---------------------------------------\n";
    while((row = mysql_fetch_row(res))){
        cout << "Appointment ID: " << row[0] 
             << " | Patient ID: " << row[1] 
             << " | Date: " << row[2] << endl;
    }

    mysql_free_result(res);
}


