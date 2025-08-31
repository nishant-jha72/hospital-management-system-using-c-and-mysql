# hospital-management-system-using-c-and-mysql
creating a c++ project with mysql and qt framework it will be able to store patient details , doctors details , and admins panel to change anything into database its my major project for c++ and software devlopment Journey

# Day 1 :

1. Created All Databse Schema In Devise for Use   it can be update and modify After as per use

2. The Database Schema is As Follow :
 
   1. pt_list :- storing patient List
  ```sql    p_id         INT
      p_name       varchar(100)
      p_address    varchar(1000)
      p_phone_number    int
      p_diesease      varchar(100)
```

   2. pt_fee_details :-  store Patient fee details
  ```
      p_id        int
      p_fee_unpaid    int
      p_fee_paid      int

  ```
   3. doc_details :- storing doctor details
```
        doc_id           int
        doc_name         varchar(100)
        doc_spec         enum(doctor types)
        doc_sal          int
        doc_phone        int

```
  4.appoint_table :- storing the appointment date for patient and Doctor
```
      app_id      int
      doc_id      int
      p_id         int
      app_date      date
      status         enum(done, pending)

```

   5. feedback :- Store patient Feedback about Doctor
```
      doc_name       varchar
      p_name         varchar
      p_feedback      varchar
      ratings          enum(1,2,3,4,5)
      doc_id           int
```

   6. master_list :
```
      same as pt_list But here patient details Will be saved For Future Use
```
