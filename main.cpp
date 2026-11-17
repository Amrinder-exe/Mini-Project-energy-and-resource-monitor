#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// Simulated readings for a small console demonstration. No real sensors are used.
class Building {
private:
    string name;
    double electricityKwh;
    double waterLitres;
    double temperatureC;
    int occupancy;

public:
    Building(string buildingName, double power, double water, double temperature, int people)
        : name(buildingName), electricityKwh(power), waterLitres(water),
          temperatureC(temperature), occupancy(people) {}

    string getName() const { return name; }
    double getElectricity() const { return electricityKwh; }
    double getWater() const { return waterLitres; }

    void display() const {
        cout << left << setw(18) << name
             << right << setw(12) << fixed << setprecision(1) << electricityKwh
             << setw(14) << waterLitres << setw(12) << temperatureC
             << setw(12) << occupancy << '\n';
    }

    void checkAlerts() const {
        if (electricityKwh > 100.0)
            cout << "[ENERGY ALERT] " << name << " is above 100 kWh.\n";
        if (waterLitres > 5000.0)
            cout << "[WATER ALERT]  " << name << " is above 5,000 litres.\n";
        if (temperatureC > 28.0)
            cout << "[COMFORT ALERT] " << name << " is warmer than 28 C.\n";
    }
};

class CampusMonitor {
private:
    vector<Building> buildings;

public:
    CampusMonitor() {
        // Example readings; edit these values to demonstrate different alerts.
        buildings.emplace_back("Engineering", 128.5, 4200, 29.3, 86);
        buildings.emplace_back("Library",      74.2, 5700, 23.8, 142);
        buildings.emplace_back("Cafeteria",    96.0, 6350, 27.1, 54);
        buildings.emplace_back("Administration",62.4, 2800, 25.0, 31);
    }

    void showDashboard() const {
        double totalEnergy = 0, totalWater = 0;
        cout << "\nSMART CAMPUS ENERGY & RESOURCE MONITOR\n";
        cout << "Demo data only - readings are simulated, not from live sensors.\n\n";
        cout << left << setw(18) << "Building" << right << setw(12) << "Energy kWh"
             << setw(14) << "Water L" << setw(12) << "Temp C"
             << setw(12) << "People" << '\n';
        cout << string(68, '-') << '\n';
        for (const auto& building : buildings) {
            building.display();
            totalEnergy += building.getElectricity();
            totalWater += building.getWater();
        }
        cout << string(68, '-') << '\n';
        cout << left << setw(18) << "CAMPUS TOTAL" << right << setw(12)
             << fixed << setprecision(1) << totalEnergy << setw(14) << totalWater << "\n";

        cout << "\nALERTS\n";
        bool anyAlert = false;
        for (const auto& building : buildings) {
            if (building.getElectricity() > 100.0 || building.getWater() > 5000.0) {
                anyAlert = true;
                building.checkAlerts();
            }
        }
        if (!anyAlert) cout << "No resource alerts.\n";

        cout << "\nSUGGESTED ACTION\n";
        cout << "Review after-hours equipment use in the highest-energy building, "
             << highestEnergyBuilding() << ". Check for leaks in buildings with water alerts.\n";
    }

    void showBuildingDetails() const {
        cout << "\nBUILDING DETAILS\n";
        for (size_t i = 0; i < buildings.size(); ++i)
            cout << (i + 1) << ". " << buildings[i].getName() << '\n';
        cout << "Select a building number: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number.\n"; return;
        }
        if (choice < 1 || choice > static_cast<int>(buildings.size())) {
            cout << "That building number is not on the list.\n"; return;
        }
        const Building& b = buildings[static_cast<size_t>(choice - 1)];
        cout << "\n" << b.getName() << " monitoring status:\n";
        b.display();
        b.checkAlerts();
    }

private:
    string highestEnergyBuilding() const {
        auto it = max_element(buildings.begin(), buildings.end(),
            [](const Building& a, const Building& b) {
                return a.getElectricity() < b.getElectricity();
            });
        return it == buildings.end() ? "N/A" : it->getName();
    }
};

int main() {
    CampusMonitor monitor;
    int choice = -1;
    do {
        cout << "\n=== CAMPUS RESOURCE MENU ===\n"
             << "1. View campus dashboard and alerts\n"
             << "2. View one building\n"
             << "0. Exit\n"
             << "Choice: ";
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number.\n";
            continue;
        }
        switch (choice) {
            case 1: monitor.showDashboard(); break;
            case 2: monitor.showBuildingDetails(); break;
            case 0: cout << "Demo closed.\n"; break;
            default: cout << "Choose 1, 2, or 0.\n";
        }
    } while (choice != 0);
    return 0;
}
