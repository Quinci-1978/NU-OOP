#include <iostream>
#include <thread>
#include <chrono>
#include <string>

class Microwave {
private:
    bool runningStatus;
    bool doorStatus;
    int pLevel;
    int timeLeft;

    std::string formatTime(int t) {
        int mins = t / 60;
        int secs = t % 60;
        std::string result = std::to_string(mins) + ":";
        if (secs < 10) result += "0";
        result += std::to_string(secs);
        return result;
    }

public:
    Microwave() {
        runningStatus = false;
        doorStatus = false;
        pLevel = 10;
        timeLeft = 0;
    }

    void openMicrowaveDoor() {
        doorStatus = true;
        if (runningStatus) {
            stopMicrowave();
        }
        std::cout << "Door is now open\n";
    }

    void closeMicrowaveDoor() {
        doorStatus = false;
        std::cout << "Door is now closed\n";
    }

    void setPower(int lvl) {
        if (lvl > 10 || lvl < 1) {
            std::cout << "Not a valid power level\n";
        } else {
            pLevel = lvl;
            std::cout << "Power is now set to: " << pLevel << "\n";
        }
    }

    void addCookTime(int t) {
        if (runningStatus) {
            timeLeft += t;
        } else {
            timeLeft = t;
        }
        std::cout << "Time set to " << formatTime(timeLeft) << "\n";
    }

    void quickCook() {
        if (doorStatus == false) {
            timeLeft = 30;
            startMicrowave();
        } else {
            std::cout << "Close the door first!\n";
        }
    }

    void startMicrowave() {
        if (timeLeft <= 0) {
            std::cout << "Set time first\n";
            return;
        }
        if (doorStatus) {
            std::cout << "Please shut the door first\n";
            return;
        }

        runningStatus = true;
        std::cout << "Starting microwave...\n";

        while (timeLeft > 0 && runningStatus) {
            std::cout << "\nMicrowave Info:\n";
            std::cout << "Time left: " << formatTime(timeLeft) << "\n";
            std::cout << "Power Level: " << pLevel << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            timeLeft--;
        }

        if (timeLeft <= 0) {
            std::cout << "\nDone! Beep! Beep!\n";
            runningStatus = false;
        }
    }

    void stopMicrowave() {
        runningStatus = false;
        std::cout << "Microwave stopped.\n";
    }
};

int main() {
    Microwave mw;
    std::string cmd;

    std::cout << "Microwave Simulator\n";
    std::cout << "Type commands: open, close, power <1-10>, time <seconds>, start, stop, quick, quit\n";

    while (1) {
        std::cout << "> ";
        std::getline(std::cin, cmd);

        if (cmd == "quit") {
            break;
        } else if (cmd == "open") {
            mw.openMicrowaveDoor();
        } else if (cmd == "close") {
            mw.closeMicrowaveDoor();
        } else if (cmd == "start") {
            mw.startMicrowave();
        } else if (cmd == "stop") {
            mw.stopMicrowave();
        } else if (cmd == "quick") {
            mw.quickCook();
        } else if (cmd.substr(0, 5) == "power") {
            try {
                int level = std::stoi(cmd.substr(6));
                mw.setPower(level);
            } catch (...) {
                std::cout << "Error in power format\n";
            }
        } else if (cmd.substr(0, 4) == "time") {
            try {
                int sec = std::stoi(cmd.substr(5));
                mw.addCookTime(sec);
            } catch (...) {
                std::cout << "Error in time format\n";
            }
        } else {
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}
