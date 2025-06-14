#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype> // for isdigit
using namespace std;

class Course{
public:
    string name;
    string code;
    int MinPersentage;
    int seat;
    int enrolled;

    bool IsEligible(int persentage) const{
        return persentage >= MinPersentage;
    }

    bool IsVacant() const{
        return seat > enrolled;
    }

};


class Student{
private:
    string Password;

public:
    string fname;
    string lname;
    float percentage;
    string phone_number;
    string aadhar_number;
    string email;
    string DOB;
    vector<string> course;

    bool IsRegistered(string courseCode) const{
        return find(course.begin(),course.end(),courseCode) != course.end();

    };

    // fname only alphabate and not empty.
    bool IsValidfname(const string& fname){
        if(fname.empty()){
            return false;
        }
        for(char ch: fname){
            if(!isalpha(ch)) return false;
        } 
        return true;
    }


    // lname only alphabate and not empty.
    bool IsValidlname(const string& lname){
        if(lname.empty()){
            return false;
        }
        for(char ch: lname){
            if(!isalpha(ch)) return false;
        } 
        return true;
    }

    // percentage is only integer value .
    bool IsValidPercentage(const string& percentage){
        if(percentage.empty()){
            return false;
        }

        if (percentage.length() > 3) return false;

        for(char ch: percentage){
        if(!isdigit(ch)) return false;
        }
        return true;
    }

    //DOB formate check dd-mm-yyyy 
    bool IsValidDOB(const string& dob){
        if(dob.length()!=10) return false;
        if((dob[2] !='-') &&(dob[5]!='-')){
            return false;
        }
        for(int i=0;i<10;i++){
            if(i==2 || i==5){
                continue;
            }
            if(!isdigit(dob[i])){
                return false;
            }
        }
        return true;
    }


    // Validitation for Aadhar No. 
    bool IsValidAadhar(const string& aadhar){
        if(aadhar.length()!=12){
            return false;
        }
        for(char ch : aadhar){
            if(!isdigit(ch)) return false;
        }
        return true;
    }

    void setAadharNo(const string& NewAadharNo){
        if(IsValidAadhar(NewAadharNo)){
            aadhar_number=NewAadharNo;
        }
        else{
            cout<<"Invalid Aadhar No. It must be 12 digit (only number)."<<endl;
        }
    }

    string getAadhar() const{
        return aadhar_number;
    }

    // Valid phone number 10 digit nd all are integer.
    bool IsValidPhoneNo(const string& phone){
        if(phone.length()!=10){
            return false;
        }
        for(char ch : phone){
            if(!isdigit(ch)) return false;
        }
        return true;
    }

    void setPhoneNo(const string& NewPhoneNo){
        if(IsValidPhoneNo(NewPhoneNo)){
            phone_number=NewPhoneNo;
        }
        else{
            cout<<"Invalid Phone No. It must be 10 digit(only number)."<<endl;
        }
    }

    string getPhoneNo() const{
        return phone_number;
    }





    void RegisterStudent(Student& student){
    string input;
        
    // First Name Input.
    while(true){
        cout<<"Enter your first name: ";
        cin>>input;
        if(student.IsValidfname(input)){
            student.fname=input;
            break;
        }
        else{
            cout<<"Invalid first name. Please use only alphabets."<<endl;
        }
    }

    // Last Name Input.
    while(true){
        cout<<"Enter your last name: ";
        cin>>input;
        if(student.IsValidlname(input)){
            student.lname=input;
            break;
        }
        else{
            cout<<"Invalid last name. Please use only alphabets."<<endl;
        }
    }


    //Percentage
    while(true){
        cout<<"Enter percentage(only number and without decimal e.g. 55 ): ";
        cin>>input;
         if (student.IsValidPercentage(input)) {
            student.percentage = stoi(input);
            break;
        } else {
            cout << "Enter percentage (only whole numbers, e.g., 55): " << endl;
        }
    }

    // Date of Birth
    while (true) {
        cout << "Enter DOB (dd-mm-yyyy): ";
        cin >> input;
        if (student.IsValidDOB(input)) {
            student.DOB = input;
            break;
        } else {
            cout << "Invalid DOB format. Please use dd-mm-yyyy." << endl;
        }
    }

    // Phone Number
    while (true) {
        cout << "Enter Phone Number (10 digits): ";
        cin >> input;
        student.setPhoneNo(input);
        if (student.getPhoneNo() == input) break; // Only accepted if set successfully
    }

    // Aadhar Number
    while (true) {
        cout << "Enter Aadhar Number (12 digits): ";
        cin >> input;
        student.setAadharNo(input);
        if (student.getAadhar() == input) break; // Only accepted if set successfully
    }

    }
};






int main(){
    cout << "----------------------------------------" << endl;
    cout << " Welcome to our course registration system" << endl;
    cout << "----------------------------------------\n" << endl;

    Student student;
    student.RegisterStudent(student);  //Function call
    cout << "\nStudent information:" << endl;
    cout << "Name       : " << student.fname << " " << student.lname << endl;
    cout << "Percentage : " << student.percentage << "%" << endl;
    cout << "DOB        : " << student.DOB << endl;
    cout << "Phone No.  : " << student.getPhoneNo() << endl;
    cout << "Aadhar No. : " << student.getAadhar() << endl;

    return 0;
}