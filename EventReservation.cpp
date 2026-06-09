#include "EventReservation.h"

EventReservation::EventReservation(int id, int gid, string type, string singer, string date, double price)
    : EventResID(id), GuestID(gid), EventType(type), SingerOption(singer), EventDate(date), EventPrice(price) {}

int EventReservation::getEventResID() const { return EventResID; }
int EventReservation::getGuestID() const { return GuestID; }
string EventReservation::getEventType() const { return EventType; }
string EventReservation::getSingerOption() const { return SingerOption; }
string EventReservation::getEventDate() const { return EventDate; }
double EventReservation::getEventPrice() const { return EventPrice; }

string EventReservation::toFileString() const {
    return to_string(EventResID) + "," + to_string(GuestID) + "," +
        EventType + "," + SingerOption + "," + EventDate + "," + to_string(EventPrice);
}