#ifndef TOURISM_H_INCLUDED
#define TOURISM_H_INCLUDED
 
enum state{menu,loggedin};
enum state current state=menu;

typedef struct user
{
char username[100];
char password[100];
char place[100];
float price;
int numtick;
struct user*next;
}user;

void ShowBrochure();
user* InitializeList(user*);
user* AddUser(user*);
void LoginUser(user*);
void BookTicket(user*);
void PrintTicket(user*);
void CancelTicket(user*);
void ChangePassword(user*);
void LogoutUser();
void CheckTicket(user*);
void DisplayAll(user*);
void WriteToFile(user*);
void ExitProgram();

char currenttuser[100];


#endif // TOURISM
