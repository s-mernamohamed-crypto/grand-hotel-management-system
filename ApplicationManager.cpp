#include "ApplicationManager.h"

ApplicationManager::ApplicationManager() {
    fileMgr.LoadRooms(rooms);
    fileMgr.LoadUsers(users);
    fileMgr.LoadReservations(reservations);
    fileMgr.LoadEvents(events);
}

ApplicationManager::~ApplicationManager() {
    ExitAndSave();
    for (auto u : users) delete u;
}

void ApplicationManager::ExitAndSave() { fileMgr.SaveAll(rooms, reservations, users, events); }

User* ApplicationManager::AuthenticateUser(string u, string p) {
    for (auto user : users) if (user->loggin(u, p)) return user;
    return nullptr;
}

void ApplicationManager::RegisterNewGuest(string u, string p) {
    users.push_back(new Guest(u, users.size() + 1, p));
    ExitAndSave();
}

vector<Room>& ApplicationManager::getRooms() { return rooms; }
vector<Reservation>& ApplicationManager::getReservations() { return reservations; }
vector<EventReservation>& ApplicationManager::getEvents() { return events; }

int ApplicationManager::generateReservationID() { return (reservations.empty() ? 1 : reservations.back().getReservationID() + 1); }
int ApplicationManager::generateEventID() { return (events.empty() ? 1 : events.back().getEventResID() + 1); }

int ApplicationManager::getEventCountOnDate(string date) {
    int count = 0;
    for (const auto& ev : events) {
        if (ev.getEventDate() == date) count++;
    }
    return count;
}

double ApplicationManager::CalculateGuestTotalBill(int guestID, double extraCharges) {
    double total = extraCharges;
    for (const auto& res : reservations) {
        if (res.getGuestID() == guestID) {
            for (const auto& r : rooms) {
                if (r.getRoomNum() == res.getRoomNum()) {
                    double mealPrice = (res.getBreakfast() * 100.0) + (res.getLunch() * 200.0) + (res.getDinner() * 250.0);
                    total += res.getDuration() * (r.getRoomPrice() + mealPrice);
                    break;
                }
            }
        }
    }
    for (const auto& ev : events) {
        if (ev.getGuestID() == guestID) {
            total += ev.getEventPrice();
        }
    }
    return total;
}