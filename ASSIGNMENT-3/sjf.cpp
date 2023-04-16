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

} Process;
bool compareArrival(Process a, Process b)
{
    return (a.arrival_time < b.arrival_time);
}
bool compareBurst(Process a, Process b)
{
    return (a.burst_time < b.burst_time);
}

int main(int argc, char const *argv[])
{

    cout << "------------- Precision is set to 3 digits -------------\n"
         << setprecision(3);
    int n = 0;
    cout << "Enter the number of processes : ";
    try
    {
        cin >> n;
        if (n <= 0)
            throw "Exception : Zero or Negative processes entered\n";
    }
    catch (const char *exception)
    {
        cout << exception;
        return -1;
    }
    vector<Process> arr(n);
    // vector<Process> arr = {Process(0, 1, 7), Process(1, 3, 3), Process(2, 6, 2), Process(3, 7, 10), Process(4, 9, 8)};
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i << "] Arrivaltime Bursttime: ";
        arr[i].id = i;
        try
        {
            cin >> arr[i].arrival_time >> arr[i].burst_time;
            if (arr[i].arrival_time < 0)
                throw "Exception : Arrival time cannot be less than zero\n";
            if (arr[i].burst_time <= 0.00)
                throw "Exception : Burst time cannot be less than equal to zero\n";
        }
        catch (const char *exception)
        {
            cout << exception;
            return -1;
        }
    }

    sort(arr.begin(), arr.begin() + n, compareArrival);
    vector<Process> readyQ;
    set<int> completed;
    double avg_wait = 0;
    double avg_tat = 0;
    double time = 0.0;
    cout << "Gantt Chart : \n";
    cout << "|Start-time|----Process----|End-time| \n\n";
    while (completed.size() != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i].arrival_time <= time && completed.find(arr[i].id) == completed.end())
            {
                readyQ.push_back(arr[i]);
                completed.insert(arr[i].id);
            }
        }
        sort(readyQ.begin(), readyQ.end(), compareBurst);
        if (readyQ.empty() != true)
        {
            for (int i = 0; i < n; i++)
            {
                if (arr[i].id == readyQ[0].id)
                {
                    cout << "|" << time << "|"
                         << "--P[" << arr[i].id << "]--|";
                    arr[i].completion_time = readyQ[0].burst_time + time;
                    arr[i].turnaround_time = arr[i].completion_time - arr[i].arrival_time;
                    arr[i].waiting_time = arr[i].turnaround_time - arr[i].burst_time;
                    avg_tat += arr[i].turnaround_time;
                    avg_wait += arr[i].waiting_time;
                }
            }
            time = time + readyQ[0].burst_time;
            cout << time << "|";
            readyQ.erase(readyQ.begin());
        }
        else
            time += 0.01;
    }
    while (readyQ.empty() != true)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i].id == readyQ[0].id)
            {
                cout << "|" << time << "|"
                     << "--P[" << arr[i].id << "]--|";
                arr[i].completion_time = readyQ[0].burst_time + time;
                arr[i].turnaround_time = arr[i].completion_time - arr[i].arrival_time;
                arr[i].waiting_time = arr[i].turnaround_time - arr[i].burst_time;
                avg_tat += arr[i].turnaround_time;
                avg_wait += arr[i].waiting_time;
            }
        }
        time = time + readyQ[0].burst_time;
        cout << time << "|";
        readyQ.erase(readyQ.begin());
    }
    cout << "\n\n";
    cout << "Process id\t\t"
         << "Arrival Time\t\t"
         << "Burst Time\t\t"
         << "Completion Time\t\t"
         << "Wait Time\t\t"
         << "TAT\n";
    for (int i = 0; i < n; i++)
    {
        cout << setprecision(3) << arr[i].id << "\t\t\t" << arr[i].arrival_time << "\t\t\t" << arr[i].burst_time << "\t\t\t" << arr[i].completion_time << "\t\t\t" << arr[i].waiting_time << "\t\t\t" << arr[i].turnaround_time << "\n";
    }
    avg_wait = avg_wait / n;
    avg_tat = avg_tat / n;
    cout << "Average Wait Time : " << avg_wait << "\n";
    cout << "Average Turnaround Time : " << avg_tat << "\n";
    return 0;
}