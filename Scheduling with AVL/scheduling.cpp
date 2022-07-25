#include "avlbst.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
using namespace std;

bool isConflict (AVLTree<int, int>& class_time, vector<vector<int>> student_class, int student_num, int time_num){ // remember to delete memory
    int** student_time = new int* [student_num];
    BinarySearchTree<int, int>::iterator it;
    // initialize matrix of student-time
    // 0 indicate this time slot of this student is not used, 1 indicates used
    for (int i = 0; i < student_num; ++i) {
        student_time[i] = new int[time_num];
    }
    for (int i = 0; i < student_num; ++i) {
        for(int j = 0; j < time_num; j++){
            student_time[i][j] = 0;
        }
    }
    for (it = class_time.begin(); it != class_time.end(); ++it) {
        int coursenum = it->first;
        int timeslot = it->second;
        for (unsigned int i = 0; i < student_class.size(); ++i) {
            for (unsigned int j = 0; j < student_class[i].size(); ++j) {
                // if should be set to 1 but already set to 1, conflict
                if (student_class[i][j] == coursenum && student_time[i][timeslot] == 1){
                    for (int z = 0; z < student_num; ++z) {
                        delete student_time[z];
                    }
                    delete[] student_time;
                    return true;
                }
                // if should be set to 1 and not yet set to 1, set to 1
                else if (student_class[i][j] == coursenum){
                    student_time[i][timeslot] = 1;
                }
            }
        }
    }
    for (int z = 0; z < student_num; ++z) {
        delete student_time[z];
    }
    delete[] student_time;
    return false;
}

void scheduling (AVLTree<int, int>& class_time, vector<int> classes, vector<vector<int>> student_class, int student_num,
                 int time_num, int exam_num, int current, int& counter){
    if (current == exam_num){ // a solution has been found
        counter = 1;
        throw 100; // throw a value in order to stop the recusion and proceed to printing out
    }
    for (int i = 0; i < time_num; ++i) {
        pair<int, int> temp = make_pair(classes[current], i);
        class_time.insert(temp);
        if (!isConflict(class_time, student_class, student_num, time_num)){ // if no conflict, proceed to recursion
            scheduling(class_time, classes, student_class, student_num, time_num, exam_num, ++current, counter);
        }
        class_time.remove(classes[current]);
    }
}

int main(int argc, char** argv){
    string filename = argv[1];
    ifstream ifile(filename);
    if (!ifile){
        cout << "Cannot open the file" << endl;
    }
    int exam_num = 0;
    int student_num = 0;
    int time_num = 0;
    ifile >> exam_num >> student_num >> time_num;
    string line;
    getline(ifile, line); // get rid of the blank first line after reading in 3 values
    AVLTree<int, int> class_time;
    vector<vector<int>> student_class;
    vector<int> classes; // store different classes

    int num = 0;
    // initialize matrix of student_class
    while (!ifile.eof()){
        vector<int> emptyVec;
        student_class.push_back(emptyVec);
        string line;
        getline(ifile, line);
        stringstream ss;
        ss << line;
        string student;
        ss >> student;
        int temp;
        while (ss >> temp){
            student_class[num].push_back(temp);
            int repeat = 0;
            for (unsigned int i = 0; i < classes.size(); ++i) {
                if (classes[i] == temp){
                    repeat = 1;
                }
            }
            if (!repeat){ // only push in class that is not already stored
                classes.push_back(temp);
            }
        }
        ++num;
    }


    int counter = 0; // falg for slution, if counter = 0, no solution
    try {
        scheduling(class_time, classes, student_class, student_num, time_num, exam_num, 0, counter);
    }
    catch (int a) { // successfully catch a solution, print out
        for(BinarySearchTree<int, int>::iterator myit = class_time.begin(); myit != class_time.end(); ++myit){
            cout << myit->first << " " << 1 + myit->second << endl;
        }
    }
    if (counter == 0){
        cout << "No valid solution." << endl;
    }
}



