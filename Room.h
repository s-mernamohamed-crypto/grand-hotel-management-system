#ifndef ROOM_H
#define ROOM_H
#include <string>
using namespace std;
class Room {
private:
    int RoomNum;
    string RoomType;
    string RoomStatus;
    double RoomPrice;

public:
    Room();
    Room(int num, string type, double price);

    void setRoomStatus(string status);
    int getRoomNum() const;
    string getRoomType() const;
    string getRoomStatus() const;
    double getRoomPrice() const;
    string toFileString() const;
};

#endif