#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void displayList();
void addNewData();
void updaterecord();
void searchIceCream();
void deleterecord();

struct Icecream
{
	int ice_cream_id;
	char name[30];
	int num_scoops;
	float price;
};
struct Icecream ice;
int main()
{
	int ch;
	while(ch!=6)
	{
		printf("\n\n---Ice-cream Parlour Management System---");
		printf("\n1- Display Ice-cream list");
		printf("\n2- Add new Ice-cream");
		printf("\n3- Update any record");
		printf("\n4- Search any Ice-cream");
		printf("\n5- Delete any Ice-cream");
		printf("\n6- Exit");
		printf("\n\nEnter your choice (1-6): ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				displayList();
				break;
			case 2:
				addNewData();
				break;
			case 3:
				updaterecord();
				break;
			case 4:
				searchIceCream();
				break;
			case 5:
				deleterecord();
				break;
			case 6:
				printf("\nThankyou for using this system!");
				exit(0);
				break;
			default:
				printf("Invalid choice! Please give valid input.");
		}
	}
}
void addNewData()
{
	FILE *fp;
	fp=fopen("Ice_list.txt","r");
	if(fp==NULL)
	{
		printf("\n\t\t Error: Cannot open the File!!!");
	}
	printf("\t-----Previous Ice-cream List-----");
	displayList();
	
	printf("\n\n\t----Enter New Ice-cream Data----");
	
	printf("\nEnter Ice-cream ID no: ");
	scanf("%d",&ice.ice_cream_id);
	fflush(stdin);
	
	printf("\nEnter Ice-cream name: ");
	gets(ice.name);
	
	printf("\nEnter no of scoops: ");
	scanf("%d",&ice.num_scoops);
	
	printf("\nEnter the price: ");
	scanf("%f",&ice.price);
	int flag=0;
	fclose(fp);
	
	fp=fopen("Ice_list.txt","a");
	flag=fwrite(&ice,sizeof(ice),1,fp);
	if(flag)
	{
		printf("Contents of the structure written successfully");
	}
	else
	{
		printf("Error writing to file!");
	}
	fclose(fp);
	printf("\n\t\t----Updated Record----");
	displayList();
}
void displayList()
{
	FILE *fp;
	fp=fopen("Ice_list.txt","r");
	if(fp==NULL)
	{
		printf("\n\t\t Error: Cannot open the File!!!");
		return;
	}
	printf("\n\n\t----Ice-cream List - Are as follow----\n");
	printf("\nIce-cream ID_no\t\tIce-cream_name\t\tNo_of_scoop(S)\t\tPrice_of_ice-cream\n");
	while(fread(&ice,sizeof(ice),1,fp)==1)
	{
		printf("\n%d\t\t\t%-15s\t\t\t%d\t\t\tRs.%0.2f",ice.ice_cream_id,ice.name,ice.num_scoops,ice.price);
	}
	fclose(fp);
}
void searchIceCream()
{
	int id,flag=0;
	FILE *fp;
	fp=fopen("Ice_list.txt","r");
	if(fp==NULL)
	{
		printf("\n\t\t Error: Cannot open the File!!!");
		return;
	}
	printf("\n\n\tEnter Ice-cream ID which you want to search: ");
	scanf("%d",&id);
	while(fread(&ice,sizeof(ice),1,fp) > 0 && flag==0)
	{
		if(ice.ice_cream_id == id)
		{
			flag=1;
			printf("\n\n\tSearch Successfully and Ice-cream Records is as Follows:\n\n");
			printf("\nIce-cream ID_no\t\tIce-cream_name\t\tNo_of_scoops(S)\t\tPrice_of_ice-cream\n");
			printf("\n%d\t\t\t%-15s\t\t\t%d\t\t\tRs.%0.2f",ice.ice_cream_id,ice.name,ice.num_scoops,ice.price);			
		}
	}
	if(flag==0)
	{
		printf("\n\n\tNo such record found!!!\n");
	}
	fclose(fp);
}

void deleterecord()
{
	FILE *fp,*fp1;
	int j,rn,found=0,rno;
	fp=fopen("Ice_list.txt","r");
	fp1=fopen("Ice_temp.txt","w");
	printf("Enter id to delete: ");
	fflush(stdin);
	scanf("%d",&rno);
	
	while(fread(&ice,sizeof(ice),1,fp))
	{
		if(ice.ice_cream_id==rno)
		{
			found=1;
		}
		else
		    fwrite(&ice,sizeof(ice),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	if(found)
	{
		fp1=fopen("Ice_temp.txt","r");
		fp=fopen("Ice_list.txt","w");
		
		while(fread(&ice,sizeof(ice),1,fp1))
		{
			fwrite(&ice,sizeof(ice),1,fp);
		};
		fclose(fp1);
		fclose(fp);
	}
	else
	{
		printf("\nRecord not found");
	}
	displayList();
}

void updaterecord()
{
    FILE *fp;
    int found = 0,id;

    fp = fopen("ice_list.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    printf("\n\n\tEnter Ice-cream ID which you want to update: ");
	scanf("%d",&id);
	printf("\t-----Previous Ice-cream List-----");
	displayList();

    while (fread(&ice, sizeof(ice), 1, fp) == 1) {
        if (ice.ice_cream_id==id) {
            printf("\nIce-cream ID_no\t\tIce-cream_name\t\tNo_of_scoops(S)\t\tPrice_of_ice-cream\n");
			printf("\n%d\t\t\t%-15s\t\t\t%d\t\t\tRs.%0.2f\n",ice.ice_cream_id,ice.name,ice.num_scoops,ice.price);
			printf("\n\t\t-----Now enter the new record-----");
			
			printf("\n\tUpdated Ice-cream ID: ");
			scanf("%d",&ice.ice_cream_id);
			fflush(stdin);
			
			printf("\n\tUpdated Ice-cream name: ");
			gets(ice.name);
			
			printf("\n\tUpdated no of scoops: ");
			scanf("%d",&ice.num_scoops);
			fflush(stdin);
			
			printf("\n\tUpdated price: ");
			scanf("%f",&ice.price);
			fflush(stdin);
            fseek(fp, -sizeof(ice), SEEK_CUR);
            fwrite(&ice, sizeof(ice), 1, fp);
            found = 1;
            break;
        }
    }

    if (found) {
        printf("\tRecord updated successfully.\n");
    } else {
        printf("Record not found.\n");
    }

    fclose(fp);
}
