#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#include<time.h>

#include <pthread.h>

#include <stdbool.h>

#include <unistd.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>

pthread_t thread;
int counter;
pthread_mutex_t lock;
bool x;
int clientSocket;

int c = 0;
typedef struct alumnus {
  char Name[100];
  char Dob[100];
  char Gen[100];
  char Gid[100];
  char Dot[100];
  char Email[100];
  char Telephone_num[100];

};

struct Point {
  char name[100];
  char dob[20];
  char gender[20];
  char gid[100];
  char dot[20];
  int ticket_num;
  char email[100];
  char telephone_num[100];
};
const char * getfield(char * line, int num) {
  const char * tok;
  for (tok = strtok(line, ","); tok && * tok; tok = strtok(NULL, ",\n")) {
    if (!--num)
      return tok;
  }
  return NULL;
}

void reservation();
void inquiry();
void* modification(void* xyz);
void cancelation();

char buffer[1024];

int execute(int abc) {
  int clientSocket = abc;
  //printf("ClientSocket value: %d",clientSocket);
  char c;
  printf("Server>> To see menu press any key:\n");
  scanf("%c", & c);
  if (pthread_mutex_init( & lock, NULL) != 0) {
    printf("\n mutex init has failed\n");
    return 1;
  }
  while (1) {
    if (c != "") {
      printf("Server>> Choose any option from below:\n");
      printf("Server>> \n1. Make Reservation\n2. Inquiry about the ticket\n3. Modify the reservation\n4. Cancel the reservation\n5. Exit\n");
      int i;
      scanf("%d", &i);
      //printf("%d-------",i);
      sprintf(buffer, "%d", i);
      //printf("%s-------",buffer);
      send(clientSocket, buffer, strlen(buffer), 0);
      bzero(buffer, sizeof(buffer));
      //printf("[%s] after clearing the buffer-------",buffer);

      switch (i) {
      case 1:
        reservation();
        break;
      case 2:
        inquiry();
        break;
      case 3:
        pthread_create(&thread, NULL, &modification, NULL);
        pthread_join(thread, NULL);
        break;
      case 4:
        cancelation();
        break;
      case 5:
        return (1);
      default:
        printf("Server>> invalid choice\n");
      }
    }
  }
  pthread_mutex_destroy( & lock);
  return 0;
}

void reservation() {
  //clientSocket = xyz;
  c++;
  int customer;
  printf("Server>> For how many people do you want to reserve ticket:");
  printf("\nClient: ");
  scanf("%d", & customer);
  //printf("%d customeressssssssssssss",customer);
  sprintf(buffer, "%d", customer);
  //printf("#%s----",buffer);
  send(clientSocket, buffer, strlen(buffer), 0);
  bzero(buffer, sizeof(buffer));
  if (customer >= 0) {
    int counter = 0;
    int available[150];
    if (c == 1) {
      for (int i = 1; i <= 150; i++) {
        available[i] = i;
      }
    }
    for (int i = 1; i <= 150; i++) {
      if (available[i] != 0) {
        counter++;
      }

    }

    if (counter >= customer) {
      int y_n;
      int seat_choice[customer];
      printf("Server>> Seats are available\n");
      printf("Server>> Do you want to choose seats yourself?\n1.Yes\n2.No\n");
      scanf("%d", & y_n);
      
      sprintf(buffer, "%d", y_n);
      send(clientSocket, buffer, strlen(buffer), 0);
      bzero(buffer, sizeof(buffer));
      if (y_n == 1) {
        printf("Server>> Selected seats are available:(0 stands for not available)\n");
        for (int i = 1; i <= 150; i++) {
          printf("%d ", available[i]);
          if (i % 2 == 0)
            printf("\n");
        }

        printf("Server>> Enter the Seat No. You want to book for %d people:\n", customer);
        for (int i = 1; i <= customer; i++) {
          int a;
          scanf("%d", & a);
		  sprintf(buffer, "%d", a);
          send(clientSocket, buffer, strlen(buffer), 0);
          bzero(buffer, sizeof(buffer));
          if (available[a] == 0) {
            printf("Server>> This seat has already been booked. Choose another one:\n");
            i--;
          } else
            seat_choice[i] = a;

        }
        for (int i = 1; i <= 150; i++) {
          if (available[i] == i) {
            for (int j = 1; j <= customer; j++) {
              if (i == seat_choice[j])
                available[i] = 0;

            }
          }
        }
      }
      if (y_n == 2) {
        int customer1 = customer;
        for (int i = 1; i <= 150; i++) {
          if (available[i] == i && customer1 > 0) {
            available[i] = 0;
            seat_choice[customer1] = i;
            customer1--;
          }

        }

      }

      char result[50];
      srand(time(0));
      int ran = rand();
      sprintf(result, "%d", ran);
	  send(clientSocket, result, strlen(result), 0);
      char * file_name = result;
      char * file_extension = ".csv";
      strcat(file_name, file_extension);

      FILE * fpc, * fps;
      fpc = fopen(file_name, "a");
      int k = 1, l;
      struct Point p[10][10];
      while (k <= customer) {
        if (k == 1) {
          printf("Server>> Enter Name:");
		  printf("\nClient: ");
          scanf("%s", & p[k][c].name);
		  send(clientSocket, p[k][c].name, strlen(p[k][c].name), 0);
          printf("Server>> Enter Date of Birthday:");
		  printf("\nClient: ");
          scanf("%s", & p[k][c].dob);
		  send(clientSocket, p[k][c].dob, strlen(p[k][c].dob), 0);
          printf("Server>> Enter Gender:");
		  printf("\nClient: ");
          scanf("%s", & p[k][c].gender);
		  send(clientSocket, p[k][c].gender, strlen(p[k][c].gender), 0);
          printf("Server>> Enter Gov. ID:");
		  printf("\nClient: ");
          scanf("%s", & p[k][c].gid);
		  send(clientSocket, p[k][c].gid, strlen(p[k][c].gid), 0);
          printf("Server>> Enter Date of Travel(MM-DD-YY):");
		  printf("\nClient: ");
          scanf("%s", & p[k][c].dot);
		  send(clientSocket, p[k][c].dot, strlen(p[k][c].dot), 0);
          printf("Server>> Enter Your Telephone No.:");
		  printf("\nClient: ");
          scanf("%s", & p[k][c].telephone_num);
		  send(clientSocket, p[k][c].telephone_num, strlen(p[k][c].telephone_num), 0);
          printf("Server>> Enter Your Email ID:");
		  printf("\nClient: ");
          scanf("%s", & p[k][c].email);
		  send(clientSocket, p[k][c].email, strlen(p[k][c].email), 0);
          p[k][c].ticket_num = ran;
          fprintf(fpc, "%d,%s,%s,%s,%s,%s,%s,%s\n", p[k][c].ticket_num, p[k][c].name, p[k][c].dob, p[k][c].gender, p[k][c].gid, p[k][c].dot, p[k][c].telephone_num, p[k][c].email);

        } else {
          printf("Server>> Enter Name:");
		  printf("\nClient: ");
          scanf("%s", & p[k][c].name);
		  send(clientSocket, p[k][c].name, strlen(p[k][c].name), 0);
          printf("Server>> Enter Date of Birthday:");
		  printf("\nClient: ");
          scanf("%s", & p[k][c].dob);
		  send(clientSocket, p[k][c].dob, strlen(p[k][c].dob), 0);
          printf("Server>> Enter Gender:");
		  printf("\nClient: ");
          scanf("%s", & p[k][c].gender);
		  send(clientSocket, p[k][c].gender, strlen(p[k][c].gender), 0);
          printf("Server>> Enter Gov. ID:");
		  printf("\nClient: ");
          scanf("%s", & p[k][c].gid);
		  send(clientSocket, p[k][c].gid, strlen(p[k][c].gid), 0);
          p[k][c].ticket_num = ran;
          fprintf(fpc, "%d,%s,%s,%s,%s,%s\n", p[k][c].ticket_num, p[k][c].name, p[k][c].dob, p[k][c].gender, p[k][c].gid, p[1][c].dot);
        }
        k++;
        l = k - 1;
      }
      char result_1[50];
      sprintf(result_1, "%d", p[1][c].ticket_num);
	  send(clientSocket, result_1, strlen(result_1), 0);
      char * file_name_s = p[1][c].dot;
      strcat(file_name_s, file_extension);
      fps = fopen(file_name_s, "a");
      for (int i = 1; i <= l; i++)
        fprintf(fps, "%s,%s,%s,%d\n", result_1, p[i][c].name, p[i][c].gender, seat_choice[i]);
      fclose(fps);
      fclose(fpc);
    } else {
      printf("Server>> We haven't enough number of seats for %d people\n", customer);
    }
  } else {
    printf("Server>> Enter valid Number of customers:\n");
  }

}

void inquiry() {
  char result[50];
  int ticket_num;
  printf("Server>> please enter your Ticket Number that you want to inquiry:");
  scanf("%d", & ticket_num);
  sprintf(result, "%d", ticket_num);
  send(clientSocket, result, strlen(result), 0);
  char * file_name = result;
  char * file_extension = ".csv";
  strcat(file_name, file_extension);
  FILE * fpc = fopen(file_name, "r");

  if (fpc == NULL) {
    printf("Server>> Invalid Ticket Number\n");
  } else if (fpc != NULL) {
    char * buf_customer[100];
	printf("Server>> ");
    while (fscanf(fpc, "%s", buf_customer) == 1) {
      printf("%s \n", buf_customer);
    }
  }

}
void* modification(void* arg)

{
  pthread_mutex_lock( & lock);
  x = true;
  char as[100];
  char result[50];
  int ticket_num;
  printf("Server>> please enter your Ticket Number that you want to Modify:");
  scanf("%d", & ticket_num);
  sprintf(result, "%d", ticket_num);
  send(clientSocket, result, strlen(result), 0);
  char * file_name = result;
  char * file_extension = ".csv";
  strcat(file_name, file_extension);
  FILE * fpc = fopen(file_name, "r");
  FILE * ftest = fopen("test.csv", "r");

  if (ftest != NULL) {
    printf("Server>> This file can't be modified now!\n");
  } else {
  if (fpc == NULL) {
    printf("Server>> Invalid Ticket Number\n");
  } else if (fpc != NULL) {
    int lines = 0;
    FILE * fptr;
    fptr = fopen("test.csv", "a");
    char ch;
    int c;
    while (EOF != (fscanf(fpc, "%*[^\n]"), fscanf(fpc, "%*c"))) {
      ++lines;
    }
    struct alumnus REC1[100];

    fclose(fpc);
    fpc = fopen(file_name, "r");
    char ch1[100];
    char ch2[100];
    char ch3[100];
    char ch4[100];
    char ch5[100];
    char ch6[100];
    char ch7[100];
    char result_1[50];
    sprintf(result_1, "%d", ticket_num);
	send(clientSocket, result_1, strlen(result_1), 0);
    int k, l, m, n, o;
    k = l = m = n = o = 1;

    for (int i = 1; i <= lines; i++) {
      int j = 1;
      char line[1024];
      char * line1[100];
      char * line2[100];
      char * line3[100];
      char * line4[100];
      char * line5[100];
      char * line6[100];
      char * line7[100];
      while (fgets(line, 1024, fpc)) {
        char * tmp = strdup(line);
        strcpy(line1, getfield(tmp, 2));
        strcpy(REC1[k].Name, line1);
        printf("Server>> %s\n", REC1[k].Name);
        free(tmp);
        k++;
      }

      fclose(fpc);
      fpc = fopen(file_name, "r");
      while (fgets(line, 1024, fpc)) {
        char * tmp = strdup(line);
        strcpy(line2, getfield(tmp, 3));
        strcpy(REC1[l].Dob, line2);
        printf("Server>> %s\n", REC1[l].Dob);
        free(tmp);
        l++;
      }

      fclose(fpc);
      fpc = fopen(file_name, "r");
      while (fgets(line, 1024, fpc)) {
        char * tmp = strdup(line);
        strcpy(line3, getfield(tmp, 4));
        strcpy(REC1[m].Gen, line3);
        printf("Server>> %s\n", REC1[m].Gen);
        free(tmp);
        m++;
      }
      fclose(fpc);
      fpc = fopen(file_name, "r");
      while (fgets(line, 1024, fpc)) {
        char * tmp = strdup(line);
        strcpy(line4, getfield(tmp, 5));
        strcpy(REC1[n].Gid, line4);
        printf("Server>> %s\n", REC1[n].Gid);
        free(tmp);
        n++;
      }
      fclose(fpc);
      fpc = fopen(file_name, "r");
      while (fgets(line, 1024, fpc)) {
        char * tmp = strdup(line);
        strcpy(line5, getfield(tmp, 6));
        strcpy(REC1[o].Dot, line5);
        printf("Server>> %s\n", REC1[o].Dot);
        free(tmp);
        o++;
      }
      fclose(fpc);
      fpc = fopen(file_name, "r");
      fgets(line, 1024, fpc);
      char * tmp = strdup(line);
      strcpy(line6, getfield(tmp, 7));
      strcpy(REC1[1].Telephone_num, line6);
      printf("Server>> %s\n", REC1[1].Telephone_num);
      free(tmp);
      fclose(fpc);
      fpc = fopen(file_name, "r");
      fgets(line, 1024, fpc);
      char * tmp1 = strdup(line);
      strcpy(line7, getfield(tmp1, 8));
      strcpy(REC1[1].Email, line7);
      printf("Server>> %s\n", REC1[1].Email);
      free(tmp);
      if (i == 1) {

        while (j <= 1) {
          int press;
          printf("Server>>  Press 1 to change the name\n Press 2 to the change the date of birth\n Press 3 to change the gender\n Press 4 to change the government ID number\n Press 5 to change Phone Number\n Press 6 to change mail address\n Press 7 if you don't want to change anything over here\n");
          scanf("%d", & press);
          switch (press) {
          case 1:
            printf("Server>> Enter the new name:\n");
            scanf("%s", & ch1);
            strcpy(REC1[i].Name, ch1);
            break;
          case 2:
            printf("Server>> Enter the  DOB:\n");
            scanf("%s", & ch2);
            strcpy(REC1[i].Dob, ch2);

            break;
          case 3:
            printf("Server>> Enter the gender:\n");
            scanf("%s", & ch3);
            strcpy(REC1[i].Gen, ch3);

            break;
          case 4:
            printf("Server>> Enter the Gov ID:\n");
            scanf("%s", & ch4);
            strcpy(REC1[i].Gid, ch4);
            break;
          case 5:
            printf("Server>> Enter the Phone Number:\n");
            scanf("%s", & ch5);
            strcpy(REC1[i].Telephone_num, ch5);
            break;
          case 6:
            printf("Server>> Enter the Email ID:\n");
            scanf("%s", & ch6);
            strcpy(REC1[i].Email, ch6);
            break;
          case 7:
            break;
          default:
            break;
          }
          j++;
        }
        fprintf(fptr, "%s,%s,%s,%s,%s,%s,%s,%s\n", result_1, REC1[i].Name, REC1[i].Dob, REC1[i].Gen, REC1[i].Gid, REC1[i].Dot, REC1[i].Telephone_num, REC1[i].Email);
        //printf("Server>> %s",as);

      }
      //strcpy(as,REC1[1].Name);

      if (i > 1) {

        while (j <= 1) {
          int press;
          printf("Server>>  Press 1 to change the name\n Press 2 to the change the date of birth\n Press 3 to change the gender\n Press 4 to change the government ID number\n Press 5 if you don't want to change anything over here\n");
          scanf("%d", & press);
		  send(clientSocket, buffer, strlen(buffer), 0);
		  bzero(buffer, sizeof(buffer));
          switch (press) {
          case 1:
            printf("Server>> Enter the new name:\n");
            scanf("%s", & ch1);
            strcpy(REC1[i].Name, ch1);
            break;
          case 2:
            printf("Server>> Enter the  DOB:\n");
            scanf("%s", & ch2);
            strcpy(REC1[i].Dob, ch2);

            break;
          case 3:
            printf("Server>> Enter the gender:\n");
            scanf("%s", & ch3);
            strcpy(REC1[i].Gen, ch3);

            break;
          case 4:
            printf("Server>> Enter the Gov ID:\n");
            scanf("%s", & ch4);
            strcpy(REC1[i].Gid, ch4);
            break;
          case 5:
            break;
          default:
            break;
          }
          j++;
        }
        fprintf(fptr, "%s,%s,%s,%s,%s,%s\n", result_1, REC1[i].Name, REC1[i].Dob, REC1[i].Gen, REC1[i].Gid, REC1[i].Dot);
      }
    }
	
    //FILE* fpc = fopen(file_name,"r");
    char line[1024];
    char * line1[100];
    while (fgets(line, 1024, fpc)) {
      char * tmp = strdup(line);
      strcpy(line1, getfield(tmp, 6));
	        free(tmp);
	     }
    char * file_name_s[100];
    strcpy(file_name_s, line1);
    strcat(file_name_s, file_extension);
    FILE * fps = fopen(file_name_s, "r");
    FILE * fps1 = fopen("server_record1.csv", "a");
    int a;
    char * line_a[1024];
    char line_1[100];
    char comparing_1[100];
    int s = 1;
    char comparing[100];

    char line_t[100];
    while (fgets(line_a, 1024, fps)) {
      char comparing[100];
      char * tmp = strdup(line_a);
      char * ts = getfield(tmp, 1);
      strcpy(line_1, ts);
	        free(tmp);
      for (int i = 0; i < strlen(line_1); i++) {
        comparing[i] = line_1[i];
      }
      a = strcmp(comparing, result_1);
      printf("Server>> [%s]\n", comparing);
      printf("Server>> [%s]\n", result_1);
      printf("Server>> %d", a);
      if (a >= 0 && s <= lines) {
        char * tmp1 = strdup(line_a);
        char * ts1 = getfield(tmp1, 4);
        strcpy(line_t, ts1);
        free(tmp1);
        fprintf(fps1, "%s,%s,%s,%s\n", result_1, REC1[s].Name, REC1[s].Gen, line_t);
        s++;
      } else {
        fprintf(fps1, "%s", line_a);
      }
    }
    fclose(fptr);
    fclose(fpc);
    char newname[100];
    strcpy(newname, file_name);
    remove(file_name);
    remove(newname);
    rename("test.csv", newname);

    fclose(fps);
    fclose(fps1);
    char newname_s[100];
    strcpy(newname_s, file_name_s);
    remove(newname_s);
    rename("server_record1.csv", newname_s);
	strcpy(result_1,"");
	strcpy(comparing,"");
	strcpy(line_1,"");    
  }
  }
	pthread_mutex_unlock( & lock);
}

void cancelation() {
  char result[50];
  int ticket_num;
  printf("Server>> please enter your Ticket Number that you want to cancel:");
  scanf("%d", & ticket_num);
  sprintf(result, "%d", ticket_num);
  send(clientSocket, result, strlen(result), 0);
  char * file_name = result;
  char * file_extension = ".csv";
  strcat(file_name, file_extension);
  FILE * fpc = fopen(file_name, "r");

  if (fpc == NULL) {
    printf("Server>> Invalid Ticket Number\n");
  } else if (fpc != NULL) {
    char line[1024];
    char * line1[100];
    while (fgets(line, 1024, fpc)) {

      char * tmp = strdup(line);
      strcpy(line1, getfield(tmp, 6));
      free(tmp);
    }
    char * file_name_s[100];

    strcpy(file_name_s, line1);
    strcat(file_name_s, file_extension);
    FILE * fps = fopen(file_name_s, "r");
    FILE * fps1 = fopen("server_record1.csv", "w");
    char * buf_server[100];
    int a, j = 0;
    char result_1[100];
    sprintf(result_1, "%d", ticket_num);

    char * line_a[1024];
    char line_1[100];
    while (fgets(line_a, 1024, fps)) {
      char comparing[100];
      char * tmp = strdup(line_a);
      char * ts = getfield(tmp, 1);
      strcpy(line_1, ts);
      free(tmp);
      for (int i = 0; i < strlen(line_1); i++) {
        comparing[i] = line_1[i];
      }
      a = strcmp(comparing, result_1);
      if (a == 0) {
        j++;
        if (j == 1)
          printf("Server>> Ticket Number has been found by the system\nCancellation is Processing....\n");
      } else {
        fprintf(fps1, "%s\n", line_a);
      }
    }
    if (j = !0)
      printf("Server>> \nCanceled\n");
    fclose(fpc);
    fclose(fps);
    fclose(fps1);
    char oldname[] = "srever_record1.csv";
    char newname[] = "server_record.csv";
    strcpy(newname, file_name_s);
    remove(file_name);
    remove(file_name_s);
    remove(newname);
    rename("server_record1.csv", newname);

  }

}