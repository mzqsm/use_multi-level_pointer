#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>
#include <inttypes.h>
#include <windows.h>
#include <string.h>

typedef struct player_info {
	char* name;
	int32_t ID;
	int32_t level;
}p_info;

void program_bar();

char* update_player_list(p_info** player_struction, p_info* update_player, int32_t* cur_num_player, int32_t new_num_player);

void print_list(p_info* player_struction, int32_t cur_player);

void free_space(p_info** player_struction, int32_t cur_player);

int main(void)
{
	errno = 0;

	program_bar();

	char* ret_check = NULL;

	p_info* player_struction = NULL;

	int32_t cur_player = 0;

	//create player1

	p_info* player1 = (p_info*)malloc(sizeof(p_info));

	if (player1 == NULL)
	{
		errno = ENOMEM;
		perror("Failed to allocate memory for player1's info!");

		return EXIT_FAILURE;
	}

	const char* p1_name = "frank";

	player1->name = (char*)malloc(strlen(p1_name) + 1);

	if (player1->name == NULL)
	{
		errno = ENOMEM;
		perror("Failed to allocate memory for player1's name!");

		free(player1);

		return EXIT_FAILURE;
	}

	errno_t if_copy_p1 = strcpy_s(player1->name, (rsize_t)strlen(p1_name) + 1, p1_name);

	if (if_copy_p1 != 0)
	{
		errno = EINVAL;
		perror("Failed to copy player1's name!");

		free(player1->name);
		free(player1);

		return EXIT_FAILURE;
	}

	player1->ID = 1;
	player1->level = 30;

	ret_check = update_player_list(&player_struction, player1, &cur_player, cur_player + 1);

	if (ret_check == NULL)
	{
		errno = ENOMEM;
		perror("the mistake happened while creating player1!");

		free(player1->name);
		free(player1);

		return EXIT_FAILURE;
	}

	// create player2

	p_info* player2 = (p_info*)malloc(sizeof(p_info));

	if (player2 == NULL)
	{
		errno = ENOMEM;
		perror("Failed to allocate memory for player2's info!");

		return EXIT_FAILURE;
	}

	const char* p2_name = "kevin";

	player2->name = (char*)malloc(strlen(p2_name) + 1);

	if (player2->name == NULL)
	{
		errno = ENOMEM;
		perror("Failed to allocate memory for player2's name!");

		free(player2);

		return EXIT_FAILURE;
	}

	errno_t if_copy_p2 = strcpy_s(player2->name, (rsize_t)strlen(p2_name) + 1, p2_name);

	if (if_copy_p2 != 0)
	{
		errno = EINVAL;
		perror("Failed to copy player2's name!");

		free(player2->name);
		free(player2);

		return EXIT_FAILURE;
	}

	player2->ID = 2;
	player2->level = 24;

	ret_check = update_player_list(&player_struction, player2, &cur_player, cur_player + 1);

	if (ret_check == NULL)
	{
		errno = ENOMEM;
		perror("the mistake happened while creating player2!");

		free(player2->name);
		free(player2);

		return EXIT_FAILURE;
	}

	//create player3

	p_info* player3 = (p_info*)malloc(sizeof(p_info));

	if (player3 == NULL)
	{
		errno = ENOMEM;
		perror("Failed to allocate memory for player3's info!");

		return EXIT_FAILURE;
	}

	const char* p3_name = "Niko";

	player3->name = (char*)malloc(strlen(p3_name) + 1);

	if (player3->name == NULL)
	{
		errno = ENOMEM;
		perror("Failed to allocated memory for player3's name!");

		free(player3);

		return EXIT_FAILURE;
	}

	errno_t if_copy_p3 = strcpy_s(player3->name, (rsize_t)strlen(p3_name) + 1, p3_name);

	if (if_copy_p3 != 0)
	{
		errno = EINVAL;
		perror("Failed to copy the player3's name!");

		free(player3->name);
		free(player3);

		return EXIT_FAILURE;
	}

	player3->ID = 3;
	player3->level = 66;

	ret_check = update_player_list(&player_struction, player3, &cur_player, cur_player + 1);

	if (ret_check == NULL)
	{
		errno = ENOMEM;
		perror("the mistake happened while creating player3!");

		free(player3->name);
		free(player3);

		return EXIT_FAILURE;
	}

	print_list(player_struction, cur_player);

	free_space(&player_struction, cur_player);

	return EXIT_SUCCESS;
}

void program_bar()
{
	puts("loading.....");

	const int32_t length = 100;

	for (int32_t i = 0; i <= length; i++)
	{
		printf("\r[");

		for (int32_t j = 0; j < i; j++)
		{
			printf("#");
		}

		for (int32_t j = length; j > i; j--)
		{
			printf(" ");
		}

		printf("]");

		printf(" (%d%%)", (i * 100) / 100);

		fflush(stdout);
		Sleep(10);
	}
	printf("\n");
}

char* update_player_list(p_info** player_struction, p_info* update_player, int32_t* cur_num_player, int32_t new_num_player)
{
	p_info* temp = realloc(*player_struction, new_num_player * sizeof(p_info));

	if (temp == NULL)
	{
		perror("Failed to allocate the memory for the player list!");
		return NULL;
	}

	(*player_struction) = temp;

	if ((*cur_num_player) < new_num_player)
	{
		(*player_struction)[*cur_num_player] = *update_player;// value copy.

		(*player_struction)[*cur_num_player].name = (char*)malloc(strlen(update_player->name) + 1);//to achieve deep copy.

		if ((*player_struction)[*cur_num_player].name == NULL) 
		{
			perror("Failed to allocate memory for name!");
			return NULL;
		}

		strcpy_s((*player_struction)[*cur_num_player].name, (rsize_t)(strlen(update_player->name) + 1), update_player->name);

		free(update_player->name);// player1,2,3'sname is useless in main function. 
		free(update_player); // player1,2,3 is useless in main function.

		(*cur_num_player) = new_num_player;

		return "Hello";
	}
	else
	{
		printf("Error!");
		return NULL;
	}
}

void print_list(p_info* player_struction, int32_t cur_player)
{
	puts("current player list :");

	for (int32_t i = 0; i < cur_player; i++)
	{
		printf("ID : %d  Name : %s  Level : %d\n", player_struction[i].ID, player_struction[i].name, player_struction[i].level);
	}
}

void free_space(p_info** player_struction, int32_t cur_player)
{
	for (int32_t i = 0; i < cur_player; i++)
	{
		if ((*player_struction)[i].name != NULL)
		{
			free((*player_struction)[i].name);
			(*player_struction)[i].name = NULL;
		}
	}
	free(*player_struction);
	*player_struction = NULL;
}