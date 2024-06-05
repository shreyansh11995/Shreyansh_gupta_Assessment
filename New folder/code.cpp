#include<bits/stdc++.h>
using namespace std;

vector<string> readWords(const string& fileName) {
    ifstream file(fileName);
    vector<std::string> words;
    string word;
    while (getline(file, word)) {
        words.push_back(word);
    }
    return words;
}
bool checkCompoundWord(const string& word, const unordered_set<string>& wordsSet, unordered_map<string, bool>& m) {
    if (m.find(word) != m.end()) {
        return m[word];
    }
    for (int i = 1; i < word.size(); ++i) {
        string prefix = word.substr(0, i);
        string suffix = word.substr(i);
        if (wordsSet.find(prefix) != wordsSet.end() && (wordsSet.find(suffix) != wordsSet.end() || checkCompoundWord(suffix, wordsSet, m))) {
            m[word] = true;
            return true;
        }
    }
    m[word] = false;
    return false;
}
pair<string, string> longestCompoundWords(const vector<string>& words) {
    unordered_set<string> wordsSt(words.begin(), words.end());
    unordered_map<string, bool> m;
    vector<string> compoundWords;

    for (const string& word : words) {
        if (checkCompoundWord(word, wordsSt, m)) {
            compoundWords.push_back(word);
        }
    }

    sort(compoundWords.begin(), compoundWords.end(), [](const string& a, const string& b) {
        return a.size() > b.size();
    });

    if (compoundWords.size() < 2) {
        return {"", ""};
    }

    return {compoundWords[0], compoundWords[1]};
}
void result(const string& fileName) {
    auto st = chrono::high_resolution_clock::now();
    
    vector<string> words = readWords(fileName);
    auto res = longestCompoundWords(words);
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timeTaken = end - st;

    cout<< "File: " << fileName << endl;
    cout<< "Longest Compound Word: " << res.first << endl;
    cout<< "Second Longest Compound Word: " << res.second << endl;
    cout<< "Time taken to process file: " << timeTaken.count() << " milliseconds\n" << endl;
}

int main() {
    vector<string> input = {"Input_01.txt", "Input_02.txt"};

    for (const string& file : input) {
        result(file);
    }

    return 0;
}
