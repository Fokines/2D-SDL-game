#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>

using namespace std;

class Player
{
private:
    int score;
    string playerName;
public:
    Player() { }

    int getScore() { return score; }

    void setScore(int score) { this->score = score; }

    string getPlayerName() { return playerName; }

    void setPlayerName(string playerName) { this->playerName = playerName; }

    bool readScore(ifstream &in)
    {
        int size;
        char buf[100] = "";
        if(!in.eof()&&in.peek() >= 0)
        {
            in.read((char*)&score, sizeof (int*));
            in.read((char*)&size, sizeof (int*));
            in.read((char*)buf, size);
            playerName = buf;
            return true;
        }
        return false;
    }

    bool writeScore(ofstream &on)
    {
        int size;
        on.write((char*)&score, sizeof (int*));
        size = playerName.size();
        on.write((char*)&size, sizeof (int*));
        on.write((char*)playerName.c_str(), size);
        return true;
    }

    ~Player(){ }
};

#endif // PLAYER_H

