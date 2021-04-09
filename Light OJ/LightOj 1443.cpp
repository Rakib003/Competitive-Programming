//Printing Divisors
#pragma GCC optimize ("Ofast")
#include"bits/stdc++.h"
using namespace std;

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;

struct _ { ios_base::Init i; _() { cin.sync_with_stdio(0); cin.tie(0); cout << fixed << setprecision(10); } } ___;
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
	cerr << name << " : " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
	const char* comma = strchr(names + 1, ',');
	cerr.write(names, comma - names) << " : " << arg1 << "  ";
	__f(comma + 1, args...);
}

#define ll long long
#define pii pair<int,int>
#define oset tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ff first
#define ss second
#define endll '\n'
#define rep(i,n) for(int i=0;i++<n;)
#define scl(i) scanf("%lld",&i)
#define int long long int
#define all(n) n.begin(),n.end()
#define mem(n,i) memset(n,i,sizeof n)
#define em(a) emplace_back(a)
#define pb(a) push_back(a)
#define srep(it,vv) for(auto &it : vv)
#define prep(it,vv) for(auto it : vv)
#define b_s(a,b) binary_search(a.begin(),a.end(),b)
#define l_b(a,b) lower_bound(a.begin(),a.end(),b)
#define u_b(a,b) upper_bound(a.begin(),a.end(),b)
//vector<vector<int>>arr(n + 5, vector<int>(m + 5,0));

typedef vector<int> vii;
typedef vector<string> vss;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int my_rand(int l, int r) {
	return uniform_int_distribution<int>(l, r) (rng);
}

const int SIZE = 70005;

vector <int> prime; // Stores generated primes
char sieve[SIZE]; // 0 means prime
void primeSieve ( int n ) {
	sieve[0] = sieve[1] = 1; // 0 and 1 are not prime

	prime.push_back(2); // Only Even Prime
	for ( int i = 4; i <= n; i += 2 ) sieve[i] = 1; // Remove multiples of 2

	int sqrtn = sqrt ( n );
	for ( int i = 3; i <= sqrtn; i += 2 ) {
		if ( sieve[i] == 0 ) {
			for ( int j = i * i; j <= n; j += 2 * i ) sieve[j] = 1;
		}
	}

	for ( int i = 3; i <= n; i += 2 ) if ( sieve[i] == 0 ) prime.push_back(i);
}

signed main()
{

	primeSieve(70000);

	int __, _ = 0;
	cin >> __;
	for (; _++ < __;)
	{
		vector<int>vv;
		vv.em(1);
		int n; cin >> n;

		prep(it, prime)
		{
			if (n == 1) break;
			while (n % it == 0)
			{
				vv.em(it);
				n /= it;
			}
		}
		if (n != 1) vv.em(n);

		// prep(it, vv) cout << it << ' ';
		// cout << endll;

		set<int>ss;
		vii ans;
		ans.em(1);
		ss.insert(1);

		for (int i = 1; i < vv.size(); i++)
		{
			int d = vv[i];
			for (int j = ans.size() - 1; j >= 0; j--)
			{
				int xx = ans[j] * d;
				if (ss.find(xx) == ss.end())
				{
					ss.insert(xx);
					ans.em(xx);
				}
				else
					break;
			}
		}
		cout << "Case " << _ << ":\n";
		prep(it, ans) cout << it << ' ';
		cout << endll;
	}
}