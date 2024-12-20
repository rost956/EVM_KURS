#include <iostream>

using namespace std;
#include <stdlib.h>
#include "command.h"
#include <ctime>


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
	srand(time(0));
	double P1 = 0;
	double P2 = 0;
	int M;
	int N;
	int num;
	int ch = 0;
	int time_1 = 0;
	cout << "Enter the probability number of the register addressing method 2 of the operand P1 (1 - 0.9, 2 - 0.8, 3 - 0.6): ";
	cin >> ch;
	switch (ch) {
	case 1:
		P1 = 0.9;
		break;
	case 2:
		P1 = 0.8;
		break;
	case 3:
		P1 = 0.6;
		break;
	}

	cout << "Enter the probability number that the type 1 command is P2 (1 - 0.9, 2 - 0.7, 3 - 0.5): ";
	cin >> ch;
	switch (ch) {
	case 1:
		P2 = 0.9;
		break;
	case 2:
		P2 = 0.8;
		break;
	case 3:
		P2 = 0.6;
		break;
	}

	cout << "Enter the number of the memory access time 2 operands N (1 - 2, 2 - 5, 3 - 10): ";
	cin >> ch;
	switch (ch) {
	case 1:
		N = 2;
		break;
	case 2:
		N = 5;
		break;
	case 3:
		N = 10;
		break;
	}

	cout << "Enter the number of the result calculation time for commands of the second type M (1 - 4, 2 - 8, 3 - 16): ";
	cin >> ch;
	switch (ch) {
	case 1:
		M = 4;
		break;
	case 2:
		M = 8;
		break;
	case 3:
		M = 16;
		break;
	}

	cout << "Enter the number of commands in the pipeline: ";
	cin >> num;
	Command* list;
	list = new Command[num];
	for (int i = 0; i < num; i++) {
		Command create;
		create.create(P1, P2);
		create.setQueue(i);
		list[i] = create;
	}
	
	int flag_read = 0;
	int flag_1oper = 0;
	int flag_2oper = 0;
	int flag_result = 0;
	int flag_write = 0;
	int cont = 0;
	int flag_first = 0;
	while (cont != 1) {
		cont = next(list, num);
		
		flag_1oper = 0;
		for (int i = 0; i < num; i++) {
			
			if (list[i].getQueue() != 0) {
				
				if (flag_first == 0){
					for (int y = 0; y < num; y++) {
						for (int p = 0; p < list[y].getQueue(); p++) {
							list[y].addPrint(" ");
						}
					}
					flag_first = 1;
				}
				list[i].setQueue((list[i].getQueue()) - 1);
				continue;
			}
			else {
				if ((list[i].getStypen() == 0) && (flag_read == 0)) { 
					list[i].setStypen(list[i].getStypen() + 1); 
					list[i].addTime(1);
					list[i].addPrint("D");
					flag_read = 1; 
				}
				else if ((list[i].getStypen() == 0) && (flag_read != 0)){
					list[i].addTime(1);
					list[i].addPrint("");
				}


				else if ((list[i].getStypen() == 1) && (flag_1oper == 0)) { 
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(1);
					list[i].addPrint("1");
					flag_1oper = 1;
				}
				else if ((list[i].getStypen() == 1) && (flag_1oper != 0)){
					list[i].addTime(1);
					list[i].addPrint(" ");
				}

				else if ((list[i].getStypen() == 2) && (flag_2oper == 0) && (list[i].getOper2() == 1)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(1);
					list[i].addPrint("2");
					flag_2oper = 1;
				}

				else if ((list[i].getStypen() == 2) && (flag_2oper == 0) && (list[i].getOper2() == 2)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(N);
					list[i].setQueue(N-1);
					list[i].addPrint("");
					for (int w = 0; w < N/2; w++) {
						list[i].addPrint("-");
					}
					list[i].addPrint("2");
					for (int w = 0; w < (N - N / 2) - 1; w++) {
						list[i].addPrint("-");
					}
					list[i].addPrint("");
					flag_2oper = N;
				}
				else if ((list[i].getStypen() == 2) && (flag_2oper != 0)) {
					list[i].addTime(1);
					list[i].addPrint(" ");
				}

				//ступень вычисления результата
				else if ((list[i].getStypen() == 3) && (flag_result == 0) && (list[i].getType() == 1)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(1);
					list[i].addPrint("C");
					flag_result = 1;
				}

				else if ((list[i].getStypen() == 3) && (flag_result == 0) && (list[i].getType() == 2)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(M);
					list[i].setQueue(M-1);
					list[i].addPrint("");
					for (int w = 0; w < M / 2; w++) {
						list[i].addPrint("-");
					}
					list[i].addPrint("C");
					for (int w = 0; w < (M - M / 2) - 1; w++) {
						list[i].addPrint("-");
					}
					list[i].addPrint("");
					flag_result = M;
				}
				else if ((list[i].getStypen() == 3) && (flag_result != 0)) {
					list[i].addTime(1);
					list[i].addPrint(" ");
				}
				
				//Ступень записи
				else if ((list[i].getStypen() == 4) && (flag_2oper == 0) && (list[i].getOper2() == 1)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(1);
					list[i].addPrint("W");
					flag_2oper = 1;
				}

				else if ((list[i].getStypen() == 4) && (flag_2oper == 0) && (list[i].getOper2() == 2)) {
					list[i].setStypen(list[i].getStypen() + 1);
					list[i].addTime(N);
					list[i].setQueue(N - 1);
					list[i].addPrint("");
					for (int w = 0; w < N / 2; w++) {
						list[i].addPrint("-");
					}
					list[i].addPrint("W");
					for (int w = 0; w < (N - N / 2) - 1; w++) {
						list[i].addPrint("-");
					}
					list[i].addPrint("");
					flag_2oper = N;
				}
				else if ((list[i].getStypen() == 4) && (flag_2oper != 0)) {
					list[i].addTime(1);
					list[i].addPrint(" ");
				}

			}
		}
		if (flag_2oper > 0){ flag_2oper--; }
		if (flag_result > 0) { flag_result--;}
		if (flag_read > 0) { flag_read--; }
		flag_first = 1;
		
	}
	for (int i = 0; i < num; i++) {
		time_1 += list[i].getTime();
	}
	
	cout << "------" << endl;
	for (int i = 0; i < num; i++) {
		list[i].print_info();
		cout << "------" << endl;
	}
	for (int i = 0; i < num; i++) {
		list[i].printBeaut();
	}
	cout << "Average command execution time: " << time_1 / num << endl;
	return 0;
}