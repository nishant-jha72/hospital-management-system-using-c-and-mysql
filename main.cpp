#include <iostream>
#include <limits>
#include "HMS.h"
#include "Admin.h"
#include "Patient.h"
#include "Doctor.h"

using namespace std;

int main() {
    HMS hs; // Initialize DB connection
    Admin admin;
    Patient patient;
    Doctor doctor;

    int mainChoice = 0;

    do {
        cout << "\n==================== HOSPITAL MANAGEMENT SYSTEM ====================\n";
        cout << "Select User Type:\n";
        cout << "1. Admin\n";
        cout << "2. Doctor\n";
        cout << "3. Patient\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

        switch(mainChoice) {
            case 1: { // Admin Menu
                int adminChoice = 0;
                do {
                    cout << "\n------------------- ADMIN MENU -------------------\n";
                    cout << "1. Show All Patients\n";
                    cout << "2. Show Feedback\n";
                    cout << "3. Add Doctor\n";
                    cout << "4. Remove Doctor\n";
                    cout << "5. Show Patient By ID\n";
                    cout << "6. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> adminChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch(adminChoice) {
                        case 1: admin.show_patient_list(); break;
                        case 2: admin.show_feedback(); break;
                        case 3: admin.add_doctor(); break;
                        case 4: {
                            int doc_id;
                            cout << "Enter Doctor ID to remove: ";
                            cin >> doc_id;
                            admin.remove_doctor(doc_id);
                            break;
                        }
                        case 5: {
                            int p_id;
                            cout << "Enter Patient ID: ";
                            cin >> p_id;
                            admin.show_patient(p_id);
                            break;
                        }
                        case 6: break;
                        default: cout << "Invalid choice! Try again.\n";
                    }

                } while(adminChoice != 6);
                break;
            }

            case 2: { // Doctor Menu
                int docChoice = 0;
                do {
                    cout << "\n------------------- DOCTOR MENU -------------------\n";
                    cout << "1. Show Appointments\n";
                    cout << "2. View Patient Details\n";
                    cout << "3. Give Feedback About Hospital\n";
                    cout << "4. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> docChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch(docChoice) {
                        case 1: doctor.show_appointment(); break;
                        case 2: doctor.patient_details(); break;
                        case 3: doctor.doctors_request(); break;
                        case 4: break;
                        default: cout << "Invalid choice! Try again.\n";
                    }

                } while(docChoice != 4);
                break;
            }

            case 3: { // Patient Menu
                int patChoice = 0;
                do {
                    cout << "\n------------------- PATIENT MENU -------------------\n";
                    cout << "1. Register\n";
                    cout << "2. View My Details\n";
                    cout << "3. Pay Bill\n";
                    cout << "4. Book Appointment\n";
                    cout << "5. Cancel Appointment\n";
                    cout << "6. Reschedule Appointment\n";
                    cout << "7. View Disease Info\n";
                    cout << "8. Give Rating to Doctor\n";
                    cout << "9. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> patChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch(patChoice) {
                        case 1: patient.registration(); break;
                        case 2: {
                            int p_id;
                            cout << "Enter Your Patient ID: ";
                            cin >> p_id;
                            patient.view_patient_details(p_id);
                            break;
                        }
                        case 3: patient.payBill(); break;
                        case 4: patient.book_appointment(); break;
                        case 5: patient.cancel_appointment(); break;
                        case 6: {
                            int app_id;
                            string date;
                            cout << "Enter Appointment ID: ";
                            cin >> app_id;
                            cin.ignore();
                            cout << "Enter New Date (YYYY-MM-DD): ";
                            getline(cin, date);
                            patient.reshudule_appointment(app_id, date);
                            break;
                        }
                        case 7: {
                            int p_id;
                            cout << "Enter Patient ID: ";
                            cin >> p_id;
                            patient.view_disease(p_id);
                            break;
                        }
                        case 8: patient.give_rating_to_doctor(); break;
                        case 9: break;
                        default: cout << "Invalid choice! Try again.\n";
                    }

                } while(patChoice != 9);
                break;
            }

            case 4: 
                cout << "Exiting system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please select 1-4." << endl;
        }

    } while(mainChoice != 4);

    return 0;
}
