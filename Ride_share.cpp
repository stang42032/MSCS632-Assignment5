#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ---------------- Ride Base Class ----------------
class Ride {
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance;

public:
    Ride(int id, string pickup, string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {}

    virtual double fare() const = 0;  // Abstract method → polymorphism

    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID
             << "\nPickup: " << pickupLocation
             << "\nDropoff: " << dropoffLocation
             << "\nDistance: " << distance << " miles" << endl;
    }

    virtual ~Ride() {}
};

// ---------------- StandardRide ----------------
class StandardRide : public Ride {
public:
    StandardRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 2.0;  // $2 per mile
    }

    void rideDetails() const override {
        cout << "[Standard Ride]\n";
        Ride::rideDetails();
        cout << "Fare: $" << fare() << endl;
    }
};

// ---------------- PremiumRide ----------------
class PremiumRide : public Ride {
public:
    PremiumRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 3.5;  // $3.5 per mile
    }

    void rideDetails() const override {
        cout << "[Premium Ride]\n";
        Ride::rideDetails();
        cout << "Fare: $" << fare() << endl;
    }
};

// ---------------- Driver Class ----------------
class Driver {
private:
    int driverID;
    string name;
    double rating;
    vector<Ride*> assignedRides;  // Encapsulation: private list

public:
    Driver(int id, string n, double r) : driverID(id), name(n), rating(r) {}

    void addRide(Ride* ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        cout << "Driver ID: " << driverID
             << "\nName: " << name
             << "\nRating: " << rating << endl;
        cout << "Assigned Rides: " << assignedRides.size() << endl;
    }
};

// ---------------- Rider Class ----------------
class Rider {
private:
    int riderID;
    string name;
    vector<Ride*> requestedRides;

public:
    Rider(int id, string n) : riderID(id), name(n) {}

    void requestRide(Ride* ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        cout << "Rider: " << name << " has requested " << requestedRides.size() << " rides." << endl;
        for (auto ride : requestedRides) {
            ride->rideDetails();
            cout << "-------------------\n";
        }
    }
};

// ---------------- Main ----------------
int main() {
    // Create rides
    Ride* r1 = new StandardRide(1, "Downtown", "Airport", 10);
    Ride* r2 = new PremiumRide(2, "Mall", "Hotel", 5);

    // Polymorphism: store rides in same list
    vector<Ride*> rides = {r1, r2};

    cout << "=== Ride Details (Polymorphism Demo) ===" << endl;
    for (auto ride : rides) {
        ride->rideDetails();  // Calls correct subclass method
        cout << "-------------------\n";
    }

    // Create Driver
    Driver d1(101, "Alice", 4.9);
    d1.addRide(r1);
    d1.addRide(r2);
    d1.getDriverInfo();

    // Create Rider
    Rider rider1(201, "Bob");
    rider1.requestRide(r1);
    rider1.requestRide(r2);
    rider1.viewRides();

    // Cleanup
    delete r1;
    delete r2;

    return 0;
}
