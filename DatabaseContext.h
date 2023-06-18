#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
using namespace std;
using namespace sql;
using namespace sql::mysql;
class Database{
    private:
        MySQL_Driver *_driver;
        Connection *_connection;
        string _username, _password, _host, _database, _lastError;
        bool _connected;
    public:
        Database(string database, string host = "tcp://127.0.0.1:3306", string username = "root", string password = "root") : _database(database), _host(host), _username(username), _password(password){
            _lastError = "";
            try{
                _driver = get_mysql_driver_instance();
                _connection = _diver->connect(host,username,password);
                _connected = true;
            }catch(SQLException &exception){
                _lastError = exception.what();
                _connected = false;
            }
        }
        auto GetLastError() const {
            return _lastError;
        }
        auto IsConnected() const {
            return _connected;
        }
        auto CloseConnection() const{
            delete con;
        }
};
sql::mysql::MySQL_Driver *driver;
sql::Connection *con;

// Crea una instancia del driver MySQL
driver = sql::mysql::get_mysql_driver_instance();

// Establece la conexión
con = driver->connect("tcp://127.0.0.1:3306", "usuario", "contraseña");
