#include <iostream>
#include <unistd.h>
#include <math.h>
using namespace std;
int delivered = 0;
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
    int dir = (lift.last_floor-lift.current_floor)/abs(lift.last_floor-lift.current_floor);
    if(((destination)-(current_floor))*dir>0)
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
    for(int i = 0; i<FLOORS;i++)
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
            if((members[j].current_floor==i)&&(members[j].travelling!=0))
            {
                cout << " I ";
            }
        }
        cout << endl;
    }
    cout << lifts[0].current_floor << " " << lifts[0].last_floor<<" Delivered: " << delivered;
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
    int dir = (lifts[min].last_floor-lifts[min].current_floor)/abs(lifts[min].last_floor-lifts[min].current_floor);
    if(dir*buffer>dir*lifts[min].last_floor)//Dont ask me what I did here, Even I do not know
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
        members[mem].current_floor = (rand()%(FLOORS-1));
        members[mem].destination = ((rand()%(FLOORS-1)));
        if(members[mem].destination!=members[mem].current_floor)
        {
            members[mem].travelling = (members[mem].destination - members[mem].current_floor)>0?1:-1;
            fastestTime(members[mem]);   
        }
    }
}
//////////////////////////////////////////////////
//Every 0.5 seconds in this code, a tick passes
void building :: tick()
{
    system("clear");
    for(int i=0;i<5;i++)
    spawn();
    //moving every lift
    for(int i=0;i<LIFTS;i++)
    {
        int dir = (lifts[i].last_floor-lifts[i].current_floor)/abs(lifts[i].last_floor-lifts[i].current_floor);
        if((dir>0)&&(lifts[i].current_floor+1<FLOORS))
        {
            lifts[i].current_floor+=1;
        }
        else if(dir<0&&lifts[i].current_floor>0)
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
            else
            {
                lifts[i].last_floor = lifts[i].current_floor==0?(FLOORS-1):0;
            }
        }
    }
    //put passenger on lift
    for(int i=0;i<RESIDENTS;i++)
    {
        if(members[i].travelling!=0)
        {
            for(int j=0;j<LIFTS;j++)
            {
                if(members[i].current_floor==lifts[i].current_floor)
                {
                    int dir = (lifts[j].last_floor-lifts[j].current_floor)/abs(lifts[j].last_floor-lifts[j].current_floor);
                    if(dir==members[i].travelling)
                    {
                        members[i].lift = lifts[j];
                        members[i].travelling = 0;
                        members[i].lift.current_floor = members[i].current_floor;
                        break;
                    }
                }
                if(members[i].destination==members[i].lift.current_floor)
                {
                    delivered++;
                    members[i].current_floor = -1;
                    members[i].destination = -1;
                }
            }
        }
    }
    construct();
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