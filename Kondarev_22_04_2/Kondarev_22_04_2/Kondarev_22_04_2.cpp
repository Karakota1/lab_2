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

using namespace std;
using namespace chrono;

void SaveData(Pipe& pipes, CS& css)
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
	}
	file.close();
}

void LoadData(Pipe& pipes, CS& css) {
	ifstream file("Saves\\"+ViewFiles("Saves"), ios::in);
	if (file.is_open() and file.peek() != EOF) {
		pipes.pipe.clear();
		css.cs.clear();
		pipes.PipeDataLoad(file);
		css.CSDataLoad(file);
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
			//system("cls");
			cout << "\t0.Трубы\n\t1.КС\n";
			if(!Choose(0,1))
				pipes.ViewPipes();
			else
				css.ViewCSs();
			break;
		case 4:
			//system("cls");
			cout << "Выберите трубу для редактирования: ";
			pipes.ViewPipes();
			cout << "Введите номер трубы для редактирования: ";
			pipes.PipeChange(Choose(1,pipes.pipe.size()));
			//system("cls");
			break;
		case 5:
			//system("cls");
			cout << "Выберите КС для редактирования: ";
			css.ViewCSs();
			cout << "Введите номер цеха для редактирования: ";
			css.CSChange(Choose(1,css.cs.size()));
			//system("cls");
			break;
		case 6:
			SaveData(pipes,css);
			break;
		case 7:
			LoadData(pipes, css);
			break;
		case 8:
			pipes.packagePipe();
			break;
		case 9:
			css.packageCS();
			break;
		case 0:
			exit(0);
		default:
			system("cls");
			cout << "Ошибка ввода\n";
			break;
		}
	}
	return 0;
}