#include "ApplicationManager.h"
#include "UI.h"

int main(int argc, char* argv[]) {
    ApplicationManager sys; 
    return UI::ProcessCommand(argc, argv, sys);
}