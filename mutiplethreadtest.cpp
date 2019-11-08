#include <iostream>
#include <pthread.h>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;
string path="./data/";
int pid=1;
pthread_mutex_t mutex;
void* insert_to_file(void* filename)
{
    srand((int)(time(0)));
    string file=path+(char*)filename+".txt";
    ofstream out(file);
    vector<string> datas;
    for(int i=0;i<1000;i++)
    {
        string line;
        line.clear();
        for(int j=0;j<100;j++)
        {
            line=line+to_string(rand()%10000)+" ";
        }
        out<<line<<"\n";
    }
    out.close();
    pthread_mutex_lock(&mutex);
    cout<<pid++<<"thread finished\n";
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_t pids[1000];
    int filename[10001];
    for(int i=1;i<=1000;i++)
    {
        filename[i]=i;
        pthread_create(&pids[i],NULL,insert_to_file,(void*)&filename[i]);
        pthread_detach(pids[i]);
    }
    return 0;
}


