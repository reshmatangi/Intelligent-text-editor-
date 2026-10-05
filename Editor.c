#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char text[300];
    struct node *link;
};

struct node *uTop = NULL;
struct node *rTop = NULL;

char current[300] = "";
char Text[300];

void undoPush();
void redoPush();
void UNDO();
void REDO();
void ENTERTEXT();
void DISPLAY();
void INSERT();
void DELETE();
void SEARCH();
void REPLACE();

void main()
{
    int ch;

    while(1)
    {
        printf("\n...TEXT EDITOR...\n");
        printf("\n1.UNDO\n2.REDO\n3.ENTER TEXT\n4.DISPLAY\n5.INSERT\n6.DELETE\n7.SEARCH\n8.REPLACE\n9.EXIT\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1: UNDO(); break;
            case 2: REDO(); break;
            case 3: ENTERTEXT(); break;
            case 4: DISPLAY(); break;
            case 5: INSERT(); break;
            case 6: DELETE(); break;
            case 7: SEARCH(); break;
            case 8: REPLACE(); break;
            case 9: exit(0);
            default: printf("INVALID CHOICE\n");
        }
    }
}

void undoPush()
{
    struct node *temp;

    temp = (struct node *)malloc(sizeof(struct node));

    strcpy(temp->text,current);
    temp->link = uTop;
    uTop = temp;
}

void redoPush()
{
    struct node *temp;

    temp = (struct node *)malloc(sizeof(struct node));

    strcpy(temp->text,current);
    temp->link = rTop;
    rTop = temp;
}

void UNDO()
{
    struct node *p;

    if(uTop == NULL)
    {
        printf("Nothing to undo\n");
    }
    else
    {
        redoPush();
        strcpy(current,uTop->text);

        p = uTop;
        uTop = uTop->link;
        free(p);

        printf("Undo successful\n");
    }
}

void REDO()
{
    struct node *p;

    if(rTop == NULL)
    {
        printf("Nothing to redo\n");
    }
    else
    {
        undoPush();
        strcpy(current,rTop->text);

        p = rTop;
        rTop = rTop->link;
        free(p);

        printf("Redo successful\n");
    }
}

void ENTERTEXT()
{
    struct node *p;

    printf("Enter text: ");
    scanf(" %[^\n]",Text);

    undoPush();
    strcpy(current,Text);

    while(rTop != NULL)
    {
        p = rTop;
        rTop = rTop->link;
        free(p);
    }

    printf("Text updated\n");
}

void DISPLAY()
{
    printf("\nCURRENT TEXT:\n");
    printf("%s\n",current);
}

void INSERT()
{
    char word[30],result[300];
    int pos,i,j=0;

    printf("Enter word: ");
    scanf("%s",word);

    printf("Enter position: ");
    scanf("%d",&pos);

    undoPush();

    for(i=0;i<pos;i++)
        result[j++]=current[i];

    for(i=0;word[i]!='\0';i++)
        result[j++]=word[i];

    for(i=pos;current[i]!='\0';i++)
        result[j++]=current[i];

    result[j]='\0';

    strcpy(current,result);

    while(rTop != NULL)
    {
        struct node *p = rTop;
        rTop = rTop->link;
        free(p);
    }

    printf("Word inserted\n");
}

void DELETE()
{
    char word[30],result[300];
    int i=0,j,k=0;

    printf("Enter word to delete: ");
    scanf("%s",word);

    undoPush();

    while(current[i]!='\0')
    {
        j=0;

        while(word[j]!='\0' && current[i+j]==word[j])
            j++;

        if(word[j]=='\0')
            i=i+strlen(word);
        else
            result[k++]=current[i++];
    }

    result[k]='\0';

    strcpy(current,result);

    while(rTop != NULL)
    {
        struct node *p = rTop;
        rTop = rTop->link;
        free(p);
    }

    printf("Word deleted\n");
}

void SEARCH()
{
    char word[30];
    int i,j;

    printf("Enter word to search: ");
    scanf("%s",word);

    for(i=0;current[i]!='\0';i++)
    {
        j=0;

        while(word[j]!='\0' && current[i+j]==word[j])
            j++;

        if(word[j]=='\0')
        {
            printf("Found at position %d\n",i);
            return;
        }
    }

    printf("Word not found\n");
}

void REPLACE()
{
    char old[30],new[30],result[300];
    int i=0,j,k=0;

    printf("Enter old word: ");
    scanf("%s",old);

    printf("Enter new word: ");
    scanf("%s",new);

    undoPush();

    while(current[i]!='\0')
    {
        j=0;

        while(old[j]!='\0' && current[i+j]==old[j])
            j++;

        if(old[j]=='\0')
        {
            for(j=0;new[j]!='\0';j++)
                result[k++]=new[j];

            i=i+strlen(old);
        }
        else
            result[k++]=current[i++];
    }

    result[k]='\0';

    strcpy(current,result);

    while(rTop != NULL)
    {
        struct node *p = rTop;
        rTop = rTop->link;
        free(p);
    }

    printf("Word replaced\n");
}
