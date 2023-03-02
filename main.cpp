#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    string fp_iden = "Input.txt";
    ifstream fp;
    fp.open(fp_iden);
    if (fp.is_open())
        printf("Success");
    else printf("Failed to open file");

    return 0;
}