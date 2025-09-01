Overview

This is a Hospital Management System (HMS) project developed in C++ with MySQL integration. The system is designed to manage hospital operations including doctor management, appointments, patient records, and feedback.
#Day 3
Progress Made Today
1. File Organization

All project files have been categorized and organized into a single folder named hospital_management.

Separated classes into respective .cpp and .h files for better modularity:

HMS – base class for MySQL connection.

Admin – admin functionalities (show patient list, manage doctors, view feedback).

Doctor – fully implemented today, handles:

Viewing appointments.

Viewing patient details.

Submitting feedback about the hospital.

Placeholder structure created for Patient class (to be implemented next).

2. Doctor Class Implementation

Methods added:

show_appointment() – view all appointments assigned to the doctor.

patient_details() – view details of a specific patient.

doctors_request() – submit feedback about the hospital.

Integrated MySQL queries inside class methods for fetching and updating data.

Applied input validation for feedback length.

3. MySQL Integration

Connected Doctor class methods with database tables:

appoint_table – appointment records.

pt_list – patient details.

feedback_hospital – doctor’s feedback about the hospital.

4. Notes

All methods are tested for successful database connection and query execution.

The Doctor class is ready to be used in the main menu along with Admin and Patient options.

Input/output handled using cin/cout and MySQL results with MYSQL_RES and MYSQL_ROW.

And All Major Work Is Doned Here You can Find Main file In Code Section Or read a Full View And Final Readme File For THat 




Thank you 


==========Nishant Jha ==============================
