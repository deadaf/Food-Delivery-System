#include<iostream> //FINALLLLLL
#include<stdlib.h>
#include<vector>
#include<limits.h>
#include<algorithm>
#include <windows.h>
#include <chrono>
#include <thread>

using namespace std;
int n; // vertices
int m; //edges
//int graph[MAXN][MAXN];
const int MAXN = 16;
//vector<bool>check(20,false);
vector<int> BY1(30,0);
vector<int> BY2(30,0);
vector<int> BY3(30,0);
vector<int> BY4(30,0);
vector<int> BY5(30,0);

    int distanceBY1=0;
    int distanceBY2=0;
    int distanceBY3=0;
    int distanceBY4=0;
    int distanceBY5=0;


int graph[MAXN][MAXN] = {0}; // weighted adjacency matrix

int nearest_neighbor(int start, vector<int>& tour) {
    bool visited[MAXN] = {false}; // whether a vertex has been visited
    visited[start] = true;
    tour.push_back(start);

    int cost = 0;
    while (tour.size() < n) {
        int min_cost = INT_MAX;
        int min_vertex = -1;
        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                for (int j = 0; j < n; j++) {
                    if (!visited[j] && graph[i][j] != 0 && graph[i][j] < min_cost) {
                        min_cost = graph[i][j];
                        min_vertex = j;
                    }
                }
            }
        }
        if (min_vertex == -1) {
            // the graph is not connected, start a new component
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    start = i;
                    visited[start] = true;
                    tour.push_back(start);
                    break;
                }
            }
        } else {
            tour.push_back(min_vertex);
            visited[min_vertex] = true;
            cost += min_cost;
        }
    }

    // add the cost of returning to the starting vertex
    tour.push_back(start);
    cost += graph[tour.back()][start];

    return cost;
}


int findd(vector<vector<int>> dist,int n,int s,vector<bool> check)
{
    int minto=1000;
    int a=0;
    int alpha=0;
    for(alpha=0;alpha<n;alpha++)
    {
        if(dist[s][alpha]<minto && check[alpha]!=true)
        {
            a=alpha;
            minto=dist[s][alpha];
        }
    }

    return a;
}

void printSolution(vector<vector<int>> dist, int n)
{
    cout << "The following matrix shows the shortest "
            "distances"
            " between every pair of vertices \n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == 1000)
                cout << "INF"
                     << " ";
            else
                cout << dist[i][j] << "   ";
        }
        cout << endl;


    }
}

int floydd(vector<int> tour, vector<vector<int>> dist,int n,int vertices)
{
      for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((dist[i][j] > (dist[i][k] + dist[k][j]) )&& dist[k][j] !=INT_MAX
                        && dist[i][k] != INT_MAX)
                        {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    int count=0;
    int s=0;
    //tour.push_back(0);
    vector<bool>check(n,false);
    do{
    int ans=findd(dist,n,s,check);
    tour.push_back(ans);
    check[ans]=true;
    s=ans;
    count++;
    }
    while(count!=(vertices+1));
    tour.push_back(0);

    printSolution(dist,n);

    //path printing

    int costt=0;
    cout<<"~~~~~~~"<<endl;
     for (int i = 0; i < 168; i++)
     { cout << "*";
    cout.flush();  // ensure the * is immediately displayed
    this_thread::sleep_for(chrono::milliseconds(2));  // wait 50 milliseconds between each *
  }
     cout<<"Pay-Out for the delivery boy is : Rs."<<(n-1)*50<<endl;
      for (int i = 0; i < 168; i++)
     { cout << "*";
    cout.flush();  // ensure the * is immediately displayed
    this_thread::sleep_for(chrono::milliseconds(2));  // wait 50 milliseconds between each *
  }
    for(int i=0;i<tour.size();i++)
    {
        cout<<tour[i]<<"-->";
        costt += dist[i][i+1];
    }



    return costt;


}



/*int nearest_neighbor(int start, vector<int>& tour, vector<vector<int>>& graph,int n)
{
    //int n = graph.size();
    bool visited[20] = {false}; // whether a vertex has been visited
    tour.push_back(start); // starting from vertex 0
    visited[start] = true;

    for (int i = 1; i < n; i++) {
        int curr = tour[i-1];
        int min_dist = 1000;
        int min_vertex = -1;
        //for (auto [next, dist] : graph[curr]) { // iterate over all neighbors
        for (int j = 0; j < graph[curr].size(); j++)
        {
            int next = graph[curr][j];
            int dist = graph[curr][j+1];
            // rest of the loop body


            if (!visited[next] && dist < min_dist) {
                min_dist = dist;
                min_vertex = next;
            }
        }
        if (min_vertex == -1) {
            return -1; // the graph is not connected
        }
        tour.push_back(min_vertex);
        visited[min_vertex] = true;
    }

    // add the cost of returning to the starting vertex
    tour.push_back(start);

    // calculate the total distance travelled by each delivery partner for incentive purpose
    int cost = 0;
    for (int i = 0; i < n; i++) {
        cost += graph[tour[i]][tour[i+1]];
    }

    // print the path
    cout << "Path: ";
    for (int i = 0; i < tour.size(); i++) {
        cout << tour[i] << " ";
    }
    cout << endl;

    cout<<"cost from nearest "<<cost<<endl;
    return cost;
}*/

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}



void quicksort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[low];
        int i = low + 1, j = high;
        while (i <= j) {
            while (i <= j && arr[i] >= pivot) i++;
            while (i <= j && arr[j] < pivot) j--;
            if (i <= j) {
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
        swap(arr[low], arr[j]);
        quicksort(arr, low, j - 1);
        quicksort(arr, j + 1, high);
    }
}
int bill()
{
//system("color 78");
        /*for (int i = 0; i < 168; i++)
     { cout << "~";
    cout.flush();  // ensure the * is immediately displayed
    this_thread::sleep_for(chrono::milliseconds(1));  // wait 50 milliseconds between each *
  }*/
  cout<<endl;
        //cout << "\t\t\t\t\t\t\t#### CODES  FOR   FOOD    ITEMS ####\t\t\t\t" << endl;
         /*for (int i = 0; i < 168; i++)
     { cout << "~";
    cout.flush();  // ensure the * is immediately displayed
    this_thread::sleep_for(chrono::milliseconds(1));  // wait 50 milliseconds between each *
  }*/
  cout<<endl;
        int food;
        int check2;
        int totalcost = 0;
        //cout << "enter -1 for bill amount calculation or any other number to add more items" << endl;
        //cout << "1) for paneer" << endl << "2)for dal" << endl << "3)for chinese" << endl << "4)for breads" << endl << "for italian" << endl;
        //while(check2!=-1)
        do
        {   //cout<<"CODES FOR FODD ITEMS / MENU:-"<<endl;
     //MessageBox(NULL, "1) for paneer \n 2)for dal \n 3)for chinese \n 4)for breads \n 5)for italian", "MENU", MB_OK);
            cout << "enter code" << endl;
          cin >> food;


          switch (food)
          {
          case 1: cout<<"\t\t\t\t\t1 X Paneer  :  Rs.100 "<<endl;
            totalcost += 100;
            break;
          case 2: cout<<"\t\t\t\t\t1 X Dal   :  Rs.200 "<<endl;
            totalcost += 200;
            break;
          case 3: cout<<"\t\t\t\t\t1 X Chinese  :  Rs.300 "<<endl;
            totalcost += 300;
            break;
          case 4: cout<<"\t\t\t\t\t1 X Breads  :  Rs.400 "<<endl;
            totalcost += 400;
            break;
          case 5: cout<<"\t\t\t\t\t1 X Italian  :  Rs.500 "<<endl;
            totalcost += 500;
            break;
          }


        }

         while (food != -1);

return totalcost;
}
int vert()
{
        // read input
        cout<<endl;
        cout<<"enter number of deliveries and edges between them : " ;
    int m; // number of edges
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w; // the graph is undirected
    }
    int vt;
    cout<<endl;
    cout<<"Enter Delivery Person code : ";
    cin>>vt;
    switch(vt)
        {
            case 1: BY1.push_back(n-1); break;
            case 2: BY2.push_back(n-1); break;
            case 3: BY3.push_back(n-1); break;
            case 4: BY4.push_back(n-1); break;
            default: BY5.push_back(n-1); break;
        }
         vector<int> tour;
         int start = 0;
        // switch(vt)
        // {
        //     case 1: distanceBY1+=nearest_neighbor(start, tour); cout<<"Distance calculated from nearest neighbour is "<<distanceBY1; break;
        //     case 2: distanceBY2+=nearest_neighbor(start, tour); cout<<"Distance calculated from nearest neighbour is "<<distanceBY2;break;
        //     case 3: distanceBY3+=nearest_neighbor(start, tour); cout<<"Distance calculated from nearest neighbour is "<<distanceBY3;break;
        //     case 4: distanceBY4+= nearest_neighbor(start, tour); cout<<"Distance calculated from nearest neighbour is "<<distanceBY4;break;
        //     default: distanceBY5+=nearest_neighbor(start, tour);cout<<"Distance calculated from nearest neighbour is "<<distanceBY5; break;
        // }

    // find the minimal tour starting from vertex 0

    int cost = nearest_neighbor(start, tour);

    // print the minimal tour
    cout << "Minimal tour starting from " << start << ": ";
    for (int vertex : tour) {
        cout << vertex << " ";
    }
    cout<<"~~~~~~~"<<endl;
    cout<<"Pay-Out for the delivery boy is : "<<(n-1)*50<<endl;


    return 0;

}
int work()
{
    while(!0)
    {int opt;
    cout<<"1. Do you want to Determine Employee Of the Week?"<<endl;
    cout<<"2. Create New order"<<endl;
    cin>>opt;
    if (opt==1)
    {

        vector<int> arr;
        for(int i = 0; i < 5; i++) {
            int detail;
            cout << "Enter Details of Delivery Boy " << i + 1 << ": ";
            cin >> detail;
            arr.push_back(detail);
        }

        // Sort the array in descending order
        quicksort(arr, 0, arr.size() - 1);
        reverse(arr.begin(), arr.end());

        // Print the sorted array
        cout << "Sorted order of details ";
        for(int i = 0; i < arr.size(); i++) {
            cout << arr[i] << " ";
        }

        // Print the very first element of the sorted array
        cout << "\nEmployee of the week Deliveries are " << arr[4]<<endl;
    }

    else if (opt==2){
    int rows, cols,vertices, costy=0;
    cout << "Enter number of deliveries : ";
    cin >> rows;
    vertices=rows;
    cols=rows+1;
    rows=rows+1;
    //bill
    cout<<"\t\t\t\t\t\t\tCODES FOR FODD ITEMS / MENU:-"<<endl;
     MessageBox(NULL, "1) for paneer \n 2)for dal \n 3)for chinese \n 4)for breads \n 5)for italian \n -1 For BILLING ", "MENU", MB_OK);
     //cout <<  << endl;
    for(int i=0;i<vertices;i++)
    { cout<<endl<<endl;
         cout<<"\t\t\t\t\t\t\t ~~PAPII DI HATTI~~\t\t\t\t\t\t\t"<<endl<<endl;
        // Get the current time point
    auto now = chrono::system_clock::now();

    // Convert the time point to a time_t object
    time_t time = chrono::system_clock::to_time_t(now);

    // Print the time stamp
    cout << "\t\tTime : " << ctime(&time);
    cout<<"\t\t GSTIN: 21145879610"<<endl;
        int tc=bill();
        for (int i = 0; i < 168; i++)
     { cout << "-";
    cout.flush();  // ensure the * is immediately displayed
    this_thread::sleep_for(chrono::milliseconds(1));  // wait 50 milliseconds between each *
  }
  cout<<endl;
        cout<<"\t\t\t\t\t\t\t Bill for "<<i<<" order is ==>  "<<tc<<endl;
        for (int i = 0; i < 168; i++)
     { cout << "-";
    cout.flush();  // ensure the * is immediately displayed
    this_thread::sleep_for(chrono::milliseconds(1));  // wait 50 milliseconds between each *
  }
  cout<<endl;
        cout<<endl;

    }

    vector<vector<int>> matrix(rows, vector<int>(cols));
    vector<int> tour;
if(vertices<=5)
{
    cout << "Enter delivery coordinates ~~ Enter 1000000 for distance between same coordinate ( 1000000 here is taken as infinity) :\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(i==j)
            {
                matrix[i][j]=0;
            }
            else{
            cout <<"Enter ditance between "<< i << "th location to "<<j<<"th location  : ";
            cin >> matrix[i][j];
            }
        }
        cout<<endl;
    }
     cout << "The coordianates you entered are :\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";

        }
        cout<<endl;
    }
}


    if(vertices<=5)
    {
        int vt=0;
        cout<<"enter the code for delivery person available"<<endl;
        cin>>vt;

        switch(vt)
        {
            case 1: BY1.push_back(vertices); break;
            case 2: BY2.push_back(vertices); break;
            case 3: BY3.push_back(vertices); break;
            case 4: BY4.push_back(vertices); break;
            default: BY5.push_back(vertices); break;
        }
        switch(vt)
        {
            case 1: distanceBY1+=floydd(tour,matrix,rows,vertices); return distanceBY1; break;
            case 2: distanceBY2+=floydd(tour,matrix,rows,vertices); return distanceBY2;break;
            case 3: distanceBY3+=floydd(tour,matrix,rows,vertices); return distanceBY3;break;
            case 4: distanceBY4+=floydd(tour,matrix,rows,vertices); return distanceBY4;break;
            default: distanceBY5+=floydd(tour,matrix,rows,vertices);return distanceBY5; break;
        }


    }

    else
    {
        vert();
    }


}
}
}
int main()
{

system("color 5F");
    for (int i = 0; i < 168; i++)
     { cout << "*";
    cout.flush();  // ensure the * is immediately displayed
    this_thread::sleep_for(chrono::milliseconds(2));  // wait 50 milliseconds between each *
  }
  cout<<endl;
    cout << "\t\t\t\t\t\t\t** WELCOME TO REASTURANT FOOD-DELIVERY SERVICES **" << endl << endl;
    cout << "\t\t \t\t\t*HERE YOU CAN CHOOSE FOR DELIVERY TASK ASSIGNMENT OR EMPLOYEE INCENTIVE MANAGEMENT *" << endl << endl;

    for (int i = 0; i < 168; i++)
     { cout << "*";
    cout.flush();  // ensure the * is immediately displayed
    this_thread::sleep_for(chrono::milliseconds(2));  // wait 50 milliseconds between each *
  }
cout<<endl;
cout<<"enter yes for delivery continutaion and no for exiting delivery task"<<endl;
string sa= "yes";
while(sa!="no")
{
  int ay= work();

    for (int i = 0; i < 168; i++)
     { cout << "`";
    cout.flush();  // ensure the * is immediately displayed
    this_thread::sleep_for(chrono::milliseconds(2));  // wait 50 milliseconds between each *
  }

   cout<<"enter test conditin : ";
   cin>>sa;
   transform(sa.begin(), sa.end(), sa.begin(), ::tolower);
}
    //bonus

    cout<<endl;
    //QUICK SORT STARTING FROM HERE

   // vector<int> arr = {distanceBY1,distanceBY2,distanceBY3,distanceBY4,distanceBY5};
   // vector<int> arr = { *max_element(BY1.begin(),BY1.end()),
   //                 *max_element(BY2.begin(),BY2.end()),
   //                 *max_element(BY3.begin(),BY3.end()),
   //                 *max_element(BY4.begin(),BY4.end()),
   //                 *max_element(BY5.begin(),BY5.end()) };
// vector<int> arr[5];
//cout << "Enter Details of Delivery Boys" << endl;
// for(int i = 0; i < 5; i++) // Note that arrays in C++ start from index 0
//     {
//       int detail;
//         cin >> detail;
//         arr[i].push_back(detail);
//     }
//
//
//nt no = arr.size();
// quicksort(arr, 0, no - 1);
// cout<<"Weakest performer list"<<endl;
// for (int i = 0; i < no; i++) {
//   cout << arr[i] << " ";

        vector<int> arr[5];
        cout << "Enter Details of Delivery Boys" << endl;
        for(int i = 0; i < 5; i++) {
            int detail;
            cin >> detail;
            arr[i].push_back(detail);
        }

        int no = 5;
        for (int i = 0; i < no; i++) {
            quicksort(arr[i], 0, arr[i].size() - 1);
        }

        cout << "Weakest performer list" << endl;
        for (int i = 0; i < no; i++) {
            for (int j = 0; j < arr[i].size(); j++) {
                cout << arr[i][j] << " ";
            }
        }

    cout << endl;

}
