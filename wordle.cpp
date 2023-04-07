#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;
// Add prototypes of helper functions here
void Answer(const std::set<std::string>& dict, std::string floating, size_t add, std::set<std::string>& right, std::string curr);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> wordle;
    Answer(dict, floating, 0, wordle, in);
    return wordle;
}
// Define any helper functions here
void Answer(const std::set<std::string>& dict, std::string floating,
            size_t add, std::set<std::string>& right, std::string curr) {
    int num = 0;

    switch(add == curr.size() && floating.empty()) {
        case true: {
            if (dict.find(curr) != dict.end()) {
                right.insert(curr);
            }
            break;
        }
        case false: {
            if (curr[add] != '-') {
                Answer(dict, floating, add + 1, right, curr);
                break;
            }
            else {
                for (size_t j = 0; j < curr.size(); j++) {
                    if (curr[j] == '-') {
                        num = num + 1;
                    }
                }
                string currVar = floating;
                if ((int)currVar.size() == num) {
                    // go through all the floats 
                    for (size_t j = 0; j < currVar.size(); j++) {
                        curr[add] = currVar[j];
                        string copy = currVar;
                        copy.replace(j, 1, "");
                        Answer(dict, copy, add + 1, right, curr);
                    }
                }
                else if (num > (int)currVar.size()) {
                    // go through a to z 
                    for (int track = 97; track <= 122; track++) {
    switch (currVar.find(track)) {
        case string::npos:
            curr[add] = track;
            Answer(dict, currVar, add + 1, right, curr);
            break;
        default:
            curr[add] = track;
            string copy = currVar;
            copy.replace(copy.find(track), 1, "");
            Answer(dict, copy, add + 1, right, curr);
            break;
    }
}
            }
        }
    }
}
            }