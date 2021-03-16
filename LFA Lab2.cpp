// Stefan Dascalescu, grupa 151

#include<bits/stdc++.h>
using namespace std;

int nrstates; // numarul de stari
int nrletters; // numarul de litere

int nrtransitions; // numarul de tranzitii

map<pair<string, int>, int> states;
map<string, int> words;

set<string> sigma;

int type[100002];
string cuv[100002];

int cntstart, cntend;
int errortype;

bool eroare[5], rau;

vector<pair<int, string> > graph[100002];

bool ok = 0;

string word;
int startnode;

void check(int nod, int poz)
{
	if(poz == word.size() || ok == 1)
	{
		ok = 1;
		return;
	}
	for(int i = 0; i < graph[nod].size(); ++i)
	{
		int vecin = graph[nod][i].first;
		string lit = graph[nod][i].second;
		if(word[poz] == lit[0]) 
			check(vecin, poz+1), gg = 1;
	}
}
int main()
{
	// modific input ca in model
	
	cin >> nrletters;
	for(int i = 1; i <= nrletters; ++i)
	{
		string x;
		cin >> x;
		sigma.insert(x);
	}
	
	
	cin >> nrstates;
	cin.get();
	
	for(int i = 1; i <= nrstates; ++i)
	{
		char s[10002];
		cin.getline(s, 10000);
		string x;
		int poz = 0;
		while(s[poz] != ' ' && s[poz] != NULL && s[poz] != ',')
			x += s[poz], ++poz;
		while(s[poz] == ' ' || s[poz] == ',')
			++poz;
		int msk = 0; // masca pe biti, 0 = nici S, nici F, 1 = doar S, 2 = doar F, 3 = si S si F
		if(s[poz] == 'S')
			msk++, ++poz, ++cntstart, startnode = i;
		if(s[poz] == 'F')
			msk += 2, ++poz, ++cntend;
		while(s[poz] == ' ' || s[poz] == ',')
			++poz;
		if(s[poz] == 'S')
			msk++, ++poz, ++cntstart, startnode = i;
		if(s[poz] == 'F')
			msk += 2, ++poz, ++cntend;
			
		states[{x, msk}] = i; 
		words[x] = i;
		
		type[i] = msk;
		cuv[i] = x;
	}
	if(cntstart != 1)
		eroare[1] = 1, rau = 1;
	if(cntend == 0)
		eroare[2] = 1, rau = 1;
		
	cin >> nrtransitions;
	
	for(int i = 1; i <= nrtransitions; ++i)
	{
		string a, b, c;
		cin >> a >> b >> c;
		if(a.back() == ',')
			a.pop_back();
		if(b.back() == ',')
			b.pop_back();
		
		if(words.find(a) == words.end())
			eroare[3] = 1, rau = 1;
		if(words.find(c) == words.end())
			eroare[3] = 1, rau = 1;
		if(sigma.find(b) == sigma.end())
			eroare[4] = 1, rau = 1;
		
		int nra = words[a];
		int nrb = words[c];
		graph[nra].push_back({nrb, b});
	}
	if(rau != 0)
	{
		if(eroare[1] == 1)
			cout << "Numarul de stari initiale diferite de 1" << '\n';
		if(eroare[2] == 1)
			cout << "Fara stari finale" << '\n';
		if(eroare[3] == 1)
			cout << "Cuvant inexistent" << '\n';
		if(eroare[4] == 1)
			cout << "Litera inexistenta" << '\n';
		return 0;
	}
	
	cout << "Input valid" << '\n';
	
	cin >> word;
	
	check(startnode, 0);
	
	if(ok == 1)
		cout << "Cuvant acceptat " << '\n';
	else
		cout << "Cuvant neacceptat " << '\n';
	return 0;
}
