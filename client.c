#include "client-server.h"

int main(int argc, char const *argv[]){
	char data_buff[1024];
	int sock,d_send,d_recv;
	struct sockaddr_in server;

	if(argc != 3){
		puts("Error! Ejecutar como ./client <<direccion ip>> <<numero de puerto>>");
	}else{
		system("clear");
		puts("Iniciando el cliente...");
		printf("Creando socket... ");
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		if(sock == -1){
			perror("(socket) Error");
			exit(1);
		}
		puts("Hecho.");

		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr(argv[1]);
		server.sin_port = htons(atoi(argv[2]));
		int server_len = sizeof(server);

		do{
			memset(data_buff,0,sizeof(data_buff));
			printf("\nIngrese el mensaje: ");
			fgets(data_buff,sizeof(data_buff),stdin);
			deleteNewLine(data_buff);

			printf("\nEnviando mensaje... ");
			d_send = sendto(sock,data_buff,sizeof(data_buff),0,(struct sockaddr *)&server,(socklen_t)server_len);
			if(d_send == -1){
				perror("(sendto) Error");
				exit(-1);
			}puts("Hecho.");	

			printf("\nRecibiendo mensaje... ");
			memset(data_buff, 0, sizeof(data_buff));
			d_recv = recvfrom(sock,data_buff,sizeof(data_buff),0,(struct sockaddr *)&server,(socklen_t*)&server_len);
			if(d_recv == -1){
				perror("(recvfrom) Error");
				exit(-1);
			}printf("Mensaje recibido: %s\n",data_buff);
		}while(strcmp(data_buff,"Fin") != 0);

		printf("\nComunicacion terminada.\nCerrando socket... ");
		close(sock);
		puts("Hecho.");
	}

	return 0;
}