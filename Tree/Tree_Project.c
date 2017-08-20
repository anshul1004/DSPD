#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define NAME_SIZE 30
#define DEP_SIZE 10
#define ADDR_SIZE 20
//----------------------------------------------------------------------------------
typedef struct Tree_tag
{
	int roll_no;
	char name[NAME_SIZE];
	char dep[DEP_SIZE];
	int sem;
	char addr[ADDR_SIZE];
	struct Tree_tag *left;
	struct Tree_tag *right;
}Tree;
//----------------------------------------------------------------------------------
void *clearTree(Tree *root)
{
	if(root != NULL)
	{
		clearTree(root->left);
		clearTree(root->right);
		free(root);
	}
}
//----------------------------------------------------------------------------------
int max(int a, int b)
{
	if(a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
//----------------------------------------------------------------------------------
int height(Tree *root, int flag)
{
	int ret_val;
	if(root == NULL)
	{
		ret_val = -1;
	}
	else if((root->left == NULL) && (root->right == NULL))
	{
		ret_val = 0;
	}
	else
	{
		int left_ht, right_ht;
		left_ht = height(root->left, 0);
		right_ht = height(root->right, 0);
		if(flag == 0)
		{
			ret_val = 1+ max(left_ht, right_ht);
		}
		else
		{
			ret_val = left_ht - right_ht;
		}
	}
	return ret_val;
}
//----------------------------------------------------------------------------------
void printBF(int val)
{
	if(val == -2)
	{
		printf("\\\\");
	}
	else if(val == -1)
	{
		printf("\\");
	}
	else if(val == 0)
	{
		printf("-");
	}
	else if(val == 1)
	{
		printf("/");
	}
	else
	{
		printf("//");
	}
}
//----------------------------------------------------------------------------------
void PrintDatabase(Tree *root)
{
	int ret_val;
	if(root != NULL)
	{
		PrintDatabase(root->left);
		ret_val = height(root, 1);
		printf("%-4d \t     %-8s \t %-8s \t %-8d \t %-8s \t", root->roll_no, root->name, root->dep, root->sem, root->addr);
		printBF(ret_val);
		printf("\n");
		PrintDatabase(root->right);
	}
}
//----------------------------------------------------------------------------------
Tree *createNode()
{
	Tree *new_node;
	new_node = (Tree*)malloc(sizeof(Tree));
	printf("Roll No.: ");
	scanf("%d", &new_node->roll_no);
	printf("Name: ");
	scanf("%s", &new_node->name);
	printf("Department: ");
	scanf("%s", &new_node->dep);
	printf("Semester: ");
	scanf("%d", &new_node->sem);
	printf("Local Address: ");
	scanf("%s", &new_node->addr);
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}
//----------------------------------------------------------------------------------
Tree *rotate(Tree *p, int flag)
{
	Tree *ret_val = p;
	if(p != NULL)
	{
		Tree *temp;
		if(flag == 0)
		{
			temp = p->right;
			p->right = temp->left;
			temp->left = p;
		}
		else
		{
			temp = p->left;
			p->left = temp->right;
			temp->right = p;
		}
		ret_val = temp;
	}
	return ret_val;
}
//----------------------------------------------------------------------------------
Tree *insertAVL(Tree *root, Tree *node)
{
	if(root != NULL)
	{
		if((node->roll_no) < (root->roll_no))
		{
			root->left = insertAVL(root->left, node);
			if(height(root, 1) == 2)
			{
				if((node->roll_no) < ((root->left)->roll_no))
				{
					root = rotate(root, 1);
				}
				else
				{
					root->left = rotate(root->left, 0);
					root = rotate(root, 1);
				}
			}
		}
		else if((node->roll_no) > (root->roll_no))
		{
			root->right = insertAVL(root->right, node);
			if(height(root, 1) == -2)
			{
				if((node->roll_no) > ((root->right)->roll_no))
				{
					root = rotate(root, 0);
				}
				else
				{
					root->right = rotate(root->right, 1);
					root = rotate(root, 0);
				}
			}
		}
		else
		{
			char choice[4];
			printf("Entry with a smiliar key found. Do you want to update the entry: yes or no\n");
			scanf("%s", choice);
			if(strcmp(choice, "yes") == 0)
			{
				strcpy(root->name, node->name);
				strcpy(root->dep, node->dep);
				root->sem = node->sem;
				strcpy(root->addr, node->addr);
				printf("Successfully updated the entry\n");
			}
			else
			{
				printf("Failed to update the entry\n");
			}
		}
	}
	else
	{
		root = node;
		node->left = node->right = NULL;
	}
	return root;
}
//----------------------------------------------------------------------------------
Tree *insert(Tree *root)
{
	int n, i=0;
	Tree *node;
	printf("How many entries to insert: ");
	scanf("%d", &n);
	for(i=0;i<n;i++)
	{
		printf("ENTRY %d\n", i+1);
		node = createNode();
		if(root == NULL)
		{
			root = node;
		}
		else
		{
			root = insertAVL(root, node);
		}
	}
	if(root == NULL)
	{
		printf("Failed to insert entry(s)\n");
	}
	else
	{
		printf("Successfully inserted entry(s)\n");
	}
	return root;
}
//----------------------------------------------------------------------------------
Tree *Delete(Tree *root, int roll)
{
	Tree *ptr;
	if(root == NULL)
	{
		printf("Failed to delete entry(Entry not present)\n");
		return NULL;
	}
	else
	{
		if(roll < root->roll_no)
		{
			root->left = Delete(root->left, roll);
			if(height(root, 1) == -2)
			{
				if(height(root->right, 1) <= 0)
				{
					root = rotate(root, 0);
				}
				else
				{
					root->right = rotate(root->right, 1);
					root = rotate(root, 0);
				}
			}
		}
		else if(roll > root->roll_no)
		{
			root->right = Delete(root->right, roll);
			if(height(root, 1) == 2)
			{
				if(height(root->left, 1) >= 0)
				{
					root = rotate(root, 1);
				}
				else
				{
					root->left = rotate(root->left, 0);
					root = rotate(root, 1);
				}
			}
		}
		else
		{
			if(root->right != NULL)
			{
				ptr = root->right;
				while(ptr->left != NULL)
				{
					ptr = ptr->left;
				}
				root->roll_no = ptr->roll_no;
				strcpy(root->name, ptr->name);
				strcpy(root->dep, ptr->dep);
				root->sem = ptr->sem;
				strcpy(root->addr, ptr->addr);
				root->right = Delete(root->right, ptr->roll_no);
				if(height(root, 1) == 2)
				{
					if(height(root->left, 1) >= 0)
					{
						root = rotate(root, 1);
					}
					else
					{
						root->left = rotate(root->left, 0);
						root = rotate(root, 1);
					}
				}
				printf("Successfully deleted entry\n");
			}
			else
			{
				printf("Successfully deleted entry\n");
				return(root->left);
			}
		}
	}
	return root;
}
//----------------------------------------------------------------------------------
void *Search(Tree *root, int roll)
{
	Tree *ptr = root;
	while((ptr != NULL) && (roll != ptr->roll_no))
	{
		if(roll < ptr->roll_no)
		{
			ptr = ptr->left;
		}
		else
		{
			ptr = ptr->right;
		}
	}
	if((ptr != NULL) && (roll == ptr->roll_no))
	{
		printf("Roll Number  Name \t Department \t Semester \t Address\n--------------------------------------------------------------------------------\n");
		printf("%-4d \t     %-8s \t %-8s \t %-8d \t %-8s \t\n", ptr->roll_no, ptr->name, ptr->dep, ptr->sem, ptr->addr);
	}
	else
	{
		printf("Entry not found\n");
	}
}
//----------------------------------------------------------------------------------
int getNumRecords(Tree *root)
{
	int ret_val;
	if(root != NULL)
	{
		ret_val = 1 + getNumRecords(root->left) + getNumRecords(root->right);
	}
	else
	{
		ret_val = 0;
	}
	return ret_val;
}
//----------------------------------------------------------------------------------
void Range_search(Tree *root, int key1, int key2)
{
	if(key1 > key2)
	{
		int temp;
		temp = key2;
		key2 = key1;
		key1 = temp;
	}
	if(root != NULL)
	{
		if(key1 < root->roll_no)
		{
			Range_search(root->left, key1, key2);
		}
		if((key1 <= root->roll_no) && (key2 >= root->roll_no))
		{
			printf("%-4d \t     %-8s \t %-8s \t %-8d \t %-8s \t\n", root->roll_no, root->name, root->dep, root->sem, root->addr);
		}
		if(key2 > root->roll_no)
		{
			Range_search(root->right, key1, key2);
		}
	}
}
//----------------------------------------------------------------------------------
Tree *createTreeUsingFiles(FILE *fp, Tree *root)
{
	while(!feof(fp))
	{
		Tree *new_node;
		new_node = (Tree*)malloc(sizeof(Tree));
		new_node->left = NULL;
		new_node->right = NULL;
		fscanf(fp, "%d %s %s %d %s", &new_node->roll_no, &new_node->name, &new_node->dep, &new_node->sem, &new_node->addr);
		if(root == NULL)
		{
			root = new_node;
		}
		else
		{
			root = insertAVL(root, new_node);
		}
	}
	return root;
}
//----------------------------------------------------------------------------------          
main()
{
	Tree *root = NULL;
	FILE *fp;
	int num, num2;
	char choice[DEP_SIZE], bool_choice[4];
	printf("********************************************************************************\n");
	printf("                         STUDENT DATABASE RECORD                                \n");
	printf("********************************************************************************\n");
	printf("Do you want to copy entries from file: yes or no\n");
	scanf("%s", bool_choice);
	if(strcmp(bool_choice, "yes") == 0)
	{
		fp = fopen("file.txt", "r");
		root = createTreeUsingFiles(fp, root);
		fclose(fp);
		printf("Successfully copied entries\n");
	}
	do
	{
		printf("********************************************************************************\n");
		printf("WELCOME TO MAIN MENU!\n");
		printf("Use '_'(underscore) instead of ''(space) wherever necessary\n");
		printf("Press the appropriate key as mentioned\n");
		printf("(1)  or (insert)    : Insert/Update entries\n");
		printf("(2)  or (delete)    : Delete an entry\n");
		printf("(3)  or (search)    : Search for an entry\n");
		printf("(4)  or (active)    : Get number of active records\n");
		printf("(5)  or (height)    : Find height of the tree\n");
		printf("(6)  or (range)     : Search for entries in the provided range\n");
		printf("(7)  or (disp)      : Display the entries\n");
		printf("(8)  or (clear)     : Clear the whole tree\n");
		printf("(0)  or (exit)      : Exit\n");
		printf("********************************************************************************\n");
		scanf("%s", choice);
		if((strcmp(choice, "1") == 0) || (strcmp(choice, "insert") == 0))
		{
			root = insert(root);
		}
		else if((strcmp(choice, "2") == 0) || (strcmp(choice, "delete") == 0))
		{
			printf("Enter the roll number to be deleted\n");
			scanf("%d", &num);
			root = Delete(root, num);
		}
		else if((strcmp(choice, "3") == 0) || (strcmp(choice, "search") == 0))
		{
			printf("Enter the roll number to be searched\n");
			scanf("%d", &num);
			Search(root, num);
		}
		else if((strcmp(choice, "4") == 0) || (strcmp(choice, "active") == 0))
		{
			num = getNumRecords(root);
			printf("Number of active records present : %d\n", num);
		}
		else if((strcmp(choice, "5") == 0) || (strcmp(choice, "height") == 0))
		{
			num = height(root, 0);
			printf("Height of the tree : %d\n", num);
		}
		else if((strcmp(choice, "6") == 0) || (strcmp(choice, "range") == 0))
		{
			printf("Enter key 1\n");
			scanf("%d", &num);
			printf("Enter key 2\n");
			scanf("%d", &num2);
			printf("Roll Number  Name \t Department \t Semester \t Address\n--------------------------------------------------------------------------------\n");
			Range_search(root, num, num2);
		}
		else if((strcmp(choice, "7") == 0) || (strcmp(choice, "disp") == 0))
		{
			printf("Roll Number  Name \t Department \t Semester \t Address   Bal. Factor\n--------------------------------------------------------------------------------\n");
			PrintDatabase(root);
		}
		else if((strcmp(choice, "8") == 0) || (strcmp(choice, "clear") == 0))
		{
			clearTree(root);
			root = NULL;
		}
	}while((strcmp(choice, "0") != 0) && (strcmp(choice, "exit") !=0));
	clearTree(root);
	printf("END OF PROGRAM \n");
	getch();
}
