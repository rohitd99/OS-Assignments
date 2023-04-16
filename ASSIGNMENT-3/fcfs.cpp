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
    sort(arr.begin(), arr.end(), compareArrival);
    double avg_wait = 0;
    double avg_tat = 0;
    double time = 0;
    cout << "\n\nGantt Chart :\n";
    cout << "|Start-time|----Process----|End-time| \n\n";
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            time = arr[i].arrival_time;
            cout << "|" << time << "|"
                 << "--P[" << arr[i].id << "]--|";
            arr[i].waiting_time = 0;
            arr[i].completion_time = arr[i].arrival_time + arr[i].burst_time;
            time += (arr[i].completion_time - time);
            cout << time << "|";
        }
        else
        {
            if (arr[i].arrival_time < arr[i - 1].completion_time)
            {
                arr[i].completion_time = arr[i - 1].completion_time + arr[i].burst_time;
            }
            else
            {
                arr[i].completion_time = arr[i].arrival_time + arr[i].burst_time;
                time = arr[i].arrival_time;
            }
            cout << "|" << time << "|"
                 << "--P[" << arr[i].id << "]--|";
            time += (arr[i].completion_time - time);
            cout << time << "|";
        }
        arr[i].turnaround_time = arr[i].completion_time - arr[i].arrival_time;
        arr[i].waiting_time = arr[i].turnaround_time - arr[i].burst_time;
        avg_tat += arr[i].turnaround_time;
        avg_wait += arr[i].waiting_time;
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
