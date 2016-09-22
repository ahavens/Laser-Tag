#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

using namespace std;

class Player
{
private:
    int id;
    string name;
    int oppID;
    int timesTagged;
    int timeTaggedWho;
    int oppPlayerCount;
    //dynamic array created to hold IDs and times tagged of opposite team
    int **taggingArray;


public:
    int points;
    int tags;
    Player();
    //a player object has their id number, name, points, and number of times they tagged a person
    Player(int id, string name);
    Player(int id, string name,int points,int tags, int oppID);
    void addPoints(int points);
    int getPoints();
    void getPlayName(string name);
    void setPlayID(int playID);
    int getPlayID();
    string showName();
    int teamPoints;

    void timesPlayerTagged();
    int getTagged();
    void createArray(int oppTeamCount, Player*& oppTeamInfo);
    void addToTag(int& oppPlayID);
    int returnTagInfo(int oppPlayID);
    int returnTeamPoints(Player*& teamArray, int teamCount);
    void organizeTeamArray(Player*& teamArray, int teamCount);
    int highestScore(Player*& teamArray, int teamCount);



};

#endif // PLAYER_H

