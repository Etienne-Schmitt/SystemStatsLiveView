#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include "RS232.h"

pthread_t Reception, Transmission;
pthread_mutex_t mutex;
sem_t sem;


struct sockaddr_rc loc_addr = {0}, rem_addr = {0};
char buffer[32] = { 0 }, receive_addr[8] = { 0 };
int sock, client, status;
socklen_t opt = sizeof(rem_addr);

int *sendOutput();

void main()
{
    printf("Starting Bluetooth Server\n");
    sem_init(&sem, 0, 0);

    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;

    bind(sock, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    listen(sock, 10);

    pthread_create(&Reception, NULL, readInput, NULL);
    pthread_create(&Transmission, NULL, sendOutput, NULL);

    

    while (1)
    {
        sleep(1);
    }
    close(client);
    close(sock);
}

int *sendOutput()
{
    while (1) //Thread 2
    {
        sem_wait(&sem);

        if (client = accept(sock, (struct sockaddr *)&rem_addr, &opt))
        {
            ba2str( &rem_addr.rc_bdaddr, receive_addr );
            fprintf(stderr, "Connexion recu de : %s\n", receive_addr);

            status = write(sock, "Test !", 6);
            if (status < 0)
            {
                perror("Sending error");
                exit(1);
            }
/*
            while (1)
            {            
                sem_wait(&sem);
                status = write(sock, "Test !", 6);

                if (status < 0)
                {
                    perror("Sending error");
                    exit(1);
                }
            }
            */
        }

       
        printf("sendOutput() : buffer = %s\n", buffer);
    }
    pthread_exit(NULL);
    return 0;
}