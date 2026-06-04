#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct InputData
{
    vector<char> alphabet;
    vector<string> strings;
};

int hammingDistance(const string &a, const string &b){
    int d = 0;

    for (int i = 0; i < (int)a.size(); i++)
    {
        if (a[i] != b[i])
            d++;
    }

    return d;
}

InputData getStringsFromFile(const string &filename){
    ifstream f(filename);

    if (!f.is_open())
    {
        cerr << "Failed to open " << filename << endl;
        exit(1);
    }

    int n;
    f >> n;
    f.ignore();

    vector<string> strings;
    set<char> alphabetSet;

    for (int i = 0; i < n; i++)
    {
        string s;
        getline(f, s);

        if (!s.empty() && s.back() == '\r')
            s.pop_back();

        strings.push_back(s);

        for (char c : s)
            alphabetSet.insert(c);
    }

    vector<char> alphabet(alphabetSet.begin(), alphabetSet.end());

    return {alphabet, strings};
}

void writeSolutionToFile(const string &filename, const string &solution){
    ofstream f(filename);

    if (!f.is_open())
    {
        cerr << "Failed to open " << filename << endl;
        exit(1);
    }

    f << solution << '\n';
}

int findBadString(const InputData &data, const string &holy, int k){
    int worstIndex = -1;
    int worstDistance = k;

    for (int i = 0; i < (int)data.strings.size(); i++)
    {
        int d = hammingDistance(holy, data.strings[i]);

        if (d > worstDistance)
        {
            worstDistance = d;
            worstIndex = i;
        }
    }

    return worstIndex;
}

bool solveHamming(const InputData &data, string holy, int k, int depthLeft, string &answer){
    int badIndex = findBadString(data, holy, k);

    if (badIndex == -1)
    {
        answer = holy;
        return true;
    }

    if (depthLeft == 0)
        return false;

    const string &bad = data.strings[badIndex];

    int d = hammingDistance(holy, bad);

    if (d - depthLeft > k)
        return false;

    vector<int> diffPositions;

    for (int pos = 0; pos < (int)holy.size(); pos++)
    {
        if (holy[pos] != bad[pos])
            diffPositions.push_back(pos);
    }

    for (int pos : diffPositions)
    {
        string next = holy;
        next[pos] = bad[pos];

        if (solveHamming(data, next, k, depthLeft - 1, answer))
            return true;
    }

    return false;
}

bool feasible(const InputData &data, int k, string &answer){
    string holy = data.strings[0];

    return solveHamming(data, holy, k, k, answer);
}

int getUpperBound(const InputData &data){
    string holy = data.strings[0];

    int upperBound = 0;

    for (const string &s : data.strings)
    {
        upperBound = max(upperBound, hammingDistance(holy, s));
    }

    return upperBound;
}

int main(int argc, char *argv[]){

    InputData data = getStringsFromFile(argv[1]);

    int low = 0;
    int high = getUpperBound(data);

    int bestK = high;
    string bestAnswer = data.strings[0];

    while (low <= high)
    {
        int mid = (low + high) / 2;

        cerr << "Trying k = " << mid << endl;

        string answer;

        if (feasible(data, mid, answer))
        {
            bestK = mid;
            bestAnswer = answer;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    writeSolutionToFile(string("solution") + argv[1], bestAnswer);

    cerr << "Best k found: " << bestK << endl;

    return 0;
}