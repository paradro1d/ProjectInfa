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


static PGconn* conn = NULL;
static PGresult* res = NULL;

static const char host[] = "rc1c-tu9ikdrrlhkp9lu5.mdb.yandexcloud.net";
static const char port[] = "6432";
static const char user[] = "dev";
static const char password[] = "tpips000";
static const char dbname[] = "db1";




void create_table_users() {
    // создаём один нужную нам бызу данных
    // забовая интедефикация 
    int libpq_ver = PQlibVersion();
    std::cout << libpq_ver << std::endl; // просто проверка версии

    std::stringstream connection_string; //создаём строку для соединения
    connection_string
        << "host=" << host << ' '
        << "port=" << port << ' '
        << "user=" << user << ' '
        << "password=" << password << ' '
        << "dbname=" << dbname;

    conn = PQconnectdb(connection_string.str().c_str()); // открываем соединение
    if (PQstatus(conn) != CONNECTION_OK) { // проверяем успешность соединения
        std::cerr << PQerrorMessage(conn) << std::endl;
    }


    std::cout << std::endl << "Start creating" << std::endl;
    if (true) { // создаём таблицу
        std::string create_query = "CREATE TABLE IF NOT EXISTS users \
    (id SERIAL PRIMARY KEY, name VARCHAR(64),password VARCHAR(64), position VARCHAR(64))";

        res = PQexec(conn, create_query.c_str()); // при исполении CREATE, INSERT, DELETE, UPDATE только проверка статуса
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }
    }
    std::cout << std::endl << "End creating" << std::endl;

    std::cout << std::endl << "Start testing" << std::endl;

    if (false) { // добавляем данные для тестирования
        char const* insert_query =
            "INSERT INTO users (name, password, position)"
            "VALUES ('editor', 'dev', '2');"; 

    res = PQexec(conn, insert_query);

            if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                std::cerr << PQerrorMessage(conn) << std::endl;
            }
        //}
    }
    std::cout << std::endl << "End testing" << std::endl;

    std::cout << std::endl << "Start reading" << std::endl;
    if (true) { // читаем данные
        res = PQexec(conn, "SELECT id, name, password, position FROM users");
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }

        int ncols = PQnfields(res); // сколько колонок в одной записи
        std::cout << "One row contains " << ncols << " fields" << std::endl;
        for (int i = 0; i < ncols; i++)
        {
            char* name = PQfname(res, i);
            std::cout << name << ' ';
        }
        std::cout << std::endl;

        int nrows = PQntuples(res); // количество строк (записей)
        for (int i = 0; i < nrows; i++)
        {
            char* id = PQgetvalue(res, i, 0);
            char* name = PQgetvalue(res, i, 1);
            char* password = PQgetvalue(res, i, 2);
            char* position = PQgetvalue(res, i, 3);
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
    int libpq_ver = PQlibVersion();
    std::cout << libpq_ver << std::endl; // просто проверка версии

    std::stringstream connection_string; //создаём строку для соединения
    connection_string
        << "host=" << host << ' '
        << "port=" << port << ' '
        << "user=" << user << ' '
        << "password=" << password << ' '
        << "dbname=" << dbname;

    conn = PQconnectdb(connection_string.str().c_str()); // открываем соединение
    if (PQstatus(conn) != CONNECTION_OK) { // проверяем успешность соединения
        std::cerr << PQerrorMessage(conn) << std::endl;
    }


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

        res = PQexec(conn, create_query.c_str()); // при исполении CREATE, INSERT, DELETE, UPDATE только проверка статуса
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }
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
        res = PQexec(conn, insert_query);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }
        //}
    }
    std::cout << std::endl << "End testing" << std::endl;

    std::cout << std::endl << "Start reading" << std::endl;
    if (true) { // читаем данные
        res = PQexec(conn, "SELECT creator ,q_number, "
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
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }

        int ncols = PQnfields(res); // сколько колонок в одной записи
        std::cout << "One row contains " << ncols << " fields" << std::endl;
        for (int i = 0; i < ncols; i++)
        {
            char* name = PQfname(res, i);
            std::cout << name << ' ';
        }
        std::cout << std::endl;

        int nrows = PQntuples(res); // количество строк (записей)
        std::cout << "N_items: " << nrows << std::endl; 
        for (int i = 0; i < nrows; i++)
        {
            std::cout
                << "Creator: " << PQgetvalue(res, i, 0)
                << "q_number: " << PQgetvalue(res, i, 0);

            for (int j = 0; j < 10; j++)
            {
                char* q = PQgetvalue(res, i, 5 * j+2);
                char* a0 = PQgetvalue(res, i, 5 * j + 2+1);
                char* a1 = PQgetvalue(res, i, 5 * j + 2+2);
                char* a2 = PQgetvalue(res, i, 5 * j + 2+3);
                char* a3 = PQgetvalue(res, i, 5 * j + 2+4);
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
    int libpq_ver = PQlibVersion();
    std::cout << libpq_ver << std::endl; // просто проверка версии

    std::stringstream connection_string; //создаём строку для соединения
    connection_string
        << "host=" << host << ' '
        << "port=" << port << ' '
        << "user=" << user << ' '
        << "password=" << password << ' '
        << "dbname=" << dbname;

    conn = PQconnectdb(connection_string.str().c_str()); // открываем соединение
    if (PQstatus(conn) != CONNECTION_OK) { // проверяем успешность соединения
        std::cerr << PQerrorMessage(conn) << std::endl;
    }


    std::cout << std::endl << "Start creating" << std::endl;
    if (true) { // создаём таблицу
        // таблица включает в себя дату прохождения теста, имя пользователя и само наименование теста, оценку а так же ответы на все 10 вопросов
        std::string create_query = "CREATE TABLE IF NOT EXISTS tests_res \
    (id SERIAL PRIMARY KEY, date VARCHAR(64), user_name VARCHAR(64), test_name VARCHAR(64), mark INT,"
            "a1 VARCHAR(64), a2 VARCHAR(64), a3 VARCHAR(64), a4 VARCHAR(64), a5 VARCHAR(64),"
            "a6 VARCHAR(64), a7 VARCHAR(64), a8 VARCHAR(64), a9 VARCHAR(64), a10 VARCHAR(64))";

        res = PQexec(conn, create_query.c_str()); // при исполении CREATE, INSERT, DELETE, UPDATE только проверка статуса
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }
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
        res = PQexec(conn, insert_query);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }
        //}
    }
    std::cout << std::endl << "End testing" << std::endl;

    std::cout << std::endl << "Start reading" << std::endl;
    if (true) { // читаем данные
        res = PQexec(conn, "SELECT date , user_name, test_name, mark, "
            "a1 , a2 , a3 , a4 , a5 ,"
            "a6 , a7 , a8 , a9 , a10 FROM tests_res");
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }

        int ncols = PQnfields(res); // сколько колонок в одной записи
        std::cout << "One row contains " << ncols << " fields" << std::endl;
        for (int i = 0; i < ncols; i++)
        {
            char* name = PQfname(res, i);
            std::cout << name << ' ';
        }
        std::cout << std::endl;

        int nrows = PQntuples(res); // количество строк (записей)
        std::cout << "N_items: " << nrows << std::endl;
        for (int i = 0; i < nrows; i++)
        {
            std::cout << std::endl;
            for (int j = 0; j < ncols; j++)
            {
                std::cout << " " << PQgetvalue(res, i, j);
            }
        }
    }
    std::cout << std::endl << "End reading" << std::endl;
}

int get_log(
    char const* login,
    char const* Password) {
    // проверка на совпадение пароля пользователя и логина - отсутствие - 0
    // 1 - обычный пользователь
    // 2 - редактор (может добавлять тесты)
    // 3 - админ (может добавлять и удалять тесты и удалять и добавлять редакторов)
    int libpq_ver = PQlibVersion();
    // std::cout << libpq_ver << std::endl; // просто проверка версии

    std::stringstream connection_string; //создаём строку для соединения
    connection_string
        << "host=" << host << ' '
        << "port=" << port << ' '
        << "user=" << user << ' '
        << "password=" << password << ' '
        << "dbname=" << dbname;

    conn = PQconnectdb(connection_string.str().c_str()); // открываем соединение
    if (PQstatus(conn) != CONNECTION_OK) { // проверяем успешность соединения
        std::cerr << PQerrorMessage(conn) << std::endl;
    }
    
    // std::cout << std::endl << "Start reading" << std::endl;
    
    int Position = 0;
    if (true) { // читаем данные
        /// <summary>
        /// Тут стоит заглушка: нужно присвоить name и password значения
        /// </summary>
        
        char const* insert_query = "SELECT position FROM users WHERE name = 'admin' AND password = 'dev'";

        res = PQexec(conn, insert_query);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }

        int ncols = PQnfields(res); // сколько колонок в одной записи
        for (int i = 0; i < ncols; i++)
        {
            char* name = PQfname(res, i);
        }

        int nrows = PQntuples(res); // количество строк (записей)
        for (int i = 0; i < nrows; i++)
        {
            Position = atoi(PQgetvalue(res, i, 0));

        }

        if (nrows > 1) {
            std::cout << std::endl << "Error: N_items > 1;";
            return 404;
        }
        else {
            return Position;
        }
    }
}

std::vector<std::string> get_test(
    char const* login,
    char const* Password) {
    // если пользователь есть в системе, то даём доступ
    // программа выдаёт наименование тестов (названия) в формате std::vector<std::string>
    /// <summary>
    /// Тут костыль: мы используем название теста и имя создателя вместе (можно исправить)
    /// </summary>
    /// <returns>можно переписать таблицу</returns>


    int libpq_ver = PQlibVersion();
    // std::cout << libpq_ver << std::endl; // просто проверка версии

    std::stringstream connection_string; //создаём строку для соединения
    connection_string
        << "host=" << host << ' '
        << "port=" << port << ' '
        << "user=" << user << ' '
        << "password=" << password << ' '
        << "dbname=" << dbname;

    conn = PQconnectdb(connection_string.str().c_str()); // открываем соединение
    if (PQstatus(conn) != CONNECTION_OK) { // проверяем успешность соединения
        std::cerr << PQerrorMessage(conn) << std::endl;
    }
    

    std::vector<std::string> Tests;
    if (get_log(login, Password) > 0) { // читаем данные
        char const* insert_query = "SELECT creator FROM tests";

        res = PQexec(conn, insert_query);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }

        int ncols = PQnfields(res); // сколько колонок в одной записи
        for (int i = 0; i < ncols; i++)
        {
            char* name = PQfname(res, i);
        }

        int nrows = PQntuples(res); // количество строк (записей)
        for (int i = 0; i < nrows; i++)
        {
            Tests.push_back(PQgetvalue(res, i, 0));
        }
        return Tests;
    }
}

std::vector<std::string> get_certain_test(
    char const* login,
    char const* Password,
    char const* test_name) {
    // программа выдаёт список вопросов в формате std::vector<std::vector<std::string>> 
    // и список ответов в формате std::vector<std::string>, чтобы можно было сравнить ответы
    // если рассматривать защищённость программы, то получается что когда пользователь запускает бинарник, то унего нет доступа к дебагингу т.е. к получению ответов на тест
    
    int libpq_ver = PQlibVersion();
    // std::cout << libpq_ver << std::endl; // просто проверка версии

    std::stringstream connection_string; //создаём строку для соединения
    connection_string
        << "host=" << host << ' '
        << "port=" << port << ' '
        << "user=" << user << ' '
        << "password=" << password << ' '
        << "dbname=" << dbname;

    conn = PQconnectdb(connection_string.str().c_str()); // открываем соединение
    if (PQstatus(conn) != CONNECTION_OK) { // проверяем успешность соединения
        std::cerr << PQerrorMessage(conn) << std::endl;
    }

    char const* insert_query = "SELECT creator ,q_number, "
        "q1 , q1_a1 , q1_a2 , q1_a3 , q1_a4 ,"
        "q2 , q2_a1 , q2_a2 , q2_a3 , q2_a4 ,"
        "q3 , q3_a1 , q3_a2 , q3_a3 , q3_a4 ,"
        "q4 , q4_a1 , q4_a2 , q4_a3 , q4_a4 ,"
        "q5 , q5_a1 , q5_a2 , q5_a3 , q5_a4 ,"
        "q6 , q6_a1 , q6_a2 , q6_a3 , q6_a4 ,"
        "q7 , q7_a1 , q7_a2 , q7_a3 , q7_a4 ,"
        "q8 , q8_a1 , q8_a2 , q8_a3 , q8_a4 ,"
        "q9 , q9_a1 , q9_a2 , q9_a3 , q9_a4 ,"
        "q10 , q10_a1 , q10_a2 , q10_a3 , q10_a4 FROM tests WHERE creator = 'admain'";

    /// <summary>
        /// Тут стоит заглушка: нужно присвоить test_name значения
    /// </summary>

    std::vector<std::string> Certain_Test; // определяем вектор результирующих значеий


    if (get_log(login, Password) > 0) { // читаем данные
        res = PQexec(conn, insert_query);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }

        int ncols = PQnfields(res); // сколько колонок в одной записи
        for (int i = 0; i < ncols; i++)
        {
            char* name = PQfname(res, i);
        }

        int nrows = PQntuples(res); // количество строк (записей)

        // записываем данные в вектор
        for (int i = 0; i < nrows; i++)
        {
            for (int j = 0; j < 52; j++)
                Certain_Test.push_back(std::string(PQgetvalue(res, i, j)));
        }
    }
    return Certain_Test;
}

void set_result(
    char const* date,
    char const* login,
    char const* Password,
    char const* test_name,
    int mark,
    std::vector<char const*> answers
) {
    // определённому пользователю ставится определённа оценка за тест (пока базовая версия с целочисленным результатом и подробностями)

    int libpq_ver = PQlibVersion();
    // std::cout << libpq_ver << std::endl; // просто проверка версии

    std::stringstream connection_string; //создаём строку для соединения
    connection_string
        << "host=" << host << ' '
        << "port=" << port << ' '
        << "user=" << user << ' '
        << "password=" << password << ' '
        << "dbname=" << dbname;

    conn = PQconnectdb(connection_string.str().c_str()); // открываем соединение
    if (PQstatus(conn) != CONNECTION_OK) { // проверяем успешность соединения
        std::cerr << PQerrorMessage(conn) << std::endl;
    }

    char const* insert_query =
            "INSERT INTO tests_res (date , user_name, test_name, mark, "
            "a1 , a2 , a3 , a4 , a5 ,"
            "a6 , a7 , a8 , a9 , a10)"
            "VALUES ('15.10.2021', 'user', 'your_test', 10,"
            "'A', 'A', 'A', 'A', 'A',"
            "'A', 'A', 'A', 'A', 'A')";

    /// <summary>
    /// тут стоит заглушка: вместо параметров надо поставить нужные знаения
    /// </summary>


    if (get_log(login, Password) > 0) { // добавляем данные для тестирования
        res = PQexec(conn, insert_query);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }
    }
}

std::vector<std::vector<std::string>> get_grades(
    char const* login,
    char const* Password) {
    // определённому пользователю программы выдаёт все оценки за тесты которые он прошёл 
    
    int libpq_ver = PQlibVersion();
    // std::cout << libpq_ver << std::endl; // просто проверка версии

    std::stringstream connection_string; //создаём строку для соединения
    connection_string
        << "host=" << host << ' '
        << "port=" << port << ' '
        << "user=" << user << ' '
        << "password=" << password << ' '
        << "dbname=" << dbname;

    conn = PQconnectdb(connection_string.str().c_str()); // открываем соединение
    if (PQstatus(conn) != CONNECTION_OK) { // проверяем успешность соединения
        std::cerr << PQerrorMessage(conn) << std::endl;
    }

    char const* insert_query =
        "SELECT * FROM tests_res WHERE user_name = 'admin'";
    std::vector<std::vector<std::string>> Res;
    if (get_log(login, Password) > 0) { // читаем данные
        res = PQexec(conn, insert_query);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }

        int ncols = PQnfields(res); // сколько колонок в одной записи
        for (int i = 0; i < ncols; i++)
        {
            char* name = PQfname(res, i);
        }

        int nrows = PQntuples(res); // количество строк (записей)

        // записываем данные в вектор
        for (int i = 0; i < nrows; i++)
        {
            std::vector<std::string> test_item;
            for (int j = 0; j < 13; j++) {
                test_item.push_back(std::string(PQgetvalue(res, i, 2)));
                test_item.push_back(std::string(PQgetvalue(res, i, 1)));
                test_item.push_back(std::string(PQgetvalue(res, i, 3)));
                test_item.push_back(std::string(PQgetvalue(res, i, 4)));
            }
            Res.push_back(test_item);
        }
    }
    return Res;
}


int main() {

    // тестируем начальную программу
    
    // create_table_users();                                                              //- work
    
    // create_table_tests();                                                              //- work
    
    //create_table_tests_res();                                                           //- work

    // std::cout << "get_log('admin', 'dev') = " << get_log("admin", "dev") << std::endl; //- work
    
    //std::vector<std::string> Res = get_test("admin", "dev");
    //for (int i = 0; i < Res.size(); i++)
    //{
    //    std::cout << "Test: " << Res[i] << std::endl;                                   // - work
    //}
    

    //std::vector<std::string> Res = get_certain_test("admin", "dev", "admain");
    //std::cout << "get_certain_test('admin', 'dev', 'admain') = ";
    //for (int i = 0; i < Res.size(); i++)
    //{
    //    std::cout << Res[i] << " ";                                                     // - work
    //}

    /*
    std::vector<std::vector<std::string>> Res = get_grades("admin", "dev");
    std::cout << "get_grades('admin', 'dev') = ";
    for (int i = 0; i < Res.size(); i++)
    {
        std::cout << std::endl;
        for (int j = 0; j < 4; j++)
        {
            std::cout << Res[i][j] << " ";                                                 // - work

        }
        std::cout << std::endl;
    }*/


    //std::vector<char const*> answers;
    //set_result("23.10.2019", "user", "qwerty", "your_test", 10, answers);               // - work




    int libpq_ver = PQlibVersion();
    std::cout << libpq_ver << std::endl; // просто проверка версии

    std::stringstream connection_string; //создаём строку для соединения
    connection_string
        << "host=" << host << ' '
        << "port=" << port << ' '
        << "user=" << user << ' '
        << "password=" << password << ' '
        << "dbname=" << dbname;

    conn = PQconnectdb(connection_string.str().c_str()); // открываем соединение
    if (PQstatus(conn) != CONNECTION_OK) { // проверяем успешность соединения
        std::cerr << PQerrorMessage(conn) << std::endl;
    }

    if (false) { // создаём таблицу
        std::string create_query = "CREATE TABLE IF NOT EXISTS phonebook \
    (id SERIAL PRIMARY KEY, name VARCHAR(64),phone VARCHAR(64), last_changed TIMESTAMP)";

        res = PQexec(conn, create_query.c_str()); // при исполении CREATE, INSERT, DELETE, UPDATE только проверка статуса
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }
    }

    if (false) { // добавляем данные
        std::string insert_query =
            "INSERT INTO phonebook (name, phone, last_changed) "
            " VALUES ($1, $2, now());"; // параметризованный запрос
        std::vector<std::pair<std::string, std::string>> data_to_insert;
        data_to_insert.emplace_back("Andre", "1234567");
        data_to_insert.emplace_back("Harry", "7654321");
        data_to_insert.emplace_back("Robert", "1324576");

        for (auto const& p : data_to_insert) {
            char const* const params[] = { p.first.data(),p.second.data() };
            res = PQexecParams(
                conn,                 // параметр соединение, полученный ранее
                insert_query.c_str(), // строка запроса
                2,                    // количество параметров в запросе
                NULL,                 // массив OIDs, просто опустить
                params,               // массив параметров (указатель на начало массива
                NULL,                 // размер в байтах для данных передаваемых бинарно
                NULL,                 // спецификаторы передачи данных в бинарном режиме (NULL - текст)
                0                     // 0 - результат как тектс, 1 - бинарные данные
            );

            if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                std::cerr << PQerrorMessage(conn) << std::endl;
            }
        }
    }

    if (0) { // читаем данные
        res = PQexec(conn, "SELECT id, name, phone, last_changed FROM phonebook");
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << PQerrorMessage(conn) << std::endl;
        }

        int ncols = PQnfields(res); // сколько колонок в одной записи
        std::cout << "One row contains " << ncols << " fields" << std::endl;
        for (int i = 0; i < ncols; i++)
        {
            char* name = PQfname(res, i);
            std::cout << name << ' ';
        }
        std::cout << std::endl;

        int nrows = PQntuples(res); // количество строк (записей)
        for (int i = 0; i < nrows; i++)
        {
            char* id = PQgetvalue(res, i, 0);
            char* name = PQgetvalue(res, i, 1);
            char* phone = PQgetvalue(res, i, 2);
            char* last_changed = PQgetvalue(res, i, 3);
            std::cout
                << "Id: " << id << ' '
                << "Name: " << name << ' '
                << "Phone: " << phone << ' '
                << "Last changed: " << last_changed
                << std::endl;
        }
    }

CLEAR:
    if (NULL != res) PQclear(res);
    if (NULL != conn) PQfinish(conn);
    return 0;
}

/*
    res = PQexec(conn, "SELECT id, name, phone, last_changed "
                       "FROM phonebook");
    if(PQresultStatus(res) != PGRES_TUPLES_OK)
        terminate(1);

    int ncols = PQnfields(res);
    printf("There are %d columns:", ncols);
    for(int i = 0; i < ncols; i++)
    {
        char *name = PQfname(res, i);
        printf(" %s", name);
    }
    printf("\n");

    int nrows = PQntuples(res);
    for(int i = 0; i < nrows; i++)
    {
        char* id = PQgetvalue(res, i, 0);
        char* name = PQgetvalue(res, i, 1);
        char* phone = PQgetvalue(res, i, 2);
        char* last_changed = PQgetvalue(res, i, 3);
        printf("Id: %s, Name: %s, Phone: %s, Last changed: %s\n",
            id, name, phone, last_changed);
    }

    printf("Total: %d rows\n", nrows);
*/

//