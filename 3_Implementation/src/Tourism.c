/*
    OPTIMIZED TOURISM MANAGEMENT SYSTEM
    ----------------------------------
    Features:
    - User Registration/Login
    - Book Ticket
    - Cancel Ticket
    - Print Ticket
    - Change Password
    - File Handling
    - Linked List Storage
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100
#define TOUR_COUNT 10

typedef struct User
{
    char username[MAX_STR];
    char password[MAX_STR];
    char place[MAX_STR];

    float price;
    int numtick;

    struct User *next;

} user;

typedef struct
{
    char code[10];
    char name[100];
    float price;

} Tour;

Tour tours[TOUR_COUNT] =
{
    {"LL",  "Antelope Canyon Tours",      40000},
    {"JK",  "Grand Canyon Local Tours",   60000},
    {"SK",  "San Francisco Local Tours",  25000},
    {"SHM", "Miami Vacation",             38000},
    {"AND", "Hawaii",                     120000},
    {"BHB", "Atlanta Vacation",           10000},
    {"AG",  "San Francisco",              30000},
    {"ND",  "Alaska Vacation",            32000},
    {"RJ",  "Orlando Vacation",           45000},
    {"SI",  "South US Tour",              250000}
};

char currentuser[MAX_STR] = "";

typedef enum
{
    MENU,
    LOGGED_IN

} State;

State currentstate = MENU;

/* -------------------------------------------------- */

void clearInput()
{
    int c;

    while((c = getchar()) != '\n' && c != EOF);
}

/* -------------------------------------------------- */

user* FindUser(user *head, const char *username)
{
    while(head)
    {
        if(strcmp(head->username, username) == 0)
            return head;

        head = head->next;
    }

    return NULL;
}

/* -------------------------------------------------- */

void WriteToFile(user *head)
{
    FILE *fp = fopen("users.txt", "w");

    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while(head)
    {
        fprintf(fp,
                "%s %s %s %.2f %d\n",
                head->username,
                head->password,
                head->place,
                head->price,
                head->numtick);

        head = head->next;
    }

    fclose(fp);
}

/* -------------------------------------------------- */

user* InitializeList()
{
    FILE *fp = fopen("users.txt", "r");

    if(fp == NULL)
        return NULL;

    user temp;
    user *head = NULL;
    user *tail = NULL;

    while(fscanf(fp,
                 "%99s %99s %99s %f %d",
                 temp.username,
                 temp.password,
                 temp.place,
                 &temp.price,
                 &temp.numtick) == 5)
    {
        user *newNode = (user*)malloc(sizeof(user));

        if(newNode == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(fp);
            return head;
        }

        *newNode = temp;
        newNode->next = NULL;

        if(head == NULL)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(fp);

    return head;
}

/* -------------------------------------------------- */

void ShowBrochure()
{
    printf("\n=========== TOUR PACKAGES ===========\n\n");

    for(int i = 0; i < TOUR_COUNT; i++)
    {
        printf("%-5s %-30s Rs %.2f\n",
               tours[i].code,
               tours[i].name,
               tours[i].price);
    }

    printf("\n");
}

/* -------------------------------------------------- */

user* AddUser(user *head)
{
    user *newUser = (user*)malloc(sizeof(user));

    if(newUser == NULL)
    {
        printf("Memory allocation failed.\n");
        return head;
    }

    printf("Enter Username/Email: ");
    scanf("%99s", newUser->username);

    if(FindUser(head, newUser->username))
    {
        printf("User already exists.\n");
        free(newUser);
        return head;
    }

    clearInput();

    printf("Enter Password: ");
    fgets(newUser->password, MAX_STR, stdin);

    newUser->password[strcspn(newUser->password, "\n")] = '\0';

    strcpy(newUser->place, "N/A");

    newUser->price = 0;
    newUser->numtick = 0;
    newUser->next = NULL;

    if(head == NULL)
    {
        head = newUser;
    }
    else
    {
        user *temp = head;

        while(temp->next)
            temp = temp->next;

        temp->next = newUser;
    }

    WriteToFile(head);

    printf("Registration Successful!\n");

    return head;
}

/* -------------------------------------------------- */

void LoginUser(user *head)
{
    char username[MAX_STR];
    char password[MAX_STR];

    printf("Enter Username: ");
    scanf("%99s", username);

    clearInput();

    printf("Enter Password: ");
    fgets(password, MAX_STR, stdin);

    password[strcspn(password, "\n")] = '\0';

    user *u = FindUser(head, username);

    if(u == NULL)
    {
        printf("User not found.\n");
        return;
    }

    if(strcmp(u->password, password) == 0)
    {
        currentstate = LOGGED_IN;

        strcpy(currentuser, username);

        printf("Login Successful!\n");
    }
    else
    {
        printf("Incorrect Password.\n");
    }
}

/* -------------------------------------------------- */

void BookTicket(user *head)
{
    user *u = FindUser(head, currentuser);

    if(u == NULL)
        return;

    if(strcmp(u->place, "N/A") != 0)
    {
        printf("Cancel existing booking first.\n");
        return;
    }

    ShowBrochure();

    char code[20];
    int tickets;

    printf("Enter Tour Code: ");
    scanf("%19s", code);

    int found = 0;

    for(int i = 0; i < TOUR_COUNT; i++)
    {
        if(strcmp(code, tours[i].code) == 0)
        {
            found = 1;

            printf("Enter Number of Tickets: ");
            scanf("%d", &tickets);

            if(tickets <= 0)
            {
                printf("Invalid ticket count.\n");
                return;
            }

            strcpy(u->place, code);

            u->price = tours[i].price;
            u->numtick = tickets;

            WriteToFile(head);

            printf("Booking Successful!\n");

            return;
        }
    }

    if(!found)
        printf("Invalid Tour Code.\n");
}

/* -------------------------------------------------- */

void CheckTicket(user *head)
{
    user *u = FindUser(head, currentuser);

    if(u == NULL)
        return;

    if(strcmp(u->place, "N/A") == 0)
    {
        printf("No tickets booked.\n");
        return;
    }

    float total = u->price * u->numtick;

    printf("\n========== TICKET DETAILS ==========\n");

    printf("Tour Code      : %s\n", u->place);
    printf("Ticket Price   : %.2f\n", u->price);
    printf("Total Tickets  : %d\n", u->numtick);
    printf("Total Cost     : %.2f\n", total);
}

/* -------------------------------------------------- */

void PrintTicket(user *head)
{
    user *u = FindUser(head, currentuser);

    if(u == NULL)
        return;

    if(strcmp(u->place, "N/A") == 0)
    {
        printf("No booking found.\n");
        return;
    }

    char filename[150];

    sprintf(filename, "%s_ticket.txt", u->username);

    FILE *fp = fopen(filename, "w");

    if(fp == NULL)
    {
        printf("Unable to create ticket file.\n");
        return;
    }

    float total = u->price * u->numtick;

    fprintf(fp,
            "=========== TOURISM TICKET ===========\n\n");

    fprintf(fp, "User           : %s\n", u->username);
    fprintf(fp, "Tour Code      : %s\n", u->place);
    fprintf(fp, "Price          : %.2f\n", u->price);
    fprintf(fp, "Tickets        : %d\n", u->numtick);
    fprintf(fp, "Total Cost     : %.2f\n", total);

    fclose(fp);

    printf("Ticket printed successfully.\n");
}

/* -------------------------------------------------- */

void CancelTicket(user *head)
{
    user *u = FindUser(head, currentuser);

    if(u == NULL)
        return;

    if(strcmp(u->place, "N/A") == 0)
    {
        printf("No booking found.\n");
        return;
    }

    float refund = u->price * u->numtick;

    printf("Booking Cancelled.\n");
    printf("Refund Amount: %.2f\n", refund);

    strcpy(u->place, "N/A");

    u->price = 0;
    u->numtick = 0;

    WriteToFile(head);
}

/* -------------------------------------------------- */

void ChangePassword(user *head)
{
    user *u = FindUser(head, currentuser);

    if(u == NULL)
        return;

    char oldpass[MAX_STR];
    char newpass[MAX_STR];

    clearInput();

    printf("Enter Current Password: ");
    fgets(oldpass, MAX_STR, stdin);

    oldpass[strcspn(oldpass, "\n")] = '\0';

    if(strcmp(oldpass, u->password) != 0)
    {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter New Password: ");
    fgets(newpass, MAX_STR, stdin);

    newpass[strcspn(newpass, "\n")] = '\0';

    strcpy(u->password, newpass);

    WriteToFile(head);

    printf("Password Changed Successfully.\n");
}

/* -------------------------------------------------- */

void LogoutUser()
{
    if(currentstate == MENU)
    {
        printf("No user logged in.\n");
        return;
    }

    currentstate = MENU;

    strcpy(currentuser, "");

    printf("Logged out successfully.\n");
}

/* -------------------------------------------------- */

void FreeList(user *head)
{
    user *temp;

    while(head)
    {
        temp = head;

        head = head->next;

        free(temp);
    }
}

/* -------------------------------------------------- */

int main()
{
    user *head = InitializeList();

    int choice;

    while(1)
    {
        printf("\n========== TOURISM MANAGEMENT ==========\n");

        if(currentstate == MENU)
        {
            printf("1. Register\n");
            printf("2. Login\n");
            printf("3. Exit\n");

            printf("Enter Choice: ");
            scanf("%d", &choice);

            switch(choice)
            {
                case 1:
                    head = AddUser(head);
                    break;

                case 2:
                    LoginUser(head);
                    break;

                case 3:
                    FreeList(head);

                    printf("Exiting Program...\n");

                    return 0;

                default:
                    printf("Invalid choice.\n");
            }
        }
        else
        {
            printf("\nLogged in as: %s\n", currentuser);

            printf("1. Show Brochure\n");
            printf("2. Book Ticket\n");
            printf("3. Check Ticket\n");
            printf("4. Print Ticket\n");
            printf("5. Cancel Ticket\n");
            printf("6. Change Password\n");
            printf("7. Logout\n");

            printf("Enter Choice: ");
            scanf("%d", &choice);

            switch(choice)
            {
                case 1:
                    ShowBrochure();
                    break;

                case 2:
                    BookTicket(head);
                    break;

                case 3:
                    CheckTicket(head);
                    break;

                case 4:
                    PrintTicket(head);
                    break;

                case 5:
                    CancelTicket(head);
                    break;

                case 6:
                    ChangePassword(head);
                    break;

                case 7:
                    LogoutUser();
                    break;

                default:
                    printf("Invalid choice.\n");
            }
        }
    }

    return 0;
}
