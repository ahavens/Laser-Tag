#include "Player.h"
#include <iostream>

using namespace std;

Player:: Player()
{
    teamPoints  = 0;
}

Player:: Player(int playID, string playname)
{
    id = playID;
    name = playname;
    teamPoints = 0;
}

void Player::setPlayID(int playID)
{
    id = playID;
}

int Player::getPlayID()
{
    return id;
}

void Player::getPlayName(string playName)
{
    name = playName;
}

string Player:: showName()
{
    return name;
}

//add onto the points the player has
void Player::addPoints(int playPoints)
{
    if(playPoints == 1)
    {
        points += 5;
    }
    else if(playPoints == 2)
    {
        points += 8;
    }
    else if(playPoints == 3)
    {
        points += 10;
    }
    else if(playPoints == 4)
    {
        points += 15;
    }
    else points += 0;
}

int Player:: getPoints()
{
    return points;
}

//determines how many times the player tagged someone, doesn't matter who
 void Player::timesPlayerTagged()
 {
     timesTagged += 1;
 }
 int Player::getTagged()
 {
    return timesTagged;
 }

//array is declared and filled with oppteam's player IDs
void Player::createArray(int oppTeamCount, Player*& oppTeamInfo)
{
    oppPlayerCount = oppTeamCount;

    //two dimensional array is initialized
    taggingArray = new int*[oppPlayerCount];
    for(int i = 0; i < oppPlayerCount; i++)
        taggingArray[i] = new int[2];

    //Now fill with oppTeamIDs
    for(int i = 0; i < oppPlayerCount; i++)
    {
        taggingArray[i][0] = oppTeamInfo[i].getPlayID();
        for(int j = 1; j < 2; j++)
            taggingArray[i][j] = 0;
    }

}

//adds onto the number of times a player tagged a specific person
void Player::addToTag(int& oppPlayID)
{
    for(int i = 0; i < oppPlayerCount; i++)
    {
        for(int j = 1; j < 2; j++)
        {
            if(taggingArray[i][0] == oppPlayID)
                taggingArray[i][j] += 1;
        }
    }
}

//returns the number of times a player tagged a specific person
int Player::returnTagInfo(int oppPlayID)
{
    int taggedTimes;
    for(int i = 0; i < oppPlayerCount; i++)
    {
        for(int j = 1; j < 2; j++)
        {
            if(taggingArray[i][0] == oppPlayID)
                taggedTimes = taggingArray[i][j];
        }
    }
    return taggedTimes;
}

//adds up all the team points and returns them
int Player::returnTeamPoints(Player*& teamArray, int teamCount)
{
    for(int i = 0; i < teamCount; i++)
    {
        teamPoints += teamArray[i].getPoints();
    }
    return teamPoints;
}

//organizes the team by who has the highest number of tags
void Player::organizeTeamArray(Player*& teamArray, int teamCount)
{
    Player tempplayer;
    //Need to sort array to determine who has highest tag, using an exchange sort example
      for (int i=0; i< (teamCount -1); i++)    // element to be compared
        {
           for(int j = (i+1); j < teamCount; j++)   // rest of the elements
              {
                 if (teamArray[i].getPoints() < teamArray[j].getPoints())          // descending order
                  {
                            tempplayer= teamArray[i];          // swap
                            teamArray[i] = teamArray[j];
                            teamArray[j] = tempplayer;
                  }
               }
         }
}

//determines who has the highest score in the team
int Player::highestScore(Player*& teamArray, int teamCount)
{
    int tempPlayer = 0;
    int points = 0;

    //need to figure out who has the highest score for team A
    for(int i = 0; i < teamCount; i++)
    {
        if(teamArray[i].getPoints() > points)
        {
            tempPlayer = i;
            points = teamArray[i].getPoints();
        }
    }
    return tempPlayer;
}
