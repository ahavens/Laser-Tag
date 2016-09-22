#include <iostream>
#include <string>
#include <fstream>
#include "Player.h"
#include "DataCrunch.h"
using namespace std;

//when running ./main teamA.txt teamB.txt MatchFile.txt

int main(int argc, char *argv[])
{
    //counts number of text files
    if(argc != 6)
    {
        cout<<"invalid number of arguments, shame on you";
        exit(1);
    }

    string verbosity = argv[5];
    //input objects for all text files
    ifstream teamA(argv[1]);
    ifstream teamB(argv[2]);
    ifstream matchInfo(argv[3]);
    //output file
    ofstream outPutFile(argv[4]);
    //data crunch object to access the class
    //note there is print output so need to get rid of that
    DataCrunch *object = new DataCrunch();
    object->crunchTeamA(teamA);
    object->crunchTeamB(teamB);
    object->crunchMatchFile(matchInfo);

    if(verbosity.compare("vlow") == 0)
    {
       object->outPuttoFileLow(outPutFile);
    }
    else if(verbosity.compare("vmed") == 0)
    {
       object->outPuttoFileMedium(outPutFile);
    }
    else if(verbosity.compare("vhigh") == 0)
    {
       object->outPuttoFileHigh(outPutFile);
    }

    return 0;
}
