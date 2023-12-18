#include <iostream>
#include <unistd.h>
#include <math.h>
using namespace std;
const int LIMIT = 6;
class elevator
{
    public:
    int direction;
    int last_floor;
    int current_floor;
    int people;
    int otherDest;
    public:
    elevator();
};
elevator :: elevator()
{
    direction = 0;
    last_floor = 0;
    people = 0;
    current_floor = 0;
    otherDest = -1;
}
//////////////////////////////////////////////////
class people
{
    public:
    elevator lift;
    int current_floor;
    int destination;
    int travelling;
    //It will be 1 for up, -1 for down and 0 for not travelling
    public:
    people();
    int time(elevator lift);
};
people :: people()
{
    current_floor = -1;
    destination = -1;
    travelling = 0;

}
int people :: time(elevator lift)//Returns the time taken
{
    if(((destination)-(current_floor))*lift.direction>0)
    {
        return(abs(lift.current_floor-current_floor));
    }
    else
    {
        return(abs(lift.last_floor-lift.current_floor)+abs(lift.current_floor-current_floor));
    }
}
//////////////////////////////////////////////////
class building
{
    public:
    int RESIDENTS,FLOORS,LIFTS,RPF;
    building();
    people *members;
    elevator *lifts;
    void construct();
    void fastestTime(people human);
    void tick();
    void spawn();
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
void building :: construct()
{
    cout << endl;
    for(int i = FLOORS-1; i>=0;i--)
    {
        cout << "||\t";
        for(int j=0;j<LIFTS;j++)
        {
            if(lifts[j].current_floor==i)
            cout << "[|]\t";
            else
            cout << " | \t";
        }
        cout << " ||";
        for(int j=0;j<RESIDENTS;j++)
        {
            if(members[j].current_floor==i)
            {
                cout << " I ";
            }
        }
        cout << endl;
    }

}
void building :: fastestTime(people human)
{
    int* time = new int[LIFTS];
    int min,minindex,buffer;
    minindex = 0;
    min = 1000000;
    for(int i=0;i<LIFTS;i++)
    {
        buffer = human.time(lifts[i]);
        if(buffer<min)
        {
            min = buffer;
            minindex = i;
        }
    }
    buffer = lifts[min].last_floor;
    int dir = lifts[min].direction;
    if(lifts[min].direction*buffer>lifts[min].direction*lifts[min].last_floor)//Dont ask me what I did here, Even I do not know
    {
        lifts[min].last_floor=buffer;
    }
    else if(dir*buffer<dir*lifts[min].current_floor)
    {
        lifts[min].otherDest=buffer;
    }
}
void building :: spawn()
{
    int mem = (rand()%RESIDENTS);
    if(members[mem].travelling==0)
    {
        members[mem].current_floor = (rand()%(FLOORS)-1);
        members[mem].destination = ((rand()%(FLOORS)-1));
        members[mem].travelling = (members[mem].destination - members[mem].current_floor)>0?1:-1;
    }
}
//////////////////////////////////////////////////
//Every 0.5 seconds in this code, a tick passes
void building :: tick()
{
    construct();
    //moving every lift
    for(int i=0;i<LIFTS;i++)
    {
        int dir = (lifts[i].last_floor-lifts[i].current_floor)/abs(lifts[i].last_floor-lifts[i].current_floor);
        if(dir>0&&lifts[i].current_floor+1<FLOORS)
        {
            lifts[i].current_floor+=1;
        }
        else if(dir<0&&lifts[i].current_floor+1>0)
        {
            lifts[i].current_floor--;
        }
        else if(lifts[i].current_floor==lifts[i].last_floor)
        {
            if(lifts[i].otherDest!=-1)
            {
                lifts[i].last_floor = lifts[i].otherDest;
                lifts[i].otherDest = -1;
            }
            //If no error occurs, leave it like that, otherwise if lift glitches, add a condition
        }
    }
    //put passenger on lift
    for(int i=0;i<RESIDENTS;i++)
    {
        if(members[i].travelling!=0)
        {
            fastestTime(members[i]);
            for(int j=0;i<LIFTS;j++)
            {
                if(members[i].current_floor==lifts[i].current_floor)
                {
                    int dir = (lifts[j].last_floor-lifts[j].current_floor)/abs(lifts[j].last_floor-lifts[j].current_floor);
                    if(dir==members[i].travelling)
                    {
                        members[i].lift = lifts[j];
                    }
                }
                if(members[i].destination==lifts[i].current_floor)
                {
                    members[i].travelling = 0;
                }
            }
        }
    }
    for(int i=0;i<5;i++)
    spawn();
    system("cls");
}
//////////////////////////////////////////////////
int main()
{
    building xyz;
    while(true)
    {
        xyz.tick();
        sleep(1);
    }
    return 0;
}