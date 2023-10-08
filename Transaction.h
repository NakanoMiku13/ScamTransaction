#include "DateTime.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>

// Definición de la clase Transaction
class Transaction {
private:
    // Variables miembro privadas
    long double _transactionAmount; // Monto de la transacción
    string _transactionId; // ID de la transacción
    string _sourceInterbankKey; // Clave interbancaria de la fuente
    string _targetInterbankKey; // Clave interbancaria del objetivo
    DateTime _transactionDateTime; // Fecha y hora de la transacción

    // Función privada para generar un carácter aleatorio
    auto _RandChar() -> char {
        int p = rand() % 2;
        return (p == 0) ? (char)((rand() % (90 - 65 + 1)) + 65) : (char)((rand() % (122 - 97 + 1)) + 97);
    }

    // Función privada para generar un entero aleatorio
    auto _RandInt() {
        return rand() % 10;
    }

    // Función privada para generar un ID aleatorio
    auto _IdGenerator() -> string {
        int length = 32;
        string id = "";
        for (int i = 0, n = rand() % 2; i < length; i++, n = rand() % 2) {
            if (n == 0)
                id += to_string(_RandInt());
            else
                id += _RandChar();
        }
        return id;
    }

public:
    // Constructor de la clase Transaction con parámetros
    Transaction(string sourceInterbankKey, string targetInterbankKey, float transactionAmount) :
        _transactionAmount(transactionAmount),
        _sourceInterbankKey(sourceInterbankKey),
        _targetInterbankKey(targetInterbankKey) {
        _transactionDateTime = DateTime();
        _transactionId = _IdGenerator();
    }

    // Constructor de la clase Transaction sin parámetros
    Transaction() {
        srand(time(NULL));
        _transactionId = _IdGenerator();
        _transactionDateTime = DateTime();
    }

    // Sobrecarga del operador de igualdad (==)
    auto operator==(const Transaction& other) {
        return _transactionId == other._transactionId;
    }

    // Función para obtener el ID de la transacción
    auto GetId() const {
        return _transactionId;
    }

    // Función para obtener el monto de la transacción
    auto GetTransactionAmount() const {
        return _transactionAmount;
    }

    // Función para obtener la clave interbancaria de la fuente
    auto GetSourceKey() const {
        return _sourceInterbankKey;
    }

    // Función para obtener la clave interbancaria del objetivo
    auto GetTargetKey() const {
        return _targetInterbankKey;
    }

    // Función para obtener la fecha y hora de la transacción
    auto GetTransactionTime() const {
        return _transactionDateTime;
    }

    // Sobrecarga del operador de inserción (<<) para imprimir la transacción
    friend ostream& operator<<(ostream& os, const Transaction& transaction) {
        os << "Transaction id: " << transaction.GetId() << "\nTransaction time: " << transaction.GetTransactionTime() << endl;
        os << "Source: " << transaction.GetSourceKey() << " -> Target: " << transaction.GetTargetKey() << endl;
        return os;
    }
};
