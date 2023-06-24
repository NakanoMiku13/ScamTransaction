#include "DateTime.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string>
class Transaction{
    private:
        long double _transactionAmount;
        string _transactionId, _sourceInterbankKey, _targetInterbankKey;
        DateTime _transactionDateTime;
        auto _RandChar()->char{
            int p = rand() % (2);
            return (p == 0) ? (char)((rand() % (90 - 65 + 1)) + 65) : (char)((rand() % (122 - 97 + 1)) + 97);
        }
        auto _RandInt(){
            return rand() % 10;
        }
        auto _IdGenerator()->string{
            int length = 32;
            string id = "";
            for(int i=0, n = rand() % 2; i < length; i++, n = rand() % 2) if(n == 0) id += to_string(_RandInt()); else id += _RandChar();
            return id;
        }
    public:
        Transaction(string sourceInterbankKey, string targetInterbankKey, float transactionAmount): _transactionAmount(transactionAmount), _sourceInterbankKey(sourceInterbankKey), _targetInterbankKey(targetInterbankKey){
            _transactionDateTime = DateTime();
            _transactionId = _IdGenerator();
        }
        Transaction(){
            srand(time(NULL));
            _transactionId = _IdGenerator();
            _transactionDateTime = DateTime();
        }
        auto operator==(const Transaction& other){
            return _transactionId == other._transactionId;
        }
        auto GetId() const {
            return _transactionId;
        }
        auto GetTransactionAmount() const{
            return _transactionAmount;
        }
        auto GetSourceKey() const {
            return _sourceInterbankKey;
        }
        auto GetTargetKey() const {
            return _targetInterbankKey;
        }
        auto GetTransactionTime() const {
            return _transactionDateTime;
        }
        friend ostream& operator<<(ostream& os, const Transaction& transaction){
            os<<"Transaction id: "<<transaction.GetId()<<"\nTransaction time: "<<transaction.GetTransactionTime()<<endl<<"Source: "<<transaction.GetSourceKey()<<" -> Target: "<<transaction.GetTargetKey()<<endl;
            return os;
        }
};