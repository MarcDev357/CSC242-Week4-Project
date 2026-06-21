/*
 * ============================================================
 * Program Name : SpellChecker.cpp
 * Course       : CSC 242
 * Assignment   : Signature Assignment (Group Project)
 * Team Members : Marcus Wiggs, David Cruz, Cassius Miller
 * Date         : June 2026
 *
 * Description  :
 *   Spell Checker — P8.2
 *   Reads each word of a target file and prints any word that
 *   is not found in the system dictionary word list
 *   (/usr/share/dict/words, provided locally as words.txt).
 *
 * Usage        :
 *   Run the program, then enter the name of the file to check
 *   when prompted (e.g., test.txt).
 *
 * Work split   :
 *   Marcus Wiggs — normalize, loadDictionary, checkFile, main
 * ============================================================
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// On UNIX/Linux/Mac this would be "/usr/share/dict/words".
// On Windows: download a copy of that word list, save it as
// words.txt in the SpellChecker project folder (next to the
// .vcxproj file), since that's the working directory when you
// run from Visual Studio.
const string DICTIONARY_FILE = "words.txt";

// ----- Author: Marcus Wiggs -----
// Strips punctuation and forces lowercase so comparisons are
// case-insensitive (e.g. "The" matches dictionary entry "the").
string normalize(const string& word)
{
    string result;
    for (char c : word)
    {
        if (isalpha(static_cast<unsigned char>(c)))
        {
            result += static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
    }
    return result;
}

// ----- Author: Marcus Wiggs -----
// Reads every word from the dictionary file into a vector of
// normalized strings. Exits if the file cannot be opened.
vector<string> loadDictionary(const string& filename)
{
    ifstream dictFile(filename);
    if (dictFile.fail())
    {
        cout << "Error: could not open dictionary file \""
            << filename << "\"." << endl;
        exit(1);
    }

    vector<string> words;
    string word;
    while (dictFile >> word)
    {
        words.push_back(normalize(word));
    }
    dictFile.close();
    return words;
}

// ----- Author: Marcus Wiggs -----
// Reads every word from the target file. If a word is not found
// in the dictionary vector, prints its original spelling.
void checkFile(const string& filename, const vector<string>& words)
{
    ifstream inFile(filename);
    if (inFile.fail())
    {
        cout << "Error: could not open file \""
            << filename << "\"." << endl;
        exit(1);
    }

    string word;
    while (inFile >> word)
    {
        string cleaned = normalize(word);
        // Skip empty tokens (e.g. all-punctuation), then search
        // the dictionary vector for the cleaned word.
        if (!cleaned.empty() &&
            find(words.begin(), words.end(), cleaned) == words.end())
        {
            cout << word << endl;   // print the original, not the normalized form
        }
    }
    inFile.close();
}

// ----- Author: Marcus Wiggs -----
int main()
{
    vector<string> words = loadDictionary(DICTIONARY_FILE);

    cout << "Enter the name of the file to spell-check: ";
    string filename;
    cin >> filename;

    cout << "\nWords not found in the dictionary:\n";
    checkFile(filename, words);

    return 0;
}