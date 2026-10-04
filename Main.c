#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int chkUser(char user[20], char pass[20], char fname[20])
{
    FILE *fp;
    fp = fopen(fname, "r");
    if (fp == NULL)
    {
        printf("\n File open error\n Check user module!");
    }
    else
    {
        char user1[20], pass1[20];
        fscanf(fp, "%s %s", user1, pass1);
        fclose(fp);
        if (strcmp(user, user1) == 0 && strcmp(pass, pass1) == 0)
        {
            return 1;
        }
    };
    return 0;
};

struct book
{
    int book_id;
    char book_name[20];
    char book_author[20];
    char book_publication[20];
    float book_price;
};
//CODE FOR ADDING RECORD
void add()
{
    struct book b;
    FILE *fp;
    fp = fopen("book2.txt", "ab");
    if (fp == NULL)
    {
        printf("\n\t book.txt file open error in Add Module.");
    }
    else
    {
        printf("\n\t Enter the Book ID: ");
        scanf("%d", &b.book_id);
        printf("\n\t Enter the Book name: ");
        scanf("%s", &b.book_name);
        printf("\n\t Enter the Book author: ");
        scanf("%s", &b.book_author);
        printf("\n\t Enter the Book Publisher: ");
        scanf("%s", &b.book_publication);
        printf("\n\t Enter the Book Price: ");
        scanf("%f", &b.book_price);

        fwrite(&b,sizeof(b),1,fp);
        printf("\n\t Record Added Successfully. ");
        fclose(fp);
    }
}

//CODE TO DISPLAY RECORD
void display()
{
    struct book b;
    FILE *fp;
    int count = 0;
    fp = fopen("book2.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t book.txt file open error in Display Module.");
    }
    else
    {
        printf("\n *************************************************************");
        printf("\n ID      Name        Author        Publication        Price");
        printf("\n *************************************************************");

        while(fread(&b,sizeof(b),1,fp)==1)
        {
            count++;
            printf("\n %d %s %s %s %f", b.book_id, b.book_name, b.book_author, b.book_publication, b.book_price);
        };
        fclose(fp);
        printf("\n *************************************************************");
        printf("\n Total Records:%d",count);
        printf("\n *************************************************************");
    }
}
void Search(int id)
{
    struct book b;
    FILE *fp;
    int count = 0;
    fp = fopen("book2.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t book.txt file open error in Search Module.");
    }
    else
    {
        printf("\n **********************************************************");
        printf("\n ID      Name        Author        Publication        Price");
        printf("\n **********************************************************");
        while(fread(&b,sizeof(b),1,fp)==1)
        {
            if(b.book_id==id)
            {
                count++;
                printf("\n %d  %s   %s  %s  %f", b.book_id, b.book_name, b.book_author, b.book_publication, b.book_price);
            }
        };
        fclose(fp);
        if(count==0)
        {
            printf("\n\t Record for %d not found",id);
        }
        else
        {
            printf("\n ************************************************************");
            printf("\n Total Records:%d",count);
            printf("\n ************************************************************");
        }
    }
}
//CODE TO UPDATE RECORD
void Update(int id)
{
    struct book b;
    FILE *fp,*temp;
    int count = 0;
    fp = fopen("book2.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t book.txt file open error in Update Module.");
    }
    else
    {
        temp = fopen("temp.txt", "wb");
        if(temp == NULL)
        {
            printf("Cannot open temp file in update module");
        }
        while(fread(&b,sizeof(b),1,fp)==1)
        {
            if(b.book_id==id)
            {
                count++; 
                printf("\n\t Enter new book name: ");
                scanf("%s", &b.book_name);

                printf("\n\t Enter new Book author: ");
                scanf("%s", &b.book_author);

                printf("\n\t Enter new Book Publisher: ");
                scanf("%s", &b.book_publication);

                printf("\n\t Enter new Book Price: ");
                scanf("%f", &b.book_price);

                fwrite(&b,sizeof(b),1,temp);
            }
            else
            {
                fwrite(&b,sizeof(b),1,temp);
            }
        };
        fclose(fp);
        fclose(temp);
        remove("book2.txt");
        rename("temp.txt","book2.txt");
        if(count==0)
        {
            printf("\n\t Record for %d not found",id);
        }
        else
        {
            printf("\n ************************************************************");
            printf("\n Total Updated Records:%d",count);
            printf("\n ************************************************************");
        }
    }
}
//CODE TO REMOVE RECORD
void Remove(int id)
{
    struct book b;
    FILE *fp,*temp;
    int count = 0;
    fp = fopen("book2.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t book.txt file open error in Remove Module.");
    }
    else
    {
        temp = fopen("temp.txt", "wb");
        if(temp == NULL)
        {
            printf("Cannot open temp file in Remove module");
        }
        while(fread(&b,sizeof(b),1,fp)==1)
        {
            if(b.book_id==id)
            {
                count++; 
            }
            else
            {
                fwrite(&b,sizeof(b),1,temp);
            }
        };
        fclose(fp);
        fclose(temp);
        remove("book2.txt");
        rename("temp.txt","book2.txt");
        if(count==0)
        {
            printf("\n\t Record for %d not found",id);
        }
        else
        {
            printf("\n ************************************************************");
            printf("\n Removed records:%d",count);
            printf("\n ************************************************************");
        }
    }
}

int main()
{
    char ch;
    int choice, id, x;
    char user[20], pass[20];
    do
    {
        system("clear");
        printf("\n\t *********************************************************");
        printf("\n\t                WELCOME TO BOOK MANAGEMENT                ");
        printf("\n\t *********************************************************");
        printf("\n\t  Login Menu                          ");
        printf("\n\t **********************************************************");
        printf("\n\t 1. Admin Login");
        printf("\n\t 2. User Login");
        printf("\n\t 3. Quit");
        printf("\n\t *********************************************************");
        printf("\n\t Enter choice[1-3]: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\n Enter Your adminname: ");
            scanf("%s", user);
            printf("\n Enter Your Password: ");
            scanf("%s", pass);
            x = chkUser(user, pass, "admin.txt");
            if (x == 1)
            {
                do
                {
                    system("clear");
                    printf("\n\t *******************************************************");
                    printf("\n\t               WELCOME TO ADMIN LOGIN     ");
                    printf("\n\t *******************************************************");
                    printf("\n\t  Admin Menu                          ");
                    printf("\n\t *******************************************************");
                    printf("\n\t 1. Add Record");
                    printf("\n\t 2. Display Records");
                    printf("\n\t 3. Search Records");
                    printf("\n\t 4. Update Records");
                    printf("\n\t 5. Remove Records");
                    printf("\n\t 6. Logout");
                    printf("\n\t *******************************************************");
                    printf("\n\t Enter choice[1-6]: ");
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        add();
                        break;
                    case 2:
                        display();
                        break;
                    case 3:
                        printf("\n\t Enter the book id to search the record:");
                        scanf("%d",&id);
                        Search(id);
                        break;
                    case 4:
                        printf("\n\t Enter the book id to Update the record:");
                        scanf("%d",&id);
                        Update(id);
                        break;
                    case 5:
                     printf("\n\t Enter the book id to Delete the record:");
                        scanf("%d",&id);
                        Remove(id);
                        break;
                    case 6:
                        exit(0);
                        break;
                    default:
                        printf("\n Something went wrong!");
                        printf("\n Try again");
                    }
                    printf("\n Do you want to continue in Admin Login (Y/N): ");
                    scanf("%s", &ch);
                }
                while (ch=='Y'|| ch=='y');
            }
            else
            {
                printf("\n Invalid Admin credentials!");
                printf("\n Try Again");
            }
            break;
            case 2:
            printf("\n Enter Your username: ");
            scanf("%s", user);
            printf("\n Enter Your Password: ");
            scanf("%s", pass);
            x = chkUser(user, pass, "user.txt");
            if (x == 1)
            {
                do
                {
                    system("clear");
                    printf("\n\t **************************************************");
                    printf("\n\t              WELCOME TO USER LOGIN                ");
                    printf("\n\t **************************************************");
                    printf("\n\t  User Menu                           ");
                    printf("\n\t **************************************************");
                    printf("\n\t 1. Display Records");
                    printf("\n\t 2. Search Records");
                    printf("\n\t 3. Logout");
                    printf("\n ****************************************************");
                    printf("\n Enter choice[1-3]: ");
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        display();
                        break;
                    case 2:
                        printf("\n\t Enter the book id to search the record:");
                        scanf("%d",&id);
                        Search(id);
                        break;
                    case 3:
                        exit(0);
                        break;
                    default:
                        printf("\n Something went wrong!");
                        printf("\n Try again");
                    }
                    printf("\n Do you want to continue in User Login (Y/N): ");
                    scanf("%s", &ch);
                }while (ch=='Y'|| ch=='y');
            }
            else
            {
                printf("\n Invalid Admin credentials!");
                printf("\n Try Again");
            }
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("\n Something went wrong!");
            printf("\n Try again");
        }
        printf("\n Do you want to continue (Y/N): ");
        scanf("%s", &ch);
    }while (ch=='Y'|| ch=='y');
    return 0;
}
