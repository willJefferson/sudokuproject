#pragma once
#include<iostream>
class sudoku
{
private:
	char Buff[200];//������
	int sudo[9][9];//������
	int temp[9];//���ڴ洢������ɵ�9������ͬ����
	bool result = false;//��ɱ�־
	void backtrack(int position);//���ݷ�
	bool Isright(int  position);//�ж��������Ƿ���Ϲ���
	void randomgenerate();//����9����ͬ����
public:
	sudoku();
	void init();//��1��5��9�ŷ��������������
	void sudoSolving();//������ȫ����
	void sudoWrite(std::ostream& out);//�����д���ļ�
	~sudoku();
};

