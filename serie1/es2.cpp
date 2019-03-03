#include <string>
#include <iostream>
#include <fstream>

void es2()
{
    using namespace std;

    int lucky{7};
    float pi{3.14};
    double e{2.71};

    ofstream outf;

    outf.open("mydata");

//    outf << lucky << endl;
//    outf << pi << endl;
//    outf << e << endl;

//  outf.open("mydata", std::fstream::trunc|std::fstream::binary);

    // ************************************************
    // https://stackoverflow.com/questions/2478121/write-set-of-integers-to-stdofstream-and-be-able-to-read-them-back
    // operator<< produces formatted text as its output
    // ************************************************
    outf.write(reinterpret_cast<char*>(&lucky),sizeof(lucky));
    outf.write(reinterpret_cast<char*>(&pi),sizeof(pi));
    outf.write(reinterpret_cast<char*>(&e),sizeof(e));
//    outf << lucky;
//    outf << pi;
//    outf << e;

    outf << "This is an example" << endl;
    outf.close();

    int i;
    float f;
    double d;
    string s;

    ifstream inf;
    inf.open("mydata");
//    inf.open("mydata", ofstream::binary);

    inf.read(reinterpret_cast<char*>(&i), sizeof(int));
    inf.read(reinterpret_cast<char*>(&f), sizeof(float));
    inf.read(reinterpret_cast<char*>(&d), sizeof(double));

//    inf >> i;
//    inf >> f;
//    inf >> d;
    inf >> s;
    inf.close();

    cout << "i:" << i << " f:" << f << " d:" << d << " s:" << s << endl;


}
