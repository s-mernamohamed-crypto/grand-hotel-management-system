#ifndef EVENTRESERVATION_H
#define EVENTRESERVATION_H
#include <string>
using namespace std;
class EventReservation {
private:
    int EventResID;
    int GuestID;
    string EventType;
    string SingerOption;
    string EventDate;
    double EventPrice;
public:
    EventReservation(int id, int gid, string type, string singer, string date, double price);
    int getEventResID() const;
    int getGuestID() const;
    string getEventType() const;
    string getSingerOption() const;
    string getEventDate() const;
    double getEventPrice() const;
    string toFileString() const;
};

#endif