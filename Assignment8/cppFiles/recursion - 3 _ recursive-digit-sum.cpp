#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'superDigit' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING n
 *  2. INTEGER k
 */
 string wrapper(int temp, int k){
     string result;
     string num = to_string(temp);
     int extra  = 0;
     int helper = 0;
     for(int i=0; i<num.length(); i++){
        string s(1, num[num.length()-i-1]);
        helper = (stoi(s) * k) + extra; 
        extra = helper/10;
        helper = helper%10; 
        result = to_string(helper) + result;
     }
     if(extra != 0){
         result = to_string(extra) + result;
     }
    
    return result;
 }

int superDigit(string n, int k) {
    if(n.length() == 1){
        return stoi(n);
    }
    int temp   = 0;
    for(int i=0; i<n.length(); i++){
        string s(1, n[i]);
        temp += stoi(s); 
    }
    
    if( k!=1){
        n = wrapper(temp,k);
    }else{
        n = to_string(temp);
    }
     
    return superDigit(n, 1);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    string n = first_multiple_input[0];

    int k = stoi(first_multiple_input[1]);

    int result = superDigit(n, k);

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
