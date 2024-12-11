
class Command {
	int time;
	int oper2;
	int type;
	int num_stypen;
	int queue;
public:
	Command(const Command& com);
	Command();
	Command(int time, int oper2, int type, int stypen, int queue);
	~Command();
	void setTime(int time);
	void setOper2(int oper);
	void setType(int type);
	void setStypen(int stypen);
	void setQueue(int queue);

	int getQueue() const;
	int getStypen() const;
	int getTime() const;
	int getOper2() const;
	int getType() const;

	void addTime(int time);

	void print_info() const;
	void create(double oper2, double type);
};
