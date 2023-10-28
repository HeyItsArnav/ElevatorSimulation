#include <iostream>
#include <cstdlib>
#include<unistd.h>
using namespace std;
int height,lifts;
class Passenger
{
    bool done;//0 means arrived, 1 means not arrived, -1 means in lift
    int current;
    int destination;
    int assignedLift;//0 to lift number, -1 means to assigned, -2 means reached location
    public:
    //Functions here
    Passenger(int start,int end);
    friend allot(Passenger human);
};
//Passenger functions go
Passenger :: Passenger(int start,int end)
{
    done = start==end?-2:-1;
    current = start;
    destination = end;
}
class Lift
{
    int direction;
    int floor;
    int* people[6];//It will store the addresses
    int farthestPoint;
    public:
    //Function definitions here
    Lift();
    void arrived();
    void enter();
    friend allot(Passenger human);
    friend void generateTerrain();
};
Lift elevators[];//Global Variable
//Lift functions go here
Lift :: Lift()
{
    direction = 0;
    floor = 0;
    finalDestination = 0;

}
void allot(Passenger human)
{
    int min = height;
    int minLift = 0;
    for(int i=0;i<lifts;i++)
    {
        min = min>abs(human.current-elevators[i].floor)?abs(human.current-elevators[i].floor):min;
        minLift = i;
    }


}
//Other Functions from here
void tick()//To speed up or slow down the simulation
{
    usleep(200000);//for 0.2 seconds
}
Passenger passengerSpawner(int height)
{
    //Creates a Passenger object and returns it later
    int start = rand() % height;
    int end = rand() % height;
    Passenger ob = new Passenger(start,end);
    return ob;
}
void generateTerrain()
{
    //The top of the building
    cout << "MyCorp"<<endl;
    for(int i=0;i<height;i++)
    {
        cout << "|";
        lifts
    }
}
int main()
{

    cout << "Enter the height of the building: ";
    cin >> height;
    cout << "Enter the number of lifts in the building: ";
    cin >> lifts;
    //Creating the lifts
    elevator = new elevator[lifts];
    for(int i=0;i<lifts;i++)
        elevator[i] = new elevator();
    liftEngineer(elevators);
    //Now to add objects
    Passenger unassigned[1000];
    //This will carry all the passengers that have not been assigned a lift yet
    newPassenger = passengerSpawner(height);
    if(done!=0)
    allot(newPassenger);
    return 0;
}