class Client {
private:
    string _clientName, _clientInterbankKey;
    long double _maximumTransactionAmount, _averageTransactionAmount;
    int _transactionsPerMonth, _transactionsPerDay, _maximumTransactionsPerMonth, _maximumTransactionsPerDay;
    bool _reported;
public:
    // Constructor de la clase
    Client(string clientName = "Unknown", string clientInterbankKey = "0000000000000000", long double maximumTransactionAmount = 0.0, int maximumTransactionsPerMonth = 0, int maximumTransactionsPerDay = 0, List<Client> closeTransactions = List<Client>()) :
        _clientName(clientName), _clientInterbankKey(clientInterbankKey), _maximumTransactionAmount(maximumTransactionAmount), _maximumTransactionsPerMonth(maximumTransactionsPerMonth), _reported(false) {
        // Generar un informe aleatorio para el cliente
        int report = rand() % 6;
        if (report == 4 || report == 5)
            _reported = true;
        else
            _reported = false;
        
        // Inicializar el contador de transacciones diarias y mensuales
        _transactionsPerDay = _transactionsPerMonth = 0;
    }

    // Sobrecarga de operadores
    auto operator==(const Client& comparison) {
        return _clientInterbankKey == comparison._clientInterbankKey && _clientName == comparison._clientName;
    }

    auto operator==(const Transaction& comp) {
        return _clientInterbankKey == comp.GetSourceKey();
    }

    // Funciones de obtención (get)
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

    // Funciones de asignación (set)
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

    auto SetReport() {
        _reported = true;
    }

    auto RemoveReport() {
        _reported = false;
    }

    // Función amiga para la sobrecarga del operador de inserción (<<)
    friend ostream& operator<<(ostream& os, const Client& client) {
        os << client.GetClientName() << " " << client.GetClientInterbankKey();
        return os;
    }
};
