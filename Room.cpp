#include "Room.h"
Room::Room() : RoomNum(0), RoomPrice(0.0) {}
Room::Room(int num, string type, double price) : RoomNum(num), RoomType(type), RoomStatus("Available"), RoomPrice(price) {}
void Room::setRoomStatus(string status) { RoomStatus = status; }
int Room::getRoomNum() const { return RoomNum; }
string Room::getRoomType() const { return RoomType; }
string Room::getRoomStatus() const { return RoomStatus; }
double Room::getRoomPrice() const { return RoomPrice; }

string Room::toFileString() const {
    return to_string(RoomNum) + "," + RoomType + "," + RoomStatus + "," + to_string(RoomPrice);
}