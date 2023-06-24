#include<iostream>
#include "ScamDetector.h"
#include<random>
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
		connections.Add(Pair<Client,Client>(clients[first],clients[second]));
	}
	return connections;
}
auto FindClient(List<Client> clients, string key){
	for(int i = 0 ; i < clients.Size() ; i++) if(clients[i].GetClientInterbankKey() == key) return clients[i];
	return (Client)null;
}
auto GetClientTransactions(List<Transaction> transactions, string key){
	List<Transaction> clientTransactions = List<Transaction>();
	for(int i = 0 ; i < transactions.Size() ; i++) if(transactions[i].GetSourceKey() == key) clientTransactions.Add(transactions[i]);
	return clientTransactions;
}
auto main()->int{
    AdjacentList<Client> clientConnectionList = AdjacentList<Client>();
	List<Client> clients = List<Client>();
	srand(time(NULL));
	int y;
	cout<<"Creating clients..."<<endl;
	for(int i = 0 ; i < 50; i++) clients.Add(AddClient());
	List<Pair<Client,Client>> clientsC = CreateRandConnections(clients);
	for(int i = 0 ; i < clientsC.Size() ; i++){
		clientConnectionList.Add(clientsC[i]);
	}
	cout<<"Clients created..."<<endl;
	cout<<"Creating transactions: "<<endl;
	List<Transaction> allTransactions = List<Transaction>();
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(0, clients.Size() - 1);
	int n = (dist(gen) % clients.Size()) * (dist(gen) % clients.Size());
	for(int i = 0; i < n ; i ++){
		cout<<"Transactions created left "<<n - i<<endl;
		int options = dist(gen) % 6;
		int source = dist(gen);
		int target = dist(gen);
		string sourceKey = clients[source].GetClientInterbankKey(), targetKey = clients[target].GetClientInterbankKey();
		int maxAmount = clients[source].GetMaximumTransactionAmount();
		int randomMultiplier = rand() % 50;
		int randomAmount = rand() % maxAmount;
		long double transactionAmount = static_cast<long double>(randomAmount) * randomMultiplier;
		int z;
		if(options == 5 or options == 4) { transactionAmount += (transactionAmount * (long double)(rand() % maxAmount)) * (long double)(rand() % maxAmount);}
		Transaction transaction = Transaction(sourceKey,targetKey,transactionAmount);
		allTransactions.Add(transaction);
	}
	cout<<"Verifying transactions..."<<endl;
	int scamTransactions = 0, nonScam = 0;
	for(int i = 0 ; i < allTransactions.Size() ; i++){
		cout<<"Left: "<<allTransactions.Size() - i <<endl;
		Transaction transaction = allTransactions[i];
		Client source = FindClient(clients,transaction.GetSourceKey()), target = FindClient(clients,transaction.GetTargetKey());
		List<Transaction> clientTransactions = GetClientTransactions(allTransactions, source.GetClientInterbankKey());
		ScamDetector detector = ScamDetector(transaction, source, target, clientTransactions);
		cout<<"\nScam probability: "<<detector.GetScamProbability()<<endl;
		cout<<"Transaction: \n"<<transaction;
		if(detector.IsScam()){
			cout<<"This is a scam transaction...\n";
			scamTransactions++;
		}else{
			cout<<"Is not an scam...\n";
		}
	}
	cout<<"Transactions evaluated: "<<allTransactions.Size()<<endl;
	cout<<"Scam transactions found: "<<scamTransactions<<endl;
    return 0;
}
