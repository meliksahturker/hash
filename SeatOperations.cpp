/*
Student Name: Meliksah Turker
Student Number: 2019700120
Project Number: 3
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: I implemented a recursive Hash function where I re-hashed using recursion according to type of the passenger.
Instead of using the vector given in the header, I preferred using array of Classes for my own convenience, which was initally declared as Struct
but I changed it to Class in order to be able to write copy constructor because I wanted DEEP COPY.
*/
#include "SeatOperations.h"

using namespace std;

Person arr[2000];
int N, M;

SeatOperations::SeatOperations(int a, int b){
    N = a;
    M = b;
}


void SeatOperations::addNewPerson(int personType, const string& ticketInfo){
    int seatNumber = atoi(ticketInfo.substr(1).c_str()) -1 ;
    int ab;
    int T = N + (seatNumber % M);

    if (ticketInfo.substr(0,1) == "A") {
        ab = 0;
    }
    else{
        ab = 1;
        }

    Person newPerson;
    newPerson.seatNumber = seatNumber;
    newPerson.type3LastOperation = 0;
    newPerson.type = personType;
    newPerson.line_origin = ab;
    newPerson.line = ab;


    // Line A
    if (ab == 0) {
        // koltuk boşsa
        if(arr[seatNumber % N].seatNumber == -1) {
            arr[seatNumber % N] = newPerson;
        }
        // if Seat is not empty
        else {
            Person tempo = arr[seatNumber % N];
            tempo.prev_seat = seatNumber % N;

            arr[seatNumber % N] = newPerson;
            recursiveSeatFunction(tempo);
                }
            }

    //Line B
    else {
        if(arr[T].seatNumber == -1) {
            arr[T] = newPerson;
        }
            // if Seat is not empty
        else {
            Person tempo = arr[T];
            tempo.prev_seat = T;

            arr[T] = newPerson;
            recursiveSeatFunction(tempo);

    }
    }
}

void SeatOperations::recursiveSeatFunction(Person& tempo) {
    int loc_A = tempo.seatNumber % N;
    int loc_B = N + (tempo.seatNumber % M);
    // TYPE_1 person
    if (tempo.type == 1) {
        // LINE A'den geliyorsa
        if (tempo.line == 0) {
            // if Seat is empty
            if (arr[loc_B].seatNumber == -1) {
                arr[loc_B] = tempo;
                arr[loc_B].line = 1;
            }
                // if Seat is not empty
            else {
                Person tempoo(arr[loc_B]);
                tempoo.prev_seat = loc_B;

                arr[loc_B] = tempo;
                arr[loc_B].line = 1;
                recursiveSeatFunction(tempoo);
            }

        }
        // LINE B'den geliyorsa
        else {
            // if Seat is empty
            if(arr[loc_A].seatNumber == -1) {
                arr[loc_A] = tempo;
                arr[loc_A].line = 0;
            }
                // if Seat is not empty
            else {
                Person tempoo(arr[loc_A]);
                tempoo.prev_seat = loc_A;

                arr[loc_A] = tempo;
                arr[loc_A].line = 0;

                recursiveSeatFunction(tempoo);
            }


        }
    }

    // TYPE_2 person

    else if (tempo.type == 2){
        // LINE A'den geliyorsa
        if (tempo.line == 0) {
            // son sıradaysa
            if (tempo.prev_seat == N-1) {
                // diğer line'ın ilk koltuğu boşsa
                if(arr[N].seatNumber == -1){
                    arr[N] = tempo;
                    arr[N].line = 1;

                }

                // diğer line'ın ilk koltuğu boş değilse
                else {
                    Person tempoo(arr[N]);
                    tempoo.prev_seat = N;

                    arr[N] = tempo;
                    arr[N].line = 1;

                    recursiveSeatFunction(tempoo);
                }
            }
            // son sırada değilse
            else{
                // bir sonraki koltuk boşsa
                if (arr[tempo.prev_seat + 1].seatNumber == -1){
                    arr[tempo.prev_seat + 1] = tempo;
                }
                // bir sonraki koltuk boş değilse
                else{
                    Person tempoo(arr[tempo.prev_seat + 1]);
                    tempoo.prev_seat = tempo.prev_seat + 1;

                    arr[tempo.prev_seat + 1] = tempo;

                    recursiveSeatFunction(tempoo);

                }


            }
        }
        // LINE B'den geliyorsa
        else if (tempo.line == 1) {
            // son sıradaysa
            if (tempo.prev_seat == N + M -1) {
                // diğer line'ın ilk koltuğu boşsa
                if(arr[0].seatNumber == -1) {
                    arr[0] = tempo;
                    arr[0].line = 0;
                }
                // diğer line'ın ilk koltuğu boş değilse
                else{
                    Person tempoo(arr[0]);
                    tempoo.prev_seat = 0;

                    arr[0] = tempo;
                    arr[0].line = 0;

                    recursiveSeatFunction(tempoo);

                }
            }
            // son sırada değilse
            else{
                // bir sonraki koltuk boşsa
                if (arr[tempo.prev_seat + 1].seatNumber == -1){
                    arr[tempo.prev_seat + 1] = tempo;
                }
                else{
                    // bir sonraki koltuk boş değilse
                    Person tempoo(arr[tempo.prev_seat + 1]);
                    tempoo.prev_seat = tempo.prev_seat + 1;

                    arr[tempo.prev_seat + 1] = tempo;

                    recursiveSeatFunction(tempoo);


                }

            }

        }

    }
    // TYPE 3 PERSON
    else{
        tempo.type3LastOperation ++;
        int sq = (tempo.type3LastOperation * tempo.type3LastOperation);
        // ORIGINAL LINE'ı A ise:
        if (tempo.line_origin == 0) {
            // seatNumber + i^2 < N ise
            if ((loc_A + sq) % (N+M) < N){
                // yeni seat boş ise
                if(arr[(loc_A + sq) % (N+M)].seatNumber == -1){
                    arr[(loc_A + sq) % (N+M)] = tempo;
                    // line değişmedi zaten
                }
                else{
                    Person tempoo(arr[(loc_A + sq) % (N+M)]);
                    tempoo.prev_seat = (loc_A + sq) % (N+M);

                    arr[(loc_A + sq) % (N+M)] = tempo;
                    // line değişmedi zaten
                    recursiveSeatFunction(tempoo);
                }

            }
                // seatNumber + i^2 >= N  & < N+M ise; yani M sırasına yerleşecekse
            else if ((loc_A + sq) % (N+M) >= N){
                // yeni seat boş ise
                if(arr[(loc_A+ sq) % (N+M)].seatNumber == -1){
                    arr[(loc_A + sq) % (N+M)] = tempo;
                    arr[(loc_A + sq) % (N+M)].line = 1;
                }
                    //yeni seat boş değilse:
                else{
                    Person tempoo(arr[(loc_A + sq) % (N+M)]);
                    tempoo.prev_seat = (loc_A + sq) % (N+M);
                    arr[(loc_A + sq) % (N+M)] = tempo;
                    arr[(loc_A + sq) % (N+M)].line = 1;
                    recursiveSeatFunction(tempoo);
                }

            }
        }
            // ORIGINAL LINE'ı B ise
        else{
            // seatNumber + i^2 < N ise ilk sıraya geçer
            if ((loc_B + sq) % (N+M) < N){
                // yeni seat boş ise
                if(arr[(loc_B + sq) % (N+M)].seatNumber == -1){
                    arr[(loc_B + sq) % (N+M)] = tempo;
                    arr[(loc_B + sq) % (N+M)].line = 0;

                }
                else{
                    Person tempoo(arr[(loc_B + sq) % (N+M)]);
                    tempoo.prev_seat = (loc_B + sq) % (N+M);

                    arr[(loc_B + sq) % (N+M)] = tempo;
                    arr[(loc_B + sq) % (N+M)].line = 0;
                    // line değişmedi zaten
                    recursiveSeatFunction(tempoo);
                }

            }
                // şayet bunun mod(N+M) değeri N'den büyükse yani B sırasında kalacaksa
            else{

                // yerleşeceği yer boşsa
                if ((arr[(loc_B + sq) % (N+M)].seatNumber == -1)) {
                    arr[(loc_B + sq) % (N+M)] = tempo;
                    // aynı sırada kaldı
                }
                    // yerleşeceği yer doluysa
                else {
                    Person tempoo = arr[(loc_B + sq) % (N+M)];
                    tempoo.prev_seat = (loc_B + sq) % (N+M);
                    arr[(loc_B + sq) % (N+M)] = tempo;
                    // aynı sırada kaldı
                    recursiveSeatFunction(tempoo);
                }
            }




        }
    }
}


void SeatOperations::printAllSeats(ofstream& outFile){
    for (int i = 0; i< N + M; i++){
        if (arr[i].seatNumber ==-1){
            outFile << 0 << endl;
        }
        else{
            if (arr[i].line_origin == 0){
                outFile << arr[i].type << " A" << arr[i].seatNumber+1 << endl;
            }
            else{
                outFile << arr[i].type << " B" << arr[i].seatNumber+1 << endl;
            }
        }
    }
}