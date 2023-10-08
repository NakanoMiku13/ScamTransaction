#include "Client.h"

// Definición de la clase ScamDetector
class ScamDetector {
private:
    // Variables miembro privadas
    Client _source, _target; // Cliente fuente y cliente objetivo
    double _scamProbability; // Probabilidad de estafa
    Transaction _suspectTransaction; // Transacción sospechosa
    List<Transaction> _transactions; // Lista de transacciones

    // Función privada para verificar si el cliente objetivo es amigo
    auto _IsFriend() -> bool {
        int counter = 0;
        for (int i = 0; i < _transactions.Size(); i++) {
            string targetKey = _transactions[i].GetTargetKey();
            if (targetKey == _target.GetClientInterbankKey()) {
                counter++;
            }
        }
        return counter >= 3;
    }

public:
    // Constructor de la clase ScamDetector
    ScamDetector(Transaction suspectTransaction, Client source = Client(), Client target = Client(), List<Transaction> transactions = List<Transaction>()) :
        _source(source), _target(target), _scamProbability(0), _transactions(transactions), _suspectTransaction(suspectTransaction) {
        CalculateScamProbability(); // Calcular la probabilidad de estafa al crear el objeto
    }

    // Función para obtener la probabilidad de estafa
    auto GetScamProbability() const {
        return _scamProbability;
    }

    // Función para calcular la probabilidad de estafa
    auto CalculateScamProbability() -> void {
        if (_source.GetMaximumTransactionAmount() > _suspectTransaction.GetTransactionAmount()) {
            _scamProbability += 50; // Sumar 50 puntos si el monto de la transacción es mayor al máximo permitido por el cliente fuente
        }
        if (!_IsFriend()) {
            _scamProbability += 50; // Sumar 50 puntos si el cliente objetivo no es amigo
        }
        if (_suspectTransaction.GetTransactionTime().hour > 23) {
            _scamProbability += 20; // Sumar 20 puntos si la transacción se realiza en una hora tardía (mayor a las 23:00)
        }
        if (_target.IsReported()) {
            _scamProbability += 100; // Sumar 100 puntos si el cliente objetivo ha sido reportado
        }
    }

    // Función para verificar si es una estafa
    auto IsScam() const {
        return (_scamProbability >= 150.0); // Devolver true si la probabilidad de estafa es mayor o igual a 150.0
    }
};
