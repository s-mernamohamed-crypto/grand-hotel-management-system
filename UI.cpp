#include "UI.h"
#include "User.h" 
#include "ApplicationManager.h"
#include <iostream>
using namespace std;
int UI::ProcessCommand(int argc, char* argv[], ApplicationManager& sys) {
    if (argc < 2) {
        cout << "ERROR:No command provided\n";
        return 1;
    }
    string command = argv[1];
    if (command == "LOGIN") {
        if (argc < 4) {
            cout << "ERROR:Missing parameters for LOGIN\n";
            return 1;
        }
        string username = argv[2];
        string password = argv[3];

        User* loggedInUser = sys.AuthenticateUser(username, password);

        if (loggedInUser != nullptr) {
            double extraCharges = 0.0;
            if (loggedInUser->getusertype() == "guest") {
                Guest* g = dynamic_cast<Guest*>(loggedInUser);
                if (g) extraCharges = g->getExtraCharges();
            }
            
            cout << "SUCCESS:" << loggedInUser->getusername() << "," 
                 << loggedInUser->getid() << "," 
                 << loggedInUser->getusertype() << "," 
                 << extraCharges << "\n";
            return 0;
        } else {
            cout << "ERROR:Invalid credentials\n";
            return 1;
        }
    }
    

    else if (command == "REGISTER") {
        if (argc < 4) {
            cout << "ERROR:Missing parameters for REGISTER\n";
            return 1;
        }
        string username = argv[2];
        string password = argv[3];
        sys.RegisterNewGuest(username, password);
        cout << "SUCCESS:Registered successfully\n";
        return 0;
    }
  
    else if (command == "BOOK") {
        if (argc < 4) {
            cout << "ERROR:Missing parameters for BOOK\n";
            return 1;
        }
        
        try {
            int targetID = stoi(argv[2]);
            double amount = stod(argv[3]);
            
            cout << "ERROR: Update ApplicationManager to support AddChargeToGuest\n";
            return 1; 

        } catch (...) {
            cout << "ERROR:Invalid numeric parameters for BOOK\n";
            return 1;
        }
    }
    
    else {
        cout << "ERROR:Unknown command\n";
        return 1;
    }
}