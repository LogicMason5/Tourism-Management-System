#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("\t\t\t==== || TOURISM MANAGEMENT SYSTEM || ====\n");
    user *h=NULL;
    int ch1,ch2;
    h=InitializeList(h);
    while (1)
    {
    	
        if(currentstate==menu)
        {
        	
            printf("\n\t\t\t\tAdd User - 1\n\t\t\t\tLogin User - 2\n\t\t\t\tBrochure - 3\n\t\t\t\tExit - 4\n\n\t\t\t\tEnter:");
            scanf("%d",&ch1);
            switch(ch1)
            {
                case 1:
                    h=AddUser(h);
                    break;
                case 2:
                    LoginUser(h);
                    break;
                case 3:
                    ShowBrochure();
                    break;
                case 4:
                    ExitProgram();
                    exit(0);
                    break;
                default:
                    printf("Not a valid input at this stage\n");
            }
        }
        else if(currentstate==loggedin)
        {
        system("CLS");
        printf("\n\t\t\t\t=========================");
		printf("\n\t\t\t\tTOURISM MANAGEMENT SYSTEM");
		printf("\n\t\t\t\t=========================\n");	
            printf("\n\t\t\t\tBook Package - 1\n\t\t\t\tCheck Ticket - 2\n\t\t\t\tPrint Ticket - 3\n\t\t\t\tCancel Ticket - 4\n\t\t\t\tChange Password - 5"
                   "\n\t\t\t\tLogout User - 6\n\t\t\t\tBrochure - 7\n\t\t\t\tExit - 8\n");
            scanf("%d",&ch2);
            switch(ch2)
            {
                case 1:
                    BookTicket(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 2:
                    CheckTicket(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 3:
                    PrintTicket(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 4:
                    CancelTicket(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 5:
                    ChangePassword(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 6:
                    LogoutUser(h);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 7:
                    ShowBrochure();
                    system("PAUSE");
                    system("CLS");
                    break;
                case 8:
                    ExitProgram();
                    exit(0);
                    break;
                default:
                    printf("Not a valid input at this stage\n");
            }
        }
    }
    return 0;
}
