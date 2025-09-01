#include "Admin.h"
#include <thread>
#include <chrono>
#include <cstdlib>
#include <limits>

// ==================== Patient Methods ====================
void Admin::show_patient_list() {
    string query = "SELECT * FROM pt_list";
    if (mysql_query(conn, query.c_str())) {
        cout << "Failed To Retrieve Patient List: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row;
    if (!res) {
        cout << "Error fetching results: " << mysql_error(conn) << endl;
        return;
    }
    while ((row = mysql_fetch_row(res))) {
        cout << "PATIENT ID: " << row[0] << " | NAME: " << row[1] << " | FEE: " << row[2] << endl;
    }
    mysql_free_result(res);
}

void Admin::show_patient(int p_id) {
    string query = "SELECT * FROM pt_list WHERE p_id = " + to_string(p_id);
    if (mysql_query(conn, query.c_str())) {
        cout << "Error retrieving patient: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row;
    if (!res) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }
    while ((row = mysql_fetch_row(res))) {
        cout << "PATIENT ID: " << row[0] << " | NAME: " << row[1] << " | FEE: " << row[2] << endl;
    }
    mysql_free_result(res);
}

void Admin::remove_patient(int p_id) {
    string query = "DELETE FROM pt_list WHERE p_id = " + to_string(p_id);
    if (mysql_query(conn, query.c_str())) {
        cout << "Error removing patient: " << mysql_error(conn) << endl;
    } else {
        cout << "Patient deleted successfully" << endl;
    }
    this_thread::sleep_for(chrono::seconds(2));
}

int Admin::print_fee(int p_id) {
    string query = "SELECT SUM(p_fee_unpaid) FROM pt_fee_details WHERE p_id = " + to_string(p_id);
    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    int fee = 0;
    if (row && row[0]) fee = stoi(row[0]);
    mysql_free_result(res);
    return fee;
}

void Admin::pay_bill(int p_id) {
    int fee = print_fee(p_id);
    cout << "Enter Amount to pay: ";
    int paybill;
    cin >> paybill;

    string query;
    if (paybill >= fee)
        query = "UPDATE pt_fee_details SET p_fee_unpaid = 0 WHERE p_id = " + to_string(p_id);
    else
        query = "UPDATE pt_fee_details SET p_fee_unpaid = " + to_string(fee - paybill) + " WHERE p_id = " + to_string(p_id);

    if (mysql_query(conn, query.c_str())) {
        cout << "Error updating fee: " << mysql_error(conn) << endl;
    } else {
        cout << "Payment successful!" << endl;
    }
}

// ==================== Doctor Methods ====================
void Admin::add_doctor() {
    string name, spec;
    int salary;
    long long phone;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Doctor Name: "; getline(cin, name);
    cout << "Enter Specialization: "; getline(cin, spec);
    cout << "Enter Salary: "; cin >> salary;
    cout << "Enter Phone: "; cin >> phone;

    string query = "INSERT INTO doc_details(doc_name, doc_spec, doc_sal, doc_phonr) VALUES('" + name + "','" + spec + "'," + to_string(salary) + "," + to_string(phone) + ")";
    if (mysql_query(conn, query.c_str())) cout << "Error: " << mysql_error(conn) << endl;
    else cout << "Doctor added successfully!" << endl;
}

void Admin::remove_doctor(int doc_id) {
    string query = "DELETE FROM doc_details WHERE id = " + to_string(doc_id);
    if (mysql_query(conn, query.c_str())) cout << "Error: " << mysql_error(conn) << endl;
    else cout << "Doctor removed successfully!" << endl;
}

void Admin::doctors_info(int doc_id) {
    string query = "SELECT * FROM doc_details WHERE id = " + to_string(doc_id);
    if (mysql_query(conn, query.c_str())) {
        cout << "Error fetching doctor info: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        cout << "ID: " << row[0] << " | Name: " << row[1] << " | Spec: " << row[2] << " | Salary: " << row[3] << " | Phone: " << row[4] << endl;
    } else {
        cout << "Doctor not found." << endl;
    }
    mysql_free_result(res);
}

// ==================== Appointments ====================
void Admin::check_appoint() {
    string query = "SELECT * FROM appoint_table WHERE status='pending'";
    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        cout << "AppID: " << row[0] << " | DocID: " << row[1] << " | PatientID: " << row[2] << " | Date: " << row[3] << " | Status: " << row[4] << endl;
    }
    mysql_free_result(res);
}

void Admin::cancel_appointement() {
    cout << "Enter Appointment ID: ";
    int app_id; cin >> app_id;
    string query = "UPDATE appoint_table SET status='canceled' WHERE app_id=" + to_string(app_id);
    if (mysql_query(conn, query.c_str())) cout << "Error: " << mysql_error(conn) << endl;
    else cout << "Appointment canceled successfully" << endl;
}

void Admin::reshudule_appointement(int app_id, string date) {
    string query = "UPDATE appoint_table SET app_date='" + date + "' WHERE app_id=" + to_string(app_id);
    if (mysql_query(conn, query.c_str())) cout << "Error: " << mysql_error(conn) << endl;
    else cout << "Appointment rescheduled successfully" << endl;
}

// ==================== Feedback ====================
void Admin::show_feedback() {
    string query = "SELECT doc_name, p_feedback, ratings FROM feedback";
    if (mysql_query(conn, query.c_str())) { cout << "Error: " << mysql_error(conn) << endl; return; }

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        cout << "Doctor: " << row[0] << " | Feedback: " << row[1] << " | Ratings: " << row[2] << endl;
    }
    mysql_free_result(res);
}

void Admin::show_feedback_personal(int doc_id) {
    string query = "SELECT p_feedback FROM feedback WHERE doc_id=" + to_string(doc_id);
    if (mysql_query(conn, query.c_str())) { cout << "Error: " << mysql_error(conn) << endl; return; }

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "Feedback for Doctor ID: " << doc_id << endl;
    while ((row = mysql_fetch_row(res))) {
        cout << row[0] << endl;
    }
    mysql_free_result(res);
}

// ==================== View disease ====================
void Admin::view_disease(int p_id) {
    string query = "SELECT p_diesease FROM pt_list WHERE p_id=" + to_string(p_id);
    if (mysql_query(conn, query.c_str())) { cout << "Error: " << mysql_error(conn) << endl; return; }

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row && row[0]) cout << "Disease: " << row[0] << endl;
    mysql_free_result(res);
}

