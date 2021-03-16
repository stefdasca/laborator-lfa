// Stefan Dascalescu, grupa 151

#include<bits/stdc++.h>
using namespace std;

int nrstates; // numarul de stari
int nrletters; // numarul de litere

int nrtransitions; // numarul de tranzitii

map<pair<string, int>, int> states;
map<string, int> words;
set<string> sigma;

int cntstart, cntend;
int errortype;

bool eroare[5], rau;
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
			msk++, ++poz, ++cntstart;
		if(s[poz] == 'F')
			msk += 2, ++poz, ++cntend;
		while(s[poz] == ' ' || s[poz] == ',')
			++poz;
		if(s[poz] == 'S')
			msk++, ++poz, ++cntstart;
		if(s[poz] == 'F')
			msk += 2, ++poz, ++cntend;
		states[{x, msk}] = i; 
		words[x] = i;
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
	}
	if(rau == 0)
		cout << "Input valid" << '\n';
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
