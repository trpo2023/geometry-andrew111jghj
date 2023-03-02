#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void to_lower(std::string& s);

int main() {
    string fp_iden = "Input.txt";
    ifstream fp;
    fp.open(fp_iden);
    if (fp.is_open()) {
        string strr;
        while (getline(fp, strr)) {

            to_lower(strr);
            cout << strr << endl;
        }
    }

    return 0;
}

void to_lower(std::string& s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        return std::tolower(c);
        });
}