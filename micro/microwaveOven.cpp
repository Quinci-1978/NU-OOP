#include <iostream>
#include <thread>
#include <chrono>
#include <string>
using namespace std;

// Function to simulate typing effect
void typeEffect(const string &text, int delay = 50) {
    for (size_t i = 0; i < text.size(); ++i) {
        cout << text[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

// Function to display banner
void showBanner() {
    // Display the main banner ASCII art
    cout << "\n";
    cout << " _   _ _   _ \n";
    cout << "| \\ | | | | |\n";
    cout << "|  \\| | | | |\n";
    cout << "| |\\  | |_| |\n";
    cout << "|_| \\_|\\___/ \n";
    cout << "\n";
    
    // Display welcome message with extra spacing
    cout << "\n";
    cout << "          * Welcome to the NU SMART MICROWAVE Interface! *\n";
    cout << "\n";
}

// Function to display menu options
void showMenu() {
    cout << "============================================================\n";
    cout << "|                   Microwave Command List                 |\n";
    cout << "============================================================\n";
    cout << "|  [1] Start \"Keep Warm\" Function                          |\n";
    cout << "|  [2] Set Custom \"Keep Warm\" Duration                     |\n";
    cout << "|  [3] Stop \"Keep Warm\" Function                           |\n";
    cout << "|  [4] Display Microwave Status                            |\n";
    cout << "|  [5] Show Oven Diagnostics                             |\n";
    cout << "|  [6] Exit Microwave Interface                            |\n";
    cout << "============================================================\n";
}

// Class for Microwave functionality
class SmartMicrowave {
private:
    bool isKeepWarmActive;
    int keepWarmDuration;  
    int maxKeepWarmDuration;  
    int elapsedMinutes;
    const int safeTemperature;  

public:
    // Constructor with default values
    SmartMicrowave()
        : isKeepWarmActive(false), 
          keepWarmDuration(30), 
          maxKeepWarmDuration(180), 
          elapsedMinutes(0), 
          safeTemperature(165) {}

    void startKeepWarm() {
        isKeepWarmActive = true;
        elapsedMinutes = 0;
        typeEffect("[SYSTEM] Keep Warm function activated...\n");
        cout << "Duration: " << keepWarmDuration << " minutes, Temperature: "
             << safeTemperature << "°F.\n";
        cout << "Maintaining food temperature...\n";
        for (int i = 1; i <= keepWarmDuration; ++i) {
            this_thread::sleep_for(chrono::milliseconds(100));  // Simulates 1 minute
            if (i % 10 == 0) {
                cout << "[+] Elapsed Time: " << i << " minutes.\n";
            }
        }
        stopKeepWarm();
    }

    void stopKeepWarm() {
        isKeepWarmActive = false;
        typeEffect("[SYSTEM] Keep Warm function terminated.\n");
        cout << "Food was kept warm for " << elapsedMinutes << " minutes.\n";
    }

    void setCustomDuration(int minutes) {
        if (minutes > 0 && minutes <= maxKeepWarmDuration) {
            keepWarmDuration = minutes;
            typeEffect("[SYSTEM] Custom Keep Warm duration set successfully.\n");
            cout << "New Duration: " << keepWarmDuration << " minutes.\n";
        } else {
            typeEffect("[ERROR] Invalid duration. Enter a value between 1 and "
                       + to_string(maxKeepWarmDuration) + " minutes.\n");
        }
    }

    void displayStatus() {
        cout << "\n============================================================\n";
        cout << "|                    Microwave Status                      |\n";
        cout << "============================================================\n";
        cout << "|  Keep Warm Status: " << (isKeepWarmActive ? "ACTIVE" : "INACTIVE") << "                   |\n";
        cout << "|  Current Duration: " << keepWarmDuration << " minutes                 |\n";
        cout << "|  Elapsed Time: " << elapsedMinutes << " minutes                     |\n";
        cout << "============================================================\n";
    }
};

int main() {
    SmartMicrowave microwave;
    int choice, duration;

    showBanner();

    do {
        showMenu();
        cout << "Enter your command (e.g., 1, 2, 3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                microwave.startKeepWarm();
                break;
            case 2:
                cout << "Enter custom duration (minutes): ";
                cin >> duration;
                microwave.setCustomDuration(duration);
                break;
            case 3:
                microwave.stopKeepWarm();
                break;
            case 4:
                microwave.displayStatus();
                break;
            case 5:
                typeEffect("[SYSTEM] Diagnostics Running...\n");
                cout << "[+] All Systems Operational.\n";
                break;
            case 6:
                typeEffect("[SYSTEM] Exiting Microwave Interface... Goodbye!\n");
                break;
            default:
                typeEffect("[ERROR] Invalid command. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
