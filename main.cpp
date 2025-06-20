#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype> // for isdigit
#include <fstream> // for file
using namespace std;

class Course{
public:
    string name;
    string code;
    int MinPercentage;
    int seat;
    int enrolled;

    Course(string name,string code,int MinPersentage,int seat)
        : name(name), code(code), MinPercentage(MinPercentage), seat(seat), enrolled(0) {}

    bool IsEligible(int percentage) const{
        return percentage >= MinPercentage;
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


    //Valid Email(Contain @ and .)
    bool IsValidEmail(const string& email){
        auto atPos = email.find('@');
        auto dotPos = email.find('.', atPos);

        if (atPos == string::npos || dotPos == string::npos || atPos == 0 || dotPos <= atPos + 1 || dotPos == email.length() - 1) {
            return false;
        }
        return true;
    }



    // Registration Function.

    void RegisterStudent(){
    string input;
        
    // First Name Input.
    while(true){
        cout<<"Enter your first name: ";
        cin>>input;
        if(IsValidfname(input)){
            fname=input;
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
        if(IsValidlname(input)){
            lname=input;
            break;
        }
        else{
            cout<<"Invalid last name. Please use only alphabets."<<endl;
        }
    }


    //Percentage Input
    while(true){
        cout<<"Enter percentage(only number and without decimal e.g. 55 ): ";
        cin>>input;
         if (IsValidPercentage(input)) {
            percentage = stoi(input);
            break;
        } else {
            cout << "Enter percentage (only whole numbers, e.g., 55): " << endl;
        }
    }

    // Date of Birth Input
    while (true) {
        cout << "Enter DOB (dd-mm-yyyy): ";
        cin >> input;
        if (IsValidDOB(input)) {
            DOB = input;
            break;
        } else {
            cout << "Invalid DOB format. Please use dd-mm-yyyy." << endl;
        }
    }

    // Phone Number Input
    while (true) {
        cout << "Enter Phone Number (10 digits): ";
        cin >> input;
        setPhoneNo(input);
        if (getPhoneNo() == input) break; // Only accepted if set successfully
    }

    // Aadhar Number Input
    while (true) {
        cout << "Enter Aadhar Number (12 digits): ";
        cin >> input;
        setAadharNo(input);
        if (getAadhar() == input) break; // Only accepted if set successfully
    }

    // Password Input
    while (true) {
        string pass1, pass2;
        cout << "Create a password (min 6 characters): ";
        cin >> pass1;
        cout << "Confirm your password: ";
        cin >> pass2;

        if (pass1 == pass2 && pass1.length() >= 6) {
            Password = pass1;
            break;
        } else {
            cout << "Passwords do not match or too short (min 6 characters). Try again." << endl;
        }
    }

    // Email Input
    while (true) {
        cout << "Enter Email: ";
        cin >> input;
        if (IsValidEmail(input)) {
            email = input;
            break;
        } else {
            cout << "Invalid email format. Example: example@domain.com" << endl;
        }
    }
    }

    
};

//Student data save to file.
void SaveStudentToFile(const Student& student){
    ofstream file("student.txt",ios::app); // open in append mode
    if(file.is_open()){
         file << student.fname << " " << student.lname << ","
             << student.percentage << ","
             << student.DOB << ","
             << student.getPhoneNo() << ","
             << student.getAadhar() << ","
             << student.email << endl;
        file.close(); 
    }
    else {
        cout << "Error: Could not open students.txt" << endl;
    }
}

    // View course in file.
    void ViewCourses(const vector<Course>& courses) {
    cout << "\n--- Available Courses ---" << endl;
    cout << "Code\t\tName\t\tSeats Left" << endl;
    for (const Course& c : courses) {
        cout << c.code << "\t\t" << c.name << "\t" << (c.seat - c.enrolled) << endl;
    }
}

    //Add Course
    void AddCourse(vector<Course>& course){
        string name,code;
        int MinPercentage,seat;

        cout<<"Enter course name: ";
        cin.ignore();
        getline(cin,name);

        cout<<"Enter course code(UPPERCASE, no spaces): ";
        cin>>code;

        //Check for duplicate code
        for(const Course& c : course){
            if(c.code == code){
                cout<<"Course with this code already exists."<<endl;
                return; // do NOT continue!!
            }
        }
    cout << "Enter minimum percentage required: ";
    cin >> MinPercentage;

    cout << "Enter total seats: ";
    cin >> seat;

    course.push_back(Course(name, code, MinPercentage, seat));

    // Save to file
    ofstream file("course.txt", ios::app);
    if (file.is_open()) {
        file << name << "," << code << "," << MinPercentage << "," << seat << ",0\n";
        file.close();
        cout << "Course added and saved successfully.\n";
    } else {
        cout << "Failed to open courses.txt\n";
    }
} 








int main(){
    cout << "----------------------------------------" << endl;
    cout << " Welcome to our course registration system" << endl;
    cout << "----------------------------------------\n" << endl;

    vector<Course> courses = {
        Course("JEE Advanced Batch", "ADVJEE", 90, 20),
        Course("Main + Advanced Combo Batch", "COMBOJEE", 85, 30),
        Course("JEE Mains Only Batch", "MAINJEE", 75, 35),
        Course("Crash Course (30 Days)", "CRASH30", 65, 40),
        Course("One-Shot Revision Batch", "ONESHOT", 60, 50),
        Course("Question Bank Solving Course", "QBSOLVE", 55, 50),
        Course("PYQ Practice Batch", "PYQBATCH", 50, 60)
    };

    vector<Student> student;
    int choice;

    do {
        cout << "\n===== Course Registration Menu =====" << endl;
        cout << "1. Register New Student" << endl;
        cout << "2. View All Courses" << endl;
        cout << "3. Add New Course" << endl;
        cout << "0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:{
                Student s;
                s.RegisterStudent();
                student.push_back(s);
                SaveStudentToFile(s);

                cout << "\nStudent information:" << endl;
                cout << "Name       : " << s.fname << " " << s.lname << endl;
                cout << "Percentage : " << s.percentage << "%" << endl;
                cout << "DOB        : " << s.DOB << endl;
                cout << "Phone No.  : " << s.getPhoneNo() << endl;
                cout << "Aadhar No. : " << s.getAadhar() << endl;
                cout << "Email      : " << s.email << endl;
                break;
                }
            case 2:{
                ViewCourses(courses);
                break;
                }
            case 3:{
                AddCourse(courses);
                break;
                }
            case 0:{
                cout << "Exiting system.\n";
                break;
                }
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;

}