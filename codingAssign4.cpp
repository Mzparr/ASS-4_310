#include <iostream>
#include <fstream>
#include "gradeBook.h"

using namespace std;


int main(){
    GradeBook gb;              // gb object
    gb.loadFromDat();

    bool a = true;
    while (a) {
        gb.gradeBookMenu();          // show menu
        char cmd = gb.inputValidation(); // read single-letter command

        switch (cmd) {
            case 'S':
                gb.setupGradeBook();
                break;
            case 'A':
                if (!gb.isReady()) { cout << "Run S (Setup) first.\n"; break; }
                gb.addStudent();
                break;

                // placeholders for later steps — do NOT call unimplemented functions yet
            case 'P':
                if (!gb.isReady()) { cout << "Run S (Setup) first.\n"; break; }
                gb.programGrades();
                break;
            case 'T':
                if (!gb.isReady()) { cout << "Run S (Setup) first.\n"; break; }
                gb.testGrades();
                break;

            case 'F':
                if (!gb.isReady()) { cout << "Run S (Setup) first.\n"; break; }
                gb.finalTestGrades();
                break;

            case 'C':
                if (!gb.isReady()) { cout << "Run S (Setup) first.\n"; break; }
                gb.changeGrade();
                break;

            case 'G':
                if (!gb.isReady()) { cout << "Run S (Setup) first.\n"; break; }
                gb.finalGrade();
                break;
            case 'O':
                if (!gb.isReady()) { cout << "Run S (Setup) first.\n"; break; }
                gb.showGrades();
                break;

            case 'Q':
                gb.quitProgram();
                a = false;
                break;

            default:
                cout << "Unknown command.\n";
        }

        cout << "\n";  // spacing between cycles
    }
    return 0;
}