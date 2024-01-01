#include <iostream>
#include <iomanip>

const int NUM_BOATS = 10;
const int OPEN_HOUR = 10;
const int CLOSE_HOUR = 17;
const double HOURLY_RATE = 20.0;
const double HALF_HOUR_RATE = 12.0;

struct Boat {
    bool isAvailable;
    double moneyTaken;
    double totalHoursHired;
    int returnHour;
};

// Function to calculate money taken for one boat
void calculateMoneyForOneBoat(Boat &boat) {
    int startHour, hireDuration;
    
    std::cout << "Enter the starting hour (between 10 and 17): ";
    std::cin >> startHour;

    if (startHour < OPEN_HOUR || startHour > CLOSE_HOUR) {
        std::cout << "Boat can only be hired between 10:00 and 17:00." << std::endl;
        return;
    }

    std::cout << "Enter the hire duration in hours (1 or 0.5 for half an hour): ";
    std::cin >> hireDuration;

    if (hireDuration != 1 && hireDuration != 0.5) {
        std::cout << "Invalid hire duration. Please enter 1 or 0.5." << std::endl;
        return;
    }

    // Calculate cost
    double cost = (hireDuration == 1) ? HOURLY_RATE : HALF_HOUR_RATE;

    // Update boat information
    boat.isAvailable = false;
    boat.moneyTaken += cost;
    boat.totalHoursHired += hireDuration;
    boat.returnHour = startHour + hireDuration;

    std::cout << "Boat hired successfully. Cost: $" << std::fixed << std::setprecision(2) << cost << std::endl;
}

// Function to find the next available boat
int findNextAvailableBoat(const Boat boats[]) {
    for (int i = 0; i < NUM_BOATS; ++i) {
        if (boats[i].isAvailable) {
            return i + 1;  // Boat numbers are 1-indexed
        }
    }
    return -1;  // No available boats
}

// Function to calculate money taken for all boats at the end of the day
void calculateTotalMoney(const Boat boats[]) {
    double totalMoney = 0.0;
    double totalHours = 0.0;
    int unusedBoats = 0;
    int mostUsedBoat = 0;

    for (int i = 0; i < NUM_BOATS; ++i) {
        totalMoney += boats[i].moneyTaken;
        totalHours += boats[i].totalHoursHired;

        if (boats[i].isAvailable) {
            ++unusedBoats;
        }

        if (i == 0 || boats[i].totalHoursHired > boats[mostUsedBoat].totalHoursHired) {
            mostUsedBoat = i;
        }
    }

    // Display report
    std::cout << "\nEnd of Day Report:" << std::endl;
    std::cout << "Total money taken: $" << std::fixed << std::setprecision(2) << totalMoney << std::endl;
    std::cout << "Total hours hired: " << totalHours << " hours" << std::endl;
    std::cout << "Number of unused boats: " << unusedBoats << std::endl;
    std::cout << "Boat #" << (mostUsedBoat + 1) << " was used the most, for " << boats[mostUsedBoat].totalHoursHired << " hours." << std::endl;
}

int main() {
    Boat boats[NUM_BOATS];

    // Initialize boat data
    for (int i = 0; i < NUM_BOATS; ++i) {
        boats[i].isAvailable = true;
        boats[i].moneyTaken = 0.0;
        boats[i].totalHoursHired = 0.0;
        boats[i].returnHour = CLOSE_HOUR;
    }

    // Task 1 - Calculate money for one boat
    calculateMoneyForOneBoat(boats[0]);

    // Task 2 - Find the next available boat
    int nextAvailableBoat = findNextAvailableBoat(boats);
    if (nextAvailableBoat != -1) {
        std::cout << "Next available boat: #" << nextAvailableBoat << std::endl;
    } else {
        std::cout << "No boats available. Earliest available time: 17:00" << std::endl;
    }

    // Task 3 - Calculate total money at the end of the day
    calculateTotalMoney(boats);

    return 0;
}

