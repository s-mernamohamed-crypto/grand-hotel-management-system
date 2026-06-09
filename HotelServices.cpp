#include "HotelServices.h"
#include <iostream>
using namespace std;
void HotelServices::DisplayServicesMenu(Guest* guest, ApplicationManager& sys) {
    int mainChoice;
    while (true) {
        cout << "\n--- Hotel Services ---\n"
             << "1. Spa & Wellness (Massage, Gym, Facial, Pedicure, Manicure)\n"
             << "2. Room Service (Food Menu, Laundry, Ironing)\n"
             << "3. Medical Services\n"
             << "4. Return to Dashboard\n"
             << "Choice: ";
        cin >> mainChoice;
        if (mainChoice == 1) {
            cout << "\n-- Spa & Wellness --\n"
                 << "1. Massage (500 EGP)\n"
                 << "2. Gym Access (150 EGP)\n"
                 << "3. Facial Treatment (300 EGP)\n"
                 << "4. Pedicure (200 EGP)\n"
                 << "5. Manicure (200 EGP)\n"
                 << "Select to book (or 0 to cancel): ";
            int s; cin >> s;
            double price = 0.0; string sName = "";
            if (s == 1) { price = 500.0; sName = "Massage"; }
            else if (s == 2) { price = 150.0; sName = "Gym Access"; }
            else if (s == 3) { price = 300.0; sName = "Facial Treatment"; }
            else if (s == 4) { price = 200.0; sName = "Pedicure"; }
            else if (s == 5) { price = 200.0; sName = "Manicure"; }
            if (sName != "") {
                guest->addExtraCharge(price);
                cout << "\n===============================\n";
                cout << sName << " booked successfully!\n";
                cout << "Service Price: " << price << " EGP\n";
                cout << "Total Bill till now: " << sys.CalculateGuestTotalBill(guest->getid(), guest->getExtraCharges()) << " EGP\n";
                cout << "===============================\n";
            }
        }
        else if (mainChoice == 2) {
            cout << "\n-- Room Service --\n"
                 << "1. Food Menu Request\n"
                 << "2. Laundry (50 EGP per item)\n"
                 << "3. Ironing (30 EGP per item)\n"
                 << "Select to book (or 0 to cancel): ";
            int s; cin >> s;
            double price = 0.0; string sName = "";
            if (s == 1) {
                cout << "1. Burger (150 EGP)\n2. Pizza (200 EGP)\n3. Pasta (180 EGP)\nChoice: ";
                int f; cin >> f;
                if(f==1) {price = 150.0; sName="Burger Food Order";}
                else if(f==2){price = 200.0; sName="Pizza Food Order";}
                else if(f==3){price = 180.0; sName="Pasta Food Order";}
            }
            else if (s == 2) {
                int items; cout << "Enter number of items for Laundry: "; cin >> items;
                price = items * 50.0; sName = "Laundry Request";
            }
            else if (s == 3) {
                int items; cout << "Enter number of items for Ironing: "; cin >> items;
                price = items * 30.0; sName = "Ironing Request";
            }

            if (sName != "") {
                guest->addExtraCharge(price);
                cout << "\n===============================\n";
                cout << sName << " requested successfully! Staff will be with you shortly.\n";
                cout << "Service Price: " << price << " EGP\n";
                cout << "Total Bill till now: " << sys.CalculateGuestTotalBill(guest->getid(), guest->getExtraCharges()) << " EGP\n";
                cout << "===============================\n";
            }
        }
        else if (mainChoice == 3) {
            cout << "\n-- Medical Services --\n"
                 << "1. Request Doctor Consultation (1000 EGP)\n"
                 << "2. Request First Aid / Nurse (Free)\n"
                 << "Select to book (or 0 to cancel): ";
            int s; cin >> s;

            double price = 0.0; string sName = "";
            if (s == 1) { price = 1000.0; sName = "Doctor Consultation"; }
            else if (s == 2) { price = 0.0; sName = "First Aid / Nurse"; }

            if (sName != "") {
                guest->addExtraCharge(price);
                cout << "\n===============================\n";
                cout << sName << " requested! Medical personnel have been notified.\n";
                cout << "Service Price: " << price << " EGP\n";
                cout << "Total Bill till now: " << sys.CalculateGuestTotalBill(guest->getid(), guest->getExtraCharges()) << " EGP\n";
                cout << "===============================\n";
            }
        }
        else if (mainChoice == 4) {
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
}