#ifndef DATACRUNCH_H
#define DATACRUNCH_H
using namespace std;
#include <fstream>
#include <string>
#include "Player.h"

class DataCrunch
{
private:
    //strings and ints pertaining to .cpp
    string line, playid, name, name2, newName, teamAName, teamBName, teamcount, tags, taggerString, taggedString, secondsString, pointsString;
    int id, tagsInMatch, teamAPoints, teamBPoints, teamACount, teamBCount, tagger, tagged, seconds, points;

    //player object arrays
    Player *teamAInfo;
    Player *teamBInfo;



public:
    DataCrunch();
    void crunchTeamA(std::ifstream& teamA);
    void crunchTeamB(std::ifstream& teamB);
    void crunchMatchFile(std::ifstream& matchFile);
    void outPuttoFileLow(std::ofstream& outputFile);
    void outPuttoFileMedium(std::ofstream& outputFile);
    void outPuttoFileHigh(std::ofstream& outputFile);

};

#endif // DATACRUNCH_H
