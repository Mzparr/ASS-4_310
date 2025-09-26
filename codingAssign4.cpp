#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include "student.h"
#include "gradeBook.h"

using namespace std;


int main(){
    char result;
    GradeBook gb;
    //creating menu for user
    //gb.gradeBookMenu();
    //result = gb.inputValidation();
    //cout << "The result is: " << result << "\n";
    cout << "\n";
   // cout << "Testing basic numProgram + weight validation\n" ;
    //gb.setupGradeBook();
    
    cout << "Now testing addStudent feature\n";
    gb.addStudent();
    gb.printRoster();

    cout << "Adding another student: NOT ALPHABETICAL\n";
    gb.addStudent();
    cout << "\nChecking roster again\n";
    gb.printRoster();
    return 0;
}