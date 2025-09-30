#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "gradeBook.h"
#include "student.h"
using namespace std;


//clearing buffer function
void clearBuffer(){
    cin.clear();
    cin.ignore(100, '\n');
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
    cout << "Please enter students last name: ";
    cin >> s.lastName;
    cout << "\n";

    cout << "Please enter students first name: ";
    cin >> s.firstName;
    cout << "\n";

    //asking user for student Id
    while(true){
        cout << "Please enter students ID number(between 1 - 9999): ";
        cin >> s.id;
        if (cin.fail() || s.id < 1 || s.id > 9999){
            cout << "Please enter a valid ID between 1 and 9999!\n";
            cout << "\n";
            clearBuffer();
        } else {
            break;
        }
    }
    roster[count] = s;
    ++count;
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