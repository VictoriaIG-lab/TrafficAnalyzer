#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>  
#include <iostream>


struct Location {
    double latitude;
    double longitude;
};

class Road {
public:
    Road(const time_t& time, const Location& location)
        : time(time), location(location) {}

    time_t time;
    Location location;
};

class TrafficAnalyzer {
public: void addRoad(const Road& road) {
       roads.push_back(road); // add the "road" object received as a parameter to a data structure 
    }

    tm peakTrafficHour() {
        std::vector<int> trafficCounts(24, 0); // Initialize a vector to count traffic for every hour

        for (const Road& road : roads) { 
             tm* timeInfo = localtime(&road.time);
            int hour = timeInfo->tm_hour;
            trafficCounts[hour]++;
        }

        // looking for the hour with the highest traffic
        int maxTraffic = *max_element(trafficCounts.begin(), trafficCounts.end());
        int peakHour = distance(trafficCounts.begin(), find(trafficCounts.begin(), trafficCounts.end(), maxTraffic));

        tm peakTimeInfo{};
        peakTimeInfo.tm_hour = peakHour;

        return peakTimeInfo;
    }

    std::vector<Location> mostPopulatedLocations() {
        const double squareDiameter = 10;// Diameter of the square (change its size as needed)
        std::vector<Location> populatedLocations;

        for (const Road& road : roads) {
            int count = 0; // Initialize count for each road
            for (const Road& otherRoad : roads) {
                if (calculateDistance(road.location, otherRoad.location) <= squareDiameter) {
                    count++;
                }
            }

            if (count >= 2) { // (change its step as needed)
                populatedLocations.push_back(road.location);
            }
        }

        return populatedLocations;
    }


private:
    std:: vector<Road> roads;

    double calculateDistance(const Location& loc1, const Location& loc2) {
        double dx = loc1.latitude - loc2.latitude;
        double dy = loc1.longitude - loc2.longitude;
        return sqrt(dx * dx + dy * dy);
    }
};

int main() {
    TrafficAnalyzer analyzer;

    // Adding some roads
    analyzer.addRoad(Road(time(nullptr), { 25.0, -73.0 }));
    analyzer.addRoad(Road(time(nullptr), { 46.0, -72.0 }));
    analyzer.addRoad(Road(time(nullptr), { 76.76, 23.58 }));
    analyzer.addRoad(Road(time(nullptr), { 77.72, 23.46 }));
    analyzer.addRoad(Road(time(nullptr), { 75.73, 33.48 }));
    // Add more roads for the test

    tm peakHour = analyzer.peakTrafficHour();
    std::cout << "Ora de varf a traficului: " << peakHour.tm_hour << ":" << peakHour.tm_min <<'\n';


    std::vector<Location> popularLocations = analyzer.mostPopulatedLocations();
    std::cout << "Locatiile cele mai populate:" <<'\n';
    for (const Location& location : popularLocations) {
        std:: cout << "Lat: " << location.latitude << ", Lon: " << location.longitude <<'\n';
    }

    return 0;
}