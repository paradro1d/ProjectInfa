#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <utility>
#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>


#define EXCEPTION_CONN network_exception()
#define EXCEPTION_DATA database_exception()
#define EXCEPTION_LOGI user_password_exception()


//static PGconn* conn = NULL;
//static PGresult* res = NULL;

static const char host[] = "rc1c-tu9ikdrrlhkp9lu5.mdb.yandexcloud.net";
static const char port[] = "6432";
static const char user[] = "dev";
static const char password[] = "tpips000";
static const char dbname[] = "db1";
static const char input[] = "host=rc1c-tu9ikdrrlhkp9lu5.mdb.yandexcloud.net port=6432 user=dev password=tpips000 dbname=db1";
/*
class conn_y : protected PGconn {

}

PGconn::PGconn() {

}
*/
class res_class {
public:
    PGconn** conn;
    PGresult** res;
    res_class() {
        conn = nullptr;
        res = nullptr;
    }
    res_class(const char* input_data) {
        conn = new PGconn*;
        *conn = PQconnectdb((input_data));
        res = nullptr;
    }
    res_class(res_class const& conn_source) {
        if (conn_source.conn != nullptr) {
            conn = new PGconn*;
            *conn = *(conn_source.conn);
        }
        else {
            conn = nullptr;
        }
        if (conn_source.res != nullptr) {
            res = new PGresult*;
            *res = *(conn_source.res);
        }else {
            res = nullptr;
        }
    }
 
    res_class& operator=(res_class const& conn_source) {
        res_class temp = res_class(conn_source);
        if (temp.conn != nullptr) {
            conn = new PGconn*;
            *conn = *(temp.conn);
        }
        else {
            if (conn != nullptr) {
                delete conn;
            }
        }
        if (temp.res != nullptr) {
            res = new PGresult*;
            *res = *(temp.res);
        }
        else {
            if (res != nullptr) {
                delete res;
            }
        }
        return *this;
    }
    res_class& operator=(static PGresult* source) {
        if (source != nullptr) {
            if (res != nullptr) {
                delete res;
            }
            res = new PGresult*;
            *res = source;
        }
        return *this;
    }

    ~res_class() {
        if (conn != nullptr) {
            delete conn;
        }
        if (res != nullptr) {
            delete res;
        }
    }
};

static PGconn* get_static(res_class const& input) {
    return *(res_class(input).conn);
}

static PGresult* get_static_result(res_class const& input) {
    return *(res_class(input).res);
}

class Connection {
private:
    res_class conn;
public:
    Connection() {
        // забовая интедефикация 
        int libpq_ver = PQlibVersion();
        std::cout << libpq_ver << std::endl; // просто проверка версии

        conn = res_class(input);
        
        if (PQstatus(get_static(conn)) != CONNECTION_OK) { // проверяем успешность соединения
            std::cerr << PQerrorMessage(get_static(conn)) << std::endl;
        }
    }

    void PQ_exec(std::string create_query) {
        conn = PQexec(get_static(conn), create_query.c_str()); // при исполении CREATE, INSERT, DELETE, UPDATE только проверка статуса
        
        if (PQresultStatus(get_static_result(conn)) != PGRES_COMMAND_OK) {
            std::cerr << PQerrorMessage(get_static(conn)) << std::endl;
        }
        else {
            //throw EXCEPTION_CONN;
        }
    }

    int PQ_nfields() {
        return PQnfields(get_static_result(conn));
    }
    
    char* PQ_fname(int i) {
        return PQfname(get_static_result(conn), i);
    }

    char* PQ_getvalue(int i, int j) {
        return PQgetvalue(get_static_result(conn), i, j);
        
    }

    ExecStatusType PQ_resultStatus() {
        return PQresultStatus(get_static_result(conn));
    }

    int PQ_ntuples() {
        return PQntuples(get_static_result(conn));
    }

    ~Connection() {
    CLEAR:
        if (NULL != get_static_result(conn)) PQclear(get_static_result(conn));
        if (NULL != get_static(conn)) PQfinish(get_static(conn));
    }
};


void create_table_users() {
    // создаём один нужную нам бызу данных
    // забовая интедефикация 
    Connection Conn;

    std::cout << std::endl << "Start creating" << std::endl;
    if (true) { // создаём таблицу
        std::string create_query = "CREATE TABLE IF NOT EXISTS users \
    (id SERIAL PRIMARY KEY, name VARCHAR(64),password VARCHAR(64), position VARCHAR(64))";

        Conn.PQ_exec(create_query.c_str()); // при исполении CREATE, INSERT, DELETE, UPDATE только проверка статуса
    }
    std::cout << std::endl << "End creating" << std::endl;

    std::cout << std::endl << "Start testing" << std::endl;

    if (false) { // добавляем данные для тестирования
        char const* insert_query =
            "INSERT INTO users (name, password, position)"
            "VALUES ('editor', 'dev', '2');"; 
        Conn.PQ_exec(insert_query);
    }
    std::cout << std::endl << "End testing" << std::endl;

    std::cout << std::endl << "Start reading" << std::endl;
    if (true) { // читаем данные
        Conn.PQ_exec("SELECT id, name, password, position FROM users");

        int ncols = Conn.PQ_nfields(); // сколько колонок в одной записи
        std::cout << "One row contains " << ncols << " fields" << std::endl;
        for (int i = 0; i < ncols; i++)
        {
            char* name = Conn.PQ_fname(i);
            std::cout << name << ' ';
        }
        std::cout << std::endl;

        int nrows = Conn.PQ_ntuples(); // количество строк (записей)
        for (int i = 0; i < nrows; i++)
        {
            char* id = Conn.PQ_getvalue(i, 0);
            char* name = Conn.PQ_getvalue(i, 1);
            char* password = Conn.PQ_getvalue(i, 2);
            char* position = Conn.PQ_getvalue(i, 3);
            std::cout
                << "Id: " << id << ' '
                << "Name: " << name << ' '
                << "Phone: " << password << ' '
                << "Last changed: " << position
                << std::endl;
        }
    }
    std::cout << std::endl << "End reading" << std::endl;
}

void create_table_tests() {
    // создаём один нужную нам бызу данных
    // забовая интедефикация 
    Connection Conn;

    std::cout << std::endl << "Start creating" << std::endl;
    if (true) { // создаём таблицу
        std::string create_query = "CREATE TABLE IF NOT EXISTS tests \
    (id SERIAL PRIMARY KEY, creator VARCHAR(64),q_number INT, "
            "q1 VARCHAR(64), q1_a1 VARCHAR(64), q1_a2 VARCHAR(64), q1_a3 VARCHAR(64), q1_a4 VARCHAR(64),"
            "q2 VARCHAR(64), q2_a1 VARCHAR(64), q2_a2 VARCHAR(64), q2_a3 VARCHAR(64), q2_a4 VARCHAR(64),"
            "q3 VARCHAR(64), q3_a1 VARCHAR(64), q3_a2 VARCHAR(64), q3_a3 VARCHAR(64), q3_a4 VARCHAR(64),"
            "q4 VARCHAR(64), q4_a1 VARCHAR(64), q4_a2 VARCHAR(64), q4_a3 VARCHAR(64), q4_a4 VARCHAR(64),"
            "q5 VARCHAR(64), q5_a1 VARCHAR(64), q5_a2 VARCHAR(64), q5_a3 VARCHAR(64), q5_a4 VARCHAR(64),"
            "q6 VARCHAR(64), q6_a1 VARCHAR(64), q6_a2 VARCHAR(64), q6_a3 VARCHAR(64), q6_a4 VARCHAR(64),"
            "q7 VARCHAR(64), q7_a1 VARCHAR(64), q7_a2 VARCHAR(64), q7_a3 VARCHAR(64), q7_a4 VARCHAR(64),"
            "q8 VARCHAR(64), q8_a1 VARCHAR(64), q8_a2 VARCHAR(64), q8_a3 VARCHAR(64), q8_a4 VARCHAR(64),"
            "q9 VARCHAR(64), q9_a1 VARCHAR(64), q9_a2 VARCHAR(64), q9_a3 VARCHAR(64), q9_a4 VARCHAR(64),"
            "q10 VARCHAR(64), q10_a1 VARCHAR(64), q10_a2 VARCHAR(64), q10_a3 VARCHAR(64), q10_a4 VARCHAR(64))";

        Conn.PQ_exec(create_query.c_str()); // при исполении CREATE, INSERT, DELETE, UPDATE только проверка статуса
    }
    std::cout << std::endl << "End creating" << std::endl;

    std::cout << std::endl << "Start testing" << std::endl;

    if (false) { // добавляем данные для тестирования
        char const* insert_query =
            "INSERT INTO tests (creator ,q_number, "
            "q1 , q1_a1 , q1_a2 , q1_a3 , q1_a4 ,"
            "q2 , q2_a1 , q2_a2 , q2_a3 , q2_a4 ,"
            "q3 , q3_a1 , q3_a2 , q3_a3 , q3_a4 ,"
            "q4 , q4_a1 , q4_a2 , q4_a3 , q4_a4 ,"
            "q5 , q5_a1 , q5_a2 , q5_a3 , q5_a4 ,"
            "q6 , q6_a1 , q6_a2 , q6_a3 , q6_a4 ,"
            "q7 , q7_a1 , q7_a2 , q7_a3 , q7_a4 ,"
            "q8 , q8_a1 , q8_a2 , q8_a3 , q8_a4 ,"
            "q9 , q9_a1 , q9_a2 , q9_a3 , q9_a4 ,"
            "q10 , q10_a1 , q10_a2 , q10_a3 , q10_a4)"
            "VALUES ('admain', 10,"
            "'What is your name 11?', 'A', 'B', 'C', 'D',"
            "'What is your name 12?', 'A', 'B', 'C', 'D',"
            "'What is your name 13?', 'A', 'B', 'C', 'D',"
            "'What is your name 14?', 'A', 'B', 'C', 'D',"
            "'What is your name 15?', 'A', 'B', 'C', 'D',"
            "'What is your name 16?', 'A', 'B', 'C', 'D',"
            "'What is your name 17?', 'A', 'B', 'C', 'D',"
            "'What is your name 18?', 'A', 'B', 'C', 'D',"
            "'What is your name 19?', 'A', 'B', 'C', 'D',"
            "'What is your name 20?', 'A', 'B', 'C', 'D')";
        Conn.PQ_exec(insert_query);
    }
    std::cout << std::endl << "End testing" << std::endl;

    std::cout << std::endl << "Start reading" << std::endl;
    if (true) { // читаем данные
        Conn.PQ_exec("SELECT creator ,q_number, "
            "q1 , q1_a1 , q1_a2 , q1_a3 , q1_a4 ,"
            "q2 , q2_a1 , q2_a2 , q2_a3 , q2_a4 ,"
            "q3 , q3_a1 , q3_a2 , q3_a3 , q3_a4 ,"
            "q4 , q4_a1 , q4_a2 , q4_a3 , q4_a4 ,"
            "q5 , q5_a1 , q5_a2 , q5_a3 , q5_a4 ,"
            "q6 , q6_a1 , q6_a2 , q6_a3 , q6_a4 ,"
            "q7 , q7_a1 , q7_a2 , q7_a3 , q7_a4 ,"
            "q8 , q8_a1 , q8_a2 , q8_a3 , q8_a4 ,"
            "q9 , q9_a1 , q9_a2 , q9_a3 , q9_a4 ,"
            "q10 , q10_a1 , q10_a2 , q10_a3 , q10_a4 FROM tests");
        
        int ncols = Conn.PQ_nfields(); // сколько колонок в одной записи
        std::cout << "One row contains " << ncols << " fields" << std::endl;
        for (int i = 0; i < ncols; i++)
        {
            char* name = Conn.PQ_fname(i);
            std::cout << name << ' ';
        }
        std::cout << std::endl;

        int nrows = Conn.PQ_ntuples(); // количество строк (записей)
        std::cout << "N_items: " << nrows << std::endl; 
        for (int i = 0; i < nrows; i++)
        {
            std::cout
                << "Creator: " << Conn.PQ_getvalue(i, 0)
                << "q_number: " << Conn.PQ_getvalue(i, 0);

            for (int j = 0; j < 10; j++)
            {
                char* q = Conn.PQ_getvalue(i, 5 * j+2);
                char* a0 = Conn.PQ_getvalue(i, 5 * j + 2+1);
                char* a1 = Conn.PQ_getvalue(i, 5 * j + 2+2);
                char* a2 = Conn.PQ_getvalue(i, 5 * j + 2+3);
                char* a3 = Conn.PQ_getvalue(i, 5 * j + 2+4);
                std::cout
                    << "Q: " << q << ' '
                    << "A0: " << a0 << ' '
                    << "A1: " << a1 << ' '
                    << "A2: " << a2 << ' '
                    << "A3: " << a3 << ' ' << std::endl;
            }
        }
    }
    std::cout << std::endl << "End reading" << std::endl;
}

void create_table_tests_res() {
    // создаём один нужную нам бызу данных
    // забовая интедефикация 
    Connection Conn;

    std::cout << std::endl << "Start creating" << std::endl;
    if (true) { // создаём таблицу
        // таблица включает в себя дату прохождения теста, имя пользователя и само наименование теста, оценку а так же ответы на все 10 вопросов
        std::string create_query = "CREATE TABLE IF NOT EXISTS tests_res \
    (id SERIAL PRIMARY KEY, date VARCHAR(64), user_name VARCHAR(64), test_name VARCHAR(64), mark INT,"
            "a1 VARCHAR(64), a2 VARCHAR(64), a3 VARCHAR(64), a4 VARCHAR(64), a5 VARCHAR(64),"
            "a6 VARCHAR(64), a7 VARCHAR(64), a8 VARCHAR(64), a9 VARCHAR(64), a10 VARCHAR(64))";

        Conn.PQ_exec(create_query.c_str()); // при исполении CREATE, INSERT, DELETE, UPDATE только проверка статуса
        
    }
    std::cout << std::endl << "End creating" << std::endl;

    std::cout << std::endl << "Start testing" << std::endl;

    if (false) { // добавляем данные для тестирования
        char const* insert_query =
            "INSERT INTO tests_res (date , user_name, test_name, mark, "
            "a1 , a2 , a3 , a4 , a5 ,"
            "a6 , a7 , a8 , a9 , a10)"
            "VALUES ('15.10.2021', 'admin', 'your_test', 6,"
            "'A', 'C', 'A', 'A', 'D',"
            "'C', 'A', 'B', 'A', 'A')";
        Conn.PQ_exec(insert_query);
    }
    std::cout << std::endl << "End testing" << std::endl;

    std::cout << std::endl << "Start reading" << std::endl;
    if (true) { // читаем данные
        Conn.PQ_exec("SELECT date , user_name, test_name, mark, "
            "a1 , a2 , a3 , a4 , a5 ,"
            "a6 , a7 , a8 , a9 , a10 FROM tests_res");

        int ncols = Conn.PQ_nfields(); // сколько колонок в одной записи
        std::cout << "One row contains " << ncols << " fields" << std::endl;
        for (int i = 0; i < ncols; i++)
        {
            char* name = Conn.PQ_fname(i);
            std::cout << name << ' ';
        }
        std::cout << std::endl;

        int nrows = Conn.PQ_ntuples(); // количество строк (записей)
        std::cout << "N_items: " << nrows << std::endl;
        for (int i = 0; i < nrows; i++)
        {
            std::cout << std::endl;
            for (int j = 0; j < ncols; j++)
            {
                std::cout << " " << Conn.PQ_getvalue(i, j);
            }
        }
    }
    std::cout << std::endl << "End reading" << std::endl;
}


int get_log(
    std::string login,
    std::string Password) {
    // проверка на совпадение пароля пользователя и логина - отсутствие - 0
    // 1 - обычный пользователь
    // 2 - редактор (может добавлять тесты)
    // 3 - админ (может добавлять и удалять тесты и удалять и добавлять редакторов)
    Connection Conn;
    int Position = 0;
    if (true) { // читаем данные
        /// <summary>
        /// Тут стоит заглушка: нужно присвоить name и password значения
        /// </summary>
        
        Conn.PQ_exec("SELECT position FROM users WHERE name = '" + login + "' AND password = '" + Password + "'");
        

        int ncols = Conn.PQ_nfields(); // сколько колонок в одной записи
        for (int i = 0; i < ncols; i++)
        {
            char* name = Conn.PQ_fname(i);
        }

        int nrows = Conn.PQ_ntuples(); // количество строк (записей)
        for (int i = 0; i < nrows; i++)
        {
            Position = atoi(Conn.PQ_getvalue(i, 0));

        }

        if (nrows > 1) {
            std::cout << std::endl << "Error: N_items > 1;";
            //throw EXCEPTION_DATA;
            return 404;
        }
        else {
            if (Position == 0) {
                //throw EXCEPTION_LOGI;
                return Position;
            }
            else {
                return Position;
            }
        }
    }
}


int get_log(
    std::string login) {
    Connection Conn;

    int Position = 0;
    if (true) { 

        Conn.PQ_exec("SELECT position FROM users WHERE name = '" + login + "'");
        
        int ncols = Conn.PQ_nfields(); // сколько колонок в одной записи
        for (int i = 0; i < ncols; i++)
        {
            char* name = Conn.PQ_fname(i);
        }

        int nrows = Conn.PQ_ntuples(); // количество строк (записей)
        for (int i = 0; i < nrows; i++)
        {
            Position = atoi(Conn.PQ_getvalue(i, 0));

        }

        if (nrows > 1) {
            std::cout << std::endl << "Error: N_items > 1;";
            //throw EXCEPTION_DATA;
            return 404;
        }
        else {
            if (Position == 0) {
                //throw EXCEPTION_LOGI;
            }
            else {
                return Position;
            }
        }
    }
}

void registeration(
    std::string login,
    std::string Password, 
    std::string Position) {
    // происходит регистрация пользователя по заданным параметрам: имя пароль и статусс 
    // 1 - обычный пользователь
    // 2 - редактор (может добавлять тесты)
    // 3 - админ (может добавлять и удалять тесты и удалять и добавлять редакторов)

    Connection Conn;
    if (get_log(login) == 0) { // читаем данные
        Conn.PQ_exec("INSERT INTO users (name, password, position)"
            "VALUES ('" + login + "', '" + Password + "', '"  + Position + "')");
    }
    else {
        std::cout << "Error: user with that login is in the system";
    }
}


std::vector<std::string> get_test(
    std::string login,
    std::string Password) {
    // если пользователь есть в системе, то даём доступ
    // программа выдаёт наименование тестов (названия) в формате std::vector<std::string>
    Connection Conn;
    
    std::vector<std::string> Tests;
    if (get_log(login, Password) > 0) { // читаем данные
        char const* insert_query = "SELECT creator FROM tests";

        Conn.PQ_exec(insert_query);

        int ncols = Conn.PQ_nfields(); // сколько колонок в одной записи
        for (int i = 0; i < ncols; i++)
        {
            char* name = Conn.PQ_fname(i);
        }

        int nrows = Conn.PQ_ntuples(); // количество строк (записей)
        for (int i = 0; i < nrows; i++)
        {
            Tests.push_back(Conn.PQ_getvalue(i, 0));
        }
        return Tests;
    }
}

std::vector<std::string> get_certain_test(
    std::string login,
    std::string Password,
    std::string test_name) {
    // программа выдаёт список вопросов в формате std::vector<std::vector<std::string>> 
    // и список ответов в формате std::vector<std::string>, чтобы можно было сравнить ответы
    // если рассматривать защищённость программы, то получается что когда пользователь запускает бинарник, то унего нет доступа к дебагингу т.е. к получению ответов на тест
    
    Connection Conn;
    std::vector<std::string> Certain_Test; // определяем вектор результирующих значеий


    if (get_log(login, Password) > 0) { // читаем данные
        Conn.PQ_exec(("SELECT creator ,q_number, "
        "q1 , q1_a1 , q1_a2 , q1_a3 , q1_a4 ,"
        "q2 , q2_a1 , q2_a2 , q2_a3 , q2_a4 ,"
        "q3 , q3_a1 , q3_a2 , q3_a3 , q3_a4 ,"
        "q4 , q4_a1 , q4_a2 , q4_a3 , q4_a4 ,"
        "q5 , q5_a1 , q5_a2 , q5_a3 , q5_a4 ,"
        "q6 , q6_a1 , q6_a2 , q6_a3 , q6_a4 ,"
        "q7 , q7_a1 , q7_a2 , q7_a3 , q7_a4 ,"
        "q8 , q8_a1 , q8_a2 , q8_a3 , q8_a4 ,"
        "q9 , q9_a1 , q9_a2 , q9_a3 , q9_a4 ,"
            "q10 , q10_a1 , q10_a2 , q10_a3 , q10_a4 FROM tests WHERE creator = '" + test_name + "'").c_str());

        int ncols = Conn.PQ_nfields(); // сколько колонок в одной записи
        for (int i = 0; i < ncols; i++)
        {
            char* name = Conn.PQ_fname(i);
        }

        int nrows = Conn.PQ_ntuples(); // количество строк (записей)

        // записываем данные в вектор
        for (int i = 0; i < nrows; i++)
        {
            for (int j = 0; j < 52; j++)
                Certain_Test.push_back(std::string(Conn.PQ_getvalue(i, j)));
        }
    }
    return Certain_Test;
}

void set_result(
    std::string date,
    std::string login,
    std::string Password,
    std::string test_name,
    int mark,
    std::vector<std::string> answers
) {
    // определённому пользователю ставится определённа оценка за тест (пока базовая версия с целочисленным результатом и подробностями)

    Connection Conn;

    if (get_log(login, Password) > 0) { // добавляем данные для тестирования
        Conn.PQ_exec(("INSERT INTO tests_res (date , user_name, test_name, mark, "
            "a1 , a2 , a3 , a4 , a5 ,"
            "a6 , a7 , a8 , a9 , a10)"
            "VALUES ('" + date + "', '" + login +  "', '" + test_name + "', " + std::to_string(mark) + ","
            "'" + answers[0] + "', '" + answers[1] + "', '" + answers[2] + "', '" + answers[3] + "', '" + answers[4] + "',"
            "'" + answers[5] + "', '" + answers[6] + "', '" + answers[7] + "', '" + answers[8] + "', '" + answers[9] + "')").c_str());
    }
}

std::vector<std::vector<std::string>> get_grades(
    std::string login,
    std::string Password) {
    // определённому пользователю программы выдаёт все оценки за тесты которые он прошёл 
    
    Connection Conn;

    std::vector<std::vector<std::string>> Res;
    if (get_log(login, Password) > 0) { // читаем данные
        Conn.PQ_exec(("SELECT * FROM tests_res WHERE user_name = '" + login + "'").c_str());
        
        int ncols = Conn.PQ_nfields(); // сколько колонок в одной записи
        for (int i = 0; i < ncols; i++)
        {
            char* name = Conn.PQ_fname(i);
        }

        int nrows = Conn.PQ_ntuples(); // количество строк (записей)

        // записываем данные в вектор
        for (int i = 0; i < nrows; i++)
        {
            std::vector<std::string> test_item;
            for (int j = 0; j < 13; j++) {
                test_item.push_back(std::string(Conn.PQ_getvalue(i, 2)));
                test_item.push_back(std::string(Conn.PQ_getvalue(i, 1)));
                test_item.push_back(std::string(Conn.PQ_getvalue(i, 3)));
                test_item.push_back(std::string(Conn.PQ_getvalue(i, 4)));
            }
            Res.push_back(test_item);
        }
    }
    return Res;
}
