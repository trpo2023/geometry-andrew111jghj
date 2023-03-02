#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void to_lower(std::string& s);
void err_msg(std::string str, int index, std::string err_msg);
int define_figure(std::string str);
enum Arguments { NUM, DOT };
const vector<string> name_object = { "circle" };

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
    int index = define_figure(strr);
    if (index == -1) {
        err_msg(
            strr, 0, "expected 'circle'");
        return 1;
    }

    return 0;
}

void to_lower(std::string& s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        return std::tolower(c);
        });
}

void err_msg(std::string str, int index, std::string err_msg)
{
    std::cerr << str << std::endl;
    for (int i = 0; i < index - 1; i++) {
        std::cout << " ";
    }
    std::cout << "^" << std::endl
        << "Error at column " << index << ": " + err_msg << std::endl;
}

int define_figure(std::string str)
{
    int index = -1;
    for (size_t i = 0; i < name_object.size(); i++) {
        if (str.find(name_object[i]) == 0) {
            index = i;
            break;
        };
    }
    return index;
}