#include "sudoku.h"
#include<iostream>
#include<fstream>
sudoku::sudoku()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			sudo[i][j] = 0;
	}
}
void sudoku::randomgenerate()
{
	int i,j;
	//��ʼ������
	for (i = 0; i < 9; i++)
		temp[i] = 0;
	for (i = 0; i < 9; i++)
	{
		temp[i] = rand() % 9 + 1;
		for (j = 0; j < i; j++)
		{
			if (temp[i] == temp[j])
			{
				--i;
				break;
			}
		}
	}

}
void sudoku::init()
{
	int i , j=0 ,k=0;
	
	//��д1�ŷ���
	randomgenerate();
	for (i=0; i < 3; i++)
	{
		for (j=0; j < 3; j++)
		{
			sudo[i][j] = temp[k++];
		}
	}
	//��д5�ŷ���
	k = 0;
	randomgenerate();
	for (i = 3; i < 6; i++)
	{
		for (j = 3; j < 6; j++)
		{
			sudo[i][j] = temp[k++];
		}
	}
	//��д9�ŷ���
	k = 0;
	randomgenerate();
	for (i = 6; i < 9; i++)
	{
		for (j = 6; j < 9; j++)
		{
			sudo[i][j] = temp[k++];
		}
	}

}


bool sudoku::Isright(int position)
{
	int row = position / 9;//��λ��
	int col = position % 9;//��λ��
	int i;
	//��ͬһ����Ƚ�
	for (i = 0; i < 9; i++)
	{
		if (i != col&&sudo[row][i] == sudo[row][col])
			return false;
	}
	//��ͬһ����Ƚ�
	for (i = 0; i < 9; i++)
	{
		if (i != row&&sudo[i][col] == sudo[row][col])
			return false;
	}
	//�Ƿ�����3*3С�������
	int temprow = row / 3 * 3;//����С����ĵ�һ��
	int tempcol = col / 3 * 3;//����С����ĵ�һ��
	for (i = temprow; i < temprow + 3; i++)
	{
		for (int j = tempcol; j < tempcol + 3; j++)
		{
			if (sudo[i][j] == sudo[row][col] && i != row&&j != col)
				return false;
		}
	}
	return true;

}
void sudoku::backtrack(int position)
{
	if (position ==81)
	{
		//�������������
		result = true;
		return;
	}
	int row = position / 9;//��λ��
	int col = position % 9;//��λ��
	if (sudo[row][col] == 0)
	{
		for (int i = 1; i <=9; i++)
		{
			sudo[row][col] = i;//����
			if (Isright(position))
			{
				
				backtrack(position+1);
				if (result)
					return;
				
			}
		}
		
		sudo[row][col] = 0;//����
	}
	else
	{
		//��ǰλ������д����ʼ��һλ��
		backtrack(position+1);
	}
}
void sudoku::sudoSolving()
{
	backtrack(0);
}
void sudoku::sudoWrite(std::ostream& out)
{
	int k = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Buff[k++] = sudo[i][j] + '0';
			Buff[k++] = ' ';
		}
		Buff[k++] = '\n';
	}
	Buff[k] = '\0';
	out << Buff ;
}
	
sudoku::~sudoku()
{
}
int main(int agrc, char*agrv[])
{
	int N=0;
	if (agrc == 3)
	{
		N = atoi(agrv[2]);
		if (N == 0)
		{
			std::cout << "�������̸���Ϊ���֣������벻Ϊ�����Ȼ��" << std::endl;
			return 0;
		}
		else
		{
			std::ofstream writer;
			writer.open("sudoku.txt", std::ios::out | std::ios::app);
			if (!writer.is_open())
			{
				return -1;
			}
			while (N-- > 0)
			{
				sudoku a;
				a.init();
				a.sudoSolving();
				a.sudoWrite(writer);
				if (N)
					writer << '\n';
			}
		}
	}
	else
		std::cout << "������������Ϊ3����" << std::endl;
	return 0;

}