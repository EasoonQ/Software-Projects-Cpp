#include "fstream"
#include "iostream"
#include "math.h"
#include "sstream"
#include <vector>
using namespace std;

long modularExp(long b, long n, long m) {
    // change n to base2 number and use a vector to store its digits
    vector<int> nBase2;
    while (n > 0) {
        nBase2.push_back(n % 2);
        n /= 2;
    }
    // perform modular exponentiation
    long x = 1;
    long power = b % m;
    for (long i = 0; i < (long)nBase2.size(); i++) {
        if (nBase2[i] == 1) {
            x = (x * power) % m;
        }
        power = (power * power) % m;
    }
    return x;
}

// return lcd of two long
long Euc(long a, long b) {
    long R;
    while ((a % b) != 0) {
        R = a % b;
        a = b;
        b = R;
    }
    return b;
}

// return decrytion key
long extendedEuc(long e, long p, long q) {
    long L = (p - 1) * (q - 1) / Euc(p - 1, q - 1);  // use function Euc to get lcd(p-1,q-1)
    if (L <= e) {
        cout << "Bad choice of p,q. Program terminated." << endl;
        exit(1);
    }
    long t = 1;
    long old_t = 0;
    long r = e;
    long old_r = L;
    while (r != 0) {
        long quotient = old_r / r;
        long temp = r;
        r = old_r - quotient * r;
        old_r = temp;
        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }
    if (old_r != 1) {
        cout << "Bad choice of p,q. Program terminated." << endl;
        exit(1);
    }
    if (old_t < 0) {
        old_t += (p - 1) * (q - 1);
    }
    return old_t;
}

// this function decrypts an encrypted long, a
// and append the decrypted message to string& letters
// this will be called in decypt function
void toLetters(long a, string& letters, long x) {
    string result;
    while (a > 0) {
        long temp = a % 100;  // get last 2 digits
        a = a / 100;
        char temp2;
        // decrypt the char represented by last 2 digits
        if (temp == 0) {
            temp2 = ' ';
        } else {
            temp2 = (char)(temp + 96);
        }
        result = temp2 + result;
    }
    while ((long)result.length() < x) {  // add blank space
        result = ' ' + result;
    }
    letters = letters + result;
}

// this function encrypts a char
// and append the encrypted message to string& digits
// this will be called in encrypt fucntion
void toDigits(char a, string& digits) {
    int val = (int)a - 96;
    if (a == ' ') {
        digits.push_back('0');
        digits.push_back('0');
    } else if (val <= 9) {
        digits.push_back('0');
        digits.push_back((char)(val + 48));
    } else if (val >= 10 && val <= 19) {
        digits.push_back('1');
        digits.push_back((char)(val - 10 + 48));
    } else if (val >= 20) {
        digits.push_back('2');
        digits.push_back((char)(val - 20 + 48));
    }
}

void decrypt(ifstream& input, ofstream& output, long d, long n) {
    long a;
    string result;
    long x = 1 + (long)(log(n / 27) / log(100));
    while (input >> a) {
        long temp = modularExp(a, d, n);
        // each iteration, decrypt and append decrypted message in "result"
        toLetters(temp, result, x);
    }
    output << result;
}

void encrypt(ofstream& output, long n, string message, long e) {
    long x = 1 + (long)(log(n / 27) / log(100));
    long pos = 0;
    while (pos < (long)message.length()) {
        string digits;
        // each iteration, encrypt and append encrypted message in "digits"
        if (pos + x <= (long)message.length()) {  // more than x chars remained
            for (long i = 0; i < x; i++) {
                toDigits(message[pos + i], digits);
            }
        } else {  // less than x chars remained, add 00
            long count = 0;
            for (long i = 0; pos + i < (long)message.length(); i++) {
                toDigits(message[pos + i], digits);
                count++;
            }
            for (long i = 0; i < x - count; i++) {
                digits.push_back('0');
                digits.push_back('0');
            }
        }
        long num = stol(digits);
        long c = modularExp(num, e, n);
        output << c << " ";
        pos += x;
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {  // there must be 3 args
        cout << "Invalid arguments. Program terminated." << endl;
        exit(1);
    }
    long p = stol(argv[1]);
    long q = stol(argv[2]);
    if((p == 0) || (q == 0)){
        cout << "Bad choice of p,q. Program terminated." << endl;
        exit(1);
    }
    long e = 65537;
    long d = extendedEuc(e, p, q);  // encryption key
    while (1) {                     // loop and prompt the user again
        cout << "Please enter the command." << endl;
        string operation;
        if (cin >> operation) {
            if (operation == "EXIT") {
                cout << "Exit successfully." << endl;
                exit(0);
            } else if (operation == "DECRYPT") {
                string inname;
                string outname;
                if (cin >> inname >> outname) {
                    ifstream ifile(inname);
                    if (!ifile) {
                        cout << "Cannot open the input file. Program terminated." << endl;
                        exit(1);
                    }
                    ofstream ofile(outname, ofstream::trunc);  // clear the file before using as output file
                    if (!ofile) {
                        cout << "Cannot open the output file. Program terminated." << endl;
                        exit(1);
                    }
                    decrypt(ifile, ofile, d, p * q);  // n = p * q
                } else {
                    cout << "Invalid command. Program terminated" << endl;
                    exit(1);
                }
            } else if (operation == "ENCRYPT") {
                string outname;
                long n;
                if (cin >> outname >> n) {
                    ofstream ofile(outname, ofstream::trunc);  // clear the file before using as output file
                    if (n < 27) {
                        cout << "n is too small. Program terminated." << endl;
                        exit(1);
                    }
                    string message;
                    getline(cin, message);        // get the rest as the message waiting for encryption
                    message = message.substr(1);  // get rid of the leading space
                    encrypt(ofile, n, message, e);
                } else {
                    cout << "Invalid command. Program terminated" << endl;
                    exit(1);
                }
            } else {
                cout << "Invalid command. Program terminated" << endl;
                exit(1);
            }
        } else {
            cout << "Invalid command. Program terminated" << endl;
            exit(1);
        }
    }
}
