#include<iostream>
#include "ScamDetector.h"
using namespace std;
List<string> names = List<string>({"Acme", "Alpha", "Apex", "Aurora", "BlueSky", "Catalyst", "Citadel", "DigiCom", "Dynamic", "Elektra",
            "Excel", "Falcon", "Gemini", "Global", "Horizon", "Infinity", "Interstellar", "Javelin", "Kinetic",
            "Luna", "Magnum", "Neptune", "Nexus", "Omega", "Orion", "Pinnacle", "Quantum", "Redwood", "Sapphire",
            "Solaris", "Stellar", "Sunflower", "Techtronix", "Transatlantic", "TriStar", "Universal", "Vanguard",
            "Vertex", "Vortex", "Wavecrest", "Xenon", "Yotta", "Zenith", "Zenithro", "Zephyr", "Zeta", "Zulu", "Zypher"});

auto CreateName(){
	return (names[rand() % names.Size() + 1] + " " + names[rand() % names.Size() + 1]);
}
auto CreateId(){
	int n = 16;
	string ret = "";
	for(int i = 0, j = rand() % 10; i < n ; i++, ret += (char)(j + 48), j = rand() % 10);
	return ret;
}
auto AddClient() {
    return Client(CreateName(), CreateId(), 50, 50, 50);
}
auto CreateRandConnection()
auto main()->int{
    AdjacentList<Client> clientConnectionList = AdjacentList<Client>();
	List<Client> clients = List<Client>();
//	cout<<"hi";
//	for(int i = 0, j = rand() % names.Size() + 1; i<6; i++, j = rand() % names.Size() + 1) cout<<names[j]<<endl;
	for(int i = 0; i<5;i++){
		Client nC = AddClient();
		cout<<nC.GetClientName()<<endl;
		clients.Add(nC);
	}
	cout<<clientList.Size();
    return 0;
}
