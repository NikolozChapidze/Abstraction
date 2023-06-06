#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'countLuck' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING_ARRAY matrix
 *  2. INTEGER k
 */
 
 void getToVisit(vector<pair<int,int>> &toVisit,pair<int, int> M,vector<string> matrix){
    if(M.first - 1 >=0 && matrix.at(M.first-1)[M.second]!='X' 
        && matrix.at(M.first-1)[M.second]!= '0'){
            toVisit.push_back(make_pair(M.first-1,M.second)); 
     }
     if(M.first + 1 <matrix.size() && matrix.at(M.first+1)[M.second]!='X' 
        && matrix.at(M.first+1)[M.second]!= '0'){
            toVisit.push_back(make_pair(M.first+1,M.second)); 
     }
     if(M.second - 1 >=0 && matrix.at(M.first)[M.second-1]!='X' 
        && matrix.at(M.first)[M.second-1]!= '0'){
            toVisit.push_back(make_pair(M.first,M.second-1)); 
     }
     if(M.second + 1 <matrix.at(0).size() && matrix.at(M.first)[M.second+1]!='X' 
        && matrix.at(M.first)[M.second+1]!= '0'){
            toVisit.push_back(make_pair(M.first,M.second+1)); 
     } 
 }
 bool wrapper(int count, pair<int, int> M, int k, vector<string> matrix){
     if(matrix.at(M.first)[M.second] == '*'){
         return count == k;
     }
     vector<pair<int,int>> toVisit;
     getToVisit(toVisit,M,matrix);
     if(toVisit.size()>=2){
         count++;
     }
     matrix.at(M.first)[M.second] = '0';
     for(int i=0; i<toVisit.size();i++){
         if(wrapper(count,toVisit.at(i), k, matrix)){
             return true;
         }
     }
     return false;
 }

string countLuck(vector<string> matrix, int k) {
    int x = 0;
    int y = 0;
    for(int i=0; i<matrix.size(); i++){
        string tmp = matrix.at(i);
        if(tmp.find("M") != std::string::npos){
            x = i;
            y = tmp.find("M");
            break;
        }
    }
    pair<int,int> M =  make_pair(x, y);
    if(wrapper(0,M,k,matrix)){
        return "Impressed";
    }
    return "Oops!";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<string> matrix(n);

        for (int i = 0; i < n; i++) {
            string matrix_item;
            getline(cin, matrix_item);

            matrix[i] = matrix_item;
        }

        string k_temp;
        getline(cin, k_temp);

        int k = stoi(ltrim(rtrim(k_temp)));

        string result = countLuck(matrix, k);

        fout << result << "\n";
    }

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
