#include <bits/stdc++.h>
using namespace std;

int GCD(int a,int b){
	if(b == 0) return a;
	return GCD(b,a%b);
}

int str2int(string s) {
	stringstream ss(s);
	int x;
	ss >> x;
	return x;
}

string int2str(int a) {
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}

string char2str(char a) {
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}

string reverse(string s) {
	for (int i = 0, j = s.length() - 1; i < j; i++, j--) {
		swap(s[i], s[j]);
	}
	return s;
}

int binary2int(int num) {
	int bin = num, dec = 0, rem, base = 1;
	cin >> num;
	bin = num;
	while (num > 0) {
		rem = num % 10;
		dec = dec + rem * base;
		base = base * 2;
		num = num / 10;
	}
	cout << "The decimal equivalent of " << bin << " : " << dec << endl;
	return dec;
}

string int2binary(unsigned int val) {
	unsigned int mask = 1 << (sizeof(int) * 8 - 1);
	string s = "";
	for (int i = 0; i < (int) (sizeof(int) * 8); i++) {
		if ((val & mask) == 0) {
			s.append("0");
		} else {
			s.append("1");
		}
		mask >>= 1;
	}
	cout << "The binary equivalent of " << val << " : " << s << endl;
	return s;
}

bool is_the_double_is_integer(double value) {
	int num = ceil(value);
	double newValue = (double) num;
	if (abs(value - newValue) <= 0.00000000000001) {
		return true;
	} else {
		return false;
	}
}

string char_array_2_string(char * a) {
	int Len = strlen(a);
	string s = "";
	for (int i = 0; i < Len; i++) {
		s = s.append(char2str(a[i]));
	}
	return s;
}

char * string_2_char_array(string s) {
	int Len = s.length();
	char a[Len + 1];
	for (int i = 0; i < Len; i++) {
		a[i] = s[i];
	}
	a[Len] = '\0';
	return a;
}

string remove_leading_space(string s) {
	string t = "";
	int Len = s.length();
	int i = 0;
	while (i < Len && s[i] == ' ')
		i++;
	for (int c = i; c < Len; c++) {
		t = t.append(char2str(s[c]));
	}
	return t;
}

string remove_trailing_space(string s) {
	string t = "";
	int Len = s.length();
	int i = Len - 1;
	while (i >= 0 && s[i] == ' ')
		i--;
	for (int c = 0; c <= i; c++) {
		t = t.append(char2str(s[c]));
	}
	return t;
}

void string_input_coma_delimetre() {
	char tokenstring[] = "Hello,25.5,World,15";
	int i;
	double fp;
	char o[10], f[10], s[10], t[10];

	int result = sscanf(tokenstring, "%[^','],%[^','],%[^','],%s", o, s, t, f);
	fp = atof(s); //Convert from string to float;
	i = atoi(f); //Convert from string to int;
	printf(" %s\n %lf\n %s\n %d\n", o, fp, t, i);
}

void string_input_other_delimetre() {
	char text[120] = "hello.123.234.223";
	int a[3] = { -1, -1, -1 };
	char str[120];
	sscanf(text, "%[a-z-A-Z].%d.%d.%d", &str, &a[0], &a[1], &a[2]);

	//%[a-z-A-Z] indicate to store all characters from a to z, A to Z.
	//And you can add in any symbol and numbers such as add in 0-9 and underscore.
	//Example : %[a-z-A-Z-0-9-_]
	printf("%s, %d, %d, %d\n", str, a[0], a[1], a[2]);
}

void sscanf_known_no_of_inputs_in_a_line() {
	char sentence[] = "Rudolph is 12 years old";
	char s1[20], s2[20], s3[20], s4[20];
	int i;
	sscanf(sentence, "%s %s %d %s %s", &s1, &s2, &i, &s3, &s4);
	printf("%s\n%s\n%d\n%s\n%s\n", s1, s2, i, s3, s4);
}

void stringstream_unknown_no_of_integer_inputs_in_a_line() {
	stringstream ss;
	string input = "a b c 4 e 10 15 frd 20 50 hh 100";
	ss << input;
	int found;
	string temp;

	while (getline(ss, temp, ' ')) {
		if (stringstream(temp) >> found) {
			cout << found << endl;
		}
	}
}

void unknown_no_of_any_inputs_in_a_line() {
	char input[] = "10 12 hello 15 20 hahaha 30 Good 50";
	int Len = strlen(input);
	string s = "";
	for (int i = 0; i < Len; i++) {
		if (input[i] == ' ') {
			if (s.length() != 0) {
				if (s[0] >= '0' && s[0] <= '9') {
					int int_value = str2int(s);
					cout << "The int value is: " << int_value << endl;
				} else {
					cout << "The string value is: " << s << endl;
				}
			}
			s = "";
		} else {
			s = s.append(char2str(input[i]));
		}
	}

	//For the last value:
	if (s.length() != 0) {
		if (s[0] >= '0' && s[0] <= '9') {
			int int_value = str2int(s);
			cout << "The int value is: " << int_value << endl;
		} else {
			cout << "The string value is: " << s << endl;
		}
	}
}

int main() {
    string_input_coma_delimetre();
	return 0;
}
