#include "Client.h"
class ScamDetector{
    private:
        Client _source, _target;
        double _scamProbability;
        Transaction _suspectTransaction;
        List<Transaction> _transactions;
        auto _IsFriend()->bool{
		int counter = 0;
		for(int i = 0; i < _transactions.Size(); i++){
			string targetKey = _transactions[i].GetTargetKey();
			if(targetKey == _target.GetClientInterbankKey()) counter++;
		}
		return counter >= 4;
        }
    public:
        /*
            Evaluate probability with Transactions
            Scam >= 150 pts
            * Transaction amount higher than maximum allowed by source = 50 pts
            * Target is not Friend = 50 pts
            * Target is from physical money = 20 pts
            * Hour of transaction (late) = 20 pts
            * Target is reported = 100 pts
        */
        ScamDetector(Transaction suspectTransaction, Client source = Client(), Client target = Client(), List<Transaction> transactions = List<Transaction>()):
        _source(source), _target(target), _scamProbability(0), _transactions(transactions), _suspectTransaction(suspectTransaction){}
        auto GetScamProbability() const { return _scamProbability; }
        auto CalculateScamProbability() {
            if(_source.GetMaximumTransactionAmount() > _suspectTransaction.GetTransactionAmount()) _scamProbability += 50;
            if(!_IsFriend()) _scamProbability += 50;
		if(_suspectTransaction.GetTransactionTime().hour > 23) _scamProbability += 20;
		if(_target.IsReported()) _scamProbability += 100;
        }
	auto IsScam() const {
		return (_scamProbability >= 150.0);
	}
};
