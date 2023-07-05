#include <bits/stdc++.h>
using namespace std;
typedef long long int ll ;

int main() {
	int n ; 
	cout << "Enter the number of task: " ;
	cin >> n ;
	
	vector<pair<ll, ll> > v ;
	int arr[n+2], burst[n+2] ;
	ll maxpossibletime = 0 ;
	for(int i=1; i<=n; i++) {
		ll b, a ;
		cout << "Enter the burst time of P" << i << ": " ;
		cin >> b ;
		cout << "Enter the arrival time of P" << i << ": " ;
		cin >> a ;
		v.push_back({a, i}) ;
		arr[i] = a ;
		burst[i] = b ;
		maxpossibletime += (a+b) ;
	}
	
	sort(v.begin(), v.end()) ;
	
	ll task=0, ongoing_process=0 ;
	queue<ll>q ;
	ll start[n+2] ;
	ll idx = 0 ;
	cout << "\nGantt Chart: " ;
	for(int t=0; t<=maxpossibletime; t++) {
		while(v[task].first == t) {
			q.push(v[task].second) ;
			task++ ;
		}
		
		if(!ongoing_process) {
			idx = q.front() ;
			ongoing_process = burst[idx] ;
			start[idx] = t ;
			q.pop() ;
		}
		
		if(ongoing_process) {
			cout << idx ;
			ongoing_process-- ;
		} else {
			idx = 0 ;
			cout << idx ;
		}
	}
	cout << endl ;
	float total_wait = 0, total_tat=0 ;
	for(int i=1; i<=n; i++) {
		ll end = start[i]+burst[i]-1 ;
		ll wait = start[i]-arr[i] ;
		ll tat = burst[i] + wait ;
		total_wait += wait ;
		total_tat += tat ;
		cout << "Process: P" << i << " Start time: " << start[i] << " End time: " << end << " Waiting time: " << wait << " Turnaround time: " << tat << endl ;
	}
	
	float avgw = total_wait/n ;
	float avgtat = total_tat/n ;
	
	cout << "Average Waiting/Response time: " << avgw << endl ;
	cout << "Average Turnaround time: " << avgtat << endl ;
	
	return 0;
}
