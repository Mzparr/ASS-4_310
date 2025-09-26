//prototypes of all commands for gradebook
//keeping all prototypes as void to create stubs
#pragma once
#include <string>

const int MAX_PROGRAMS = 6;
const int MAX_TESTS = 4;


class Student
{
    public:
        Student();
        std::string lastName, firstName;
        int id = 0;
        double programGrades[MAX_PROGRAMS];
        double testGrades[MAX_TESTS];
        double finalExam;
};
