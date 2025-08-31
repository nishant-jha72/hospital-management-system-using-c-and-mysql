# Day 3

today i have completed The Admin class By adding One More method

check_pending_appointement();


Also i have Worked With Patient Class Which is A derived Class from Admin Class So I can acces all member and Their Method in Patient Class As per use
1 . Inheritance used here Derived patient Class With Admin Class
```
class patient : protected Admin
{
 .... code 
```
2 . Register Function for new User Registration
    
 ```
   int registration()
    {
        cout << "Welcome To The Hospital :- " << endl;

        cout << "Enter Patient Name :- ";
        string p_name;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, p_name);

        cout << "Enter Patient Address :- ";
        string p_address;
        getline(cin, p_address);

        cout << "Enter Patient Phone Number :- ";
        int p_number;
        cin >> p_number;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Disease Name (If Emergency Write Emergency):- ";
        string p_disease;
        getline(cin, p_disease);

        string query = "INSERT INTO pt_list(p_name, p_address, p_phone_number, p_diesease) VALUES ('" + p_name + "', '" + p_address + "', " + to_string(p_number) + ", '" + p_disease + "')";

        if (mysql_query(conn, query.c_str()))
        {
            cout << "Error At Line 303 Reason :- " << mysql_error(conn) << endl;
        }
        else
        {
            cout << "Data Inserted Successfully! Rows Affected: " << mysql_affected_rows(conn) << endl;
        }

        int p_id = mysql_insert_id(conn);
        cout << "Patient Id Is " << p_id << " (Remember This for Future Use)" << endl;
        return p_id;
    }
```

3. show patient Details With their Patient Id
```
    // show Patient List
    void view_patient_deatils(int p_id){
        cout << "Patient Deatils Are :-" << endl;
        cout << "====================================================" << endl;
        show_patient(p_id);
    }
```
4/ Pay Bill Of Any Patient.
```
    // pay Bill 
    void payBill(){
        cout << "Enter Your Patient ID:- ";
        int p_id;
        cin >> p_id;
        pay_bill(p_id);
    }
```
5. Book Appointement With doctor
```
    //book Appointment 
    void book_appointment(){
        cout << "Enter Doctor ID:- ";
        int doc_id;
        cin >> doc_id;
        cout<< "Enter Patient ID:- ";
        int p_id;
        cin >> p_id;

        string date;
        cout << "Enter Your Appointment date (YYYY-MM-DD) Format :- ";
        cin.ignore();
        getline(cin , date);
        string status = "pending";
        string query = "INSERT INTO appoint_table(doc_id , p_id , app_date , status) VALUES (" +to_string(doc_id) + " , " +to_string(p_id) + ", ' " + date + " ' , ' " +status+ "')";
        if(mysql_query(conn , query.c_str())){
            cout << "Error At Line 360 " << mysql_error(conn) << endl;
        }
        else {
            cout << "Appointment is Succesfull Please Note The Date To Comeback Hospital on" << date << "And meet Doctor With doc_id :-" << doc_id << endl;
         }

         int app_id = mysql_insert_id(conn);
         cout << "Remeber The Appointement Id :- " << app_id << endl;
    }
```
6. Cancel appointement with doctor
```
    // cancel appointement 
    void cancel_appointement(int app_id){
        string query = "DELETE FROM appoint_table WHERE app_id = " +to_string(app_id);
        if(mysql_query(conn , query.c_str())){
            cout << "Error At Line 374 Reason :- " << mysql_error(conn) << endl;
        }
        else {
            cout << "Appointement With Appointement Id :- " << app_id << " Is Deleted Succesfully" << endl;
        }
    }
```
7. Reshudule Appointement
```
    void reshudule_appointement(int app_id, string date){ 
        string query = "UPDATE appoint_table SET app_date = ' " +date+ "' WHERE app_id = " +to_string(app_id);
        if(mysql_query(conn , query.c_str())){
            cout << "Error At Line 374 Reason :- " << mysql_error(conn) << endl;
        }
        else {
            cout << "Appointement With Appointement Id :- " << app_id << " Is Updated Succesfully" << endl;
        }
    }
```
8 . View Diesease of any Patient :- 
```
    void view_disease (int p_id) {
        string query = "SELECT p_disease FROM pt_list WHERE p_id = " +to_string(p_id);
        if(mysql_query(conn,query.c_str())){
            cout << "Error caused At Line 392 Reason :- " << mysql_error(conn);
        }
        MYSQL_RES *res;
        MYSQL_ROW row;
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if(!res){
            cout << "No Data Found" << endl;
        }
        if(row && row[0]){
            cout << "Dieseases :- " << endl << row[0] <<endl;
        }
        mysql_free_result(res);
    }
}; // class have been closed 
```


#This is how I Ended My 3rd Days And the Project Is Still Going On And I think it will almost Take 5 to 6 Days More To Complete 

#Author :- Nishant JHA
