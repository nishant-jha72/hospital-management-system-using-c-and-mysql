#include "Patient.h"
#include <iostream>
#include <limits>
using namespace std;

int Patient::registration() {
    cout << "Welcome To The Hospital :- " << endl;

    string p_name, p_address, p_disease;
    int p_number;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Patient Name: "; getline(cin, p_name);
    cout << "Enter Patient Address: "; getline(cin, p_address);
    cout << "Enter Patient Phone Number: "; cin >> p_number;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Disease Name (If Emergency write Emergency): "; getline(cin, p_disease);

    string query = "INSERT INTO pt_list(p_name, p_address, p_phone_number, p_diesease) VALUES ('" +
                   p_name + "','" + p_address + "'," + to_string(p_number) + ",'" + p_disease + "')";
    if (mysql_query(conn, query.c_str())) {
        cout << "Error inserting patient: " << mysql_error(conn) << endl;
    } else {
        cout << "Data Inserted Successfully!" << endl;
    }

    int p_id = mysql_insert_id(conn);
    cout << "Patient ID is: " << p_id << " (Remember this for future use)" << endl;
    return p_id;
}

void Patient::view_patient_details(int p_id) {
    cout << "Patient Details: " << endl;
    show_patient(p_id);
}

void Patient::payBill() {
    int p_id;
    cout << "Enter Patient ID: "; cin >> p_id;
    pay_bill(p_id);
}

void Patient::book_appointment() {
    int doc_id, p_id;
    string date;
    cout << "Enter Doctor ID: "; cin >> doc_id;
    cout << "Enter Patient ID: "; cin >> p_id;
    cin.ignore();
    cout << "Enter Appointment Date (YYYY-MM-DD): "; getline(cin, date);

    string status = "pending";
    string query = "INSERT INTO appoint_table(doc_id, p_id, app_date, status) VALUES (" +
                   to_string(doc_id) + "," + to_string(p_id) + ",'" + date + "','" + status + "')";
    if (mysql_query(conn, query.c_str())) {
        cout << "Error booking appointment: " << mysql_error(conn) << endl;
    } else {
        cout << "Appointment booked successfully for " << date << endl;
        int app_id = mysql_insert_id(conn);
        cout << "Remember your Appointment ID: " << app_id << endl;
    }
}

void Patient::cancel_appointment() {
    cancel_appointement();
}

void Patient::reshudule_appointment(int app_id, string date) {
    string query = "UPDATE appoint_table SET app_date='" + date + "' WHERE app_id=" + to_string(app_id);
    if (mysql_query(conn, query.c_str())) {
        cout << "Error rescheduling appointment: " << mysql_error(conn) << endl;
    } else {
        cout << "Appointment rescheduled successfully" << endl;
    }
}

void Patient::view_disease(int p_id) {
    Admin::view_disease(p_id);
}

void Patient::give_rating_to_doctor() {
    int doc_id, rating;
    cout << "Enter Doctor ID: "; cin >> doc_id;
    cout << "Enter your Rating (1-5) for Doctor " << doc_id << ": "; cin >> rating;
    if (rating < 1 || rating > 5) { cout << "Invalid rating! Try again." << endl; return; }

    string query = "INSERT INTO rating_table(doc_id,rating) VALUES (" + to_string(doc_id) + "," + to_string(rating) + ")";
    if (mysql_query(conn, query.c_str())) cout << "Error submitting rating: " << mysql_error(conn) << endl;
    else cout << "Rating submitted successfully!" << endl;
}
