#include<stdio.h>
#include<string.h>
#define CLASS_SIZE 4
#define SUBJ_SIZE 10
#define NAME_SIZE 50
struct student_database
{
	unsigned int roll_number;
	char subject_code[SUBJ_SIZE];
	char student_name[NAME_SIZE]; 
	unsigned int marks;
};
struct student_database list1[CLASS_SIZE];
struct student_database list2[CLASS_SIZE];
struct student_database list3[2*CLASS_SIZE];
struct student_database maxmarks[CLASS_SIZE];
/*---------------------------------------------------------------------INITIALISE------------------------------------------------------------------------------*/
void initialise(struct student_database list[], int n)
{
	int i;
	for( i=0 ; i<n ; i++ )
	{
		list[i].roll_number = 0;
		strcpy (list[i].student_name, "\0");
		strcpy (list[i].subject_code, "\0");
		list[i].marks = -1;
	}
}
/*---------------------------------------------------------------------PRINT-----------------------------------------------------------------------------------*/
void print(struct student_database list[], int n, int total_entries)
{
	int i;
	printf("Roll Number \t Subject Code \t\t Name \t\t\t Marks\n--------------------------------------------------------------------------------\n");
	for( i=0 ; i<total_entries ; i++ )
	{
		printf("%-4d \t\t %-8s \t\t %-8s \t\t %-8d\n", list[i].roll_number, list[i].subject_code, list[i].student_name, list[i].marks);
	}
	if(total_entries>0)
	{
		printf("Successfully displayed all the records\n");
	}
	else
	{
		printf("No entry present in this list\n");
	}
}
/*---------------------------------------------------------------------STRSWAP--------------------------------------------------------------------------------*/
void strswap(char a[], char b[])
{
	char temp[NAME_SIZE];
	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
}
/*---------------------------------------------------------------------SORT------------------------------------------------------------------------------------*/
void sort(struct student_database list[], int n, int total_entries)
{
	int i,j,temp;
	for( i=0 ; i<total_entries ; i++ )  
	{
		for( j=0 ; j<total_entries-1-i ; j++ )
		{
			if(list[j].roll_number == list[j+1].roll_number)
			{
				if(strcmp (list[j].subject_code, list[j+1].subject_code) > 0)
				{
					strswap(list[j].subject_code, list[j+1].subject_code);
					strswap(list[j].student_name, list[j+1].student_name);
					temp = list[j].marks;
					list[j].marks = list[j+1].marks;
					list[j+1].marks = temp;
				}
			}
			else if(list[j].roll_number > list[j+1].roll_number)
			{
				temp = list[j].roll_number;
				list[j].roll_number = list[j+1].roll_number;
				list[j+1].roll_number = temp;
				strswap(list[j].subject_code, list[j+1].subject_code);
				strswap(list[j].student_name, list[j+1].student_name);
				temp = list[j].marks;
				list[j].marks = list[j+1].marks;
				list[j+1].marks = temp;	
			}
		}
	}
}
/*---------------------------------------------------------------------INSERT----------------------------------------------------------------------------------*/
int insert(struct student_database list[], int n, int total_entries)
{
	int i, j, num_entries, new_entries, free_index, found;
	unsigned int temp_roll_number, temp_marks;
	char temp_student_name[NAME_SIZE], temp_subject_code[SUBJ_SIZE];
	new_entries = 0;
	printf("Enter number of entries you want to enter\n");
	scanf("%d", &num_entries);  
	for( i=0 ; (i<num_entries) && (i<n); i++ )
	{
		free_index=0;
		found=0;
		j=0;
		printf("Student Database for student %d\n", i+1);
		printf("Roll Number : ");
		scanf("%d", &temp_roll_number);
		printf("Subject Code : ");
		scanf("%s", &temp_subject_code);
		printf("Name : ");
		scanf("%s", &temp_student_name);
		printf("Marks : ");
		scanf("%d", &temp_marks);
		while((j<n) && (found == 0))
		{
			if((list[j].roll_number == temp_roll_number) && (strcmp (list[j].subject_code, temp_subject_code) == 0))
			{
				found = 1;
			}
			else
			{
				j++;
			}
		}
		if(found == 1)
		{
			strcpy (list[j].student_name, temp_student_name);
			list[j].marks = temp_marks;
			printf("Successfully updated entry for student %d\n", i+1);
		}
		else
		{
			j=0;
			while((j < n) && (free_index == 0))
			{
				if(list[j].roll_number == 0)
				{
					free_index = 1;
				}
				else
				{
					j++;
				}
			}
			if(free_index==0)
			{
				printf("Failed to add entry for student %d\n", i+1);
			}
			else
			{
				list[j].roll_number=temp_roll_number;
				strcpy (list[j].student_name, temp_student_name);
				strcpy (list[j].subject_code, temp_subject_code);
				list[j].marks=temp_marks;
				printf("Successfully added entry for student %d\n", i+1);
				new_entries++;
			}
		}
	}
	if(num_entries>n)
	{
		printf("Failed to insert all the entries(class size reached)\n");
	}
	printf("Finished insertion operation\n");
	total_entries = total_entries + new_entries;
	sort(list, n, total_entries);
	return new_entries;
}
/*---------------------------------------------------------------------DEL-------------------------------------------------------------------------------------*/
int del(struct student_database list[], int n, int total_entries)
{
	int i, j, temp, flag;
	unsigned int temp_roll_number;
	char temp_subject_code[SUBJ_SIZE];
	flag=0;
	printf("Enter roll number & subject code to delete that entry\n");
	printf("Enter roll number : ");
	scanf("%d", &temp_roll_number);
	printf("Enter subject_code : ");
	scanf("%s", &temp_subject_code);
	for( i=0 ; (i<total_entries) && (flag == 0); i++ )
	{
		if((list[i].roll_number == temp_roll_number) && (strcmp (list[i].subject_code, temp_subject_code) == 0))
		{
			list[i].roll_number = 0;
			strcpy (list[i].student_name, "\0");
			strcpy (list[i].subject_code, "\0");
			list[i].marks = -1;	
			for( j=i ; j<total_entries-1 ; j++ )
			{
				temp = list[j].roll_number;
				list[j].roll_number = list[j+1].roll_number;
				list[j+1].roll_number = temp;
				strswap(list[j].subject_code, list[j+1].subject_code);
				strswap(list[j].student_name, list[j+1].student_name);
				temp = list[j].marks;
				list[j].marks = list[j+1].marks;
				list[j+1].marks = temp;	
			}
			total_entries--;
			flag=1;
		}
	}
	if(flag == 1)
	{
		printf("Successfully deleted the entry\n");
	}
	else
	{
		printf("Failed to delete the entry(Entry not present)\n");
	}
	return total_entries;
}
/*---------------------------------------------------------------------GETNUMRECORDS---------------------------------------------------------------------------*/
void getNumRecords(struct student_database list[], int n, int total_entries)
{
	printf("Number of active records present : %d", total_entries);
}
/*---------------------------------------------------------------------ISEMPTY---------------------------------------------------------------------------*/
void isEmpty(struct student_database list[], int n, int total_entries)
{
	if(total_entries == 0)
	{
		printf("The list is empty\n");
	}
	else
	{
		printf("The list is not empty\n");
	}
}
/*---------------------------------------------------------------------ISFULL---------------------------------------------------------------------------*/
void isFull(struct student_database list[], int n, int total_entries)
{
	if(total_entries == n)
	{
		printf("The list is fully occupied\n");
	}
	else
	{
		printf("The list is not fully occupied\n");
	}
}
/*---------------------------------------------------------------------GETMAXMARKS-----------------------------------------------------------------------------*/
void getMaxMarks(struct student_database list[], int n, int total_entries)
{
	int i, j, max, count;
	char temp_subject_code[SUBJ_SIZE];
	max=0;
	j=0;
	count=0;
	printf("Enter the subject code for which you want to find the maximum marks\n");
	scanf("%s", &temp_subject_code);
	for(i=0;(i<total_entries) && (i<n);i++)
	{
		if(strcmp (list[i].subject_code, temp_subject_code) == 0)
		{
			if(list[i].marks > max)
			{
				max = list[i].marks;
				initialise(maxmarks, n);
				j=0;
				count=0;
				maxmarks[j].marks = max;
				maxmarks[j].roll_number = list[i].roll_number;
				strcpy (maxmarks[j].subject_code, list[i].subject_code);
				strcpy (maxmarks[j].student_name, list[i].student_name);
				count=1;
			}
			else if(list[i].marks == max)
			{
				maxmarks[++j].marks = max;
				maxmarks[j].roll_number = list[i].roll_number;
				strcpy (maxmarks[j].subject_code, list[i].subject_code);
				strcpy (maxmarks[j].student_name, list[i].student_name);
				count++;
			}	
		}
	}
	printf("Student(s) with highest marks are : \n");
	print(maxmarks, n, count);
}
/*---------------------------------------------------------------------ADD_DUPLICATES--------------------------------------------------------------------------*/
int add_duplicates(struct student_database list[], int n, int total_entries)
{
	int i, num_entries;
	unsigned int temp_roll_number, temp_marks;
	char temp_student_name[NAME_SIZE], temp_subject_code[SUBJ_SIZE];
	printf("Enter number of entries you want to enter\n");
	scanf("%d", &num_entries);  
	for(i=0;(i<num_entries) && (total_entries<n);i++)
	{
		printf("Student Database for student %d\n", i+1);
		printf("Roll Number : ");
		scanf("%d", &temp_roll_number);
		printf("Subject Code : ");
		scanf("%s", &temp_subject_code);
		printf("Name : ");
		scanf("%s", &temp_student_name);
		printf("Marks : ");
		scanf("%d", &temp_marks);
		list[total_entries].roll_number=temp_roll_number;
		strcpy (list[total_entries].student_name, temp_student_name);
		strcpy (list[total_entries].subject_code, temp_subject_code);
		list[total_entries].marks=temp_marks;
		printf("Successfully added entry for student %d\n", i+1);
		total_entries++;
	}
	if(total_entries>=n)
	{
		printf("Failed to insert all the entries(class size reached)\n");
	}
	sort(list, n, total_entries);
	return total_entries;
}
/*---------------------------------------------------------------------LIST_UNIQUE-----------------------------------------------------------------------------*/
int list_unique(struct student_database list[], int n, int total_entries)
{
	int i, j, k, temp;
	for(i=0;(i<total_entries) && (i<n);i++)
	{
		for(j=i+1;(j<total_entries) && (i<n);j++)
		{
			if((list[i].roll_number == list[j].roll_number) && (strcmp (list[i].subject_code, list[j].subject_code) == 0))
			{
				list[j].roll_number = 0;
				strcpy (list[j].student_name, "\0");
				strcpy (list[j].subject_code, "\0");
				list[j].marks = -1;	
				for( k=j ; k<total_entries-1 ; k++ )
				{
					temp = list[k].roll_number;
					list[k].roll_number = list[k+1].roll_number;
					list[k+1].roll_number = temp;
					strswap(list[k].subject_code, list[k+1].subject_code);
					strswap(list[k].student_name, list[k+1].student_name);
					temp = list[k].marks;
					list[k].marks = list[k+1].marks;
					list[k+1].marks = temp;	
				}
				total_entries--;
				j--;
			}
		}
	}
	printf("Successfuly deleted all duplicate entries(if present)\n");
	return total_entries;
}
/*---------------------------------------------------------------------LIST_OPERATION--------------------------------------------------------------------------*/
int list_operation(struct student_database list_a[], struct student_database list_b[], int n, int total_entries_a, int total_entries_b, int k, int found_val)
{
	int i, j, found;
	for(i=0;(i<total_entries_a) && (i<2*n);i++)
	{
		found=0;
		for(j=0;(j<total_entries_b) && (found==0) && (j<2*n);j++)
		{
			if((list_a[i].roll_number == list_b[j].roll_number) && (strcmp (list_a[i].subject_code, list_b[j].subject_code) == 0))
			{
				found=1;
			}
		}
		if(found == found_val)
		{
			list3[k].roll_number = list_a[i].roll_number;
			strcpy (list3[k].subject_code, list_a[i].subject_code);
			strcpy (list3[k].student_name, list_a[i].student_name);
			list3[k].marks = list_a[i].marks;
			k++;	
		}
	}
	return k;
}
/*---------------------------------------------------------------------LIST_UNION------------------------------------------------------------------------------*/
int list_union(struct student_database list1[], struct student_database list2[], int n, int total_entries1, int total_entries2)
{
	int i, found=0;
	initialise(list3, n);
	for(i=0;(i<total_entries1) && (i<n);i++)
	{
		list3[i].roll_number = list1[i].roll_number;
		strcpy (list3[i].subject_code, list1[i].subject_code);
		strcpy (list3[i].student_name, list1[i].student_name);
		list3[i].marks = list1[i].marks;
	}
	i = list_operation(list2, list1, n, total_entries2, total_entries1, i, found);
	sort(list3, n, i);
	printf("Successfully performed the operation\n");
	return i;
}
/*---------------------------------------------------------------------LIST_INTERSECTION-----------------------------------------------------------------------*/
int list_intersection(struct student_database list1[], struct student_database list2[], int n, int total_entries1, int total_entries2)
{
	int i=0, found=1;
	initialise(list3, n);
	i = list_operation(list1, list2, n, total_entries1, total_entries2, i, found);
	sort(list3, n, i);
	printf("Successfully performed the operation\n");
	return i;
}
/*---------------------------------------------------------------------LIST_DIFFERENCE-------------------------------------------------------------------------*/
int list_difference(struct student_database list1[], struct student_database list2[], int n, int total_entries1, int total_entries2)
{
	int i=0, found=0;
	initialise(list3, n);
	i = list_operation(list1, list2, n, total_entries1, total_entries2, i, found);
	sort(list3, n, i);
	printf("Successfully performed the operation\n");
	return i;
}
/*---------------------------------------------------------------------LIST_SYMMETRIC_DIFFERENCE---------------------------------------------------------------*/
int list_symmetric_difference(struct student_database list1[], struct student_database list2[], int n, int total_entries1, int total_entries2)
{
	int i=0, found=0;
	initialise(list3, n);
	i = list_operation(list1, list2, n, total_entries1, total_entries2, i, found);
	i = list_operation(list2, list1, n, total_entries2, total_entries1, i, found);
	sort(list3, n, i);
	printf("Successfully performed the operation\n");
	return i;
}
/*---------------------------------------------------------------------MAIN------------------------------------------------------------------------------------*/
main()
{
	int x, counter, total1=0, total2=0, total3=0;
	char choice[SUBJ_SIZE], list_choice[SUBJ_SIZE];
	x=CLASS_SIZE;
	initialise(list1, x);
	initialise(list2, x);
	do
	{
		printf("********************************************************************************\n");
		printf("WELCOME TO MAIN MENU!\n");
		printf("Use '_'(underscore) instead of ''(space) wherever necessary\n");
		printf("Press the appropriate key as mentioned\n");
		printf("(1)  or (insert)    : Insert/Update entries\n");
		printf("(2)  or (del)       : Delete an entry\n");
		printf("(3)  or (active)    : Get number of active records\n");
		printf("(4)  or (empty)     : Check whether list is empty or not\n");
		printf("(5)  or (full)      : Check whether list is fully occupied or not\n");
		printf("(6)  or (max)       : Find topper(s) of a particular subject\n");
		printf("(7)  or (dupinsert) : Insert entries which may contain duplicates\n");
		printf("(8)  or (dupdel)    : Remove duplicate entries\n");
		printf("(9)  or (union)     : Get union of 2 lists\n");
		printf("(10) or (int)       : Get intersection of 2 lists\n");
		printf("(11) or (diff)      : Get difference of 2 lists\n");
		printf("(12) or (symdiff)   : Get symmetric difference of 2 lists\n");
		printf("(13) or (disp)      : Display the entries\n");
		printf("(0)  or (exit)      : Exit\n");
		printf("********************************************************************************\n");
		scanf("%s", &choice);
		if((strcmp(choice, "1") == 0) || (strcmp(choice, "insert") == 0))
		{
			printf("1. Insert entries in list 1\n");
			printf("2. Insert entries in list 2\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", &list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				counter = insert(list1, x, total1);
				total1 = total1 + counter;
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				counter = insert(list2, x, total2);
				total2 = total2 + counter;
			}	
		}
		else if((strcmp(choice, "2") == 0) || (strcmp(choice, "del") == 0))
		{
			printf("1. Delete entry in list 1\n");
			printf("2. Delete entry in list 2\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", &list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				total1 = del(list1, x, total1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				total2 = del(list2, x, total2);
			}	
		}
		else if((strcmp(choice, "3") == 0) || (strcmp(choice, "active") == 0))
		{
			printf("1. Display active records of list 1\n");
			printf("2. Display active records of list 2\n");
			printf("3. Display active records of list 3\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", &list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				getNumRecords(list1, x, total1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				getNumRecords(list2, x, total2);
			}
			else if(strcmp(list_choice, "3") == 0)
			{
				getNumRecords(list3, x, total3);
			}
		}
		else if((strcmp(choice, "4") == 0) || (strcmp(choice, "empty") == 0))
		{
			printf("1. Check whether list 1 is empty or not\n");
			printf("2. Check whether list 2 is empty or not\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", &list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				isEmpty(list1, x, total1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				isEmpty(list2, x, total2);
			}
		}
		else if((strcmp(choice, "5") == 0) || (strcmp(choice, "full") == 0))
		{
			printf("1. Check whether list 1 is fully occupied or not\n");
			printf("2. Check whether list 2 is fully occupied or not\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", &list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				isFull(list1, x, total1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				isFull(list2, x, total2);
			}
		}
		else if((strcmp(choice, "6") == 0) || (strcmp(choice, "max") == 0))
		{
			printf("1. Find topper(s) of a particular subject in list 1\n");
			printf("2. Find topper(s) of a particular subject in list 2\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", &list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				getMaxMarks(list1, x, total1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				getMaxMarks(list2, x, total2);
			}
		}
		else if((strcmp(choice, "7") == 0) || (strcmp(choice, "dupinsert") == 0))
		{
			printf("1. Insert entries in list 1\n");
			printf("2. Insert entries in list 2\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", &list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				total1 = add_duplicates(list1, x, total1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				total2 = add_duplicates(list2, x, total2);
			}	
		}
		else if((strcmp(choice, "8") == 0) || (strcmp(choice, "dupdel") == 0))
		{
			printf("1. Remove duplicate entries from list 1\n");
			printf("2. Remove duplicate entries from list 2\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", &list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				total1 = list_unique(list1, x, total1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				total2 = list_unique(list2, x, total2);
			}	
		}
		else if((strcmp(choice, "9") == 0) || (strcmp(choice, "union") == 0))
		{
			total3 = list_union(list1, list2, x, total1, total2);
		}
		else if((strcmp(choice, "10") == 0) || (strcmp(choice, "int") == 0))
		{
			total3 = list_intersection(list1, list2, x, total1, total2);
		}
		else if((strcmp(choice, "11") == 0) || (strcmp(choice, "diff") == 0))
		{
			total3 = list_difference(list1, list2, x, total1, total2);
		}
		else if((strcmp(choice, "12") == 0) || (strcmp(choice, "symdiff") == 0))
		{
			total3 = list_symmetric_difference(list1, list2, x, total1, total2);
		}
		else if((strcmp(choice, "13") == 0) || (strcmp(choice, "disp") == 0))
		{
			printf("1. Display entries in list 1\n");
			printf("2. Display entries in list 2\n");
			printf("3. Display entries in list 3\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", &list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				print(list1, x, total1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				print(list2, x, total2);
			}
			else if(strcmp(list_choice, "3") == 0)
			{
				print(list3, x, total3);
			}
	 	}
		else 
		{
			if((strcmp(choice, "0") != 0) && (strcmp(choice, "exit") !=0))
			{
				printf("Please enter a valid choice\n");	
			}
		}
	}while((strcmp(choice, "0") != 0) && (strcmp(choice, "exit") !=0));
	printf("END OF PROGRAM \n");
}
