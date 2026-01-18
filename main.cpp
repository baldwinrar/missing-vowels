#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

/* TODO:
    4. Display clue to user and prompt response
    5. Compare response with key and display result
    6. Tally score and move on to next clue
*/

int main() {

    /* Open file and read in keys */ 
    vector<string> keys;
    string filename = "bowie keys.txt";
    ifstream readfile(filename);

    if (!readfile) {
        cout << "Couldn't open file";
        return -1;
    }

    string line;
    while (getline(readfile, line)) {
        string newkey;
        // Turn each line to our format for keys, all caps no punctuation
        for (auto c: line) {
            if (isalpha(c)) {
                newkey += toupper(c);
            }
            else if (c == '\'' || c == ',' || c == '\"' || c == '!' || c == '?' || c == ':' || c == '-') {
                continue;
            }
            else {
                newkey += c;
            }
        }
        keys.push_back(newkey);
    }

    // DEBUG: Print keys to terminal
    for (auto k: keys) {
        cout << k << endl;
    }

    /* Translate keys into clues */
    vector<string> clues;
    for (auto key: keys) {
        // Count spaces and build clue-in-progress
        int clue_len = 0; int spacenum = 0;
        string consonants; string clue;
        for (auto letter: key) {
            if (letter == ' ') {
                spacenum ++;
            }
            else if (letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U') {
                continue;
            }
            else {
                consonants += letter;
            }
        }
        clue_len = consonants.length() + spacenum;

        // Randomly add spaces back in to create final clue
        if (spacenum > 0) {

            // Create list of spaces where we can place a space
            vector<int> avail_spaces;
            for (int i=1; i<consonants.length(); i++) {
                avail_spaces.push_back(i);
            }

            // Shuffle list of spaces for our spaces
            random_shuffle(avail_spaces.begin(), avail_spaces.end());

            // Remove bottom n elements to ensure we only have the spots we need
            vector<int> assigned_spaces;
            copy(avail_spaces.begin(), avail_spaces.begin() + spacenum, back_inserter(assigned_spaces));

            // Sort spots from highest to lowest
            sort(assigned_spaces.begin(), assigned_spaces.end(), greater<int>());

            // Iterate through key and spaces to build our clue!
            int pos = 0;
            for (string::iterator it=consonants.begin(); it!=consonants.end(); ++it) {
                clue += *it;
                pos ++;
                if (assigned_spaces.back() == pos) {
                    clue += " ";
                    assigned_spaces.pop_back();
                }
            }

            // Push final clue into clue vector
            clues.push_back(clue);
        }
    }

    /* Randomly select X number of clues */

    // DEBUG: print clues to terminal
    for (auto x: clues) {
        cout << x << endl;
    }

    return 0;
}