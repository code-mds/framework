#include <string>
#include <iostream>
#include <fstream>

void es1()
{
    using namespace std;
    const int THISYEAR{2018};
    string yourName;
    int birthYear{-1};

    cout << " What is your name? " << flush;
    getline(cin, yourName);

    do {
        cout << "What year were you born? " ;
        cin >> birthYear;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            birthYear = -1;
            cout << "Invalid number " <<  endl;
        }
    } while(birthYear < 0);


    cout << "Your name is " << yourName
        << " and you are approximately "
        << (THISYEAR - birthYear)
        << " years old. " << endl;
}
