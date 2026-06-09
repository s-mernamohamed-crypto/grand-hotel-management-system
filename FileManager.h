#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include "Room.h"
#include "Reservation.h"
#include "EventReservation.h"
#include "User.h"

class FileManager {
public:
    void SaveAll(const vector<Room>& rooms, const vector<Reservation>& res, const vector<User*>& users, const vector<EventReservation>& events);
    void LoadRooms(vector<Room>& rooms);
    void LoadUsers(vector<User*>& users);
    void LoadReservations(vector<Reservation>& res);
    void LoadEvents(vector<EventReservation>& evs);
};

#endif