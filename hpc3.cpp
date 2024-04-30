#include<bits/stdc++.h>
#include<omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

int Min(vector<int> &arr)
{
    int result=arr[0];
    for(int i=1;i<arr.size();i++)
    {
        result=min(result, arr[i]);
    }
    return result;
}

int parallelMin(vector<int> &arr)
{
    int result=arr[0];
#pragma omp parallel for reduction(min:result)
    for(int i=1;i<arr.size();i++)
    {
        result=min(result, arr[i]);
    }
    return result;
}

int Max(vector<int> &arr)
{
    int result=arr[0];
    for(int i=1;i<arr.size();i++)
    {
        result=max(result, arr[i]);
    }
    return result;
}

int parallelMax(vector<int> &arr)
{
    int result=arr[0];
#pragma omp parallel for reduction(max:result)
    for(int i=1;i<arr.size();i++)
    {
        result=max(result, arr[i]);
    }
    return result;
}

int Sum(vector<int> & arr)
{
    int result=arr[0];
    for(int i=1; i<arr.size();i++)
    {
        result+=arr[i];
    }
    return result;
}

int parallelSum(vector<int> & arr)
{
    int result=arr[0];
#pragma omp parallel for reduction(+:result)
    for(int i=1; i<arr.size();i++)
    {
        result+=arr[i];
    }
    return result;
}

double Average(vector<int> &arr)
{
    int sum=Sum(arr);
    return static_cast<double>(sum)/arr.size();
}

double parallelAverage(vector<int> &arr)
{
    int sum=parallelSum(arr);
    return static_cast<double>(sum)/arr.size();
}

int main()
{
    const int size=10000;
    vector<int> arr(size);
    
    for(int i=0; i<size;i++)
    {
        arr[i]=rand()%1000;
    }
    
    auto start = high_resolution_clock::now();
    int minVal = Min(arr);
    auto stop = high_resolution_clock::now();
    auto timemin = duration_cast<nanoseconds>(stop - start);
      
    start = high_resolution_clock::now();
    int pminVal = parallelMin(arr);
    stop = high_resolution_clock::now();
    auto ptimemin = duration_cast<nanoseconds>(stop - start);
    cout << "Minimum value: " << minVal << endl;
    cout << "P Minimum value: " << pminVal << endl;
    cout<<"Sequential Minimum "<<timemin.count()<<"nanoseconds"<<endl;
    cout<<"Parallel Minimum "<<ptimemin.count()<<"nanoseconds"<<endl;
    
    start = high_resolution_clock::now();
    int maxVal = Max(arr);
    stop = high_resolution_clock::now();
    auto timemax = duration_cast<nanoseconds>(stop - start);
    
    start = high_resolution_clock::now();
    int pmaxVal = parallelMax(arr);
    stop = high_resolution_clock::now();
    auto ptimemax = duration_cast<nanoseconds>(stop - start);
    cout << "Maximum value: " << maxVal << endl;
    cout << "P Maximum value: " << pmaxVal << endl;
    cout<<"Sequential Maximum "<<timemax.count()<<"nanoseconds"<<endl;
    cout<<"Parallel Maximum "<<ptimemax.count()<<"nanoseconds"<<endl;
     
    start = high_resolution_clock::now();
    int sumVal = Sum(arr);
    stop = high_resolution_clock::now();
    auto timesum = duration_cast<nanoseconds>(stop - start);
    
    start = high_resolution_clock::now();
    int psumVal = parallelSum(arr);
    stop = high_resolution_clock::now();
    auto ptimesum = duration_cast<nanoseconds>(stop - start);

    cout << "Sum value: " << sumVal << endl;
    cout << "P Sum value: " << psumVal << endl;
    cout<<"Sequential Sum "<<timesum.count()<<"nanoseconds"<<endl;
    cout<<"Parallel Sum "<<ptimesum.count()<<"nanoseconds"<<endl;
     
    start = high_resolution_clock::now();
    int avgVal = Average(arr);
    stop = high_resolution_clock::now();
    auto timeavg = duration_cast<nanoseconds>(stop - start);
    
    start = high_resolution_clock::now();
    int pavgVal = parallelAverage(arr);
    stop = high_resolution_clock::now();
    auto ptimeavg = duration_cast<nanoseconds>(stop - start);

    cout << "Average value: " << avgVal << endl;
    cout << "P Average value: " << pavgVal << endl;
    cout<<"Sequential Average "<<timeavg.count()<<"nanoseconds"<<endl;
    cout<<"Parallel Average "<<ptimeavg.count()<<"nanoseconds"<<endl;
     
}
