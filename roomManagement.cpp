#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#define MAX   100

class Customer{
    public:
    char name[50];
    char address[100];
    char phone[10];
    char from_date[20];
    char to_date[20];
    float total_charge;
    int booking_id; 
};

class Room{
    public:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;
    class Customer cust;
    class Room addRoom(int);
    void searchRoom(int);
    void deleteRoom(int);
    void displayRoom(Room);
};

int count = 0;
class Room rooms[MAX];
Room Room::addRoom(int rno){
    class Room room;
    room.roomNumber = rno;
    cout << "\nType AC/Non-AC (A/N) : ";
    cin >> room.ac;
    cout << "\nType Comfort: Soft or Not-Soft (S/N) : ";
    cin >> room.stype;
    cout << "\nType Size: Large/Small (L/S) : ";
    cin >> room.type;
    cout << "\nDaily Rent : ";
    cin >> room.rent;
    room.status = 0;
    cout<<"\n Room Added Successfully!";
    cin.get();
    return room;
}

void Room::searchRoom(int rno){
    int found=0;
    int i;
    for(i=0;i <::count;i++){
        if(rooms[i].roomNumber == rno){
            found = 1;
            break;
        }
    }
    if(found){
        cout << "Room Details:\n";
        if(rooms[i].status == 1){
            cout << "\n     Room is Reserved";
        }else{
            cout << "\n     Room is available";
        }
        displayRoom(rooms[i]);
        cin.get();
    }else{
        cout << "Room not found";
        cin.get();
    }
}

void Room::displayRoom(Room tempRoom){
    cout << "\nRoom Number: \t" << tempRoom.roomNumber;
    cout << "\nType AC/Non-AC: \t" << tempRoom.ac;
    cout << "\nType Comfort: \t" << tempRoom.stype;
    cout << "\nType Size: \t" << tempRoom.type;
    cout << "\nRent: \t" << tempRoom.rent;
}

class HotelMgnt:protected Room{
    public:
    void checkIn();
    void getAvailRoom();
    void searchCustomer(char *);
    void checkOut(int);
    void displayAllRoom();
    void guestSummaryReport();
};

void HotelMgnt::guestSummaryReport(){
    if (::count == 0){
        cout << "\n No Guest in Hotel";
        return;
    }
    for (int i = 0; i < ::count; i++){
        cout << "\n Customer First Name: \t" << rooms[i].cust.name;
        cout << "\n Room Number: \t" << rooms[i].roomNumber;
        cout << "\n Address (only city): \t" << rooms[i].cust.address;
        cout << "\n Phone: \t" << rooms[i].cust.phone;
        cout << "\n---------------------------------------";
    }
    cin.get();
}
void HotelMgnt::checkIn(){
    int i,found=0,rno;
    Room room;
    cout << "\nEnter Room number: ";
    cin >> rno;
    for(i=0;i < ::count;i++){
        if(rooms[i].roomNumber == rno){
            found = 1;
            break;
        }
    }
    if(found){
        if(rooms[i].status == 1){
            cout << "\nRoom is already Booked";
            cin.get();
            return;
        }
        cout << "\nEnter booking id: ";
        cin >> rooms[i].cust.booking_id;
        cout << "\nEnter Customer Name (First Name): ";
        cin >> rooms[i].cust.name;
        cout << "\nEnter Address (only city): ";
        cin >> rooms[i].cust.address;
        cout << "\nEnter Phone: ";
        cin >> rooms[i].cust.phone;
        cout << "\nEnter From Date: ";
        cin >> rooms[i].cust.from_date;
        cout << "\nEnter to Date: ";
        cin >> rooms[i].cust.to_date;
        cout <<"\nEnter Payment: ";
        cin >> rooms[i].cust.total_charge;
        rooms[i].status = 1;
        cout << "Customer Checked-in Successfully..";
        cin.get();
    }else{
        cout << "Room not found";
        cin.get();
    }   
}
void HotelMgnt::getAvailRoom(){
    int i,found=0;
    for(i=0;i < ::count;i++){
        if(rooms[i].status == 0){
            displayRoom(rooms[i]);
            cout << "\n\nPress enter for next room";
            found = 1;
            cin.get();
        }
    }
    if (found == 0){
        cout << "\nAll rooms are reserved";
        cin.get();
    }
}
void HotelMgnt::searchCustomer(char *pname){
    int i,found=0;
    for(i=0;i < ::count;i++){
        if(rooms[i].status==1 && !strcmp(rooms[i].cust.name,pname)){
            cout << "Customer Name: " << pname;
            cout << "\nRoom Number: " << rooms[i].roomNumber;
            cout <<"\n\n Press enter for next record";
            found = 1;
            cin.get();
        }
    }
    if (found == 0){
        cout << "\nCustomer not found";
        cin.get();
    }
}
void HotelMgnt::checkOut(int room_no){
    int i,found=0, days, rno;
    float billAmount;
    for(i=0;i < ::count;i++){
        if(rooms[i].status == 1 && rooms[i].roomNumber == room_no){
            rooms[i].status = 0;
            cout << "Check-out Successfully";
            found = 1;
            break;
        }
    }
    if(found == 1){
        cout << "\nenter number of days: \t";
        cin >> days;
        billAmount = days * rooms[i].rent;
        cout << "\m\t############# CheckOut Details #############\n";
        cout << "\nCustomer Name: \t" << rooms[i].cust.name;
        cout << "\nRoom Number: \t" << rooms[i].roomNumber;
        cout << "\nAddress: \t" << rooms[i].cust.address;
        cout << "\nPhone: \t" << rooms[i].cust.phone; 
        cout << "\nTotal Amount: \t" << billAmount << " /";
        cout <<" \nAdvance Paid: \t" << rooms[i].cust.total_charge<<" /";
        cout << "\nTotal Payable: \t" << billAmount - rooms[i].cust.total_charge << "$ ";
        rooms[i].status = 0;
    }
    cin.get();
}
void manageRooms(){
    int i;
    char ch;
    Room room;
    do{
        system("cls");
        cout << "\n### Room Management ###";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Back to Main Menu";
        cout << "\n\nEnter Your Choice: ";
        cin >> ch;
        switch(ch){
            case '1':
                rooms[::count] = room.addRoom(::count);
                ::count++;
                break;
            case '2':
                int rno;
                cout << "Enter Room Number: ";
                cin >> rno;
                room.searchRoom(rno);
                break;
            case '3':
                break;
            default:
                cout << "\nInvalid Option";
                break;
        }
    }while(ch != '3');
}