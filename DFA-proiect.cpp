#include<bits/stdc++.h>
using namespace std;

ifstream f("input.in");

int n, m, q;
vector<pair<int, char> > v[100002];
int initial_state, cnt_finals;

bool final_state[100002];

string s;
int poz;

vector<int> path;

void dfs(int node)
{
	path.push_back(node);
	if(poz == (int) s.size())
		return;
	for(int i = 0; i < (int) v[node].size(); ++i)
	{
		int nxt = v[node][i].first;
		char letter = v[node][i].second;
		if(letter == s[poz])
		{
			++poz;
			dfs(nxt);
			break;
		}
	}
}
int main()
{
	f >> n >> m;
	for(int i = 0; i < m; ++i)
	{
		int a, b;
		char c;
		f >> a >> b >> c;
		v[a].push_back({b, c});
	}
	f >> initial_state;
	f >> cnt_finals;
	for(int i = 0; i < cnt_finals; ++i)
	{
		int node;
		f >> node;
		final_state[node] = 1;
	}
	
	f >> q;
	for(int i = 0; i < q; ++i)
	{
		f >> s;
		poz = 0;
		path.clear();
		dfs(initial_state);
		if(poz != (int) s.size())
			cout << "NU\n";
		else
		{
			cout << "DA\n";
			cout << "Traseu: ";
			for(int j = 0; j < (int) path.size(); ++j)
				cout << path[j] << " ";
			cout << '\n';
		}
	}
	return 0;
}
