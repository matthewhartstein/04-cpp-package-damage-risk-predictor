# 04-cpp-package-damage-risk-predictor

Package Damage Risk Predictor

Programming Language: C++

Libraries/Frameworks: Standard Template Library (STL) - <iostream>, <string>, <iomanip>, <vector>, <algorithm>

Description: This C++ program calculates and displays the damage risk for multiple shipments based on their fragility, weather conditions, and truck type. Users input shipment details (ID, type, fragility [1-10], weather [Clear, Rain, Snow, Windy], and truck type [Standard, Refrigerated, AirRide]). The program computes a risk score by multiplying a base risk (fragility * 10) by weather and truck factors, then sorts shipments by risk score in descending order. It displays a color-coded dashboard (red for high risk, yellow for moderate, green for low) with a risk bar and provides suggestions for each shipment (e.g., extra cushioning for high-risk shipments). ANSI escape codes are used for colored console output.
