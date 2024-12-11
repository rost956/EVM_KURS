#include <iostream>
#include <Windows.h>
using namespace std;
#include <stdlib.h>
#include "command.h"


int next(Command* proverka, int colvo){
	int ret = 1;
	for (int x = 0; x < colvo; x++) {
		if (proverka[x].getStypen() < 5) {
			ret = 0;
		}
	}
	return ret;
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	double P1 = 0;
	double P2 = 0;
	int M;
	int N;
	int num;
	int time_1 = 0;
	cout << "������� ����������� ������������ ������� ��������� 2 �������� P1 (0.9, 0.8, 0.6): ";
	cin >> P1;
	cout << "������� ����� ������� � ������ N (2, 5, 10): ";
	cin >> N;
	cout << "������� ����������� ����, ��� ������� ������� ���� P2 (0.9, 0.7, 0.5): ";
	cin >> P2;
	cout << "������� ����� ���������� ���������� ��� ������ ������� ���� M (4, 8, 16): ";
	cin >> M;
	cout << "������� ���������� ������ � ��������: ";
	cin >> num;
	cout << P1 << N << P2 << M;
	for (int i = 0; i < 20; i++) {
		cout << rand() << endl;
	}
	Command* list;
	list = new Command[num];
	for (int i = 0; i < num; i++) {
		Command create;
		create.create(P1, P2);
		create.setQueue(i);
		list[i] = create;
	}
	for (int i = 0; i < num; i++) {
		list[i].print_info();
		cout << "------" << endl;
	}
	
	int flag_read = 0;
	int flag_1oper = 0;
	int flag_2oper = 0;
	int flag_result = 0;
	int flag_write = 0;
	int cont = 0;
	while (cont != 1) {
		cont = next(list, num);
		flag_read = 0;
		flag_1oper = 0;
		for (int i = 0; i < num; i++) {
			if (list[i].getQueue() != 0) {
				list[i].setQueue((list[i].getQueue()) - 1);
				continue;
			}
			else {
				if ((list[i].getStypen() == 0) && (flag_read == 0)) { //���� �� ������ ������ � ����������, � ������ ��� ��� ���
					list[i].setStypen(list[i].getStypen() + 1); //��������� �� ��������� �������
					list[i].addTime(1); //��������� ����� ����������
					flag_read = 1; //���������� ������ �� 1 ����
				}
				else if ((list[i].getStypen() == 0) && (flag_read != 0)){
					list[i].addTime(1);
				}


				else if ((list[i].getStypen() == 1) && (flag_1oper == 0)) { //���� �� ������ ������� ������� ��������
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(1);
					flag_1oper = 1;
				}
				else if ((list[i].getStypen() == 1) && (flag_1oper != 0)){
					list[i].addTime(1);
				}

				else if ((list[i].getStypen() == 2) && (flag_2oper == 0) && (list[i].getOper2() == 1)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(1);
					flag_2oper = 1;
				}

				else if ((list[i].getStypen() == 2) && (flag_2oper == 0) && (list[i].getOper2() == 2)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(N);
					list[i].setQueue(N-1);
					flag_2oper = N;
				}
				else if ((list[i].getStypen() == 2) && (flag_2oper != 0)) {
					list[i].addTime(1);
				}

				//������� ���������� ����������
				else if ((list[i].getStypen() == 3) && (flag_result == 0) && (list[i].getType() == 1)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(1);
					flag_result = 1;
				}

				else if ((list[i].getStypen() == 3) && (flag_result == 0) && (list[i].getType() == 2)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(M);
					list[i].setQueue(M-1);
					flag_result = M;
				}
				else if ((list[i].getStypen() == 3) && (flag_result != 0)) {
					list[i].addTime(1);
				}
				
				//������� ������
				else if ((list[i].getStypen() == 4) && (flag_write == 0) && (list[i].getOper2() == 1)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(1);
					flag_write = 1;
				}

				else if ((list[i].getStypen() == 4) && (flag_write == 0) && (list[i].getOper2() == 2)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(N);
					list[i].setQueue(N - 1);
					flag_write = N;
				}
				else if ((list[i].getStypen() == 4) && (flag_write != 0)) {
					list[i].addTime(1);
				}
				/*else { list[i].setStypen(list[i].getStypen() + 1); };*/
			}
		}
		if (flag_2oper > 0){ flag_2oper--; }
		if (flag_result > 0) { flag_result--; }
		if (flag_write > 0) { flag_write--; }
		
	}
	for (int i = 0; i < num; i++) {
		time_1 += list[i].getTime();
	}
	cout << "������� ����� ���������� �������: " << time_1 / num << endl;
	cout << "------" << endl;
	for (int i = 0; i < num; i++) {
		list[i].print_info();
		cout << "------" << endl;
	}
	return 0;
}