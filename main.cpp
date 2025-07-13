#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include <sstream>
#include <fstream>
using namespace std;

//Validitation Function.
bool isValidName(const string& name) {
    return regex_match(name, regex("^[A-Za-z ]+$"));
}

bool isValidEmail(const string& email) {
    return regex_match(email, regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)"));
}

bool isValidPhone(const string& phone) {
    return regex_match(phone, regex("^[6-9][0-9]{9}$"));
}

bool isValidPercentage(float p) {
    return p >= 0 && p <= 100;
}

bool isValidDOB(const string& dob){
    return regex_match(dob,regex(R"(\d{2}-\d{2}-\d{4})"));
}

//Student Class
class Student{
    public:
    string name,phone,email,dob,coursecode;
    float percentage;
    vector<string>registeredCourses;

    //Student Constructor
    Student(string name, string email, string phone, float percentage, string dob,string coursecode)
        : name(name), email(email), phone(phone), percentage(percentage), dob(dob),coursecode(coursecode){}

    //Student Registration
    static Student RegisterStudent() {
        string name, email, phone, dob,coursecode;
        float percentage;
        bool isDuplicateStudent(const string& email, const string& phone);

        do {
            cout << "Enter Your Name: ";
            getline(cin>>ws,name);
            if (!isValidName(name)) cout << "Invalid name!\n";
        } while (!isValidName(name));

        do {
            cout << "Enter Your Email Id: ";
            cin >> email;
            if (!isValidEmail(email)) cout << "Invalid email id!\n";
            else if(isDuplicateStudent(email, "")) {
                cout << "This email is already registered!\n";
                email.clear();  // To force repeat
            }
        } while (!isValidEmail(email)|| email.empty());

        do {
            cout << "Enter Your Phone Number: ";
            cin >> phone;
            if (!isValidPhone(phone)) cout << "Invalid phone number!\n";
            else if (isDuplicateStudent("", phone)) {
                cout << "This phone number is already registered!\n";
                phone.clear();  // To force repeat
            }
        } while (!isValidPhone(phone)|| phone.empty());

        do {
            cout << "Enter Your 12th Percentage: ";
            cin >> percentage;
            if (!isValidPercentage(percentage)) cout << "Invalid percentage!\n";
        } while (!isValidPercentage(percentage));

        do{
            cout << "Enter DOB (dd-mm-yyyy): ";
            cin >> dob;
            if(!isValidDOB(dob)) cout << "Invalid DOB.";
        } while(!isValidDOB(dob));
        cout<<"Student Registered Successfully."<<endl;
        return Student(name, email, phone, percentage,dob,"");
    }

    void display() const {
        cout << "Name: " << name
            << " | Email: " << email
            << " | Phone: " << phone
            << " | %: " << percentage
            << " | DOB: " << dob;

        if (registeredCourses.empty()) {
            cout << " | Registered Courses: None";
        } else {
            cout << " | Registered Courses: ";
            for (size_t i = 0; i < registeredCourses.size(); ++i) {
                cout << registeredCourses[i];
                if (i != registeredCourses.size() - 1)
                    cout << ", ";
            }
        }

        cout << endl;
    }

    //save to file
    void SaveStudentToFile(ofstream& out) const{
        out<<name<<","<<email<<","<<phone<<","<<percentage<<","<<dob<<","<<coursecode;
        for(const string& c : registeredCourses){
            out<<","<<c;
        }
        out<<"\n";
    }
};

//Course Class
class Course{
    public:
    string coursename,coursecode;
    float minPercent;
    int seats;
    int enrolled;

    //Course Constructor
    Course(string coursename,string coursecode,float minPercent,int seats)
        :coursename(coursename),coursecode(coursecode),minPercent(minPercent),seats(seats),enrolled(0){}

    bool isEligible(float percent) const {
        return percent >= minPercent;
    }

    bool isVacantSeats() const {
        return enrolled < seats;
    }

    void display() const {
        cout << coursecode << " - " << coursename << " | Min %: " << minPercent
             << " | Seats: " << seats << " | Enrolled: " << enrolled
             << " | Left: " << (seats - enrolled) << endl;
    }
};

vector<Student> students;
vector<Course> courses;

//find student by email
Student* findStudentByEmail(const string& email) {
    for (Student& s : students) {
        if (s.email == email) {
            return &s;  // return address of the student
        }
    }
    return nullptr;  // not found
}

//Register to course
void registerToCourse(Student& s, vector<Course>& courses) {
    string code;
    cout << "Enter your course code: ";
    cin >> code;

    for (Course& c : courses) {
        if (c.coursecode == code) {
            if (!c.isEligible(s.percentage)) {
                cout << "Not eligible for this course.\n";
                return;
            }
            if (!c.isVacantSeats()) {
                cout << "No seats available.\n";
                return;
            }
            if (find(s.registeredCourses.begin(), s.registeredCourses.end(), code) != s.registeredCourses.end()) { //avoid duplicate registeration
                cout << "Already registered in this course.\n";
                return;
            }

            c.enrolled++;
            s.registeredCourses.push_back(code);
            cout << "Successfully registered in " << c.coursename << "!\n";
            return;
        }
    }
    cout << "Course not found.\n";
}

//View Registered Course
void showRegisteredCourses(const Student& s,vector<Course>& courses) {
    if(s.registeredCourses.empty()){
        cout<<"No course registered."<<endl;
        return;
    }
    cout << "Registered Courses:\n";
    for (const string& code : s.registeredCourses) {
        for (const Course& c : courses) {
            if (c.coursecode == code) {
                cout << "- " << c.coursecode << " | " << c.coursename << endl;
            }
        }
    }
}

//drop course
void dropCourse(Student& s){
    string code;
    cout<<"Enter Course Code to Drop: ";
    cin>>code;
    auto it=find(s.registeredCourses.begin(),s.registeredCourses.end(),code);
    if(it!=s.registeredCourses.end()){
        s.registeredCourses.erase(it);
        for(Course& c : courses){
            if(c.coursecode==code){
                c.enrolled--;
                break;
            }
        }
        cout<<"Course dropped successfully."<<endl;
    }else cout<<"You are not registered in this course."<<endl;
}

//sort student by name
void sortStudentsByName(vector<Student>& registeredStudent) {
    if (registeredStudent.empty()) {
        cout << "No students registered yet.\n";
        return;
    }

    sort(registeredStudent.begin(), registeredStudent.end(), [](const Student& a, const Student& b) {
        string nameA = a.name, nameB = b.name;
        transform(nameA.begin(), nameA.end(), nameA.begin(), ::toupper);
        transform(nameB.begin(), nameB.end(), nameB.begin(), ::toupper);
        return nameA < nameB;
    });

    cout << "\n== Students Sorted Alphabetically ==\n";
    for (const auto& s : registeredStudent) {
        s.display();
    }
}

// Exports all registered student data to a CSV file named "registrations.csv".
void exportCSV(){
    ofstream out("registrations.csv");
    if(!out){
        cout << "Error : Could not open registrations.csv"<<endl;
        return;
    }
    out<<"Name,Email,Phone,Percentage,DOB,Registered Course\n";
    for(const Student& s : students){
        out << "\"" << s.name << "\","
            << "\"" << s.email << "\","
            << "\"" << s.phone << "\","
            << "\"" << s.percentage << "\","
            << "\"" << s.dob << "\",";

            // Join courses with commas
            out<<"\"";
            for (size_t i = 0; i < s.registeredCourses.size(); ++i) {
                out << s.registeredCourses[i];
                if (i != s.registeredCourses.size() - 1)
                    out << ", ";
        }

        out << "\"\n";  // End the line after closing quotes
    }
    out.close();
    cout<<"Exported to registrations.csv\n";
}

//file headling function
void loadCourse(){
    ifstream in("course.txt");
    string n,c;
    float p;
    int s;
    while(in>>ws && getline(in,n,',')){
        getline(in,c,',');
        in>>p;
        in.ignore();
        in>>s;
        in.ignore();
        courses.push_back(Course(n,c,p,s));
    }
    in.close();
}

void loadStudent() {
    ifstream in("student.txt");
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string name, email, phone, dob, coursecode, percentageStr;
        float percentage;

        // Read fixed fields
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, percentageStr, ',');
        percentage = stof(percentageStr);  // string to float
        getline(ss, dob, ',');
        getline(ss, coursecode, ',');

        Student s(name, email, phone, percentage, dob, coursecode);

        // Read remaining fields as registered courses
        string course;
        while (getline(ss, course, ',')) {
            s.registeredCourses.push_back(course);

            //Update enrolled count for the course
            for (Course& c : courses) {
                if (c.coursecode == course) {
                    c.enrolled++;  // Increment enrolled count
                    break;
                }
            }
        }

        students.push_back(s);
    }
    in.close();
}
    
void saveCourse(){
    ofstream out("course.txt");
    for(const Course& c : courses){
        out<<c.coursename<<","<<c.coursecode<<","<<c.minPercent<<","<<c.seats<<endl;
    }
    out.close();
}

void saveStudents(){
    ofstream out("student.txt");
    for(const Student& s : students){
        s.SaveStudentToFile(out);
    }
    out.close();
}

//duplicate student
bool isDuplicateStudent(const string& email, const string& phone) {
    for (const Student& s : students) {
        if ((!email.empty() && s.email == email) || (!phone.empty() && s.phone == phone)) {
            return true;
        }
    }
    return false;
}

int main() {
    //Load courses from file (if exists)
    loadCourse();
    loadStudent();

    if (courses.empty()) {
        courses = {
            Course("JEE Advanced Batch", "ADVJEE", 90, 20),
            Course("Main + Advanced Combo Batch", "COMBOJEE", 85, 30),
            Course("JEE Mains Only Batch", "MAINJEE", 75, 35),
            Course("Crash Course (30 Days)", "CRASH30", 65, 40),
            Course("One-Shot Revision Batch", "ONESHOT", 60, 50),
            Course("Question Bank Solving Course", "QBSOLVE", 55, 50),
            Course("PYQ Practice Batch", "PYQBATCH", 50, 60)
        };
    }

    int choice;
    do {
        cout << "\n=== Course Registration Menu ===\n";
        cout << "1. Register New Student\n";
        cout << "2. View All Courses\n";
        cout << "3. Register to Course\n";
        cout << "4. View Registered Courses\n";
        cout << "5. Drop Course\n";
        cout << "6. View All Students (Sorted by Name)\n";
        cout << "7. Export Registrations to CSV\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        cin >> choice;
        switch (choice) {
            case 1:{
                Student s = Student::RegisterStudent();
                students.push_back(s);  // Store student in the list
                break;
            }
            case 2:{
                for (const Course& c : courses)
                    c.display();
                break;
            }
            case 3: {
                if (students.empty()) {
                    cout << "No student registered yet.\n";
                    break;
                }
                
                string email;
                cout << "Enter your registered email: ";
                cin >> email;

                for (const Course& c : courses)
                    c.display();

                Student* student = findStudentByEmail(email);  // pointer to student
                if (student == nullptr) {
                    cout << "Student not found.\n";
                    break;
                }
                string choice;
                do {
                    registerToCourse(*student, courses);  // pass by reference using '*'
                    cout << "Do you want to try registering for another course? (yes/no): ";
                    cin >> choice;
                } while (choice == "yes" || choice == "y");
                
                saveStudents();
                break;
            }
            case 4: {
                if (students.empty()) {
                    cout << "No student registered yet.\n";
                    break;
                }
                string email;
                cout << "Enter your registered email to view courses: ";
                cin >> email;

                Student* student = findStudentByEmail(email);
                if (student == nullptr) {
                    cout << "Student not found.\n";
                    break;
                }

                showRegisteredCourses(*student, courses);
                break;
            }
            case 5: {
                if (students.empty()) {
                    cout << "No student registered yet.\n";
                    break;
                }
                string email;
                cout << "Enter your registered email for drop course: ";
                cin >> email;

                Student* student = findStudentByEmail(email);  // pointer to student
                if (student == nullptr) {
                    cout << "Student not found.\n";
                    break;
                }

                string choice;
                do {
                    // Show registered courses before asking to drop
                    showRegisteredCourses(*student, courses);

                    if (student->registeredCourses.empty()) {
                        break;  // No need to continue if no registered courses
                    }

                    dropCourse(*student);

                    cout << "Do you want to drop another course? (yes/no): ";
                    cin >> choice;
                } while (choice == "yes" || choice == "y");

                saveStudents();  // Save after any course drops
                break;
            }
            
            case 6:
                sortStudentsByName(students);
                break;
            case 7:
                exportCSV();
                break;
            case 0:
                saveCourse();
                //saveStudents();
                cout << "Thank you for using our Course Registration System.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}