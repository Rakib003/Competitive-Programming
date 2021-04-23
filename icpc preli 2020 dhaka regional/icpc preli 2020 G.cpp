//#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PLL;

// #define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
// template <typename Arg1>
// void __f(const char* name, Arg1&& arg1) {
// 	cerr << name << " : " << arg1 << endl;
// }
// template <typename Arg1, typename... Args>
// void __f(const char* names, Arg1&& arg1, Args&&... args) {
// 	const char* comma = strchr(names + 1, ',');
// 	cerr.write(names, comma - names) << " : " << arg1 << "  ";
// 	__f(comma + 1, args...);
// }

const PLL M = mp(1e9 + 7, 1e9 + 9); ///Should be large primes
const LL base = 347;            ///Should be a prime larger than highest value
const int N = 2e6 + 10;        ///Highest length of string

ostream& operator<<(ostream& os, PLL hash) {
	return os << "(" << hash.ff << ", " << hash.ss << ")";
}

PLL operator+ (PLL a, LL x)     {return mp(a.ff + x, a.ss + x);}
PLL operator- (PLL a, LL x)     {return mp(a.ff - x, a.ss - x);}
PLL operator* (PLL a, LL x)     {return mp(a.ff * x, a.ss * x);}
PLL operator+ (PLL a, PLL x)    {return mp(a.ff + x.ff, a.ss + x.ss);}
PLL operator- (PLL a, PLL x)    {return mp(a.ff - x.ff, a.ss - x.ss);}
PLL operator* (PLL a, PLL x)    {return mp(a.ff * x.ff, a.ss * x.ss);}
PLL operator% (PLL a, PLL m)    {return mp(a.ff % m.ff, a.ss % m.ss);}


PLL pb[N];      ///powers of base mod M
//PLL invb;

///Call pre before everything
void hashPre() {
	pb[0] = mp(1, 1);
	for (int i = 1; i < N; i++)
		pb[i] = (pb[i - 1] * base) % M;
	//invb = inverse(pb[1]);
}

///Calculates Hash of a string
PLL Hash (string s) {
	PLL ans = mp(0, 0);
	for (int i = 0; i < s.size(); i++)
		ans = (ans * base + s[i]) % M;
	return ans;
}

///Calculates hashes of all prefixes of s including empty prefix
vector<PLL> hashList(string s) {
	int n = s.size();
	vector<PLL> ans(n + 1);
	ans[0] = mp(0, 0);

	for (int i = 1; i <= n; i++)
		ans[i] = (ans[i - 1] * base + s[i - 1]) % M;
	return ans;
}

///Calculates hash of substring s[l..r] (1 indexed)
PLL substringHash(const vector<PLL> &hashlist, int l, int r) {
	int len = (r - l + 1);
	return ((hashlist[r] - hashlist[l - 1] * pb[len]) % M + M) % M;
}

//#define int long long int
#define     uniq(x)         sort(x.begin(),x.end());x.erase(unique(x.begin(),x.end()),x.end())

vector<PLL>ha;
string s;
vector<int>siz;
int dp[N];
char buffer[N];
int n;
vector<PLL> vv[N];
int call(int idx = 1)
{
	//trace(idx, n);
	if (idx > n) return 0;
	if (dp[idx] != -1) return dp[idx];

	int x = 1e6 + 10;

	for (auto it : siz)
	{
		if (it + idx - 1 <= n)
		{
			PLL dd = substringHash(ha, idx, idx + it - 1);
			if (binary_search(vv[it].begin(), vv[it].end(), dd))
			{
				//trace(idx + it);
				x = min(x, 1 + call(idx + it));
			}
		}
		else break;
	}

	return dp[idx] = x;
}


signed main()
{
// #ifndef ONLINE_JUDGE
// 	freopen("input.txt", "r", stdin);
// 	freopen("output.txt", "w", stdout);
// #endif
	hashPre();
	int t;
	scanf("%d", &t);

	for (int cs = 1; cs <= t; ++cs)
	{
		int x; scanf("%d", &x);
		for (int i = 0; i < x; i++)
		{
			string a;
			scanf("%s", buffer); a = buffer;
			vv[a.size()].push_back(Hash(a));
			siz.emplace_back(a.size());
		}
		uniq(siz);
		for (auto it : siz)
		{
			uniq(vv[it]);
		}
		scanf("%s", buffer); s = buffer;
		ha = hashList(s);
		n = s.size();

		for (int i = 0; i <= n + 10; i++) dp[i] = -1;

		printf("Case %d: ", cs);
		int ans = call();
		if (ans <= 1e6) printf("%d\n", ans);
		else printf("impossible\n");

		for (auto it : siz) vv[it].clear();
		siz.clear();
	}
}
