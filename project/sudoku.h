#pragma once
class sudoku
{
private:
	int sudo[9][9];//������
	int temp[9];//���ڴ洢������ɵ�9������ͬ����
	bool result = false;//��ɱ�־
	void backtrack(int position);//���ݷ�
	bool Isright(int  position);//�ж��������Ƿ���Ϲ���
	void randomgenerate();//����9����ͬ����
public:
	sudoku();
	void init();//��1��5��9�ŷ��������������
	void display();//�������
	void sudoSolving();//������ȫ����
	void sudoWrite();//�����д���ļ�
	~sudoku();
};

