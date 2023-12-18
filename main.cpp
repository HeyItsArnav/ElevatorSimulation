#include <iostream>
#include <stdlib.h>
using namespace std;
const int LIMIT = 6;
class elevator
{
    protected:
    int direction;
    int last_floor;
    int current_floor;
    int people;
    public:
    elevator();
};
elevator :: elevator()
{
    direction = 0;
    last_floor = 0;
    people = 0;
    current_floor = 0;
}
//////////////////////////////////////////////////
class people
{
    elevator lift;
    int current_floor;
    int destination;
    int travelling;
    //It will be 1 for up, -1 for down and 0 for not travelling
    public:
    people();
    void spawn();
};
people :: people()
{
    current_floor = -1;
    destination = -1;
    travelling = 0;
}
void people :: spawn()
{
    current_floor = 2;//Something Random
    destination = 5;//Something random
    travelling = (destination - current_floor)>0?1:-1;
}
//////////////////////////////////////////////////
class building
{
    public:
    int RESIDENTS,FLOORS,LIFTS,RPF;
    building();
    people *members;
    elevator *lifts;
};
building :: building()
{
    cout << "Enter the height of the building: ";
    cin >> FLOORS;
    cout << "Enter the number of residents in the building: ";
    cin >> RESIDENTS;
    cout << "Enter the number of lifts available: ";
    cin >> LIFTS;
    members = new people[RESIDENTS];
    lifts = new elevator[LIFTS];
}
//////////////////////////////////////////////////
int main()
{
    building xyz;
    
    return 0;
}