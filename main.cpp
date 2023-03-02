#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void to_lower(std::string& s);

struct Coord {
    int x;
    int y;

    static Coord convert_symbol(string& str)
    {
        Coord dot = { 0, 0 };
        string val = "";
        bool x_true = false;
        for (size_t i = 0; i < str.length(); i++) {
            if ((str[i] == ' ' && str[i + 1] != ' ') || i == str.length() - 1) {
                if (i == str.length() - 1) {
                    val += str[i];
                }
                if (!x_true) {
                    dot.x = stoi(val);
                    x_true = true;
                }
                else {
                    dot.y = stoi(val);
                }
                val.clear();
            }

            if (str[i] == ' ') {
                continue;
            }
            val += str[i];
        }
        return dot;
    }
};


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