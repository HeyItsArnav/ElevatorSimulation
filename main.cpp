#include <iostream>
using namespace std;
int RESIDENTS,FLOORS,LIFTS;
const int LIMIT = 6;
class building
{
    public:
    int RESIDENTS,FLOORS,LIFTS;
    building();
};
building :: building()
{
    cout << "Enter the height of the building: ";
    cin >> FLOORS;
    cout << "Enter the number of residents in the building: ";
    cin >> RESIDENTS;
    cout << "Enter the number of lifts available: ";
    cin >> LIFTS;
}
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
    int direction;
};
//////////////////////////////////////////////////

//////////////////////////////////////////////////
int main()
{
    building xyz;

    return 0;
}