#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    int id = 0;
    double arrival_time = 0;
    double burst_time = 0;
    double waiting_time = 0;
    double completion_time = 0;
    double turnaround_time = 0;
    int priority = 0;
    // Process(int i, int at, int bt, int wt = 0, int ct = 0, int tat = 0)
    // {
    //     id = i;
    //     arrival_time = at;
    //     burst_time = bt;
    //     waiting_time = wt;
    //     completion_time = ct;
    //     turnaround_time = tat;
    // }
} Process;
void copyP(Process &a, Process &b)
{
    Process temp;
    temp.id = a.id;
    temp.arrival_time = a.arrival_time;
    temp.burst_time = a.burst_time;
    temp.completion_time = a.completion_time;
    temp.priority = a.priority;
    temp.turnaround_time = a.turnaround_time;
    temp.waiting_time = a.waiting_time;

    a.id = b.id;
    a.arrival_time = b.arrival_time;
    a.completion_time = b.completion_time;
    a.priority = b.priority;
    a.burst_time = b.burst_time;
    a.turnaround_time = b.turnaround_time;
    a.waiting_time = b.waiting_time;

    b.id = temp.id;
    b.arrival_time = temp.arrival_time;
    b.completion_time = b.completion_time;
    b.priority = temp.priority;
    b.burst_time = temp.burst_time;
    b.turnaround_time = temp.turnaround_time;
    b.waiting_time = temp.waiting_time;
}
bool compareArrival(Process a, Process b)
{
    return (a.arrival_time < b.arrival_time);
}
bool compareBurst(Process a, Process b)
{
    return (a.burst_time < b.burst_time);
}
bool comparePriority(Process a, Process b)
{
    if (a.priority == b.priority)
    {
        return (a.arrival_time < b.arrival_time);
    }
    else
        return (a.priority < b.priority);
}

// Process copy(Process a)
// {
//     Process temp;
//     temp.id = a.id;
//     temp.arrival_time = a.arrival_time;
//     temp.burst_time = a.burst_time;
//     temp.waiting_time = a.waiting_time;
//     temp.completion_time = a.completion_time;
//     temp.turnaround_time = a.turnaround_time;
// }

int main(int argc, char const *argv[])
{

    cout << "------------- Precision is set to 3 digits -------------\n"
         << setprecision(3);
    int n = 0;
    double quantum = 0;
    try
    {
        cout << "Enter the number of processes : ";
        cin >> n;
        if (n <= 0)
            throw "Exception : Zero or Negative processes entered\n";
        cout << "Enter the time quantum : ";
        cin >> quantum;
        if (quantum <= 0)
            throw "Exception : Quantum must be greater than 0\n";
    }
    catch (const char *exception)
    {
        cout << exception;
        return -1;
    }
    vector<Process> arr(n);
    // vector<Process> arr = {Process(1, 0, 5), Process(2, 1, 4), Process(3, 2, 2), Process(4, 3, 1)};
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i << "] Arrivaltime Bursttime Priority: ";
        arr[i].id = i;
        try
        {
            cin >> arr[i].arrival_time >> arr[i].burst_time >> arr[i].priority;
            if (arr[i].arrival_time < 0)
                throw "Exception : Arrival time cannot be less than zero\n";
            if (arr[i].burst_time <= 0.00)
                throw "Exception : Burst time cannot be less than equal to zero\n";
            if (arr[i].priority < 0)
                throw "Exception : Priority cannot be less than zero\n";
        }
        catch (const char *exception)
        {
            cout << exception;
            return -1;
        }
    }
    cout << "Gantt Chart : \n";
    cout << "|Start-time|----Process----|End-time| \n\n";
    sort(arr.begin(), arr.begin() + n, compareArrival);
    vector<Process> readyQ;
    map<int, double> processTimes;
    // set<int> completed;
    double avg_wait = 0;
    double avg_tat = 0;
    double time = 0;
    bool removed = true;
    while (processTimes.size() != n)
    {
        for (int i = 0; i < n; i++)
        {

            if (arr[i].arrival_time <= time && processTimes.find(arr[i].id) == processTimes.end())
            {
                readyQ.push_back(arr[i]);
                // completed.insert(arr[i].id);
                processTimes[arr[i].id] = arr[i].burst_time;
            }
        }
        if (removed == false)
        {
            Process temp;
            copyP(temp, readyQ[0]);
            readyQ.erase(readyQ.begin());
            sort(readyQ.begin(), readyQ.end(), comparePriority);
            readyQ.push_back(temp);
        }
        else
        {
            sort(readyQ.begin(), readyQ.end(), comparePriority);
        }
        if (readyQ.empty() != true)
        {
            for (int i = 0; i < n; i++)
            {
                if (arr[i].id == readyQ[0].id)
                {
                    cout << "|" << time << "|"
                         << "--P[" << arr[i].id << "]--|";
                    if (processTimes[arr[i].id] > quantum)
                    {
                        processTimes[arr[i].id] -= quantum;
                        time += quantum;
                        removed = false;
                        cout << time << "|";
                    }
                    else
                    {
                        time += processTimes[arr[i].id];
                        processTimes[arr[i].id] = 0;
                        arr[i].completion_time = time;
                        arr[i].turnaround_time = arr[i].completion_time - arr[i].arrival_time;
                        arr[i].waiting_time = arr[i].turnaround_time - arr[i].burst_time;
                        avg_tat += arr[i].turnaround_time;
                        avg_wait += arr[i].waiting_time;
                        readyQ.erase(readyQ.begin());
                        removed = true;
                        cout << time << "|";
                        if (processTimes.size() == n)
                            sort(readyQ.begin(), readyQ.end(), comparePriority);
                    }
                }
            }
        }
    }
    if (removed == false)
    {
        Process temp;
        copyP(temp, readyQ[0]);
        readyQ.erase(readyQ.begin());
        sort(readyQ.begin(), readyQ.end(), comparePriority);
        readyQ.push_back(temp);
    }
    else
    {
        sort(readyQ.begin(), readyQ.end(), comparePriority);
    }
    while (readyQ.empty() != true)
    {
        for (int i = 0; i < n; i++)
        {

            if (arr[i].id == readyQ[0].id)
            {
                cout << "|" << time << "|"
                     << "--P[" << arr[i].id << "]--|";
                if (processTimes[arr[i].id] > quantum)
                {
                    processTimes[arr[i].id] -= (double)quantum;
                    time += (double)quantum;
                    removed = false;
                    cout << time << "|";
                }
                else
                {
                    time += processTimes[arr[i].id];
                    processTimes[arr[i].id] = 0;
                    arr[i].completion_time = time;
                    arr[i].turnaround_time = arr[i].completion_time - arr[i].arrival_time;
                    arr[i].waiting_time = arr[i].turnaround_time - arr[i].burst_time;
                    avg_tat += arr[i].turnaround_time;
                    avg_wait += arr[i].waiting_time;
                    readyQ.erase(readyQ.begin());
                    removed = true;
                    cout << time << "|";
                }
            }
        }
        if (removed == false)
        {
            Process temp;
            copyP(temp, readyQ[0]);
            readyQ.erase(readyQ.begin());
            sort(readyQ.begin(), readyQ.end(), comparePriority);
            readyQ.push_back(temp);
        }
        else
        {
            sort(readyQ.begin(), readyQ.end(), comparePriority);
        }
    }
    cout << "\n\n";
    cout << "Process id\t\t"
         << "Arrival Time\t\t"
         << "Burst Time\t\t"
         << "Priority\t\t"
         << "Completion Time\t\t"
         << "Wait Time\t\t"
         << "TAT\n";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i].id << "\t\t\t" << arr[i].arrival_time << "\t\t\t" << arr[i].burst_time << "\t\t\t" << arr[i].priority << "\t\t\t" << arr[i].completion_time << "\t\t\t" << arr[i].waiting_time << "\t\t\t" << arr[i].turnaround_time << "\n";
    }
    avg_wait = avg_wait / n;
    avg_tat = avg_tat / n;
    cout << "Average Wait Time : " << avg_wait << "\n";
    cout << "Average Turnaround Time : " << avg_tat << "\n";
    return 0;
}