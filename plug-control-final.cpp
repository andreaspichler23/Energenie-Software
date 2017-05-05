
/*  written by

  Andreas Pichler

    in a hurry
    (08.2016)
				*/


#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <unistd.h>

using namespace std;

// g++ -o press-readout check-number-in-txtfile.cpp
// ./press-readout


int ReadSocketState(int socket_number) // on windows: 0 = false; 1 = true ... returns -1 if there is a problem with reading the info file
{ // the info file read here is generated new every loop iteration .. so better open and close the ifstream all the time ?!
    int error_flag = 0;
	ifstream info_file;
	string dummie;
	int line_number = 2 + socket_number * 3;
	int socket_state;
	size_t pos;
	string bool_str;
	int val_true,val_false;

	info_file.open("C:/Dokumente und Einstellungen/vip2/Desktop/info.ini");
	if(info_file.fail()){
		cout << "error opening the info file" << endl;
		error_flag = 1;
		goto error;
	}


	for(int i = 0; i < line_number; i++) {

		getline(info_file, dummie);

	}

	pos = dummie.find("=");
	bool_str = dummie.substr(pos+1);

	val_true = bool_str.compare("TRUE");// compare returns -1/1 if false and 0 if true; but bool is true = 1
	val_false = bool_str.compare("FALSE");

	//cout << "val true = " << val_true << "val_false = " << val_false << endl;

	if(val_true == 0) {
		socket_state = 1;
	} else if(val_false == 0) {
		socket_state = 0;
	} else {
		cout << "error reading the info file" << endl;
		error_flag = 1;
		goto error;
	}

	//cout << dummie << " " << bool_str << " " << socket_state  << " " << val_true << " " << val_false << endl;

	error: if(error_flag == 1){ socket_state = -1; }

	info_file.close();

	return socket_state;

}

void GetInfoFile(){

	system("pm2.lnk -info");
}

void TurnOffTurbos(){

	system("pm2.lnk -off -VIP Plug 1 -Turbos");
}

void TurnOffTube(){

	system("pm2.lnk -off -VIP Plug 1 -X Ray Tube");
}

void TurnOffSDDs(){

	system("pm2.lnk -off -VIP Plug 1 -SDDs NIM Crate");
}

double GetPressure(){// reads pressure from the file which is written in by the Arduino; returns -1 if there is a problem

	ifstream press_file;
	int error_flag = 0;
	double pressure;
	string dummie;
	string press_str;
	size_t pos;
	stringstream conv;

	press_file.open("F:/Dokumente und Einstellungen/vip2/Desktop/Gembird/pressure.dat");
	if(press_file.fail()){
		cout << "error opening the pressure file" << endl;
		error_flag = 1;
		goto error;
	}


	//getline(press_file, dummie);
	getline(press_file, dummie);

	pos = dummie.find("sure:");
	press_str = dummie.substr(pos+6);


	conv.str(press_str);
	conv >> pressure;
	//cout << pressure << endl;
	press_file.close();

	error: if(error_flag == 1){pressure = -1;}
	return pressure;

}

string GetLastLine(ifstream& in) // gets last line of a file opened by the ifstream and returns it as string
{
    string line;
    while (in >> ws && getline(in, line)); //while (in >> ws && getline(in, line)); skip empty lines


    return line;
}

string GetDate(){ // returns date in yearmoda

	time_t now = time(0);
	int year,month,day;
	tm *ltm = localtime(&now);

	stringstream ss;
	string date;
	string zero("0");

	year  = 1900+ltm->tm_year;
	month = 1+ltm->tm_mon;
	day   = ltm->tm_mday;

	if(month < 10 && day < 10){ss << year << zero << month << zero << day;}
	if(month > 9  && day < 10){ss << year << month << zero << day;}
	if(month < 10 && day > 9) {ss << year << zero << month << day;}
	if(month > 9  && day > 9) {ss << year << month << day;}
	date = ss.str();

	return date;

}

string GetTime(){ // returns time in hr:min:sec

	time_t now = time(0);
	int hour,min,sec;
	tm *ltm = localtime(&now);

	stringstream ss, ss_hour, ss_min, ss_sec;
	string h_str, m_str, s_str;
	string time;
	string zero("0");

	hour  = ltm->tm_hour;
	min   = ltm->tm_min;
	sec   = ltm->tm_sec;

	if(hour < 10){ ss_hour << zero << hour; }
	else{ ss_hour << hour; }

	if(min < 10){ ss_min << zero << min; }
	else{ ss_min << min; }

	if(sec < 10){ ss_sec << zero << sec; }
	else{ ss_sec << sec; }

	h_str = ss_hour.str();
	m_str = ss_min.str();
	s_str = ss_sec.str();


	ss << h_str << ":" << m_str << ":" << s_str;

	time = ss.str();

	return time;

}

string GetSlowFileName(){


	stringstream ss;
	string slow_name;
	string name1("C:/Documents and Settings/mario/My Documents/Slowmonitor_PXI_VIP/SlowLog/");
	//string name1("F:/Dokumente und Einstellungen/vip2/Desktop/Gembird/");
	string name2(".log");
	string name_date;


	name_date = GetDate();

	ss << name1 << name_date << name2;

	slow_name = ss.str();

	return slow_name;


}

string GetPressFileName(){


	stringstream ss;
	string press_name;
	string name1("F:/Dokumente und Einstellungen/vip2/Desktop/pressure-readout/");
	string name2(".log");
	string name_date;


	name_date = GetDate();

	ss << name1 << name_date << name2;

	press_name = ss.str();

	return press_name;


}

int GetSlowData(int &month, int &day, int &year, int &hour, int &min, int &sec, string &AmOrPm, double &ticks, double &room, double &ar_target, double &pcb_a, double &pcb_b, double &sdd1, double &argon_up, double &argon_down, double &sdd2, double &copper_int, double &copper_ext1, double &cooling_pad, double &vacuum_pres, double &current, double &argon_pres, double &voltage, double &heater_percent, double &ar_gas){
// reads the last line of the slow log file which is gotten from getslowfilename()
	int error_flag = 0;
	char dum;
	string slow_filename = GetSlowFileName();
	string slow_data;
	ifstream slow_stream;
	stringstream ss;
	slow_stream.open(slow_filename.c_str());// slow filename needs to be converted to c string here

	//cout << slow_filename << endl;

	if( slow_stream.fail() ){

		//cout << "error reading the slow control data file" << endl;
		error_flag = -1;
	}

	slow_data = GetLastLine(slow_stream);
	ss.str(slow_data);
	//cout << str << endl;

	ss >> month >> dum >> day >> dum >> year >> ws >> hour >> dum >> min >> dum >> sec;
	ss >> AmOrPm >> ws >> ticks >> ws >> room >> ws >> ar_target >> ws >> pcb_a >> ws >> pcb_b;
	ss >> sdd1 >> ws >> argon_up >> ws >> argon_down >> ws >> sdd2 >> ws >> copper_int >> ws;
	ss >> copper_ext1 >> cooling_pad >> ws >> vacuum_pres >> ws >> current >> argon_pres >> ws;
	ss >> voltage >> ws >> heater_percent >> ar_gas;

	slow_stream.close();

	return error_flag;

}

void WritePressLogFile(double pressure){

	ofstream press_file;
	string file_name = GetPressFileName();
	string time = GetTime();

	press_file.open(file_name.c_str(), ios::app);

	press_file << time << " " << pressure << endl;

	press_file.close();


}

int main()
{
    bool socket_state;
    int month, day, year, hour, min, sec;
    string amorpm;
    double ticks;
    double room, ar_target, pcb_a, pcb_b, sdd1, argon_up, argon_down, sdd2, copper_int, copper_ext1, cooling_pad, vacuum_pres, current, argon_pres, voltage, heater_percent, ar_gas;
    //double vac_pres;
    string date,time;
    int error_flag;

    //int sdd_temp_lim = -80;
    //double vac_pres_limit = 0.0001;

	int sdd1_alarm = 0, sdd2_alarm = 0, room_alarm = 0, copperint_alarm = 0, vacpres_alarm = 0;

    ofstream logfile;
    logfile.open("GenericLogfile.txt",ios::app);


    //TurnOffTube();
    //ReadSocketState(3);
    //GetSlowData(month, day, year, hour, min, sec, amorpm, ticks, room, ar_target, pcb_a, pcb_b, sdd1, argon_up, argon_down, sdd2, copper_int, copper_ext1, cooling_pad, vacuum_pres, current, argon_pres, voltage, heater_percent, ar_gas);

    //GetInfoFile();


    while(1){

        error_flag = 0;
    	//vac_pres = GetPressure();
    	//cout << vac_pres << endl;
    	//GetInfoFile(); // this needs some time < 1 sec to generate the file
     	//sleep(1);

        date = GetDate();
        time = GetTime();


    	error_flag = GetSlowData(month, day, year, hour, min, sec, amorpm, ticks, room, ar_target, pcb_a, pcb_b, sdd1, argon_up, argon_down, sdd2, copper_int, copper_ext1, cooling_pad, vacuum_pres, current, argon_pres, voltage, heater_percent, ar_gas);
        //cout << "SDD1 " << sdd1 << "SDD2 " << sdd2 << "room " << room << "copper int " << copper_int << endl;

        if(error_flag == 0){


        	if( sdd1 > -100 ){ sdd1_alarm +=1; }
			else{ sdd1_alarm = 0; }

        	if( sdd2 > -100 ){ sdd2_alarm +=1; }
			else{ sdd2_alarm = 0; }

        	if( room > 28 ){ room_alarm +=1; }
			else{ room_alarm = 0; }

        	if( copper_int > 30 ){ copperint_alarm +=1; }
			else{ copperint_alarm = 0; }

        	if( vacuum_pres > 0.0005 ){ vacpres_alarm +=1; }
			else{ vacpres_alarm = 0; }


			//logfile << " on: " << date << " " << time << endl;
        	if( sdd1_alarm > 3 || sdd2_alarm > 3 || room_alarm > 3 || copperint_alarm > 3 ){ TurnOffSDDs(); logfile << "SDD1: " << sdd1 << ", SDD2: " << sdd2 << ", room: " << room << ", copper int: " << copper_int << ", on: " << date << " " << time << endl;}
        	if( vacpres_alarm > 3 ){ TurnOffTurbos(); logfile << "vacuum pressure: " << vacuum_pres << " on: " << date << " " << time << endl;}


    	}
        //
        //TurnOffTube();
        //cout << vacuum_pres  << " " << vac_pres_limit << endl;
        //if( vacuum_pres >  vac_pres_limit) {logfile << " The pressure is too high: " << vacuum_pres << " on: " << date << " " << time << endl;}

        if( error_flag == -1){ logfile << "Error reading the log file on " << date << " " << time << endl;}


    	//WritePressLogFile(vac_pres);
    	Sleep(1800000);// in milliseconds should be half an hour
    	//Sleep(1000);
	}


    logfile.close();
	//cout << "Socket is " << socket_state << endl;



	//cout << "ar_gas = " << ar_gas << endl;

	return 0;


}


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   