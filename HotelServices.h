#ifndef HOTELSERVICES_H
#define HOTELSERVICES_H

#include "User.h"
#include "ApplicationManager.h"

class HotelServices {
public:
    static void DisplayServicesMenu(Guest* guest, ApplicationManager& sys);
};

#endif