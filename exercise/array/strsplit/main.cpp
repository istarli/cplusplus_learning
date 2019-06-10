#include <iostream>
#include <vector>
using namespace std;

vector<string> split(string s, char c){
    vector<string> res;
    int last = 0;
    for(int i = 0; i < s.size(); ++i){
        if(c == s[i]){
        	if(i != last)
            	res.push_back(move(s.substr(last,i-last)));
            last = i+1;
        }
    }
    res.push_back(move(s.substr(last,s.size()-last)));
    return res;
}

int main(int argc,char *argv[])
{
    // auto res = split("abbacdeafaaf",'a');
    for(auto& s : split("abbacdeafaaf",'a'))
        cout << s << endl;

 	return 0;
}
