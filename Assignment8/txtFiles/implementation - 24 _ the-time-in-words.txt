#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'timeInWords' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER h
 *  2. INTEGER m
 */
string timeWord[21] = {"", "one","two","three","four","five",
                "six","seven","eight","nine","ten",
                "eleven","twelve","thirteen", "fourteen","fifteen", 
                "sixteen", "seventeen", "eighteen", "nineteen","twenty"};
string timeInWords(int h, int m) {
    if(m == 0){ return timeWord[h]+" o' clock";}
    
    if(m%15 == 0){
        if(m == 15){ return "quarter past "+ timeWord[h];}
        if(m == 30){ return "half past "   + timeWord[h];}
        if(m == 45){ return "quarter to "  + timeWord[h+1];}
    }
    
    
    int min = m;
    if(m>30){ min = 60 - m;}
    
    string res = timeWord[min%20];
    
    if(min>=20){ res = timeWord[20] + " " + res;}
    (min==1) ? res+= " minute" : res+=" minutes";
    
    if(m<30){
        return res + " past " + timeWord[h];
    }
    return res + " to " + timeWord[h+1];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string h_temp;
    getline(cin, h_temp);

    int h = stoi(ltrim(rtrim(h_temp)));

    string m_temp;
    getline(cin, m_temp);

    int m = stoi(ltrim(rtrim(m_temp)));

    string result = timeInWords(h, m);

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
