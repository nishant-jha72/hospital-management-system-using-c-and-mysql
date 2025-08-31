# Day 2

Today we have Created an Admin Class and Write their Functionality 

Following Method is Described On the ADmin class
```
  1 . ADd doctor
  2. Remove Doctor
  3. Pay Bill of Patient 
  4. View Patient Record
  5. view Feedback For Doctor 
  6. Remove Patient From List 
  7. show Bill of Patient
```

#Admin Class :-
```
class Admin : protected HMS
{
public:
    // show all Patients List
    void show_patient_list()
    {
        string query = "SELECT * FROM pt_list";
        if (mysql_query(conn, query.c_str()))
        {
            cout << "Failed To Retrive The Patient List" << mysql_error(conn) << endl;
        }
        else
        {
            cout << "Data Fetched Succesfully" << endl;
        }
        MYSQL_RES *res;
        MYSQL_ROW row;

        res = (mysql_store_result(conn));
        if (!res)
        {
            cout << "Error caused at Line 44 " << mysql_error(conn) << endl;
            return;
        }
        else
        {
            cout << "Data Fetched SuccesFully" << endl;
        }
        while ((row = mysql_fetch_row(res)))
        {
            cout << "PATIENT ID :- " << row[0] << "||  PATIENT NAME :- " << row[1] << " || FEE  = " << row[2] << endl;
        }
        mysql_free_result(res);
    }
```
#show PAtient :-
```
    void show_patient(int p_id)
    {
        string query = "SELECT * FROM pt_list WHERE p_id = " + to_string(p_id);
        if (mysql_query(conn, query.c_str()))
        {
            cout << "Failed To Retrive The Patient List" << mysql_error(conn) << endl;
        }
        else
        {
            cout << "Data Fetched Succesfully" << endl;
        }
        MYSQL_RES *res;
        MYSQL_ROW row;

        res = (mysql_store_result(conn));
        if (!res)
        {
            cout << "Error caused at Line 44 " << mysql_error(conn) << endl;
            return;
        }
        else
        {
            cout << "Data Fetched SuccesFully" << endl;
        }
        while ((row = mysql_fetch_row(res)))
        {
            cout << "PATIENT ID :- " << row[0] << "||  PATIENT NAME :- " << row[1] << " || FEE  = " << row[2] << endl;
        }
        mysql_free_result(res);
    }
```
#feedback Method 
```
    // show all feedback For doctor given By customer
    void show_feedback()
    {
        string query = "SELECT doc_name , p_feedback, ratings FROM feedback";
        if (mysql_query(conn, query.c_str()))
        {
            cout << "Error caused At Line 90 Reason :- " << mysql_error(conn) << endl;
        }
        MYSQL_RES *res;
        MYSQL_ROW row;
        res = (mysql_store_result(conn));
        if (!res)
        {
            cout << "Error Caused at Line 96" << mysql_error(conn) << endl;
        }
        while ((row = mysql_fetch_row(res)))
        {
            cout << "Doctor Name: " << row[0] << endl;
            cout << "Feedback   : " << row[1] << endl;
            cout << "Ratings    : " << row[2] << endl;
            cout << "-----------------------------" << endl;
        }

        mysql_free_result(res);
    }
```
#feedback for doctor by their Uid

```
    void show_feedback_personal(int doc_id)
    {
        string query = "SELECT p_feedback FROM feedback Where doc_id = " + to_string(doc_id);
        if (mysql_query(conn, query.c_str()))
        {
            cout << "Error caused At Line 111 Reason :- " << mysql_error(conn) << endl;
        }
        MYSQL_RES *res;
        MYSQL_ROW row;
        res = (mysql_store_result(conn));
        if (!res)
        {
            cout << "Error Caused at Line 117 " << mysql_error(conn) << endl;
        }
        cout << "======= Feedback for Doctor ID: " << doc_id << " =======" << endl;
        while ((row = mysql_fetch_row(res)))
        {
            cout << "Feedback :- " << row[0] << endl;
        }
        mysql_free_result(res);
    }
```
#Remove Patient
```
    // remove patient with patint is from patient List
    void remove_patient(int p_id)
    {
        string query = "DELETE FROM pt_list WHERE p_id = " + to_string(p_id);
        if (mysql_query(conn, query.c_str()))
        {
            cout << "Error caused At Line 129 Reason :- " << mysql_error(conn) << endl;
        }
        else
        {
            cout << "Patient deleted SuccesFully" << endl;
        }
        this_thread::sleep_for(chrono::seconds(5));
        system("clear");
    }
```
#printing Fees
```
    // printing FEES of patient :-
    int print_fee(int p_id)
    {
        string query = "SELECT SUM(p_fee_unpaid) FROM pt_fee_details WHERE p_id = " + to_string(p_id);
        if (mysql_query(conn, query.c_str()))
        {
            cout << "Error caused At Line 141 Reason :- " << mysql_error(conn) << endl;
        }
        MYSQL_RES *res;
        MYSQL_ROW row;
        res = (mysql_store_result(conn));
        if (!res)
        {
            cout << "Error Caused at Line 144 " << mysql_error(conn) << endl;
        }
        cout << "Total Patient Bil for Patient id:- " << endl;
        row = (mysql_fetch_row(res));
        int fee = 0;
        if (row && row[0])
        {
            cout << row[0] << endl;
            fee = stoi(row[0]);
            mysql_free_result(res);
        }
        else
            cout << "0" << endl;
        return fee;
    }
```
#add Doctor
```
    // add doctor

    void add_doctor()
    {
        string doc_name;
        string doc_spec;
        int doc_salary;
        long long doc_phone_number;

        cout << "Enter Doctor Name: ";
        getline(cin, doc_name);

        cout << "Enter Doctor Specialization (dentist, psycho, gynac, patho, other): ";
        getline(cin, doc_spec);

        cout << "Enter Doctor Salary: ";
        cin >> doc_salary;

        cout << "Enter Doctor Phone Number: ";
        cin >> doc_phone_number;

        // Construct SQL query
        string query = "INSERT INTO doc_details(doc_name, doc_spec, doc_sal, doc_phonr) VALUES('" + doc_name + "', '" + doc_spec + "', " + to_string(doc_salary) + ", " + to_string(doc_phone_number) + ")";

        // Execute query
        if (mysql_query(conn, query.c_str()))
        {
            cout << "Error inserting doctor at line 213 " << mysql_error(conn) << endl;
        }
        else
        {
            cout << "Doctor added successfully!" << endl;
        };
        int doc_id = mysql_insert_id(conn);
        cout << "Doctors Uid Is :- " << doc_id << "Remember This For Future use" << endl;
    }
```
#remove doctor
```
    // remove doctor 

    void remove_doctor(int doc_id) {
        string query = "DELETE FROM doc_details WHERE id = " +to_string(doc_id);
        if (mysql_query(conn, query.c_str()))
        {
            cout << "Error removing doctor : " << mysql_error(conn) << endl;
        }
        else
        {
            cout << "Doctor removed successfully!" << endl;
        }
    }
```
#Pay Bill Of Patient
```
     // pay bill of patient 

     void pay_bill(int p_id){
        string query;
        int fee = print_fee(p_id);
        cout << "Enter Amount to pay the Bill" << endl;
        int paybill;
        cin >> paybill;
        if(paybill == fee){
           query = "UPDATE pt_fee_details SET p_fee_unpaid = 0 WHERE p_id = " +to_string(p_id);
        }
        else{
            int rf = fee - paybill;
            query = "UPDATE pt_fee_details SET p_fee_unpaid = " + to_string(rf) + " WHERE p_id = " + to_string(p_id);

        }
        if (mysql_query(conn, query.c_str()))
        {
            cout << "Error At Line 255  : " << mysql_error(conn) << endl;
        }
        else
        {
            cout << "Data Updated successfully!" << endl;
        }
     }
```
