#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Customer {
public:
    string name;
    string address;
    string phone;
    string from_date;
    string to_date;
    float total_charge;
    int booking_id;

    Customer() : total_charge(0), booking_id(0) {}
};

class Room {
public:
    string type;
    string stype;
    string ac;
    int roomNumber;
    int rent;
    bool isReserved;
    Customer customer;

    Room() : roomNumber(0), rent(0), isReserved(false) {}

    void display() const {
        cout << "\nRoom Number: " << roomNumber
             << "\nType AC/Non-AC: " << ac
             << "\nType Comfort: " << stype
             << "\nType Size: " << type
             << "\nRent: " << rent
             << "\nReserved: " << (isReserved ? "Yes" : "No") << endl;
    }
};

class HotelMgnt {
    vector<Room> rooms;

public:
    void addRoom();
    void checkIn();
    void checkOut();
    void displayAvailableRooms() const;
    void searchCustomer() const;
    void displayAllRooms() const;
    void guestSummaryReport() const;
};

void HotelMgnt::addRoom() {
    Room room;
    cout << "\nEnter Room Number: ";
    cin >> room.roomNumber;
    cout << "Type AC/Non-AC (A/N): ";
    cin >> room.ac;
    cout << "Type Comfort (Soft/Not-Soft S/N): ";
    cin >> room.stype;
    cout << "Type Size (Large/Small L/S): ";
    cin >> room.type;
    cout << "Enter Daily Rent: ";
    cin >> room.rent;
    room.isReserved = false;
    rooms.push_back(room);
    cout << "Room added successfully!\n";
}

void HotelMgnt::checkIn() {
    int roomNumber;
    cout << "\nEnter Room Number: ";
    cin >> roomNumber;

    for (auto& room : rooms) {
        if (room.roomNumber == roomNumber) {
            if (room.isReserved) {
                cout << "\nRoom is already reserved.\n";
                return;
            }

            cout << "Enter Booking ID: ";
            cin >> room.customer.booking_id;
            cout << "Enter Customer Name: ";
            cin.ignore();
            getline(cin, room.customer.name);
            cout << "Enter Address: ";
            getline(cin, room.customer.address);
            cout << "Enter Phone: ";
            cin >> room.customer.phone;
            cout << "Enter From Date: ";
            cin >> room.customer.from_date;
            cout << "Enter To Date: ";
            cin >> room.customer.to_date;
            cout << "Enter Total Charge: ";
            cin >> room.customer.total_charge;

            room.isReserved = true;
            cout << "\nCustomer checked in successfully.\n";
            return;
        }
    }
    cout << "\nRoom not found.\n";
}

void HotelMgnt::checkOut() {
    int roomNumber;
    cout << "\nEnter Room Number: ";
    cin >> roomNumber;

    for (auto& room : rooms) {
        if (room.roomNumber == roomNumber) {
            if (!room.isReserved) {
                cout << "\nRoom is not reserved.\n";
                return;
            }

            int days;
            cout << "Enter number of days stayed: ";
            cin >> days;
            float totalBill = days * room.rent;
            cout << "\nCheck-Out Details:\n"
                 << "Customer Name: " << room.customer.name << "\n"
                 << "Room Number: " << room.roomNumber << "\n"
                 << "Address: " << room.customer.address << "\n"
                 << "Phone: " << room.customer.phone << "\n"
                 << "Total Bill: $" << totalBill << "\n"
                 << "Advance Paid: $" << room.customer.total_charge << "\n"
                 << "Amount Due: $" << (totalBill - room.customer.total_charge) << "\n";

            room.isReserved = false;
            room.customer = Customer(); // Reset customer details
            cout << "\nCheck-out successful.\n";
            return;
        }
    }
    cout << "\nRoom not found.\n";
}

void HotelMgnt::displayAvailableRooms() const {
    cout << "\nAvailable Rooms:\n";
    for (const auto& room : rooms) {
        if (!room.isReserved) {
            room.display();
            cout << "------------------------" << endl;
        }
    }
}

void HotelMgnt::searchCustomer() const {
    string customerName;
    cout << "\nEnter Customer Name: ";
    cin.ignore();
    getline(cin, customerName);

    for (const auto& room : rooms) {
        if (room.isReserved && room.customer.name == customerName) {
            cout << "\nCustomer Found:\n"
                 << "Name: " << room.customer.name << "\n"
                 << "Room Number: " << room.roomNumber << "\n"
                 << "Address: " << room.customer.address << "\n"
                 << "Phone: " << room.customer.phone << "\n";
            return;
        }
    }
    cout << "\nCustomer not found.\n";
}

void HotelMgnt::displayAllRooms() const {
    cout << "\nAll Rooms:\n";
    for (const auto& room : rooms) {
        room.display();
        cout << "------------------------" << endl;
    }
}

void HotelMgnt::guestSummaryReport() const {
    cout << "\nGuest Summary Report:\n";
    for (const auto& room : rooms) {
        if (room.isReserved) {
            cout << "Customer Name: " << room.customer.name << "\n"
                 << "Room Number: " << room.roomNumber << "\n"
                 << "Address: " << room.customer.address << "\n"
                 << "Phone: " << room.customer.phone << "\n"
                 << "------------------------" << endl;
        }
    }
}

int main() {
    HotelMgnt hotel;
    int choice;

    do {
        cout << "\n########## Hotel Management System ##########\n"
             << "1. Add Room\n"
             << "2. Check-In\n"
             << "3. Check-Out\n"
             << "4. Display Available Rooms\n"
             << "5. Search Customer\n"
             << "6. Display All Rooms\n"
             << "7. Guest Summary Report\n"
             << "8. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.addRoom();
                break;
            case 2:
                hotel.checkIn();
                break;
            case 3:
                hotel.checkOut();
                break;
            case 4:
                hotel.displayAvailableRooms();
                break;
            case 5:
                hotel.searchCustomer();
                break;
            case 6:
                hotel.displayAllRooms();
                break;
            case 7:
                hotel.guestSummaryReport();
                break;
            case 8:
                cout << "\nExiting... Thank you!\n";
                break;
            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
