// Package Damage Risk Predictor
// Programming Language: C++
// Libraries/Frameworks: Standard Template Library (STL) - iostream, string, iomanip, vector, algorithm
// Info: This C++ program calculates and displays the damage risk for multiple shipments based on their fragility,
//       weather conditions, and truck type. Users input shipment details (ID, type, fragility [1-10],
//       weather [Clear, Rain, Snow, Windy], and truck type [Standard, Refrigerated, AirRide]).
//       The program computes a risk score by multiplying a base risk (fragility * 10) by weather and truck factors,
//       then sorts shipments by risk score in descending order. It displays a color-coded dashboard
//       (red for high risk, yellow for moderate, green for low)
//       with a risk bar and provides suggestions for each shipment (e.g., extra cushioning for high-risk shipments).
//       ANSI escape codes are used for colored console output.

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define WHITE   "\033[37m"

struct Shipment {
    string id;
    string type;
    int fragility; // 1 = very sturdy, 10 = extremely fragile
    string weather; // Clear, Rain, Snow, Windy
    string truckType; // Standard, Refrigerated, AirRide
    double riskScore = 0; // calculated later
};

double weatherFactor(const string &w) {
    if (w == "Clear") return 0.9;
    if (w == "Rain") return 1.2;
    if (w == "Snow") return 1.5;
    if (w == "Windy") return 1.3;
    return 1.0;
}

double truckFactor(const string &t) {
    if (t == "Standard") return 1.0;
    if (t == "Refrigerated") return 0.85;
    if (t == "AirRide") return 0.75;
    return 1.0;
}

string riskColor(double risk) {
    if (risk > 80) return RED;
    else if (risk > 60) return YELLOW;
    else return GREEN;
}

// Draw horizontal risk bar
string riskBar(double risk) {
    int filled = static_cast<int>(risk / 4); // 25 max
    string bar = "[";
    for (int i = 0; i < 25; i++) {
        if (i < filled) bar += "#";
        else bar += " ";
    }
    bar += "]";
    return bar;
}

// Print dashboard header
void printDashboardHeader() {
    cout << MAGENTA << "==============================================================" << RESET << "\n";
    cout << MAGENTA << "                      SHIPMENT RISK DASHBOARD                 " << RESET << "\n";
    cout << MAGENTA << "==============================================================" << RESET << "\n";
    cout << left << setw(8) << "ID" 
         << setw(15) << "Type" 
         << setw(10) << "Fragility"
         << setw(12) << "Weather"
         << setw(12) << "Truck"
         << setw(10) << "Risk"
         << " Risk Bar\n";
    cout << MAGENTA << "--------------------------------------------------------------" << RESET << "\n";
}

// Print a single shipment row
void printShipmentRow(const Shipment &s) {
    cout << left << setw(8) << s.id
         << setw(15) << s.type
         << setw(10) << s.fragility
         << setw(12) << s.weather
         << setw(12) << s.truckType
         << setw(10) << riskColor(s.riskScore) << fixed << setprecision(2) << s.riskScore << RESET
         << " " << riskColor(s.riskScore) << riskBar(s.riskScore) << RESET
         << "\n";
}

// Suggestion for a shipment
void printSuggestion(double risk) {
    if (risk > 80) {
        cout << RED << "- High risk: Extra cushioning and AirRide truck recommended." << RESET << "\n";
    } else if (risk > 60) {
        cout << YELLOW << "- Moderate risk: Add padding and weatherproof wrapping." << RESET << "\n";
    } else if (risk > 40) {
        cout << GREEN << "- Low risk: Standard packing acceptable." << RESET << "\n";
    } else {
        cout << GREEN << "- Very low risk: Minimal precautions required." << RESET << "\n";
    }
}

int main() {
    cout << endl;
    cout << MAGENTA << "=== PACKAGE DAMAGE RISK PREDICTOR WITH DASHBOARD ===" << RESET << "\n\n";

    int numShipments;
    cout << CYAN << "Enter number of shipments to process: " << RESET;
    cin >> numShipments;
    cin.ignore();

    vector<Shipment> shipments(numShipments);

    // Input loop
    for (int i = 0; i < numShipments; i++) {
        cout << "\n" << CYAN << "Entering data for shipment " << (i+1) << ":" << RESET << "\n";
        cout << "Shipment ID: ";
        getline(cin, shipments[i].id);

        cout << "Shipment Type: (e.g., Electronics, Furniture): ";
        getline(cin, shipments[i].type);

        cout << "Fragility (1=very sturdy, 10=extremely fragile): ";
        cin >> shipments[i].fragility;
        cin.ignore();

        cout << "Weather (Clear, Rain, Snow, Windy): ";
        getline(cin, shipments[i].weather);

        cout << "Truck Type (Standard, Refrigerated, AirRide): ";
        getline(cin, shipments[i].truckType);

        // Calculate risk
        double baseRisk = shipments[i].fragility * 10;
        shipments[i].riskScore = baseRisk * weatherFactor(shipments[i].weather) * truckFactor(shipments[i].truckType);
    }

    // Sort shipments by descending risk for dashboard
    sort(shipments.begin(), shipments.end(), [](const Shipment &a, const Shipment &b) {
        return a.riskScore > b.riskScore;
    });

    // Print dashboard
    cout << "\n";
    printDashboardHeader();
    for (const auto &s : shipments) {
        printShipmentRow(s);
    }

    // Detailed suggestions
    cout << "\n" << MAGENTA << "=== SUGGESTIONS ===" << RESET << "\n";
    for (const auto &s : shipments) {
        cout << s.id << ": ";
        printSuggestion(s.riskScore);
    }

    cout << "\n" << MAGENTA << "Dashboard complete." << RESET << "\n";
    return 0;
}