#include <bits/stdc++.h>
using namespace std;
void bankers(int n, int m, vector<vector<int>> &ans, vector<vector<int>> &need, vector<int> available, vector<vector<int>> &allocated, vector<bool> completed, vector<int> order)
{
    if (order.size() == n)
    {
        ans.push_back(order);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        if (completed[i])
            continue;
        for (int j = 0; j < m; j++)
        {
            
            if (need[i][j] <= available[j])
            {
                count++;
            }
            else
            {
                break;
            }
        }
        if (count == m)
        {
            completed[i] = true;
            order.push_back(i);
            for (int j = 0; j < m; j++)
            {
                available[j] = available[j] + allocated[i][j];
            }
            bankers(n, m, ans, need, available, allocated, completed, order);
            completed[i] = false;
            order.pop_back();
            for (int j = 0; j < m; j++)
            {
                available[j] = available[j] - allocated[i][j];
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    int n_process = 5, n_resource = 3;
    cout << "Enter the no of processes : ";
    cin >> n_process;
    cout << "Enter the unique no of resources : ";
    cin >> n_resource;
    vector<int> max_available(n_resource, 0);
    max_available = {10,5,7};
    cout << "Enter the max available resources : \n";
    for (int i = 0; i < n_resource; i++)
        cin >> max_available[i];
    cout << "Enter the currently available resources : \n";
    vector<int> available(n_resource, 0);
    available = {3,3,2};
    for (int i = 0; i < n_resource; i++)
        cin >> available[i];
    cout << "Enter the maximum need of each process : \n";
    vector<vector<int>> max_need(n_process, vector<int>(n_resource, 0));
    // max_need = {{7,5,3},{3,3,2},{9,0,2},{2,2,2},{4,3,3}};
    for (int i = 0; i < n_process; i++)
        for (int j = 0; j < n_resource; j++)
        {
            try
            {
                cin >> max_need[i][j];
                if (max_need[i][j] > max_available[j])
                {
                    throw "Max needed resource exceeds the total resource\n";
                }
                else if (max_need[i][j] < 0)
                {
                    throw "Max need cannot be negative\n";
                }
            }
            catch (const char *error)
            {
                cout << error;
                return -1;
            }
        }
    cout << "Enter the allocated resources of each process : \n";
    vector<vector<int>> allocated(n_process, vector<int>(n_resource, 0));
    // allocated = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    for (int i = 0; i < n_process; i++)
        for (int j = 0; j < n_resource; j++)
        {
            try
            {
                cin >> allocated[i][j];
                if (allocated[i][j] > max_available[j])
                {
                    throw "Allocated resource exceeds the total resource\n";
                }
                else if (allocated[i][j] < 0)
                {
                    throw "Allocated resource need cannot be negative\n";
                }
            }
            catch (const char *error)
            {
                cout << error;
                return -1;
            }
        }
    vector<vector<int>> need(n_process, vector<int>(n_resource, 0));
    for (int i = 0; i < n_process; i++)
        for (int j = 0; j < n_resource; j++)
        {
            need[i][j] = max_need[i][j] - allocated[i][j];
        }
    int choice = 0;
    cout << "\n\n-------Menu-------\n";
    cout << "1. Generate all safe sequences\n";
    cout << "2. Check for Additional Request\n";
    cout << "3. Exit\n";
    cout << "Enter your choice : ";
    cin >> choice;
    while(choice != 3)
    {
        switch(choice)
        {
        case 1:
            {
                vector<bool> completed(n_process, false);
                vector<int> order;
                vector<vector<int>> ans;
                bankers(n_process, n_resource, ans, need, available, allocated, completed, order);
                if(ans.empty() == false)
                {
                    for(auto i : ans)
                    {
                        for(int j = 0;j < i.size();j++)
                        {
                            if(j != i.size()-1)
                                cout << "P" << i[j] << "-> ";
                            else
                                cout << "P" << i[j];
                        }
                        cout << "\n";
                    }
                }else{
                    cout << "No Safe Sequence is possible \n";
                }
                break;
            }
        case 2:
            {
                int process = 0;
                cout << "\nEnter the process :";
                cin >> process;
                vector<int> request(n_resource,0);
                bool reqG = false;
                cout << "\nEnter the additional request for respective resources :";
                for(int i = 0;i < request.size();i++)
                    cin >> request[i];
                for(int i = 0;i < n_resource;i++)
                {
                    if(request[i] > need[process][i])
                    {
                        cout << "Request greater than need\n";
                        reqG = true;
                        break;
                    }
                }
                if(reqG)
                    break;
                else{
                    bool grant = true;
                    for(int i = 0;i < n_resource;i++)
                    {   
                        if(request[i] > available[i])
                        {
                            grant = false;
                        }
                    }
                    if(grant)
                    {
                        for(int i = 0;i < n_resource;i++)
                        {
                            available[i] = available[i] - request[i];
                            allocated[process][i] = allocated[process][i] + request[i];
                            need[process][i] = need[process][i] - request[i];
                        }
                        vector<bool> completed(n_process, false);
                        vector<int> order;
                        vector<vector<int>> ans;
                        bankers(n_process, n_resource, ans, need, available, allocated, completed, order);
                        if(ans.empty())
                        {
                            cout << "No safe sequence can be generated for the following request\n";
                        }else{
                            cout << "The request can be granted and safe sequence is/are : \n";
                            for(auto i : ans)
                            {
                                for(int j = 0;j < i.size();j++)
                                {
                                    if(j != i.size()-1)
                                        cout << "P" << i[j] << "-> ";
                                    else
                                        cout << "P" << i[j];
                                }
                                cout << "\n";
                            }
                        }
                        for(int i = 0;i < n_resource;i++)
                        {
                            available[i] = available[i] + request[i];
                            allocated[process][i] = allocated[process][i] - request[i];
                            need[process][i] = need[process][i] + request[i];
                        }
                    }else{
                        cout << "The above request cannot be granted immediately it must wait\n";
                    }
                }
                break;
            }
            
        case 3:
            return 0;
            break;
        default:
            cout << "Invalid option entered\n";
            break;
        }
        cout << "\n\n-------Menu-------\n";
        cout << "1. Generate all safe sequences\n";
        cout << "2. Check for Additional Request\n";
        cout << "3. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;
    }
    return 0;
}
