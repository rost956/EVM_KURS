#include "command.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
Command::Command(const Command& com) {
	type = com.type;
	oper2 = com.oper2;
	time = 0;
	num_stypen = 0;
	queue = 0;
}

Command::Command() {
	this->time = 0;
	this->oper2 = 0;
	this->type = 0;
	this->num_stypen = 0;
	this->queue = 0;
}

Command::Command(int time, int oper2, int type, int stypen, int queue) {
	this->time = time;
	this->oper2 = oper2;
	this->type = type;
	this->num_stypen = stypen;
	this->queue = queue;
}

Command::~Command() {};

void Command::setTime(int time) {
	this->time = time;
}

void Command::setQueue(int queue) {
	this->queue = queue;
}

void Command::setOper2(int oper) {
	this->oper2 = oper;
}

void Command::setType(int type) {
	this->type = type;
}

void Command::setStypen(int stypen) {
	this->num_stypen = stypen;
}

int Command::getQueue() const {
	return this->queue;
}

int Command::getStypen() const {
	return this->num_stypen;
}

int Command::getOper2() const {
	return this->oper2;
}

int Command::getTime() const{
	return this->time;
}

int Command::getType() const {
	return this->type;
}

void Command::create(double P1, double P2) {
	if ((rand() % 100) < (P1 * 100)) {
		oper2 = 1;
	}
	else {
		oper2 = 2;
	}
	if ((rand() % 100) < (P2 * 100)) {
		type = 1;
	}
	else {
		type = 2;
	}
	time = 0;
	queue = 0;
	num_stypen = 0;
}

void Command::print_info() const{
	cout << "Адресация: " << oper2 << endl;
	cout << "Тип команды: " << type << endl;
	cout << "Время: " << time << endl;
	cout << "Номер ступени: " << num_stypen << endl;
	cout << "В очереди: " << queue << endl;
}

void Command::addTime(int time) {
	this->time += time;
}