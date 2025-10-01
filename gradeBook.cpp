#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cctype>
#include "gradeBook.h"
#include "student.h"
using namespace std;



bool GradeBook::isReady() const {
    return semesterReady;
}

//clearing buffer function
void clearBuffer(){
    cin.clear();
    cin.ignore(100, '\n');
}

void GradeBook::logTrn(const std::string& line) {
    std::ofstream trn("Grades.trn", std::ios::app);
    if (trn) trn << line << '\n';
}

//sort by last, then first
static bool ByName(const Student& a, const Student& b) {
    if (a.lastName != b.lastName) return a.lastName < b.lastName;
    if (a.firstName != b.firstName) return a.firstName < b.firstName;
    return a.id < b.id;
}

void GradeBook::sortRosterByName() {
    std::sort(roster, roster + count, ByName);
}


bool GradeBook::loadFromDat() {
    ifstream dat("Grades.dat");
    if (!dat) {
        cout << "No Grades.dat found — starting fresh.\n";
        return false;
    }

    string line;

    //counts
    if (!getline(dat, line)) { cout << "Grades.dat is empty.\n"; return false; }
    {
        stringstream ss(line);
        char comma;
        if (!(ss >> numPrograms >> comma >> numTests >> comma >> numFinals)) {
            cout << "Bad counts line in Grades.dat.\n"; return false;
        }
    }

    // weights
    if (!getline(dat, line)) { cout << "Missing weights line in Grades.dat.\n"; return false; }
    {
        stringstream ss(line);
        char comma;
        if (!(ss >> programWeight >> comma >> testWeight >> comma >> finalWeight)) {
            cout << "Bad weights line in Grades.dat.\n"; return false;
        }
    }

    // Line 3: student count
    int declaredCount = 0;
    if (!getline(dat, line)) { cout << "Missing student count in Grades.dat.\n"; return false; }
    {
        stringstream ss(line);
        if (!(ss >> declaredCount)) { cout << "Bad student count in Grades.dat.\n"; return false; }
        if (declaredCount < 0) declaredCount = 0;
    }

    // students
    const int capacity = static_cast<int>(sizeof(roster) / sizeof(roster[0]));
    count = 0;

    for (int i = 0; i < declaredCount; ++i) {
        if (!getline(dat, line)) break;
        stringstream ss(line);

        Student s; // ctor sets arrays to -1

        if (!getline(ss, s.lastName, ',')) break;
        if (!getline(ss, s.firstName, ',')) break;

        string tok;
        if (!getline(ss, tok, ',')) break;
        s.id = stoi(tok);

        for (int p = 0; p < MAX_PROGRAMS; ++p) {
            if (!getline(ss, tok, ',')) tok = "-1";
            s.programGrades[p] = stoi(tok);
        }

        for (int t = 0; t < MAX_TESTS; ++t) {
            if (!getline(ss, tok, ',')) tok = "-1";
            s.testGrades[t] = stoi(tok);
        }

        if (!getline(ss, tok)) tok = "-1";
        s.finalExam = stoi(tok);

        if (count < capacity) {
            roster[count++] = s;
        } else {
            cout << "Roster full — extra students in Grades.dat are being ignored.\n";
            break;
        }
    }

    semesterReady = true;
    cout << "Loaded " << count << " student(s) from Grades.dat\n";
    logTrn("L: loaded " + to_string(count) + " student(s) from Grades.dat");
    return true;
}




//constructor
GradeBook::GradeBook(){
    numPrograms = 0; //starting with 0 programs
    numTests = 0; //starting with 0 tests
    numFinals = 0; //starting with 0 finals
    programWeight = 0.0; //starting with 0 weight
    testWeight = 0.0; //starting with 0 weight
    finalWeight = 0.0; //starting with 0 weight
    count = 0; //starting with 0 students

}

//setting up gradebook for the semester
void GradeBook::setupGradeBook(){
    double weightSum = 0.0;
    const double EPS = 1e-6;
    count = 0;                // empty the roster
    semesterReady = false;    // will flip to true again at the end of Setup

    //prompt user num of programs + validation
    while(true){

        cout << "Please enter in the total number of programming assignments (0-6 only): ";
        cin >> numPrograms;
        if(cin.fail() || numPrograms < 0 || numPrograms > MAX_PROGRAMS){
            cout << "Please enter a number from 0 to 6\n";
            cout << "\n";
            clearBuffer();
        } else {
            break;
        }
    }

    //prompt user num of test + validation
    while(true){
        cout << "Please enter in the total number of tests (0-4 only): ";
        cin >> numTests;
        if(cin.fail() || numTests < 0 || numTests > MAX_TESTS){
            cout << "Please enter a number from 0 to 4\n";
            cout << "\n";
            clearBuffer();
        } else {
            break;
        }
    }

    //prompt user num of finals + validation
    while(true){
        cout << "Please enter in the total number of final exams (0-1 only): ";
        cin >> numFinals;
        if(cin.fail() || numFinals < 0 || numFinals > 1){
            cout << "Please enter a number from 0 to 1\n";
            cout << "\n";
            clearBuffer();
        } else {
            break;
        }
    }

    //prompt user weight of programs + validation
    cout << "Please enter weights for programming assignments, tests and final exam\n";
    cout << "NOTE: All weights must not exceed 100%\n";
    while(true){
        //getting weight of programming assignments
        //if no programming assignments, weight will be 0%
        while(true){
            if (numPrograms == 0){
                programWeight = 0.0; //if no programming assignments, then weight will be 0
                break;
            } else {
                cout << "Please enter weight for programming assignments: ";
                cin >> programWeight;
                if (cin.fail() || programWeight < 0 || programWeight > 100){
                    cout << "Please enter a vaild weight, from 0 to 100\n";
                    cout << "\n";
                    clearBuffer();
                } else {
                    break;
                }
            }
        }
        //weight of tests
        while(true){
            if (numTests == 0){ //if there are no tests then weight will be 0
                testWeight = 0.0;
                break;
            } else {
                cout << "Please enter weight for tests: ";
                cin >> testWeight;
                if (cin.fail() || testWeight < 0 || testWeight > 100){
                    cout << "Please enter a vaild weight, from 0 to 100\n";
                    cout << "\n";
                    clearBuffer();
                } else {
                    break;
                }
            }
        }
        //weight of final exam
        while(true){
            if (numFinals == 0){
                finalWeight = 0.0; //if no final then weight will be 0
                break;
            } else {
                cout << "Please enter weight for final exam: ";
                cin >> finalWeight;
                if (cin.fail() || finalWeight < 0 || finalWeight > 100){
                    cout << "Please enter a vaild weight, from 0 to 100\n";
                    cout << "\n";
                    clearBuffer();
                } else {
                    break;
                }
            }
        }
        
        //calculating the sum all weights from programming assignments, tests, and final exam
        weightSum = programWeight + finalWeight + testWeight;

        //checking if weights add up to 100%
        if (weightSum > 100.0 + EPS) {
            cout << "Please enter weights again\n";
            cout << "Reminder that total weight from programming assignments + tests + final cannot exceed 100%\n\n";
        } else if (weightSum < 100.0 - EPS) {
            cout << "Please ensure that all weights add up to 100%\n\n";
        } else {
            //printing out summary of entries
            /*
                Next goal is to move this into a file and then save these entries into a file
            */
            cout << "\n\n";
            cout << "--------------------------------------Grade Book Summary--------------------------------------\n";
            cout << "Total number of programming assignments: " << numPrograms << "\n";
            cout << "Total number of tests: " << numTests << "\n";
            cout << "Total number of final exams: " << numFinals << "\n";
            cout << "Weight for programming assignments: " << programWeight << "%\n";
            cout << "Weight for tests: " << testWeight << "%\n";
            cout << "Weight for final exam: " << finalWeight << "%\n";
            semesterReady = true;
            logTrn(
            "S: P=" + to_string(numPrograms) +
            ", T=" + to_string(numTests) +
            ", F=" + to_string(numFinals) +
            "; W(P/T/F)=" + to_string(programWeight) + "/" +
                   to_string(testWeight) + "/" +
                   to_string(finalWeight)
);
            break;
        }
    }
}

//function to add a student
bool GradeBook::addStudent(){
    //checking if array that holds students is full or not
    if (count >= MAX_STUDENTS){
        cout << "Roster is full\n";
        return false;
    }
    Student s;
    //asking user for students first and last name
    do {
        std::cout << "Please enter students last name: ";
        std::cin  >> s.lastName;
        std::cout << "\n";
        if (s.lastName.size() > 20)
            std::cout << "Last name must be at most 20 characters.\n\n";
    } while (s.lastName.size() > 20);

    //name ≤ 20 chars
    do {
        std::cout << "Please enter students first name: ";
        std::cin  >> s.firstName;
        std::cout << "\n";
        if (s.firstName.size() > 20)
            std::cout << "First name must be at most 20 characters.\n\n";
    } while (s.firstName.size() > 20);

    //asking user for student id
    while(true){
        cout << "Please enter students ID number(between 1 - 9999): ";
        cin >> s.id;
        cout << "\n";

        if (cin.fail() || s.id < 1 || s.id > 9999){
            cout << "Please enter a valid ID between 1 and 9999!\n";
            clearBuffer();
            continue;
        }
        bool same_id = false;
        for (int i = 0; i < count; ++i) {
            if (roster[i].id == s.id) { same_id = true; break; }
        }
        if (same_id) {
            std::cout << "That ID already exists. Try another.\n\n";
            continue;
        }
        break; // good ID
    }
    roster[count] = s;
    ++count;
    logTrn("A: " + s.lastName + ", " + s.firstName + " (ID " + std::to_string(s.id) + ")");
    sortRosterByName();
    return true;
}

//quick printing function to check if all got saved properly
void GradeBook::printRoster(){
    if (count == 0){
        cout << "Roster is empty\n";
        return;
    }
    cout << "Current Roster\n";
    cout << "Total students in roster: " << count << "\n";
    cout << "\n";
    for (int i = 0; i < count; i++){
        cout << " " << roster[i].lastName << ", " << roster[i].firstName << " (ID " << roster[i].id << ")\n";
    }
    cout << endl;
}
//gradebook menu with various options
void GradeBook::gradeBookMenu(){
        cout << "Grade Book Options\n";
        cout << "S: Set up new grade book" << setw(30) << "A: Add a student\n";
        cout << "P: Record programming grade" << setw(32) << "T: Record test scores\n";
        cout << "F: Record final grade" << setw(32) << "C: Change grade\n";
        cout << "G: Calculate final grade" << setw(34) << "O: Output all grades\n";
        cout << "Q: Quit program\n";
}

//validating user input choice
char GradeBook::inputValidation(){
    string input;
    char choice;
    while(true){
        cout << "Please enter choose an option: ";
        getline(cin, input);
        if (input.length() == 1 && isalpha(input[0])){
            choice = input[0];
            break;
        } else {
            cout << "Please enter a single letter. \n";
            cout << "\n";
        }
    }
    char upperChoice = toupper(choice);
    return upperChoice;
}

void GradeBook::showGrades() {
    // ask for order
    cout << "Output order? (N = by Name, I = by ID): ";
    char order;
    cin >> order;
    order = static_cast<char>(toupper(static_cast<unsigned char>(order)));
    cout << "\n";

    // index view don't disturb stored order
    vector<int> idx(count);
    for (int i = 0; i < count; ++i) idx[i] = i;

    if (order == 'N') {
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            if (roster[a].lastName != roster[b].lastName)
                return roster[a].lastName < roster[b].lastName;
            if (roster[a].firstName != roster[b].firstName)
                return roster[a].firstName < roster[b].firstName;
            return roster[a].id < roster[b].id;
        });
    } else if (order == 'I') {
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return roster[a].id < roster[b].id;
        });
    } else {
        cout << "Unknown choice. Using Name order.\n\n";
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            if (roster[a].lastName != roster[b].lastName)
                return roster[a].lastName < roster[b].lastName;
            if (roster[a].firstName != roster[b].firstName)
                return roster[a].firstName < roster[b].firstName;
            return roster[a].id < roster[b].id;
        });
        bool needCompute = false;
        for (int k : idx) {
            if (roster[k].programAverage < 0.0 || roster[k].testAverage < 0.0 || roster[k].semesterAverage < 0.0) {
                needCompute = true; break;
            }
        }
        if (needCompute) {
            finalGrade();
        }
        order = 'N';
    }

    // write Grades.out
    ofstream out("Grades.out", ios::trunc);
    bool needCompute = false;
    for (int k : idx) {
        if (roster[k].programAverage < 0.0 ||
            roster[k].testAverage    < 0.0 ||
            roster[k].semesterAverage< 0.0) {
            needCompute = true; break;
            }
    }
    if (needCompute) {
        finalGrade();    // computes averages for all students
    }

    if (!out) {
        cout << "Could not open Grades.out for writing.\n";
        return;
    }

    out << left;

    // fixed columns first
    out << setw(20) << "Last Name"
        << setw(20) << "First Name"
        << setw(8)  << "ID";

    // dynamic Program columns: P1..PnumPrograms
    for (int p = 1; p <= numPrograms; ++p) {
        ostringstream col; col << "P" << p;
        out << setw(6) << col.str();
    }

    // dynamic Test columns: T1..TnumTests
    for (int t = 1; t <= numTests; ++t) {
        ostringstream col; col << "T" << t;
        out << setw(6) << col.str();
    }

    // summary columns
    out << setw(12) << "Prog Avg"
        << setw(12) << "Test Avg"
        << setw(8)  << (numFinals > 0 ? "Final" : "Final*")
        << setw(14) << "Semester Avg"
        << "\n";

    for (int k : idx) {
        const Student& s = roster[k];

        // Final exam display
        string fstr = "N/A";
        if (numFinals > 0) fstr = (s.finalExam == -1 ? "N/A" : to_string(s.finalExam));

        // fixed identity columns
        out << left << fixed << setprecision(1)
            << setw(20) << s.lastName
            << setw(20) << s.firstName
            << setw(8)  << s.id;

        // raw Program grades (only first numPrograms slots matter)
        out << setprecision(0); // raw grades shown as integers
        for (int p = 0; p < numPrograms; ++p) {
            string g = (s.programGrades[p] == -1 ? "NA" : to_string(s.programGrades[p]));
            out << setw(6) << g;
        }

        // raw Test grades (only first numTests slots matter)
        for (int t = 0; t < numTests; ++t) {
            string g = (s.testGrades[t] == -1 ? "NA" : to_string(s.testGrades[t]));
            out << setw(6) << g;
        }

        // averages & final (1 decimal)
        out << fixed << setprecision(1)
            << setw(12) << s.programAverage
            << setw(12) << s.testAverage
            << setw(8)  << fstr
            << setw(14) << s.semesterAverage
            << "\n";
        }


    out.flush();
    cout << "Wrote report to Grades.out\n";

    // transaction log
    logTrn(string("O: report with averages, order=") + (order == 'I' ? "ID" : "NAME")
       + ", students=" + to_string(count));
}

void GradeBook::quitProgram() {
    // Save current gradebook to Grades.dat
    ofstream dat("Grades.dat", ios::trunc);
    if (!dat) {
        cout << "Could not open Grades.dat for writing.\n";
        return;
    }

    // Line 1   counts
    dat << numPrograms << ',' << numTests << ',' << numFinals << '\n';
    // Line 2: weights
    dat << programWeight << ',' << testWeight << ',' << finalWeight << '\n';
    // Line 3: student count
    dat << count << '\n';

    // Lines 4...   one student per line:
    // last,first,id, p[0..5], t[0..3], finalExam
    for (int i = 0; i < count; ++i) {
        const Student& s = roster[i];

        dat << s.lastName << ',' << s.firstName << ',' << s.id << ',';

        // programs (MAX_PROGRAMS = 6)
        for (int p = 0; p < MAX_PROGRAMS; ++p) {
            if (p) dat << ',';
            dat << s.programGrades[p];
        }

        dat << ','; // separator between program and test blocks

        // tests (MAX_TESTS = 4)
        for (int t = 0; t < MAX_TESTS; ++t) {
            if (t) dat << ',';
            dat << s.testGrades[t];
        }

        dat << ',' << s.finalExam << '\n';
    }

    dat.flush();
    cout << "Saved " << count << " student(s) to Grades.dat\n";

    // transaction log
    logTrn("Q: saved " + to_string(count) + " student(s) to Grades.dat");
}

void GradeBook::programGrades() {
    if (numPrograms <= 0) {
        cout << "There are no programming assignments this term.\n";
        return;
    }
    if (count == 0) {
        cout << "No students in the roster.\n";
        return;
    }

    // ask which program and map to 0-based index
    int userNum = 0;
    while (true) {
        cout << "Enter program number (1 to " << numPrograms << "): ";
        cin >> userNum;
        if (cin.fail() || userNum < 1 || userNum > numPrograms) {
            cout << "Please enter a valid number between 1 and " << numPrograms << ".\n\n";
            clearBuffer();
        } else break;
    }
    int idx = userNum - 1;

    // prevent duplicates
    bool alreadyEntered = false;
    for (int i = 0; i < count; ++i) {
        if (roster[i].programGrades[idx] != -1) { alreadyEntered = true; break; }
    }
    if (alreadyEntered) {
        cout << "Program #" << userNum << " was already recorded. "
             << "Use C (Change grade) to modify individual students.\n";
        return;
    }

    //prompt grades for each student
    cout << "\nRecording grades for Program #" << userNum << ":\n";
    for (int i = 0; i < count; ++i) {
        int g = -1;
        while (true) {
            cout << "  " << roster[i].lastName << ", " << roster[i].firstName << " (ID " << roster[i].id << "): ";
            cin >> g;
            if (cin.fail() || g < 0 || g > 100) {
                cout << "    Please enter an integer grade 0..100.\n";
                clearBuffer();
            } else break;
        }
        roster[i].programGrades[idx] = g;
    }

    cout << "Recorded Program #" << userNum << " for " << count << " student(s).\n";
    logTrn("P: program #" + to_string(userNum) + " recorded for " + to_string(count) + " student(s)");
}



void GradeBook::testGrades() {
    if (numTests <= 0) {
        cout << "There are no tests this term.\n";
        return;
    }
    if (count == 0) {
        cout << "No students in the roster.\n";
        return;
    }

    //choose which test
    int userNum = 0;
    while (true) {
        cout << "Enter test number (1 to " << numTests << "): ";
        cin >> userNum;
        if (cin.fail() || userNum < 1 || userNum > numTests) {
            cout << "Please enter a valid number between 1 and " << numTests << ".\n\n";
            clearBuffer();
        } else break;
    }
    int idx = userNum - 1;

    // prevent duplicates
    bool alreadyEntered = false;
    for (int i = 0; i < count; ++i) {
        if (roster[i].testGrades[idx] != -1) { alreadyEntered = true; break; }
    }
    if (alreadyEntered) {
        cout << "Test #" << userNum << " was already recorded. "
             << "Use C (Change grade) to modify individual students.\n";
        return;
    }

    // prompt grades for each student
    cout << "\nRecording grades for Test #" << userNum << ":\n";
    for (int i = 0; i < count; ++i) {
        int g = -1;
        while (true) {
            cout << "  " << roster[i].lastName << ", " << roster[i].firstName
                 << " (ID " << roster[i].id << "): ";
            cin >> g;
            if (cin.fail() || g < 0 || g > 100) {
                cout << "    Please enter an integer grade 0..100.\n";
                clearBuffer();
            } else break;
        }
        roster[i].testGrades[idx] = g;
    }

    cout << "Recorded Test #" << userNum << " for " << count << " student(s).\n";
    logTrn("T: test #" + to_string(userNum) + " recorded for " + to_string(count) + " student(s)");
}


void GradeBook::finalTestGrades() {
    if (numFinals <= 0) {
        cout << "There is no final exam this term.\n";
        return;
    }
    if (count == 0) {
        cout << "No students in the roster.\n";
        return;
    }

    //prevent duplicates
    bool alreadyEntered = false;
    for (int i = 0; i < count; ++i) {
        if (roster[i].finalExam != -1) { alreadyEntered = true; break; }
    }
    if (alreadyEntered) {
        cout << "Final exam was already recorded. "
             << "Use C (Change grade) to modify individual students.\n";
        return;
    }

    cout << "\nRecording Final Exam grades:\n";
    for (int i = 0; i < count; ++i) {
        int g = -1;
        while (true) {
            cout << "  " << roster[i].lastName << ", " << roster[i].firstName
                 << " (ID " << roster[i].id << "): ";
            cin >> g;
            if (cin.fail() || g < 0 || g > 100) {
                cout << "    Please enter an integer grade 0..100.\n";
                clearBuffer();
            } else break;
        }
        roster[i].finalExam = g;
    }

    cout << "Recorded Final Exam for " << count << " student(s).\n";
    logTrn("F: final exam recorded for " + to_string(count) + " student(s)");
}



void GradeBook::changeGrade() {
    if (count == 0) { cout << "No students in the roster.\n"; return; }

    // 1) Which student?
    int sid = 0;
    while (true) {
        cout << "Enter student ID (1 - 9999): ";
        cin >> sid;
        if (cin.fail() || sid < 1 || sid > 9999) {
            cout << "Please enter a valid ID.\n\n";
            clearBuffer();
        } else break;
    }

    int i = -1;  // index into roster
    for (int k = 0; k < count; ++k) {
        if (roster[k].id == sid) { i = k; break; }
    }
    if (i == -1) { cout << "Student ID not found.\n"; return; }

    // 2) Which grade type?
    char type;
    cout << "Change which grade? (P = Program, T = Test, F = Final): ";
    cin >> type;
    type = static_cast<char>(toupper(static_cast<unsigned char>(type)));

    // 3) If P/T, which number?
    int which = -1;     // 1-based from user
    int idx = -1;       // 0-based index
    if (type == 'P') {
        if (numPrograms <= 0) { cout << "There are no programming assignments this term.\n"; return; }
        while (true) {
            cout << "Enter program number (1 to " << numPrograms << "): ";
            cin >> which;
            if (cin.fail() || which < 1 || which > numPrograms) {
                cout << "Please enter a valid program number.\n\n";
                clearBuffer();
            } else break;
        }
        idx = which - 1;
        // Optional: Show previous value
        int oldv = roster[i].programGrades[idx];
        cout << "Current value: " << oldv << " (use 0..100 for new value)\n";
    }
    else if (type == 'T') {
        if (numTests <= 0) { cout << "There are no tests this term.\n"; return; }
        while (true) {
            cout << "Enter test number (1 to " << numTests << "): ";
            cin >> which;
            if (cin.fail() || which < 1 || which > numTests) {
                cout << "Please enter a valid test number.\n\n";
                clearBuffer();
            } else break;
        }
        idx = which - 1;
        int oldv = roster[i].testGrades[idx];
        cout << "Current value: " << oldv << " (use 0..100 for new value)\n";
    }
    else if (type == 'F') {
        if (numFinals <= 0) { cout << "There is no final exam this term.\n"; return; }
        int oldv = roster[i].finalExam;
        cout << "Current value: " << oldv << " (use 0..100 for new value)\n";
    }
    else {
        cout << "Unknown grade type.\n";
        return;
    }

    // 4) New grade
    int newg = -1;
    while (true) {
        cout << "Enter new grade (0..100): ";
        cin >> newg;
        if (cin.fail() || newg < 0 || newg > 100) {
            cout << "Please enter an integer between 0 and 100.\n\n";
            clearBuffer();
        } else break;
    }

    // 5) Apply change
    if (type == 'P') {
        roster[i].programGrades[idx] = newg;
        cout << "Updated Program #" << which << " for " << roster[i].lastName << ", "
             << roster[i].firstName << " (ID " << sid << ") to " << newg << ".\n";
        logTrn("C: ID " + to_string(sid) + " P#" + to_string(which) + " -> " + to_string(newg));
    } else if (type == 'T') {
        roster[i].testGrades[idx] = newg;
        cout << "Updated Test #" << which << " for " << roster[i].lastName << ", "
             << roster[i].firstName << " (ID " << sid << ") to " << newg << ".\n";
        logTrn("C: ID " + to_string(sid) + " T#" + to_string(which) + " -> " + to_string(newg));
    } else { // 'F'
        roster[i].finalExam = newg;
        cout << "Updated Final Exam for " << roster[i].lastName << ", "
             << roster[i].firstName << " (ID " << sid << ") to " << newg << ".\n";
        logTrn("C: ID " + to_string(sid) + " F -> " + to_string(newg));
    }
}


void GradeBook::finalGrade() {
    if (count == 0) { cout << "No students in the roster.\n"; return; }

    for (int i = 0; i < count; ++i) {
        Student& s = roster[i];

        // ---- Program average over the first numPrograms slots
        double psum = 0.0; int pcnt = 0;
        for (int p = 0; p < numPrograms; ++p) {
            int g = s.programGrades[p];
            if (g != -1) { psum += g; ++pcnt; }
        }
        s.programAverage = (pcnt > 0 ? psum / pcnt : 0.0);

        // ---- Test average over the first numTests slots
        double tsum = 0.0; int tcnt = 0;
        for (int t = 0; t < numTests; ++t) {
            int g = s.testGrades[t];
            if (g != -1) { tsum += g; ++tcnt; }
        }
        s.testAverage = (tcnt > 0 ? tsum / tcnt : 0.0);

        // ---- Final exam
        double fscore = 0.0;
        if (numFinals > 0 && s.finalExam != -1) fscore = s.finalExam;

        // ---- Weighted semester average
        s.semesterAverage =
            (s.programAverage * programWeight +
             s.testAverage    * testWeight    +
             fscore           * finalWeight) / 100.0;
    }

    cout << "Computed averages for " << count << " student(s).\n";
    logTrn("G: recomputed averages for " + to_string(count) + " student(s)");
}