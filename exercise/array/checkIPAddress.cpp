#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    string validIPAddress(string IP)
    {
        if (checkIPv4(IP))
            return "IPv4";
        else if (checkIPv6(IP))
            return "IPv6";
        return "Neither";
    }

    bool checkIPv4(const string &IP)
    {
        auto v = split(IP, ".");
        if (v.size() != 4)
            return false;
        for (auto &s : v)
        {
            if (!checkIPv4Num(s))
                return false;
        }
        return true;
    }

    bool checkIPv6(string &IP)
    {
        auto v = split(IP, ":");
        if (v.size() != 8)
            return false;
        for (auto &s : v)
        {
            if (!checkIPv6Num(s))
                return false;
        }
        return true;
    }

    bool zeroStart(const string &s)
    {
        if (s.size() > 1 && s[0] == '0')
            return true;
        return false;
    }

    bool checkIPv4Num(const string &s)
    {
        int n = s.size();
        if (n == 0 || n > 3 || zeroStart(s))
            return false;
        for (auto c : s)
        {
            if (!checkDecimal(c))
                return false;
        }
        if (s < "0" || s > "255")
            return false;
        return true;
    }

    bool checkDecimal(char c)
    {
        return c >= '0' && c <= '9';
    }

    bool checkIPv6Num(const string &s)
    {
        int n = s.size();
        if (n == 0 || n > 4)
            return false;
        for (auto c : s)
        {
            if (!checkHex(c))
                return false;
        }
        return true;
    }

    bool checkHex(char c)
    {
        return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9');
    }

    vector<string> split(const string &s, const string &sub)
    {
        vector<string> res;
        int pos = 0, pos_old = 0;
        while ((pos = s.find(sub, pos_old)) != -1)
        {
            res.push_back(s.substr(pos_old, pos - pos_old));
            pos_old = pos + sub.size();
        }
        if (pos_old < s.size())
            res.push_back(s.substr(pos_old));
        else
            res.push_back("");
        return res;
    }
};

int main()
{
    cout << Solution().validIPAddress("20EE:FGb8:85a3:0:0:8A2E:0370:7334") << endl;
    return 0;
}