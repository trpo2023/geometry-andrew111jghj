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
void prun_str(std::string& str);

enum Arguments { NUM, DOT };
const vector<string> name_object = { "circle" };
const map<const string, const vector<Arguments>> arg_object = { {
        {"circle", {DOT, NUM}},
} };

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
            int index = define_figure(strr);
            if (index == -1) {
                err_msg(
                    strr, 0, "expected 'circle'");
                return 1;
            }
            const string name = name_object[index];
            const vector<Arguments> args = arg_object.at(name);
            vector<Coord> dots = {};
            vector<double> numb = {};
            size_t s_1 = strr.find("(");
            size_t s_2 = strr.find_last_of(")");

            while (strr[s_1] == '(' && strr[s_2] == ')') {
                s_1++;
                s_2--;
            }
            if (strr[s_1] != '(' && strr[s_2] == ')') {
                err_msg(strr, s_1 + 2, "'(' expected");
                return 1;
            }
            if (strr[s_1] == '(' && strr[s_2] != ')') {
                err_msg(strr, s_2 + 2, "')' expected");
                return 1;
            }
            string arg = "";
            int arg_num = 0;
            double rad = 0;
            for (size_t i = s_1; i <= s_2 + 1; i++) {
                if (strr[i] == ',' || i == s_2 + 1) {
                    prun_str(arg);
                    if (args[arg_num] == DOT) {
                        dots.push_back(Coord::convert_symbol(arg));
                    }

                    if (args[arg_num] == NUM) {
                        numb.push_back(stod(arg));
                        if (name == "circle") {
                            rad = stod(arg);
                        }
                    }

                    arg_num++;
                    arg.clear();
                    continue;
                }

                arg += strr[i];
            }

            if (dots.size() + numb.size()
                != arg_object.at(name).size()) {
                err_msg(strr, s_2, "expected " + to_string(arg_object.at(name).size()) + ", but got " + to_string(dots.size()) + " arguments!");
                return 1;
            }

            cout << name << " ( ";
            for (Coord exd : dots) {
                cout << exd.x << " " << exd.y << " ";
            }
            if (name == "circle") {
                cout << rad << " ";
            }
            cout << ")" << endl;
        }
        return 0;
    }
};

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

void prun_str(std::string& str)
{
    size_t start = str.find_first_not_of(' ');
    if (start != std::string::npos) {
        str.erase(0, start);
    }
    size_t end = str.find_last_not_of(' ');
    if (end != std::string::npos) {
        str.erase(end + 1);
    }
}