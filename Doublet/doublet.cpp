//
// Created by Eason Qin on 10/10/21.
//

#include "MinHeap.h"
#include "fstream"
#include "iostream"
#include <map>
using namespace std;

int compareWords(string a, string b) {  // compute the letter difference for two words
    int count = 0;
    for (int i = 0; i < (int)a.length(); ++i) {
        if (a[i] != b[i]) {
            ++count;
        }
    }
    return count;
}

void transformUp(string& s, int length) {  // transfer each letter in a word to upper case
    for (int i = 0; i < length; i++) {
        s[i] = (char)toupper(s[i]);
    }
}

int main(int argc, char** argv) {
    string start = argv[1];
    int wordLength = start.length();
    transformUp(start, wordLength);
    string end = argv[2];
    transformUp(end, wordLength);
    string filename = argv[3];
    ifstream infile(filename);
    // store the data structure as a "graph" using a map
    // keys are the each node (each word)
    // values are the adjacent nodes to each node (word that is one letter different)
    map<string, vector<string>> wordMap;
    int num;
    string word;
    infile >> num;
    for (int i = 0; i < num; ++i) {
        infile >> word;
        if ((int)word.length() != wordLength) {  // ignore the words with different length
            continue;
        } else {
            transformUp(word, wordLength);
            vector<string> s;
            wordMap[word] = s;
        }
    }

    // add adjacent nodes
    for (map<string, vector<string>>::iterator it = wordMap.begin(); it != wordMap.end(); it++) {
        for (int i = 0; i < wordLength; ++i) {  // for each letter
            string s = it->first;
            for (int j = 65; j <= 90; ++j) {  // change to A-Z
                if (j != (int)s[i]) {
                    s[i] = (char)j;
                    map<string, vector<string>>::iterator it2 = wordMap.find(s);
                    if (it2 != wordMap.end()) {
                        (it->second).push_back(s);
                    }
                    s = it->first;
                }
            }
        }
    }

    // perform A* search
    int expandNum = 0;
    map<string, bool> expanded;
    map<string, int> step;
    MinHeap<string> search(2);
    step[start] = 0;
    search.add(start, compareWords(start, end));
    while (!search.isEmpty()) {
        string s = search.peek();
        search.remove();
        if (s == end) {  // if find the target, cout and exit
            cout << step[s] << endl;
            cout << expandNum << endl;
            exit(0);
        }
        if (expanded[s] == true) {
            continue;  // if the node has already been expanded, continue to next node
        } else {
            ++expandNum;
            expanded[s] = true;
            map<string, vector<string>>::iterator it = wordMap.find(s);
            for (int i = 0; i < (int)it->second.size(); ++i) {
                string newWord = it->second[i];
                if (expanded[newWord] == true) {
                    continue;  // if this neighbor has already been expanded, continue to next neighbor
                } else {
                    map<string, int>::iterator it2 = step.find(newWord);
                    if (it2 == step.end()) {  // if the step of the node has not been added, add it
                        step[newWord] = step[s] + 1;
                    } else if (step[newWord] > step[s] + 1) {  // if the step of the node needs update, update it
                        step[newWord] = step[s] + 1;
                    }
                    search.add(
                            newWord,
                            (step[newWord] + compareWords(newWord, end)) * (wordLength + 1)
                                    + compareWords(newWord, end));
                }
            }
        }
    }
    cout << "No transformation" << endl;
    cout << expandNum << endl;
}
