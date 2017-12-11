#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct solution{
    vector<vector<int>> cost;
    vector<vector<int>> split;
};

int multiply_cost(const vector<int> matrix_chain,
                    const int i, const int j, const int k){
    return matrix_chain[i - 1] * matrix_chain[k] * matrix_chain[j];
}

solution matrix_chain_multiply(const vector<int> matrix_chain){
    solution s;
    int n = matrix_chain.size();
    for(int i = 0; i < n; ++i){
        vector<int> temp(n, 0);
        s.cost.push_back(temp);
        s.split.push_back(temp);
    }

    for(int chain_length = 2; chain_length < n; ++chain_length)
        for(int i = 1; i < n - chain_length + 1; ++i){
            int j = i + chain_length - 1;
            s.cost[i][j] = -1;
            for(int k = i; k < j; ++k){
                int cur_cost = s.cost[i][k] + s.cost[k+1][j] + multiply_cost(matrix_chain, i, j, k);
                if (s.cost[i][j] == -1 || s.cost[i][j] > cur_cost){
                    s.cost[i][j] = cur_cost;
                    s.split[i][j] = k;
                }
            }
        }

    cout << s.cost[1][n-1] << endl;
    return s;
}

void print_chain(const vector<vector<int>> s, int i, int j){
    if (i == j)
        cout << 'A' << i;
    else{
        cout << '(';
        print_chain(s, i, s[i][j]);
        print_chain(s, s[i][j] + 1, j);
        cout << ')';
    }
}

int main(){
    vector<int> matrix_chain = {30, 35, 15, 5, 10, 20 ,25};
    solution s = matrix_chain_multiply(matrix_chain);
    print_chain(s.split, 1, matrix_chain.size() - 1);
    cout << endl;
}
