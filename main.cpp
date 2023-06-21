#include<iostream>
#include "ScamDetector.h"
using namespace std;
List<string> names = List<string>({"Acme", "Alpha", "Apex", "Aurora", "BlueSky", "Catalyst", "Citadel", "DigiCom", "Dynamic", "Elektra",
            "Excel", "Falcon", "Gemini", "Global", "Horizon", "Infinity", "Interstellar", "Javelin", "Kinetic",
            "Luna", "Magnum", "Neptune", "Nexus", "Omega", "Orion", "Pinnacle", "Quantum", "Redwood", "Sapphire",
            "Solaris", "Stellar", "Sunflower", "Techtronix", "Transatlantic", "TriStar", "Universal", "Vanguard",
            "Vertex", "Vortex", "Wavecrest", "Xenon", "Yotta", "Zenith", "Zenithro", "Zephyr", "Zeta", "Zulu", "Zypher"});

auto CreateName(){
	int first = rand() % names.Size(), second = rand() % names.Size();
	string s = (names[first] + " " + names[second]);
	return s;
}
auto CreateId(){
	int n = 16;
	string ret = "";
	for(int i = 0, j = rand() % 10; i < n ; i++, ret += (char)(j + 48), j = rand() % 10);
	return ret;
}
auto AddClient() {
	int b = rand() % 5000000;
    return Client(CreateName(), CreateId(), b, (rand() % 50) * b, (rand() % 50 + b) * b);
}
auto CreateRandConnections(List<Client> clients){
	List<Pair<Client,Client>> connections = List<Pair<Client,Client>>();
	int connectionsN = rand() % 100 + 1;
	for(int i = 0, first = rand() % clients.Size(), second = rand() % clients.Size() ; i < connectionsN ; i++, first = rand() % clients.Size(), second = rand() % clients.Size()){
		if(first == second) second = rand() % clients.Size();
		cout<<"First: "<<clients[first]<<"\nSecond: "<<clients[second]<<endl<<"Val: "<<i<<endl;
		connections.Add(Pair<Client,Client>(clients[first],clients[second]));
	}
	cout<<"Complete\n";
	return connections;
}
auto CreateTransaction(List<Client> clients)->Transaction{
	int source = rand() % clients.Size(), target = rand() % clients.Size();
	int options = rand() %11;
	return (options == 5) ? Transaction(clients[source].GetClientInterbankKey(), clients[target].GetClientInterbankKey(), (float)(rand() % (int)(clients[source].GetMaximumTransactionAmount() * rand() % 50))) : Transaction(clients[source].GetClientInterbankKey(), clients[target].GetClientInterbankKey(), (float)(rand() % (int)clients[source].GetMaximumTransactionAmount()));
}
auto main()->int{
    AdjacentList<Client> clientConnectionList = AdjacentList<Client>();
	List<Client> clients = List<Client>();
	srand(time(NULL));
//	cout<<"hi";
//	for(int i = 0, j = rand() % names.Size() + 1; i<6; i++, j = rand() % names.Size() + 1) cout<<names[j]<<endl;
	for(int i = 0 ; i < 50 ; i++) clients.Add(AddClient());
	List<Pair<Client,Client>> clientsC = CreateRandConnections(clients);
	cout<<clientsC.Size()<<endl;
	for(int i = 0 ; i < clientsC.Size() ; i++){
		cout<<clientsC[i]<<endl;
	}
	for(int i = 0 ; i < clientsC.Size() ; i++) clientConnectionList.Add(clientsC[i]);
	List<Transaction> allTransactions = List<Transaction>();
	long n = (rand() % clients.Size()) * (rand() % clientConnectionList.Size() + rand() % clients.Size());
	for(long i = 0 ; i < n ; i++) allTransactions.Add(CreateTransaction(clients));
	cout<<allTransactions.Size();
    return 0;
}
