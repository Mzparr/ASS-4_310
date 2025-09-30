#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include "student.h"
#include "gradeBook.h"

using namespace std;


int main(){
    GradeBook gb;              // gb object

    bool a = true;
    while (a) {
        gb.gradeBookMenu();          // show menu
        char cmd = gb.inputValidation(); // read single-letter command

        switch (cmd) {
            case 'S':
                gb.setupGradeBook();
                break;
            case 'A':
                gb.addStudent();
                break;

                // placeholders for later steps — do NOT call unimplemented functions yet
            case 'P': std::cout << "[P] Record program grades — not implemented yet.\n"; break;
            case 'T': std::cout << "[T] Record test grades — not implemented yet.\n"; break;
            case 'F': std::cout << "[F] Record final exam — not implemented yet.\n"; break;
            case 'C': std::cout << "[C] Change a grade — not implemented yet.\n"; break;
            case 'G': std::cout << "[G] Compute averages — not implemented yet.\n"; break;
            case 'O': std::cout << "[O] Output report — not implemented yet.\n"; break;

            case 'Q':
                // we'll add saving to Grades.dat in a later step
                a = false;
                break;

            default:
                std::cout << "Unknown command.\n";
        }

        std::cout << "\n";  // spacing between cycles
    }
    return 0;
}