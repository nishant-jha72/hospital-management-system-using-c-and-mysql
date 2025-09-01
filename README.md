🏥 Hospital Management System (HMS)

Author: Nishant Jha
Language: C++
Database: MySQL
Libraries: mysqlclient, pthread

🌟 Project Overview

The Hospital Management System (HMS) is a comprehensive C++ project integrated with MySQL to efficiently manage hospital operations. This system is designed for admins, doctors, and patients to interact with hospital records, appointments, billing, and feedback.

It supports:

1. Patient Management: Registration, viewing patient details, diseases, and billing.

2. Doctor Management: Viewing appointments, patient information, and submitting hospital feedback.

3. Admin Management: Managing doctors, viewing feedback, and overseeing hospital data.

This project uses object-oriented programming (OOP) principles with inheritance, encapsulation, and modular design.

🗂️ File Organization

All project files are organized inside the folder: hospital_management.
Classes are separated into different files for modularity:

Class/File	Description
1. HMS	Base class to handle MySQL database connection.
2. Admin	Handles admin functionalities: adding/removing doctors, viewing patients, viewing feedback.
3. Doctor	Handles doctor functionalities: viewing appointments, patient details, submitting feedback.
4. Patient	Handles patient functionalities: registration, booking appointments, paying bills, giving ratings.
5. main.cpp	Main menu and entry point of the program. Integrates Admin, Doctor, and Patient functionalities.
🏗️ Classes & Methods
1️⃣ HMS Class

Handles database connectivity using MySQL:

Constructor: Connects to MySQL server and database.
```
HMS() {
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "cppuser", "Nishant@123", "hsm", 0, NULL, 0);
}
```
2️⃣ Admin Class (inherits HMS)

Handles admin operations:
```
show_patient_list() – Display all patients.

show_patient(int p_id) – Display a specific patient’s details.

show_feedback() – Display all doctor feedback.

show_feedback_personal(int doc_id) – Display feedback for a specific doctor.

add_doctor() – Add a new doctor to the system.

remove_doctor(int doc_id) – Remove a doctor by ID.

remove_patient(int p_id) – Remove a patient by ID.

print_fee(int p_id) – Print total unpaid fees for a patient.

pay_bill(int p_id) – Pay a patient’s bill.

check_appoint() – View all pending appointments.

cancel_appointement() – Cancel an appointment.

doctors_info(int doc_id) – View doctor details.
```

3️⃣ Doctor Class (inherits Admin)
```
Handles doctor-specific operations:

show_appointment() – View all appointments for the doctor.

patient_details() – View a patient’s full details.

doctors_request() – Submit feedback about the hospital.

Example: Show appointments for a doctor
```
```
void Doctor::show_appointment() {
    int doc_id;
    cout << "Enter Doctor ID: "; 
    cin >> doc_id;
    string query = "SELECT app_id, p_id, app_date FROM appoint_table WHERE doc_id = " + to_string(doc_id);
    MYSQL_RES *res;
    MYSQL_ROW row;
    res = mysql_store_result(conn);
    while ((row = mysql_fetch_row(res))) {
        cout << "Appointment Id:- " << row[0] << endl;
        cout << "Patient Id:- " << row[1] << endl;
        cout << "Appointment Date:- " << row[2] << endl;
    }
}
```
4️⃣ Patient Class (inherits Admin)
```
Handles patient-specific operations:

registration() – Register a new patient and assign a patient ID.

view_patient_details(int p_id) – View patient details.

payBill() – Pay patient fees.

book_appointment() – Book an appointment with a doctor.

cancel_appointement_patient() – Cancel an appointment.

reshudule_appointement(int app_id, string date) – Reschedule appointment.

view_disease(int p_id) – View patient’s disease details.

give_rating_to_doctor() – Give rating to a doctor.
```
Example: Patient registration
```
int registration() {
    cout << "Enter Patient Name: ";
    string p_name;
    getline(cin, p_name);
    string query = "INSERT INTO pt_list(p_name, p_address, p_phone_number, p_diesease) VALUES ('" + p_name + "', ...)";
    mysql_query(conn, query.c_str());
    int p_id = mysql_insert_id(conn);
    return p_id;
}
```
🧾 Database Schema
```
1. pt_list – Patient Details

Column	Type	Key	Extra
p_id	int	PK	auto_increment
p_name	varchar(100)		
p_address	varchar(1000)		
p_phone_number	int		
p_disease	varchar(100)		
```
```
2. pt_fee_details – Patient Billing

Column	Type	Key	Extra
p_id	int		
p_fee_unpaid	int		
p_fee_paid	int		
```
3. doc_details – Doctor Information
```
Column	Type	Key	Extra
id	int	PK	auto_increment
doc_name	varchar(100)		
doc_spec	enum('patho','dentist','gynac','psycho','other')		
doc_sal	int		
doc_phonr	int		
```
4. appoint_table – Appointments
```
Column	Type	Key	Extra
app_id	int	PK	auto_increment
doc_id	int		
p_id	int		
app_date	date		
status	enum('Done','pending','canceled')		
```
5. feedback – Doctor Feedback
```
Column	Type	Key	Extra
doc_name	varchar(100)		
p_name	varchar(100)		
p_feedback	varchar(1000)		
ratings	enum('1','2','3','4','5')		
doc_id	int
```
🎯 Features Implemented

Modular OOP design using HMS → Admin → Doctor/Patient hierarchy.

Full MySQL integration for storing and retrieving data.

Doctor functionalities fully implemented today:

Viewing appointments

Viewing patient details

Sending feedback to the hospital

Input validation for ratings and feedback length.

Database queries are safe from basic syntax errors with string handling.

🚀 Next Steps

```

g++ main.cpp HMS.cpp Admin.cpp Doctor.cpp Patient.cpp -o hms -lmysqlclient -pthread
```

Run the executable:
```
./hms
```

Note: Ensure MySQL server is running and the database credentials are correct.

📌 Credits

Developed by Nishant Jha as a major project for C++ and MySQL integration.

