#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<vector<int>> LCS_Length(const string& s1, const string& s2){
    vector<vector<int>> m;
    for (size_t i = 0; i <= s1.size(); ++i)
        m.push_back(vector<int>(s2.size() + 1));

    for (size_t i = 0; i <= s1.size(); ++i)
        m[i][0] = 0;
    for (size_t i = 0; i <= s2.size(); ++i)
        m[0][i] = 0;

    for (size_t i = 1; i <= s1.size(); ++i)
        for (size_t j = 1; j <= s2.size(); ++j){
            if (s1[i - 1] == s2[j - 1])
                m[i][j] = m[i - 1][j - 1] + 1;
            else if (m[i - 1][j] >= m[i][j - 1])
                m[i][j] = m[i - 1][j];
            else
                m[i][j] = m[i][j - 1];
        //cout << m[i][j] << endl;
        }

    //cout << m[s1.size()][s2.size()] << endl;
    return m;
}

void print_LCS(const vector<vector<int>>& m, const string& s1,
                    const string& s2, int i, int j){
    if (i == 0 || j == 0)
        return;
    if (m[i][j] == m[i - 1][j - 1] + 1){
        print_LCS(m, s1, s2, i - 1, j - 1);
        cout << s1[i - 1];
    }else if (m[i - 1][j] >= m[i][j - 1])
        print_LCS(m, s1, s2, i - 1, j);
    else
        print_LCS(m, s1, s2, i, j - 1);
}

int main(){
    vector<string> v1({"ABCBDAB", "10010101",
                       "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA"});
    vector<string> v2({"BDCABA", "010110110",
                       "GTCGTTCGGAATGCCGTTGCTCTGTAAA"});

    for (int i = 0; i < 3; ++i){
        string s1 = v1[i];
        string s2 = v2[i];
        cout << "S1: " << s1 << endl;
        cout << "S2: " << s2 << endl;

        vector<vector<int>> m(LCS_Length(s1, s2));

        cout << "Maximum length of LCS is: ";
        cout << m[s1.size()][s2.size()] << endl;

        cout << "One of LCSs is: ";
        print_LCS(m, s1, s2, s1.size(), s2.size());
        cout << endl << endl;
    }
}
