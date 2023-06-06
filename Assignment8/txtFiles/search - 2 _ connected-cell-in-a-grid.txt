#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'connectedCell' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */
 int wrapper(set<pair<int,int>> &visited, int result,
            vector<vector<int>> matrix,int i, int j){
    
    if(matrix[i][j] == 0){
        return 0;
    }            
    
    result++;
        
    visited.insert(make_pair(i, j));
    
    int startX = (i == 0) ? i : i-1;
    int startY = (j == 0) ? j : j-1;
    int endX = (i == matrix.size()-1) ? i : i+1;
    int endY = (j == matrix[i].size()-1) ? j : j+1;
    
    for(int x = startX; x<=endX; x++){
        for(int y = startY; y<=endY; y++){
            if(visited.find(make_pair(x, y)) == visited.end()){
                result += wrapper(visited, 0, matrix, x, y);
            }
        }
    }
    
    return result;
 }

int connectedCell(vector<vector<int>> matrix) {
    set<pair<int, int>> visited;
    int result = 0;
    for(int i=0; i<matrix.size();i++){
        for(int j=0; j<matrix[i].size(); j++){
            if(visited.find(make_pair(i, j)) == visited.end()){
            int temp = wrapper(visited,0,matrix, i, j);
            if(temp>result){
               result =temp;
            }
            }
        }
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string m_temp;
    getline(cin, m_temp);

    int m = stoi(ltrim(rtrim(m_temp)));

    vector<vector<int>> matrix(n);

    for (int i = 0; i < n; i++) {
        matrix[i].resize(m);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < m; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    int result = connectedCell(matrix);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
