#ifndef CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#define CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Person{
public:
    int type=0;
    int line=0;
    int seatNumber= -1;
    int type3LastOperation=0;
    int line_origin = 0; // passenger's original line(A or B)
    int prev_seat = 0; // the seat passenger sit last

    Person() {
    }

    // My own Deep Copy constructor
    Person(const Person &obj){
        type = *new int;
        type = obj.type;

        line = *new int;
        line = obj.line;

        seatNumber = *new int;
        seatNumber = obj.seatNumber;

        type3LastOperation = *new int;
        type3LastOperation = obj.type3LastOperation;

        line_origin = *new int;
        line_origin = obj.line_origin;

        prev_seat = *new int;
        prev_seat = obj.prev_seat;

    }
};

class SeatOperations{

private:
    vector<Person> lines[2];
    //int N, M;

public:
    SeatOperations(int N, int M);
    void addNewPerson(int personType, const string& ticketInfo);
    void printAllSeats(ofstream& outFile);
    void recursiveSeatFunction(Person& tempo);


};

#endif //CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
