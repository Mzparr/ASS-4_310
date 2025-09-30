//cpp file for student header, only contains the constructor
#include "student.h"
#include <string>


Student::Student(){
    programAverage = -1.0;
    testAverage    = -1.0;
    semesterAverage= -1.0;
    for (int i = 0; i < MAX_PROGRAMS; i++){
        programGrades[i] = -1; //no grades entered
    }
    for (int i = 0; i < MAX_TESTS; i++){
        testGrades[i] = -1; //no grades entered
    }
    finalExam = -1.0; //no final exam grade entered
}