#include<stdio.h>

int check();
void board();

int box[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int main()
{
	int player = 1, i, select;
	char mark;
	
	do{
	board();
	
	player = (player % 2)? 1: 2;
	mark = (player ==1)? 'X': 'O';
	
	printf("player %d please ", player);
	printf("enter the box no. : ");
	scanf("%d", &select);
	
	if (select == 1 && box[1] == '1')
		box[1] = mark;
	else if (select == 2 && box[2] == '2')
		box[2] = mark;
	else if (select == 3 && box[3] == '3')
		box[3] = mark;	
	else if (select == 4 && box[4] == '4')
		box[4] = mark;	
	else if (select == 5 && box[5] == '5')
		box[5] = mark;	
	else if (select == 6 && box[6] == '6')
		box[6] = mark;	
	else if (select == 7 && box[7] == '7')
		box[7] = mark;	
	else if (select == 8 && box[8] == '8')
		box[8] = mark;	
	else if (select == 9 && box[9] == '9')
		box[9] = mark;
	else 
	{
		player--;
		printf("X===============X\n");
		printf("invaild choice\n");
		printf("X===============X\n");
		printf("\n\nPlease enter correct choice as per box no.\n\n\n");
	}
	
	i = check();
	
	player++;
	//printf("player %d\n", player);
			
	}while (i == -1);
	
	board();
	
	if (i == 1)
	{
		printf("***************************\n");
		printf("PLAYER %d WON\n", --player);
		printf("***************************\n");
	}
	else
	{
		printf("###########################\n");
		printf("MATCH DRAWN\n");
		printf("###########################\n");
	}
}

int check()
{
	if (box[1] == box[2] && box[2] == box[3])
		return 1;
	else if (box[4] == box[5] && box[5] == box[6])
		return 1;
	else if (box[7] == box[8] && box[8] == box[9])
		return 1;
	else if (box[1] == box[4] && box[4] == box[7])
		return 1;
	else if (box[2] == box[5] && box[5] == box[8])
		return 1;
	else if (box[3] == box[6] && box[6] == box[9])
		return 1;
	else if (box[1] == box[5] && box[5] == box[9])
		return 1;
	else if (box[3] == box[5] && box[5] == box[7])
		return 1;
	else if(box[1] != '1' && box[2] != '2' && box[3] != '3' && box[4] != '4' && box[5] != '5' && box[6] != '6' && box[7] != '7' && box[8] != '8' && box[9] != '9')
		return 0;
	else 
		return -1;
}

void board()
{
	printf("\n\ntic tac toe\n\n");
	printf("Player1 = 'X' & Player2 = 'O'\n\n\n");
	
	printf("\t\t   |   |   \n");
	printf("\t\t %c | %c | %c\n", box[1], box[2], box[3]);
	printf("\t\t___|___|___\n");
	printf("\t\t   |   |  \n");
	printf("\t\t %c | %c | %c\n", box[4], box[5], box[6]);
	printf("\t\t___|___|___\n");
	printf("\t\t   |   |  \n");
	printf("\t\t %c | %c | %c\n", box[7], box[8], box[9]);
	printf("\t\t   |   |  \n\n");
}
