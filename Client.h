#include<iostream>
#include "List.h"
#include "Transaction.h"
class Client{
    private:
        string _clientName, _clientInterbankKey;
        float _maximumTransactionAmount, _averageTransactionAmount;
        int _transactionsPerMonth, _transactionsPerDay, _maximumTransactionsPerMonth, _maximumTransactionsPerDay;
        bool _reported;
    public:
        Client(string clientName = "Unknown", string clientInterbankKey = "0000000000000000", float maximumTransactionAmount = 0.0, int maximumTransactionsPerMonth = 0, int maximumTransactionsPerDay = 0, List<Client> closeTransactions = List<Client>()):
        _clientName(clientName), _clientInterbankKey(clientInterbankKey), _maximumTransactionAmount(maximumTransactionAmount), _maximumTransactionsPerMonth(maximumTransactionsPerMonth), _reported(false)
        {
            _transactionsPerDay = _transactionsPerMonth = 0;
        }
        //Operator overloads
        auto operator==(const Client& comparison){
            return _clientInterbankKey == comparison._clientInterbankKey && _clientName == comparison._clientName;
        }
        //Get functions
        auto GetClientName() const {
            return _clientName;
        }
        auto GetClientInterbankKey() const {
            return _clientInterbankKey;
        }
        auto GetTransactionsPerDay() const {
            return _transactionsPerDay;
        }
        auto GetTransactionsPerMonth() const {
            return _transactionsPerMonth;
        }
        auto GetMaximumTransactionsPerDay() const {
            return _maximumTransactionsPerDay;
        }
        auto GetMaximumTransactionsPerMonth() const {
            return _maximumTransactionsPerMonth;
        }
        auto GetMaximumTransactionAmount() const {
            return _maximumTransactionAmount;
        }
        auto GetAverageTransactionsAmount() const {
            return _averageTransactionAmount;
        }
        auto IsReported() const {
            return _reported;
        }
        //Set functions
        auto SetClientName(string clientName) {
            _clientName = clientName;
        }
        auto SetClientInterbankKey(string clientInterbankKey) {
            _clientInterbankKey = clientInterbankKey;
        }
        auto SetTransactionsPerDay(int transactionsPerDay) {
            _transactionsPerDay = transactionsPerDay;
        }
        auto SetTransactionsPerMonth(int transactionsPerMonth) {
            _transactionsPerMonth = transactionsPerMonth;
        }
        auto SetMaximumTransactionsPerDay(int maximumTransactionsPerDay) {
            _maximumTransactionsPerDay = maximumTransactionsPerDay;
        }
        auto SetMaximumTransactionsPerMonth(int maximumTransactionsPerMonth) {
            _maximumTransactionsPerMonth = maximumTransactionsPerMonth;
        }
        auto SetMaximumTransactionAmount(float maximumTransactionAmount) {
            _maximumTransactionAmount = maximumTransactionAmount;
        }
        auto SetAverageTransactionsAmount(float averageTransactionsAmount) {
            _averageTransactionAmount = averageTransactionsAmount;
        }
        auto SetReport(){
            _reported = true;
        }
        auto RemoveReport(){
            _reported = false;
        }
};