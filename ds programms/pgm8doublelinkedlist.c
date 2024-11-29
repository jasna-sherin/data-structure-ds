#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *Rlink;
    struct Node *Llink;
};

struct Node *header = NULL;

struct Node *CreateNode(int data)
{
    struct Node *newnode;
    newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->data = data;
    newnode->Rlink = NULL;
    newnode->Llink = NULL;
    return (newnode);
}

void insertAtFront(int data)
{
    struct Node *newnode;

    if (header == NULL)
    {
        newnode = CreateNode(data);
        header = newnode;
        printf("Inserted %d at position 0\n", data);
    }
    else
    {
        newnode = CreateNode(data);
        newnode->Llink = NULL;
        newnode->Rlink = header;
        header->Llink = newnode;
        header = newnode;
        printf("Inserted %d at position 0\n", data);
    }
}

void insertAtEnd(int data)
{
    struct Node *newnode = CreateNode(data);
    struct Node *ptr = header;
    int position = 0;

    if (header == NULL)
    {
        header = newnode;
        printf("Inserted %d at position 0\n", data);
    }
    else
    {
        while (ptr->Rlink != NULL)
        {
            ptr = ptr->Rlink;
            position++;
        }
        position++;
        ptr->Rlink = newnode;
        newnode->Llink = ptr;
        printf("Inserted %d at position %d\n", data, position);
    }
}

void insertAtAny(int data, int pos)
{
    struct Node *newnode = CreateNode(data);
    struct Node *ptr = header, *prev;
    int currentPos = 0;

    if (pos == 0)
    {
        newnode->Rlink = header;
        if (header != NULL)
            header->Llink = newnode;
        header = newnode;
        printf("Inserted %d at position 0\n", data);
    }
    else
    {
        while (ptr != NULL && currentPos < pos)
        {
            prev = ptr;
            ptr = ptr->Rlink;
            currentPos++;
        }
        if (currentPos == pos)
        {
            newnode->Llink = prev;
            newnode->Rlink = ptr;
            prev->Rlink = newnode;
            if (ptr != NULL)
                ptr->Llink = newnode;
            printf("Inserted %d at position %d\n", data, pos);
        }
        else
        {
            printf("Position %d not found\n", pos);
            free(newnode);
        }
    }
}

void deleteAtFront()
{
    struct Node *ptr = header;

    if (header == NULL)
        printf("Empty List\n");
    else
    {
        printf("Deleted %d from position 0\n", ptr->data);
        header = header->Rlink;
        if (header != NULL)
            header->Llink = NULL;
        free(ptr);
    }
}

void deleteAtEnd()
{
    struct Node *prev = NULL, *ptr = header;
    int position = 0;

    if (header == NULL)
        printf("Empty List\n");
    else
    {
        while (ptr->Rlink != NULL)
        {
            prev = ptr;
            ptr = ptr->Rlink;
            position++;
        }
        printf("Deleted %d from position %d\n", ptr->data, position);
        if (prev != NULL)
            prev->Rlink = NULL;
        else
            header = NULL;
        free(ptr);
    }
}

void deleteAtAny(int key)
{
    struct Node *prev = NULL, *ptr = header;
    int position = 0;

    if (header == NULL)
        printf("List is Empty\n");
    else if (ptr->data == key)
    {
        header = ptr->Rlink;
        if (header != NULL)
            header->Llink = NULL;
        printf("Deleted %d from position 0\n", key);
        free(ptr);
    }
    else
    {
        while (ptr != NULL && ptr->data != key)
        {
            prev = ptr;
            ptr = ptr->Rlink;
            position++;
        }
        if (ptr == NULL)
            printf("Key %d not found\n", key);
        else
        {
            printf("Deleted %d from position %d\n", key, position);
            prev->Rlink = ptr->Rlink;
            if (ptr->Rlink != NULL)
                ptr->Rlink->Llink = prev;
            free(ptr);
        }
    }
}

void traversal()
{
    struct Node *ptr = header;
    printf("List: ");
    while (ptr != NULL)
    {
        printf("%d\t", ptr->data);
        ptr = ptr->Rlink;
    }
    printf("\n");
}

void search(int key)
{
    struct Node *ptr = header;
    int position = 0;

    while (ptr != NULL)
    {
        if (ptr->data == key)
        {
            printf("Element %d found at position %d\n", key, position);
            return;
        }
        ptr = ptr->Rlink;
        position++;
    }

    printf("Element %d not found in the list\n", key);
}

int main()
{
    int choice, data, key;
    while (choice != 9)
    {
        printf("1.Insert at Front\n2.Insert at End\n3.Insert at Any\n4.Delete at End\n5.Delete at First\n6.Delete at Any\n7.Traverse\n8.Search\n9.Exit\n");
        printf("Enter Choice\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            insertAtFront(data);
            break;
        case 2:
            printf("Enter data: ");
            scanf("%d", &data);
            insertAtEnd(data);
            break;
        case 3:
            printf("Enter position: ");
            scanf("%d", &key);
            printf("Enter data: ");
            scanf("%d", &data);
            insertAtAny(data, key);
            break;
        case 4:
            deleteAtEnd();
            break;
        case 5:
            deleteAtFront();
            break;
        case 6:
            traversal();
            printf("Enter element to delete: ");
            scanf("%d", &key);
            deleteAtAny(key);
            break;
        case 7:
            traversal();
            break;
        case 8:
            printf("Enter key to search: ");
            scanf("%d", &key);
            search(key);
            break;
        case 9:
            return 0;
        default:
            printf("Wrong Choice\n");
        }
    }
    return 0;
}
