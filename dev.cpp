#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include <sstream>


using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "19072003dev";
const char* DB = "mydb";

class evbike {
private:
    string BRAND, MODEL;
    int SerilNo, RENT;
    bool AVAIL;
public:
    evbike(int serial, string brand, string model, int rent, bool avail) {
        SerilNo = serial;
        BRAND = brand;
        MODEL = model;
        RENT = rent;
        AVAIL = avail;
    }

    int getrent() {
        return RENT;
    }

    int getserial() {
        return SerilNo;
    }

    string getmodel() {
        return MODEL;
    }

    string getbrand() {
        return BRAND;
    }
};

bool isAvail(MYSQL* conn, string toS) {
    string comp = "SELECT AVAIL FROM mobike WHERE SerilNo = '" + toS + "'";
    if (mysql_query(conn, comp.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
        return false;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    if (result) {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row) {
            int availability = atoi(row[0]);
            mysql_free_result(result);
            return (availability == 1);
        }
        mysql_free_result(result);
    }
    return false;
}

void displayBikes(MYSQL* con) {
    string get = "SELECT * FROM mobike";
    if (mysql_query(con, get.c_str())) {
        cout << "Error: " << mysql_error(con) << endl;
    } else {
        MYSQL_RES* result = mysql_store_result(con);
        if (result) {
            int num = mysql_num_fields(result);
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                for (int i = 0; i < num; i++) {
                    cout << " " << row[i];
                }
                cout << endl;
            }
            mysql_free_result(result);
        }
    }
}


void updateAvailability(MYSQL* con, string toS, bool available) {
    stringstream ss;
    ss << (available ? 1 : 0);
    string upd = "UPDATE mobike SET AVAIL = '" + ss.str() + "' WHERE SerilNo = '" + toS + "'";
    if (mysql_query(con, upd.c_str())) {
        cout << "Error: " << mysql_error(con) << endl;
    }
}

void bookBike(MYSQL* con, evbike& bike) {
    cout << "You have successfully booked the below EVbike for a day:" << endl;
    cout << bike.getbrand() << " " << bike.getmodel() << " " << bike.getrent() << " rupees" << endl;
}

void returnBike(MYSQL* con, evbike& bike) {
    cout << "You have successfully returned the below EVbike:" << endl;
    cout << bike.getbrand() << " " << bike.getmodel() << endl;
}

int main() {
    MYSQL* con;
    con = mysql_init(NULL);
    if (!mysql_real_connect(con, HOST, USER, PW, DB, 3306, NULL, 0)) {
        cout << "Error: " << mysql_error(con) << endl;
        return 1;
    } else {
        cout << "**Welcome Namaste**" << endl;
    }

    evbike bike1(908, "ATHER", "ATHER 1", 3000, true);
    evbike bike2(909, "OLA", "Ola hero", 2000, true);
    evbike bike3(907, "DRONA", "Drona kc", 1500, true);
    evbike bike4(910, "SOLOBIKE", "Soloro", 600, true);

    string save1 = "INSERT INTO mobike(SerilNo, BRAND, MODEL, RENT, AVAIL) VALUES(908, 'ATHER', 'ATHER 1', 3000, true)";
    string save2 = "INSERT INTO mobike(SerilNo, BRAND, MODEL, RENT, AVAIL) VALUES(909, 'OLA', 'Ola hero', 2000, true)";
    string save3 = "INSERT INTO mobike(SerilNo, BRAND, MODEL, RENT, AVAIL) VALUES(907, 'DRONA', 'Drona kc', 1500, true)";
    string save4 = "INSERT INTO mobike(SerilNo, BRAND, MODEL, RENT, AVAIL) VALUES(910, 'SOLOBIKE', 'Soloro', 600, true)";

    if (mysql_query(con, save1.c_str()) || mysql_query(con, save2.c_str()) || mysql_query(con, save3.c_str()) || mysql_query(con, save4.c_str())) {
        cout << "Error saving data for EVbikes: " << mysql_error(con) << endl;
    } else {
        cout << "Data saved for EVbikes" << endl;
    }

    Sleep(5000);

    bool exit = false;

    while (!exit) {
        system("cls");

        cout << "Welcome to Evbikers Rental" << endl;
        cout << "**********" << endl;

        displayBikes(con);

        int val;

        cout << "1. Select Bike." << endl;
        cout << "2. Return Bike." << endl;
        cout << "0. Exit" << endl;
        cin >> val;

        if (val == 1) {
            int ser;
            cout << "Enter Seril No: ";
            cin >> ser;

            stringstream ss;
            ss << ser;
            string toS = ss.str();

            if (bike1.getserial() == ser) {
                if (isAvail(con, toS)) {
                    updateAvailability(con, toS, false);
                    bookBike(con, bike1);
                } else {
                    cout << "Sorry, this bike is not available" << endl;
                }
            } else if (bike2.getserial() == ser) {
                if (isAvail(con, toS)) {
                    updateAvailability(con, toS, false);
                    bookBike(con, bike2);
                } else {
                    cout << "Sorry, this bike is not available" << endl;
                }
            } else if (bike3.getserial() == ser) {
                if (isAvail(con, toS)) {
                    updateAvailability(con, toS, false);
                    bookBike(con, bike3);
                } else {
                    cout << "Sorry, this bike is not available" << endl;
                }
            } else if (bike4.getserial() == ser) {
                if (isAvail(con, toS)) {
                    updateAvailability(con, toS, false);
                    bookBike(con, bike4);
                } else {
                    cout << "Sorry, this bike is not available" << endl;
                }
            } else {
                cout << "Invalid Seril Number" << endl;
            }

            Sleep(5000);
        } else if (val == 2) {
            int ser;
            cout << "Enter Seril No: ";
            cin >> ser;

            stringstream ss;
            ss << ser;
            string toS = ss.str();

            if (bike1.getserial() == ser) {
                if (!isAvail(con, toS)) {
                    updateAvailability(con, toS, true);
                    returnBike(con, bike1);
                } else {
                    cout << "This bike is already available" << endl;
                }
            } else if (bike2.getserial() == ser) {
                if (!isAvail(con, toS)) {
                    updateAvailability(con, toS, true);
                    returnBike(con, bike2);
                } else {
                    cout << "This bike is already available" << endl;
                }
            } else if (bike3.getserial() == ser) {
                if (!isAvail(con, toS)) {
                    updateAvailability(con, toS, true);
                    returnBike(con, bike3);
                } else {
                    cout << "This bike is already available" << endl;
                }
            } else if (bike4.getserial() == ser) {
                if (!isAvail(con, toS)) {
                    updateAvailability(con, toS, true);
                    returnBike(con, bike4);
                } else {
                    cout << "This bike is already available" << endl;
                }
            } else {
                cout << "Invalid Seril Number" << endl;
            }

            Sleep(5000);
        } else if (val == 0) {
            exit = true;
            cout << "Thank you, we love to serve you again!!" << endl;
            Sleep(2000);
        }
    }

    mysql_close(con);
    return 0;
}

