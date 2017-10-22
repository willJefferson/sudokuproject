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
	int i, j;
	//初始化数组
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
	int i, j = 0, k = 0;

	//填写1号方格
	randomgenerate();

	//学号尾数为79，则(7+9)%9+1=8；
	for(i = 0; i < 9; ++i)
	{
		if (temp[i] == 8)//第一位为8
			k = i;//记录为9的位置
	}
	if (k != 0)//如果第一位不是9
	{
		//交换位置
		int num = temp[0];
		temp[0] = 9;
		temp[k] = num;
	}

	k = 0;
	for (i=0; i < 3; i++)
	{
		for (j=0; j < 3; j++)
		{
			sudo[i][j] = temp[k++];
		}
	}
	//填写5号方格
	k = 0;
	randomgenerate();
	for (i = 3; i < 6; i++)
	{
		for (j = 3; j < 6; j++)
		{
			sudo[i][j] = temp[k++];
		}
	}
	//填写9号方格
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
	int row = position / 9;//行位置
	int col = position % 9;//列位置
	int i;
	//与同一行相比较
	for (i = 0; i < 9; i++)
	{
		if (i != col&&sudo[row][i] == sudo[row][col])
			return false;
	}
	//与同一列相比较
	for (i = 0; i < 9; i++)
	{
		if (i != row&&sudo[i][col] == sudo[row][col])
			return false;
	}
	//是否满足3*3小方格规则
	int temprow = row / 3 * 3;//所在小方格的第一行
	int tempcol = col / 3 * 3;//所在小方格的第一列
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
		//建立数独已完成
		result = true;
		return;
	}
	int row = position / 9;//行位置
	int col = position % 9;//列位置
	if (sudo[row][col] == 0)
	{
		for (int i = 1; i <=9; i++)
		{
			sudo[row][col] = i;//填数
			if (Isright(position))
			{
				
				backtrack(position+1);
				if (result)
					return;
				
			}
		}
		
		sudo[row][col] = 0;//回溯
	}
	else
	{
		//当前位置已填写，开始下一位置
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
void sudoku::display()
{
	int i, j;
	for (i = 0; i < 9; ++i)
	{
		for (j = 0; j < 9; ++j)
		{
			std::cout << sudo[i][j] << ' ';
		}
		std::cout << '\n';
	}
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
			std::cout << "数独棋盘个数为数字，请输入不为零的自然数" << std::endl;
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
				//a.sudoWrite(writer);
				a.display();
				if (N)
					std::cout << '\n';
					//writer << '\n';
			}
		}
	}
	else
		std::cout << "参数个数必须为3个！" << std::endl;
	return 0;
	
}