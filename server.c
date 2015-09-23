/* to compile me in Linux, type:   gcc -o server server.c -lpthread */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "vxcore_lib.h"
#include "vxscripts.h"
#include "vxuser.h"

void * serverthread(void * parm);       /* thread function prototype    */

pthread_mutex_t  mut;

int visits =  0;                        /* counts client connections     */

char current_user[MAX_SIZE];

int main (int argc, char *argv[])
{
	//struct   hostent   *ptrh;     /* pointer to a host table entry */
	struct   protoent  *ptrp;     /* pointer to a protocol table entry */
	struct   sockaddr_in sad;     /* structure to hold server's address */
	struct   sockaddr_in cad;     /* structure to hold client's address */
	int      sd, sd2;             /* socket descriptors */
	int      port;                /* protocol port number */
	//int      alen;                /* length of address */
	socklen_t           alen;
	pthread_t  tid;             /* variable to hold thread ID */
	
	char msg[MAX_SIZE];

	pthread_mutex_init(&mut, NULL);
	memset((char  *)&sad,0,sizeof(sad)); /* clear sockaddr structure   */
	sad.sin_family = AF_INET;            /* set family to Internet     */
	sad.sin_addr.s_addr = INADDR_ANY;    /* set the local IP address */

    /* Check  command-line argument for protocol port and extract      */
    
    if (argc > 1) {                        /* if argument specified     */
		port = atoi (argv[1]); /* convert argument to binary*/
    } else {
		port = PROTOPORT;     /* use default port number   */
    }
    if (port > 0)                          /* test for illegal value    */
		sad.sin_port = htons((u_short)port);
    else {                                /* print error message and exit */
		fprintf (stderr, "bad port number %s/n",argv[1]);
		exit (1);
    }
     
    if ( ((int)(ptrp = getprotobyname("tcp"))) == 0){  /* Map TCP transport protocol name to protocol number */ 
		fprintf(stderr, "cannot map \"tcp\" to protocol number");
		exit (1);
    }
    
    sd = socket (PF_INET, SOCK_STREAM, ptrp->p_proto); /* Create a socket */
    if (sd < 0) {
		fprintf(stderr, "socket creation failed\n");
		exit(1);
    }

    if (bind(sd, (struct sockaddr *)&sad, sizeof (sad)) < 0) { /* Bind a local address to the socket */
		fprintf(stderr,"bind failed\n");
		exit(1);
    }
    
    if (listen(sd, QLEN) < 0) { /* Specify a size of request queue */
		fprintf(stderr,"listen failed\n");
		exit(1);
    }

    alen = sizeof(struct sockaddr_in);
	
	/* Main server loop - accept and handle requests */
    fprintf( stderr, "Starting server.\n");
	while (1)
	{
		printf("waiting ...\n");
		sd2=accept(sd, (struct sockaddr *)&cad, &alen);
		if (sd2 < 0)
		{
			fprintf(stderr, "accept failed\n");
			exit (1);
		}
		
		//user login
		send(sd2,"Enter user name: ",17,0);
		if ( recv(sd2, msg, sizeof(msg), 0)!=0 )
		{
			get_user("user.conf");			//get struct User_Base
			char *u_test=select_user(msg); 	//True if the user exists
			//printf("%s\n",msg);
			if (strstr(u_test,"True")!=NULL)
			{
				printf("login %s\n",msg);
				v_read ("data.db", msg);				//load data base
				char lg[255]="login ";
				strcat (lg, msg);
				strcat (lg, "\n");
				send(sd2,lg,strlen(lg),0);				
				strcpy(current_user,msg);		////Copy user name in current_user
				pthread_create(&tid, NULL, serverthread, (void *) sd2 );
				bzero(msg,MAX_SIZE);
				//return(1);
			}else
			{
				send(sd2,"Enter user name: ",17,0);
				bzero(msg,MAX_SIZE);
			}
		}
		bzero(msg,MAX_SIZE);
		//pthread_create(&tid, NULL, serverthread, (void *) sd2 );
     }
     close(sd);
}

void * serverthread(void * parm)
{
	int tsd, tvisits;
	char buf[MAX_SIZE];             //buffer for string the server sends
	char tmp[MAX_SIZE];
	char pt_user[MAX_SIZE];
	int pt_count=counter;			//copy counter to pt_count
	
	strcpy(pt_user, current_user);		//user name for thread
	struct VLine pt_line[1024];		//struct data for thread
	
	tsd = (int) parm;
	
	pthread_mutex_lock(&mut);
	tvisits = ++visits;
	pthread_mutex_unlock(&mut);

	sprintf(buf,"This server has been contacted %d time%s\n",
	   tvisits, tvisits==1?".":"s.");

	printf("SERVER thread: %s", buf);
	
	int l=0;
	while (l!=pt_count)			//copy stuct v_line to pt_line
	{
		strcpy(pt_line[l].v_name, v_line[l].v_name);
		strcpy(pt_line[l].v_user, v_line[l].v_user);
		strcpy(pt_line[l].v_type, v_line[l].v_type);
		strcpy(pt_line[l].v_data, v_line[l].v_data);
		strcpy(pt_line[l].v_id, v_line[l].v_id);
		l++;
	}
	
	//session server to client
	while (1)
	{		
		if ( recv(tsd, tmp, sizeof(tmp), 0)!=0 )
		{
			if (strstr(tmp,"read")!=NULL)
			{				
				int i=0;
				while (i != pt_count)
				{
					send(tsd,pt_line[i].v_name,strlen(pt_line[i].v_name),0);
					send(tsd,pt_line[i].v_type,strlen(pt_line[i].v_type),0);
					send(tsd,pt_line[i].v_data,strlen(pt_line[i].v_data),0);
					send(tsd,pt_line[i].v_id,strlen(pt_line[i].v_id),0);
					i++;
				}
				bzero(tmp,MAX_SIZE);
			}
			if (strstr(tmp,"user")!=NULL)
			{				
				send(tsd,pt_user,strlen(pt_user),0);
				bzero(tmp,MAX_SIZE);
			}
			if (strstr(tmp,"q")!=NULL)
			{
				printf("Quit user: %s\n",pt_user);
				bzero(tmp,MAX_SIZE);
				close(tsd);
				pthread_exit(0);
			}
			if (strstr(tmp,"ls")!=NULL)
			{
				printf(">>>>>ls\n");
				send(tsd,">>>ls",6,0);
				bzero(tmp,MAX_SIZE);
			}else{
				printf("Data send:%s\n", tmp);
				send(tsd,tmp,strlen(tmp),0);
				bzero(tmp,MAX_SIZE);
			}
		}
	bzero(tmp,MAX_SIZE);
	}
	
   close(tsd);
   pthread_exit(0);
   exit(0);   
}
