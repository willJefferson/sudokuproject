#pragma once
class sudoku
{
private:
	int sudo[9][9];//数独盘
	int temp[9];//用于存储随机生成的9个不相同的数
	bool result = false;//完成标志
	void backtrack(int position);//回溯法
	bool Isright(int  position);//判断所填数是否符合规则
	void randomgenerate();//产生9个不同的数
public:
	sudoku();
	void init();//在1，5，9号方格中填入随机数
	void display();//输出数独
	void sudoSolving();//生成完全数独
	void sudoWrite();//将结果写入文件
	~sudoku();
};

