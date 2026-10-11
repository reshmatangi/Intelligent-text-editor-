#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char text[300];
    struct node *link;
};

struct node *uTop = NULL, *rTop = NULL, *hTop = NULL;
char current[300] = "";
char word[100], operation[100];
int i, pos, len, wlen, choice;

void undoPush()
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    strcpy(temp->text, current);
    temp->link = uTop;
    uTop = temp;
}

void redoPush()
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    strcpy(temp->text, current);
    temp->link = rTop;
    rTop = temp;
}

void clearRedo()
{
    struct node *temp;

    while (rTop != NULL)
    {
        temp = rTop;
        rTop = rTop->link;
        free(temp);
    }
}

void historyAdd()
{
    struct node *temp = malloc(sizeof(struct node));
    if (temp == NULL)
        return;

    strcpy(temp->text, operation);
    temp->link = hTop;
    hTop = temp;
}

void UNDO()
{
    struct node *temp;

    if (uTop == NULL)
    {
        printf("Nothing to undo\n");
        return;
    }

    redoPush();

    temp = uTop;
    strcpy(current, temp->text);
    uTop = uTop->link;
    free(temp);

    printf("Undo successful\n");
}

void REDO()
{
    struct node *temp;

    if (rTop == NULL)
    {
        printf("Nothing to redo\n");
        return;
    }

    undoPush();

    temp = rTop;
    strcpy(current, temp->text);
    rTop = rTop->link;
    free(temp);

    printf("Redo successful\n");
}

void ENTERTEXT()
{
    undoPush();

    printf("Enter text: ");
    scanf(" %299[^\n]", current);

    clearRedo();
    strcpy(operation, "Enter Text");
    historyAdd();
}

void DISPLAY()
{
    printf("Current text: %s\n", current);
}

void INSERT()
{
    printf("Enter word: ");
    scanf("%99s", word);

    printf("Enter position: ");
    scanf("%d", &pos);

    len = strlen(current);
    wlen = strlen(word);

    if (pos < 0 || pos > len)
    {
        printf("Invalid position\n");
        return;
    }

    if (len + wlen >= 300)
    {
        printf("Text is too long\n");
        return;
    }

    undoPush();

    for (i = len; i >= pos; i--)
        current[i + wlen] = current[i];

    for (i = 0; i < wlen; i++)
        current[pos + i] = word[i];

    clearRedo();
    strcpy(operation, "Insert");
    historyAdd();

    printf("Word inserted\n");
}

void DELETE()
{
    len = strlen(current);

    printf("Enter character position to delete: ");
    scanf("%d", &pos);

    if (pos < 0 || pos >= len)
    {
        printf("Invalid position\n");
        return;
    }

    undoPush();

    for (i = pos; i < len; i++)
        current[i] = current[i + 1];

    clearRedo();
    strcpy(operation, "Delete");
    historyAdd();

    printf("Character deleted\n");
}

void SEARCH()
{
    char *p;

    printf("Enter word to search: ");
    scanf("%99s", word);

    p = strstr(current, word);

    if (p != NULL)
        printf("Word found at position %ld\n",
               (long)(p - current));
    else
        printf("Word not found\n");
}

void REPLACE()
{
    len = strlen(current);

    printf("Enter character position to replace: ");
    scanf("%d", &pos);

    if (pos < 0 || pos >= len)
    {
        printf("Invalid position\n");
        return;
    }

    printf("Enter new character: ");
    scanf(" %c", &word[0]);

    undoPush();
    current[pos] = word[0];

    clearRedo();
    strcpy(operation, "Replace");
    historyAdd();

    printf("Character replaced\n");
}

void EDITHISTORY()
{
    struct node *temp;
    int count = 1;

    temp = hTop;

    if (temp == NULL)
    {
        printf("No edit history\n");
        return;
    }

    while (temp != NULL)
    {
        printf("%d. %s\n", count, temp->text);
        count++;
        temp = temp->link;
    }
}

void SPELLCHECK()
{
    if (strstr(current, "helo") != NULL)
        printf("Suggestion: hello\n");
    else if (strstr(current, "wrld") != NULL)
        printf("Suggestion: world\n");
    else if (strstr(current, "computr") != NULL)
        printf("Suggestion: computer\n");
    else
        printf("No spelling suggestions found\n");
}

int main()
{
    while (1) { printf("\n1.Undo\n 2.Redo\n 3.EnterText\n 4.Display\n 5.Insert\n 6.Delete\n 7.Search\n 8.Replace\n 9.EditHistory\n 10.SpellingChecker\n 11.exit\n");
     printf("Enter choice: "); 
     scanf("%d", &choice);
        switch (choice)
        {
            case 1: UNDO(); break;
            case 2: REDO(); break;
            case 3: ENTERTEXT(); break;
            case 4: DISPLAY(); break;
            case 5: INSERT(); break;
            case 6: DELETE(); break;
            case 7: SEARCH(); break;
            case 8: REPLACE(); break;
            case 9: EDITHISTORY(); break;
            case 10: SPELLCHECK(); break;
            case 11: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
