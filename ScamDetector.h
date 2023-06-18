#include "Client.h"
class ScamDetector{
    private:
        Client _source, _target;
        double _scamProbability;
        Transaction _suspectTransaction;
        List<Transaction> _transactions;
        auto _IsFriend()->bool{
            return _transactions.Exist(_target);
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
        ScamDetector(Client source = Client(), Client target = Client(), List<Transaction> transactions = List<Transaction>(), Transaction suspectTransaction):
        _source(source), _target(target), _scamProbability(0), _transactions(transactions), _suspectTransaction(suspectTransaction){}
        auto GetScamProbability() const { return _scamProbability; }
        auto CalculateScamProbability() {
            if(_source.GetMaximumTransactionAmount() > _suspectTransaction.GetTransactionAmount()) _scamProbability += 50;
            if(!_IsFriend()) _scamProbability += 50;
        }
};