#include <bits/stdc++.h>
using namespace std;
typedef long long int ll ;

int main() {
	ll n, tq ; 
	cout << "Enter the number of task: " ;
	cin >> n ;
	cout << "Enter time quantum: " ;
	cin >> tq ;
	
	vector<pair<ll, ll> > v ;
	int arr[n+2], burst[n+2] ;
	ll maxpossibletime = 0 ;
	for(int i=1; i<=n; i++) {
		ll b, a, p ;
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
	
	ll task=0, ongoing_process=0, c = 0, idx = 0 ;
	deque<pair<ll, ll> >dq ;
	ll start[n+2], finish[n+2] ;
	memset(start, -1, sizeof start) ;
	memset(finish, 0, sizeof finish) ;
	
	cout << "\nGantt Chart: " ;
	for(int t=0; t<=maxpossibletime; t++) {
		while(task<n && v[task].first == t) {
			ll id = v[task].second ;
			dq.push_back({burst[id], id}) ;
			task++ ;
		}
		
		
		if(!dq.empty()) {
			ll id = dq[0].second ;
			if(id==idx) c++ ;
			else {
				idx = id ;
				c++ ;
				if(start[id]==-1)
					start[id] = t ;
				cout << t << " P" << id << " " ;
			}
			dq[0].first-- ;

			if(dq[0].first==0) {
				dq.pop_front() ;
				finish[id] = t ;
				idx = 0 ;
				c = 0 ;
			}
			if(c==tq) {
				ll bt = dq[0].first ;
				dq.pop_front() ;
				dq.push_back({bt, id}) ;
				c = 0 ;
				idx = 0 ;
			}
		} 
		else if(task<n) {
			if(idx==0) {
				cout << t << " Idle " ;
				idx = -1 ;
			}
		}
		else {
			if(idx==0) {
				cout << t ;
				idx = -2 ;
			}
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
