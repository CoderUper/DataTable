#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    fstream in;
    in.open("FileDS.txt");
    int n=1;
    string s;
    while(in>>s)
    {
        cout<<s<<endl;
        n++;
    }
    in.close();
    return 0;
}

