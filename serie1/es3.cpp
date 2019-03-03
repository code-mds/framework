#include <iostream>
#include <fstream>

using namespace std;

void es3() {
    //cout << "inserire la sequenza abcdefghijklmnopqrstuvwxyz" << endl;

    ofstream outf("data.txt");
    for (auto i{50}; i<80; i++) {
        outf << static_cast<char>(i);
    }
    outf.flush();
    outf.close();

    ifstream inf("data.txt");
    char c;

    while(inf.get(c))
        cout << c;
    cout << endl;
}
