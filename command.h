#include <stdlib.h>
#include <string>

class Command {
	int time;
	int oper2;
	int type;
	int num_stypen;
	int queue;
	std::string print_b;
public:
	Command(const Command& com);
	Command();
	Command(int time, int oper2, int type, int stypen, int queue, std::string print_b);
	~Command();
	void setTime(int time);
	void setOper2(int oper);
	void setType(int type);
	void setStypen(int stypen);
	void setQueue(int queue);
	void setPrint(std::string print_b);
	
	int getQueue() const;
	int getStypen() const;
	int getTime() const;
	int getOper2() const;
	int getType() const;
	std::string getPrint() const;

	void addTime(int time);
	void addPrint(std::string add);
	void printBeaut() const;
	void print_info() const;
	void create(double oper2, double type);
};
