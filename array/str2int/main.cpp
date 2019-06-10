#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

enum Status { Valid = 0, Invalid};
int g_Status = Valid; // global status, to differentiate Invalid-Input and "0"

int __str_to_int(const char* digit, bool minus);

int StrToInt(const char* str)
{
	g_Status = Invalid;
	int num = 0;
	// check if NULL or ""
	if(str != nullptr && *str != '\0'){
		// set minus
		bool minus = false;
		if(*str == '+')
			str++;
		else if(*str == '-'){
			minus = true;
			str++;
		}
		// check if "+" or "-"
		if(*str != '\0'){
			num = __str_to_int(str,minus);
		}
	}
	return num;
}

int __str_to_int(const char* digit, bool minus)
{
	long long num = 0;
	while(*digit != '\0'){
		if(*digit >= '0' && *digit <= '9'){
			int flag = minus ? -1 : 1;
			num = num*10 + flag * (*digit-'0');
			// check overflow
			if((!minus && num > 0x7fffffff)
				|| (minus && num < (signed int)0x80000000))
			{
				num = 0;
				break;
			}
			digit++;
		}
		else{
			num = 0;
			break;
		}
	}
	// set global flag
	if(*digit == '\0'){
		g_Status = Valid;
	}
	return (int)num;
}

int main(int argc,char *argv[])
{
	vector<const char*> strs = {
		nullptr,
		"",
		"+",
		"-",
		"1259",
		"+1259",
		"-1259",
		"+12a9",
		"666666666666666666666666666666666666666666666666",
	};
	for(auto& s : strs){
		int num = StrToInt(s);
		string input = s ? s : "null";
		string status = g_Status ? "invalid" : "valid";
		cout << input << "," << status << "," << num << endl;
	}

 	return 0;
}
