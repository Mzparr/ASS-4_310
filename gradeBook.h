#pragma once
#include "student.h"
const int MAX_STUDENTS = 100;
class GradeBook{
    public:
        bool isReady() const;
        GradeBook(); //constructor
        void setupGradeBook(); //command S
        /*
            This will prompt user for 
            # of programming assignments from 0 to 6
            # of tests from 0 to 4
            # of final exams from 0 to 1
            Relative weights of prgrams, tests and final exams - in percentages - must add up to 100%
            Example:
            Item        Number      Weight (%)
            Programs      4          50
            Tests         2          20
            Final exam    1          30
        */

        bool addStudent(); //command A
        /*
            Prompt user to add a student
            Last name then first name - Strings of no more than 20 characters
            Student ID number - from 1 to 9999
        */


        void programGrades(); //command P
        /*
            Prompt user to enter grade for programming assignment
            Ask which program assignment to grade
            Prompt to select student (alphabetical order)
            Enter grade for student
            Valid program is < than numPrograms + not previously recorded
            If not valid, print error
        */


        void testGrades(); //command T
        /*
            Records test grade for all students
            Must ask which test to record
            Valid test number -> Show students alphabetically -> prompt to enter grade
            valid = userInput < numTests + not previously recorded
        */

        void finalTestGrades(); //command F
        /*
            Records Final exam grade for all students
            Display students names alphabetically then user enter grade
            If already recorded - print message
        */

        void changeGrade(); //command C

        /*
            Change grade for particular student
            Prompt user for student grade, new grade and type of grade to change
            P,T, or F
        */

        void finalGrade(); //command G
        /*
            Calculate final grade
            Add all program grades -> average
            Add all test grades -> average
        */

        void showGrades(); //command O
        /*
            Output grade data
            Ordered by 
            Alphabetically - last/first
            Student number
            In output file, Grades.out display
            Name
            Student number
            Grade book 
        */

        void quitProgram(); //command Q
        /*
            Simply terminates the program
        */

        void gradeBookMenu();
        /*
        Display the menu of options
        */

        char inputValidation();
        /*
        Will validate user input 
        Returns the command option as a char
        */
       void printRoster();
       private:
        bool semesterReady = false;
        int numPrograms;
        int numTests;
        int numFinals;
        double programWeight;
        double testWeight;
        double finalWeight;
        Student roster[MAX_STUDENTS];
        int count;

};