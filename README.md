# Implementacija stohastičkih SAT rešavača
Seminarski rad u okviru kursa *Automatsko rezonovanje* na master studijama na Matematičkom fakultetu u Beogradu. 

U radu su predstavljene osnove iskazne logike, SAT problema i SAT rešavača, a poseban akcenat stavljen je na stohastičke SAT rešavače. Takodje je data jedna od mogućih implementacija stohastičkog rešavača WalkSAT, u programskom jeziku C++ i instanca problema na kojoj je demonstriran sam algoritam, kao i priroda rada rešavača koji koriste metode slučajnog izbora.

# Pokretanje rešavača
Kako bi se program pokrenuo, potrebno je na sistemu imati instaliran prevodilac za jezik C++.  Za sisteme zasnovane na Ubuntu distribuciji Linux sistema, u direktorijumu projekta pokrenuti sledeće komande u terminalu:

`sudo apt install build-essential`

`g++ -std=c++20 WalkSAT.cpp`

`./a.out`
