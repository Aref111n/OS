#include <bits/stdc++.h>
using namespace std;
typedef long long int ll ;

int main() {
	int n ; 
	cout << "Enter the number of task: " ;
	cin >> n ;
	
	vector<pair<ll, ll> > v ;
	int arr[n+2], burst[n+2], priority[n+2] ;
	ll maxpossibletime = 0 ;
	for(int i=1; i<=n; i++) {
		ll b, a, p ;
		cout << "Enter the burst time of P" << i << ": " ;
		cin >> b ;
		cout << "Enter the arrival time of P" << i << ": " ;
		cin >> a ;
		cout << "Enter the priority of P" << i << ": " ;
		cin >> p ;
		v.push_back({a, i}) ;
		arr[i] = a ;
		burst[i] = b ;
		priority[i] = p ;
		maxpossibletime += (a+b) ;
	}
	
	sort(v.begin(), v.end()) ;
	
	ll task=0, ongoing_process=0 ;
	priority_queue<pair<ll, pair<ll, ll> > >pq ;
	ll start[n+2], finish[n+2] ;
	memset(start, -1, sizeof start) ;
	memset(finish, 0, sizeof finish) ;
	
	ll idx = 0 ;
	cout << "\nGantt Chart: " ;
	for(int t=0; t<=maxpossibletime; t++) {
		while(task<n && v[task].first == t) {
			ll id = v[task].second ;
			pq.push({priority[id], {-burst[id], id}}) ;
			task++ ;
		}
		
		if(!pq.empty()) {
			ll id = pq.top().second.second ;
			if(idx != id) {
				if(start[id]==-1)
					start[id]=t;
				cout << t << " P" << id << " " ;
				idx = id ;
			}
			ll burst_time = -pq.top().second.first ;
			burst_time-- ;
			pq.pop() ;
			if(burst_time) 
				pq.push({priority[id], {-burst_time, idx}}) ;
			else
				finish[idx] = t+1 ;
		} else {
			if(task<n && idx) 
				cout << t << " Idle " ;
			else if(idx) 
				cout << t ;
			idx = 0 ;
		}
	}
	cout << endl ;
	float total_wait = 0, total_tat = 0, total_frpt = 0 ;
	for(int i=1; i<=n; i++) {
		ll wait = finish[i] - arr[i] - burst[i] ;
		ll tat = finish[i] - arr[i] ;
		ll frpt = start[i] - arr[i] ;
		total_wait += wait ;
		total_tat += tat ;
		total_frpt += frpt ;
		cout << "Process: P" << i << " Start time: " << start[i] << " End time: " << finish[i] << " Waiting time: " << wait << " Turnaround time: " << tat << " Response time: " << frpt << endl ;
	}
	
	float avgw = total_wait/n ;
	float avgtat = total_tat/n ;
	float avgfrpt = total_frpt/n ;
	
	cout << "Average Waiting time: " << avgw << endl ;
	cout << "Average Turnaround time: " << avgtat << endl ;
	cout << "Average Response time: " << avgfrpt << endl ;
	
	return 0;
}
