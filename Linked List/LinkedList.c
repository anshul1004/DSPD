#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define NAME_SIZE 30
#define SUBJ_SIZE 10
typedef struct Node_tag                                                           /* Structure for the node */
{
	int roll_no;
	char subj_code[SUBJ_SIZE];
	char name[NAME_SIZE];
	unsigned int marks;
	struct Node_tag *next;
}Node;                                                                            /* End of structure */
typedef enum{FAILURE, SUCCESS}status_code;
Node *copyNode(Node *lptr)                                                        /* copyNode function */
{
	Node *new_node;
	new_node = (Node*)malloc(sizeof(Node));
	new_node->roll_no = lptr->roll_no;
	strcpy(new_node->subj_code, lptr->subj_code);
	strcpy(new_node->name, lptr->name);
	new_node->marks = lptr->marks;
	new_node->next = NULL;
	return new_node;
}                                                                                 /* End of copyNode function */
Node *clearList(Node *lptr)                                                       /* clearList function */  
{
	Node *ptr;
	while(lptr!=NULL)
	{
		ptr=lptr;
		lptr=ptr->next;
		free(ptr);
	}
	return lptr;
}                                                                                  /* End of clearList function */
void printList(Node *lptr)                                                         /* printList function */
{
	Node *ptr=lptr;
	printf("Roll Number \t Subject Code \t\t Name \t\t\t Marks\n--------------------------------------------------------------------------------\n");
	while(ptr!=NULL)
	{
		printf("%-4d \t\t %-8s \t\t %-8s \t\t %-8d\n", ptr->roll_no, ptr->subj_code, ptr->name, ptr->marks);
		ptr=ptr->next;
	}
}                                                                                  /* End of printList function */
Node *insertWithSort(Node *lptr, Node *new_node, int flag)                         /* insertWithSort function */ 
{
	Node *ptr=lptr,*prev=NULL;
	if((new_node->roll_no <= ptr->roll_no)&&(strcmp(new_node->subj_code, ptr->subj_code) < 0))
	{                                                                                        /* If both keys are smaller */
		new_node->next = ptr;
		lptr = new_node;
	}
	else
	{
		while((ptr->next != NULL)&&(new_node->roll_no > ptr->roll_no))
		{                                                                                    /* Traversing list till key 1 is greater */
			prev = ptr;
			ptr = ptr->next;
		}
		while((ptr->next != NULL) && (new_node->roll_no == ptr->roll_no) && (strcmp(new_node->subj_code, ptr->subj_code) > 0))
		{                                                                                    /* Traversing list till key 1 is equal & key 2 is greater */ 
			prev = ptr;
			ptr = ptr->next;
		}
		if((new_node->roll_no == ptr->roll_no)&&(strcmp(new_node->subj_code, ptr->subj_code) == 0) && (flag == 0))
		{                                                                                    /* If both keys are equal & updation takes place */
			strcpy(ptr->name, new_node->name);
			ptr->marks = new_node->marks;
		}
		else if((new_node->roll_no == ptr->roll_no)&&(strcmp(new_node->subj_code, ptr->subj_code) == 0) && (flag == 1))
		{                                                                                    /* If both keys are equal & duplicate entries can be inserted */
			new_node->next = ptr->next;
			ptr->next = new_node;
		}
		else if((new_node->roll_no == ptr->roll_no)&&(strcmp(new_node->subj_code, ptr->subj_code) > 0))
		{                                                                                    /* If key 1 is equal & Key 2 is greater */
			new_node->next = ptr->next;                                                              /* New node is added after ptr node */
			ptr->next = new_node;
		}
		else
		{
			if((ptr->next == NULL)&&(new_node->roll_no > ptr->roll_no))                     /* If ptr is the last node */
			{                                                                                       /* New node becomes the last node now */
				ptr->next = new_node;
			}
			else                                                                                   /* New node is inserted before ptr node */
			{
				new_node->next = ptr;
				if(prev==NULL)
				{
					lptr=new_node;
				}
				else
				{
					prev->next = new_node;
				}
			}
		}
	}
	return lptr;
}                                                                                 /* End of insertWithSort function */
Node *insert(Node *lptr, int flag, FILE *fp)                                                /* insert function */
{
	int n, i=0;
	printf("How many entries to insert: ");
	scanf("%d", &n);
	for(i=0;i<n;i++)
	{
		printf("ENTRY %d\n", i+1);
		Node *new_node;
		new_node = (Node*)malloc(sizeof(Node));
		printf("Roll No.: ");
		scanf("%d", &new_node->roll_no);
		printf("Subject Code: ");
		scanf("%s", &new_node->subj_code);
		printf("Name: ");
		scanf("%s", &new_node->name);
		printf("Marks: ");
		scanf("%d", &new_node->marks);
		new_node->next = NULL;
		if(lptr==NULL)                                                                  /* If list is empty */
		{
			lptr = new_node;
		}
		else                                                                            /* If list is not empty */
		{
			lptr = insertWithSort(lptr, new_node, flag);
		}	
	}
	if(lptr == NULL)
	{
		printf("Failed to insert entry(s)\n");
	}
	else
	{
		printf("Successfully inserted entry(s)\n");
	}
	return lptr;
}                                                                                /* End of insert function */
status_code Delete(Node **lptr)                                                  /* Delete function */
{
	Node *ptr=*lptr, *prev=NULL;
	status_code ret_val=FAILURE;
	int roll;
	char sub_c[SUBJ_SIZE];
	printf("Enter the appropriate fields to delete the entry from the list\n");
	printf("Roll No.: ");
	scanf("%d", &roll);
	printf("Subject Code: ");
	scanf("%s", sub_c);
	while(ptr!=NULL && ret_val==FAILURE)
	{
		if((roll == ptr->roll_no) && (strcmp(sub_c, ptr->subj_code) == 0))                 /* If both the keys match */
		{
			if(prev == NULL)                                                                       /* First node is deleted */
			{
				*lptr = ptr->next;
				free(ptr);
				ret_val = SUCCESS;
			}
			else
			{
				prev->next = ptr->next;                                                            /* Some middle or the last node is deleted */
				free(ptr);
				ret_val = SUCCESS;
			}
		}
		prev=ptr;
		ptr=ptr->next;
	}
	return ret_val;
}                                                                                 /* End of Delete function */
void getNumRecords(Node *lptr)                                                    /* getNumRecords function */
{
	Node *ptr=lptr;
	int count=0;
	while(ptr!=NULL)
	{
		count++;
		ptr=ptr->next;
	}
	printf("Number of active records: %d\n", count);
}                                                                                  /* End of getNumRecords function */
void isEmpty(Node *lptr)                                                           /* isEmpty function */
{
	if(lptr == NULL)
	{
		printf("List is empty\n");
	}
	else
	{
		printf("List is not empty\n");
	}
}                                                                                  /* End of isEmpty function */
void List_unique(Node *lptr)                                                       /* List_unique function */
{
  Node *ptr=lptr, *next_node;
  if(lptr!=NULL)
  {
  	while(ptr->next!=NULL)
  	{
        if((ptr->roll_no ==(ptr->next)->roll_no)&&(strcmp(ptr->subj_code, (ptr->next)->subj_code) == 0))               /* If both the keys match */
    	{
    		next_node = ptr->next;
      		ptr->next = next_node->next;
      		free(next_node);
    	}
    	else
    	{
      		ptr = ptr->next;
    	}
  	}
  }
  printf("Successfully performed operation\n");
}                                                                                 /* End of List_unique function */
void *getMaxMarks(Node *lptr)                                                     /* getMaxMarks function */
{
	Node *ptr=lptr, *mptr, *tptr=NULL;
	char sub_c[SUBJ_SIZE];
	printf("Enter the subject code: ");
	scanf("%s", sub_c);
	mptr = (Node*)malloc(sizeof(Node));
	mptr->roll_no = 0;
	strcpy(mptr->subj_code, "0");
	strcpy(mptr->name, "0");
	mptr->marks = 0;
	mptr->next = NULL;
	while(ptr!=NULL)
	{
		if(strcmp(ptr->subj_code, sub_c)==0)                                                     /* If subject code matches */
		{
			if(ptr->marks > mptr->marks)                                                         /* If higher marks are encountered */
			{
				mptr = clearList(mptr);
				tptr = mptr = copyNode(ptr);
			}
			else if(ptr->marks == mptr->marks)                                                   /* If marks equal to highest marks are encountered */
			{ 
				tptr->next = copyNode(ptr);
				tptr = tptr->next;
			}
		}
		ptr = ptr->next;
	}	
	printList(mptr);
}                                                                               /* End of getMaxMarks function */
Node *list_operation(Node *lptr1, Node *lptr2, Node *lptr3, int flag)           /* list_operation function */
{
	Node *ptr1=lptr1, *ptr2=lptr2, *ptr3;
	lptr3 = clearList(lptr3);
	while((ptr1 != NULL)&&(ptr2 != NULL))
	{
		if(ptr1->roll_no < ptr2->roll_no)                                             /* If list 1 key 1 is smaller than list 2 key 1*/
		{
			if((lptr3 == NULL)&&((flag == 0) || (flag == 2) || (flag == 3)))                 /* If list 3 is empty */
			{
				ptr3 = lptr3 = copyNode(ptr1);
			}
			else if((lptr3 != NULL)&&((flag == 0) || (flag == 2) || (flag == 3)))            /* If list 3 is not empty */
			{
				ptr3->next = copyNode(ptr1);
				ptr3 = ptr3->next;
			}
			ptr1 = ptr1->next;
		}
		else if(ptr1->roll_no > ptr2->roll_no)                                       /* If list 1 key 1 is greater than list 2 key 2 */
		{
			if((lptr3 == NULL)&&((flag == 0) || (flag == 3)))                                /* If list 3 is empty */
			{
				ptr3 = lptr3 = copyNode(ptr2);
			}
			else if((lptr3 != NULL)&&((flag == 0) || (flag == 3)))                           /* If list 3 is not empty */
			{
				ptr3->next = copyNode(ptr2);
				ptr3 = ptr3->next;
			}
			ptr2 = ptr2->next;
		}
		else
		{
			if(strcmp(ptr1->subj_code, ptr2->subj_code) < 0)                /* If key 1 are equal in both lists but list 1 key 2 is smaller than list 2 key 2 */
			{
				if((lptr3 == NULL)&&((flag == 0) || (flag == 2) || (flag == 3)))            /* If list 3 is empty */
				{
					ptr3 = lptr3 = copyNode(ptr1);
				}
				else if((lptr3 != NULL)&&((flag == 0) || (flag == 2) || (flag == 3)))       /* If list 3 is not empty */
				{
					ptr3->next = copyNode(ptr1);
					ptr3 = ptr3->next;
				}
				ptr1 = ptr1->next;
			}
			else if(strcmp(ptr1->subj_code, ptr2->subj_code) > 0)           /* If key 1 are equal in both lists but list 1 key 2 is smaller than list 2 key 2 */
			{
				if((lptr3 == NULL)&&((flag == 0) || (flag == 3)))                          /* If list 3 is empty */
				{
					ptr3 = lptr3 = copyNode(ptr2);
				}
				else if((lptr3 != NULL)&&((flag == 0) || (flag == 3)))                     /* If list 3 is not empty */
				{
					ptr3->next = copyNode(ptr2);
					ptr3 = ptr3->next;
				}
				ptr2 = ptr2->next;
			}
			else                                                            /* If both keys of both lists are equal */
			{
				if((lptr3 == NULL)&&((flag == 0) || (flag == 1)))                          /* If list 3 is empty */
				{
					ptr3 = lptr3 = copyNode(ptr1);
				}
				else if((lptr3 != NULL)&&((flag == 0) || (flag == 1)))                     /* If list 3 is not empty */
				{
					ptr3->next = copyNode(ptr1);
					ptr3 = ptr3->next;
				}
				ptr1 = ptr1->next;
				ptr2 = ptr2->next;
			}
		}
	}
	while((ptr1!=NULL)&&((flag == 0) || (flag == 2) || (flag == 3)))       /* If list 1 is not empty */
	{
		if(lptr3 == NULL)                                                                  /* If list 3 is empty */
		{
			ptr3 = lptr3 = copyNode(ptr1);
		}
		else                                                                              /* If list 3 is not empty */
		{
			ptr3->next = copyNode(ptr1);
			ptr3 = ptr3->next;
		}
		ptr1 = ptr1->next;
	}
	while((ptr2!=NULL)&&((flag == 0) || (flag == 3)))                      /* If list 2 is not empty */
	{
		if(lptr3 == NULL)                                                                 /* If list 3 is empty */
		{
			ptr3 = lptr3 = copyNode(ptr2);
		}
		else                                                                              /* If list 3 is not empty */
		{
			ptr3->next = copyNode(ptr2);
			ptr3 = ptr3->next;
		}
		ptr2 = ptr2->next;
	}
	printf("Successfully performed operation\n");
	return lptr3;
}                                                                              /* End of list_operation function */
Node *list_union(Node *lptr1, Node *lptr2, Node *lptr3)                        /* list_union function */
{
	int flag_status = 0;
	lptr3 = list_operation(lptr1, lptr2, lptr3, flag_status);
	return lptr3;
}                                                                              /* End of list_union function */
Node *list_intersection(Node *lptr1, Node *lptr2, Node *lptr3)                 /* list_intersection function */
{
	int flag_status = 1;
	lptr3 = list_operation(lptr1, lptr2, lptr3, flag_status);
	return lptr3;
}                                                                              /* End of list_intersection function */
Node *list_difference(Node *lptr1, Node *lptr2, Node *lptr3)                   /* list_difference function */
{
	int flag_status = 2;
	lptr3 = list_operation(lptr1, lptr2, lptr3, flag_status);
	return lptr3;
}                                                                              /* End of list_difference function */
Node *list_symmetric_difference(Node *lptr1, Node *lptr2, Node *lptr3)         /* list_symmetric_difference function */
{
	int flag_status = 3;
	lptr3 = list_operation(lptr1, lptr2, lptr3, flag_status);
	return lptr3;
}                                                                             /* End of list_symmetric_difference function */
Node *createListUsingFiles(FILE *fp, Node *lptr)                                  /* createListUsingFiles function */
{
	int flag = 0;
	while(!feof(fp))
	{
		Node *new_node;
		new_node = (Node*)malloc(sizeof(Node));
		new_node->next = NULL;
		fscanf(fp, "%d %s %s %d", &new_node->roll_no, &new_node->subj_code, &new_node->name, &new_node->marks);
		if(lptr == NULL)
		{
			lptr = new_node;
		}
		else
		{
			lptr = insertWithSort(lptr, new_node, flag);
		}
	}
	return lptr;
}                                                                             /* End of createListUsingFiles function */
main()                                                                        /* main function */
{
	Node *head1=NULL, *head2=NULL, *head3=NULL;
	FILE *fp;
	status_code s;
	int flag;
	char choice[SUBJ_SIZE], list_choice[SUBJ_SIZE], bool_choice1[4], bool_choice2[4];
	printf("********************************************************************************\n");
	printf("                         STUDENT DATABASE RECORD                                \n");
	printf("********************************************************************************\n");
	printf("Do you want to copy entries from list1 & list2: yes or no\n");
	scanf("%s", bool_choice1);
	if(strcmp(bool_choice1, "yes") == 0)
	{
		fp = fopen("list1.txt", "r");
		head1 = createListUsingFiles(fp, head1);
		fclose(fp);
		fp = fopen("list2.txt", "r");
		head2 = createListUsingFiles(fp, head2);
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
		printf("(3)  or (active)    : Get number of active records\n");
		printf("(4)  or (empty)     : Check whether list is empty or not\n");
		printf("(5)  or (dupinsert) : Insert entries which may contain duplicates\n");
		printf("(6)  or (remdup)    : Remove duplicate entries\n");
		printf("(7)  or (max)       : Find topper(s) of a particular subject\n");
		printf("(8)  or (union)     : Get union of 2 lists\n");
		printf("(9) or (int)        : Get intersection of 2 lists\n");
		printf("(10) or (diff)      : Get difference of 2 lists\n");
		printf("(11) or (symdiff)   : Get symmetric difference of 2 lists\n");
		printf("(12) or (clear)     : Clear the whole list\n");
		printf("(13) or (disp)      : Display the entries\n");
		printf("(0)  or (exit)      : Exit\n");
		printf("********************************************************************************\n");
		scanf("%s", choice);
		if((strcmp(choice, "1") == 0) || (strcmp(choice, "insert") == 0))
		{
			printf("1. Insert entries in list 1\n");
			printf("2. Insert entries in list 2\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", list_choice);
			flag = 0;
			if(strcmp(list_choice, "1") == 0)
			{	
				head1=insert(head1, flag, fp);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				head2=insert(head2, flag, fp);
			}	
		}
		else if((strcmp(choice, "2") == 0) || (strcmp(choice, "delete") == 0))
		{
			printf("1. Delete entry in list 1\n");
			printf("2. Delete entry in list 2\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				s = Delete(&head1);
				printf("%c", s);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				s = Delete(&head2);
				printf("%c", s);
			}	
			if(s == SUCCESS)
			{
				printf("Successfully deleted entry\n");
			}
			else
			{
				printf("Failed to delete entry(not present)\n");
			}
		}
		else if((strcmp(choice, "3") == 0) || (strcmp(choice, "active") == 0))
		{
			printf("1. Display active records of list 1\n");
			printf("2. Display active records of list 2\n");
			printf("3. Display active records of list 3\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				getNumRecords(head1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				getNumRecords(head2);
			}
			else if(strcmp(list_choice, "3") == 0)
			{
				getNumRecords(head3);
			}
		}
		else if((strcmp(choice, "4") == 0) || (strcmp(choice, "empty") == 0))
		{
			printf("1. Check whether list 1 is empty or not\n");
			printf("2. Check whether list 2 is empty or not\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				isEmpty(head1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				isEmpty(head2);
			}
		}
		else if((strcmp(choice, "5") == 0) || (strcmp(choice, "dupinsert") == 0))
		{
			printf("1. Insert entries in list 1\n");
			printf("2. Insert entries in list 2\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", list_choice);
			flag = 1;
			if(strcmp(list_choice, "1") == 0)
			{	
				head1=insert(head1, flag, fp);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				head2=insert(head2, flag, fp);
			}	
		}
		else if((strcmp(choice, "6") == 0) || (strcmp(choice, "remdup") == 0))
		{
			printf("1. Remove duplicate entries in list 1\n");
			printf("2. Remove duplicate entries in list 2\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				List_unique(head1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				List_unique(head2);
			}	
		}
		else if((strcmp(choice, "7") == 0) || (strcmp(choice, "max") == 0))
		{
			printf("1. Find topper(s) of a particular subject in list 1\n");
			printf("2. Find topper(s) of a particular subject in list 2\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				getMaxMarks(head1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				getMaxMarks(head2);
			}
		}
		else if((strcmp(choice, "8") == 0) || (strcmp(choice, "union") == 0))
		{
			head3 = list_union(head1, head2, head3);
		}
		else if((strcmp(choice, "9") == 0) || (strcmp(choice, "int") == 0))
		{
			head3 = list_intersection(head1, head2, head3);
		}
		else if((strcmp(choice, "10") == 0) || (strcmp(choice, "diff") == 0))
		{
			head3 = list_difference(head1, head2, head3);
		}
		else if((strcmp(choice, "11") == 0) || (strcmp(choice, "symdiff") == 0))
		{
			head3 = list_symmetric_difference(head1, head2, head3);
		}
		else if((strcmp(choice, "12") == 0) || (strcmp(choice, "clear") == 0))
		{
			printf("1. Clear list 1\n");
			printf("2. Clear list 2\n");
			printf("3. Clear list 3\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				head1 = clearList(head1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				head2 = clearList(head2);
			}
			else if(strcmp(list_choice, "3") == 0)
			{
				head3 = clearList(head3);
			}
	 	}
		else if((strcmp(choice, "13") == 0) || (strcmp(choice, "disp") == 0))
		{
			printf("1. Display entries in list 1\n");
			printf("2. Display entries in list 2\n");
			printf("3. Display entries in list 3\n");
			printf("Press any other key to return to the main menu\n");
			scanf("%s", list_choice);
			if(strcmp(list_choice, "1") == 0)
			{	
				printList(head1);
			}
			else if(strcmp(list_choice, "2") == 0)
			{
				printList(head2);
			}
			else if(strcmp(list_choice, "3") == 0)
			{
				printList(head3);
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
	clearList(head1);
	clearList(head2);
	clearList(head3);
	printf("END OF PROGRAM \n");
	getch();
}                                                /* End of program */
