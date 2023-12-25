#include <iostream>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <string>
#include <format>
#include "Pipe.h"
#include "CS.h"
#include "Subfuncs.h"
#include "Connection.h"

using namespace std;
using namespace chrono;

void SaveData(Pipe& pipes, CS& css, Connection& con)
{
	ofstream file("Saves\\" + ChooseFileName(), ios_base::out | ios_base::trunc);
	if (!file.is_open()) {
		cout << "Ошибка чтения файла!";
	}
	else {
		//трубы
		pipes.SaveDataPipes(file);
		//кс
		css.SaveDataCS(file);
		//соединения
		con.SaveCon(file);
	}
	file.close();
}

void LoadData(Pipe& pipe, CS& css, Connection& con) {
	ifstream file("Saves\\"+ViewFiles("Saves"), ios::in);
	if (file.is_open() and file.peek() != EOF) {
		//pipe.pipes.clear();
		//css.cs.clear();
		pipe.PipeDataLoad(file);
		css.CSDataLoad(file);
		con.LoadCon(file);
	}
	else {
		cout << "\n\nОшибка загрузки файла\n\n";
	}
	file.close();
}

int main()
{
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now() + hours(3));
	ofstream logfile("Logs/log_" + time + ".txt");
	if (logfile)
		cerr_out.redirect(logfile);

	Connection con;
	Pipe pipes;
	CS css;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) {
		int number = Menu();
		switch (number) {
		case 1:
			//system("cls");
			pipes.AddPipe();
			//system("cls");
			break;
		case 2:
			//system("cls");
			css.AddCS();
			//system("cls");
			break;
		case 3:
			con.make_a_con(css,pipes);
			break;//Добавить соединение
		case 4:
			//system("cls");
			cout << "\t0.Трубы\n\t1.КС\n";
			if (!Choose(0, 1))
				pipes.ViewPipes();
			else
				//cout << con.getConLen();   
				css.ViewCSs();
			break;
		case 5:
			//system("cls");
			//system("cls");
			cout << "\t0.Трубы\n\t1.КС\n";
			if (!Choose(0, 1))
				pipes.packagePipe();
			else
				css.packageCS();
			break;
			/*cout << "Выберите трубу для редактирования: ";
			pipes.ViewPipes();
			cout << "Введите номер трубы для редактирования: ";
			pipes.PipeChange(Choose(1,pipes.pipe.size()));*/
			//system("cls");
		case 6:
			cout << "0.Кратчайший путь\n1.Топлологическая сортировка\n2.Максимальный поток\nВвод: ";
			
			switch(Choose(0, 2)) {
			case 0:	
				con.shortestPath(css, pipes);
				break;
			case 1: 
				con.topSort(css, pipes);
				break;//Редактировать соединения
			case 2:
				con.maxStream(css, pipes);
				break;
			}
			break;
		case 7:
			SaveData(pipes, css, con);
			break;
		case 8:
			LoadData(pipes, css, con);
			break;
		case 0:
			exit(0);
			break;
		}
	}
	return 0;
}