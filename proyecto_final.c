#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char **argv){
  int i,j,np,pid,iteraciones,k,n=3;
  int filas=7;

  int envio[4];
  int arregloA[np];
  double Ti,Tf;

  int columnas;



int matrizA[filas][3];
  MPI_Status stat;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&pid);
  MPI_Comm_size(MPI_COMM_WORLD,&np);
  int fila_actual[2],fila_abajo[2],fila_arriba[2],abajo=pid+1,arriba=pid-1;
//iniciando tablero
if(pid==0){
  printf("numero de procesos totales:%d\n",np );
 printf("PROCESO MASTER.. HACIENDO MATRIZ\n");

  //CREANDO MATRIZ tablero

   printf("\n");
        	for(i=0;i<filas;++i){
        		for(j=0; j<n;++j){
        			matrizA[i][j]=0+rand()%2;
        		    }
        	     }
            //IMPRIMIR MATRIZ tablero
            for(i=0;i<filas;i++){
                  for(j=0;j<n;j++){
                     printf("%i",matrizA[i][j]);
                  }
               printf("\n");

             }

    MPI_Scatter(&matrizA,3,MPI_INT,&fila_actual,3,MPI_INT,0,MPI_COMM_WORLD);//podria el buffer ir sin &

    for(int c=0;c<3;c++){
        printf("soy el proceso:%d y mi elemento es:%d\n",pid,fila_actual[c]);

        }


      //COMUNICACIÓN DE PROCESOS
      MPI_Sendrecv(&fila_actual, 3 , MPI_INT,abajo, 0 ,&fila_abajo, 3 , MPI_INT,abajo, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Sendrecv(&fila_actual, 3 , MPI_INT,np-1, 0 ,&fila_arriba, 3 , MPI_INT,arriba, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int k;
        for(k=0;k<3;k++){
          printf("ROOT recibi...%d\n",fila_abajo[k]);
     }
     for(k=0;k<3;k++){
       printf("ROOT recibi...%d\n",fila_arriba[k]);
  }
  //    MPI_Send(&fila_actual,3,MPI_INT,arriba,0,MPI_COMM_WORLD);

      //  MPI_Send(&fila_actual,3,MPI_INT,2,0,MPI_COMM_WORLD);

}else{
      MPI_Scatter(&matrizA,3,MPI_INT,&fila_actual,3,MPI_INT,0,MPI_COMM_WORLD);//podria el buffer ir sin &
      int a;
      int fila_abajo[2],fila_arriba[2];
      for(int a=0;a<3;a++){
          printf("soy el proceso:%d y mi elemento es:%d\n",pid,fila_actual[a]);
          }

      if(pid!=np-1){
        printf("\n");
        MPI_Sendrecv(&fila_actual, 3 , MPI_INT,arriba, 0 ,&fila_arriba, 3 , MPI_INT,arriba, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Sendrecv(&fila_actual, 3 , MPI_INT,abajo, 0 ,&fila_abajo, 3 , MPI_INT,abajo, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      //  MPI_Recv(&fila_arriba,3,MPI_INT,arriba,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        //MPI_Send(&fila_actual,3,MPI_INT,0,0,MPI_COMM_WORLD);
        for(a=0;a<3;a++){

        printf("SOY EL PROCESO :%d y recibi la fila de arriba:%d\n",pid,fila_arriba[a]);
      //  printf("recibi fila de abajo:%d y pid:%d\n",fila_abajo[a],pid);

      }
      for(a=0;a<3;a++){

      printf("SOY EL PROCESO :%d y recibi la fila de abajo:%d\n",pid,fila_abajo[a]);


    }


      }

      if(pid==np-1){
        printf("\n");
        MPI_Sendrecv(&fila_actual, 3 , MPI_INT,0, 0 ,&fila_arriba, 3 , MPI_INT,0, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Sendrecv(&fila_actual, 3 , MPI_INT,arriba, 0 ,&fila_abajo, 3 , MPI_INT,arriba, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for(a=0;a<3;a++){

        printf("SOY EL PROCESO :%d y recibi la fila de abajo:%d\n",pid,fila_arriba[a]);

    }
    for(a=0;a<3;a++){

    printf("SOY EL PROCESO :%d y recibi la fila de arriba:%d\n",pid,fila_abajo[a]);

}


  }

  /*    for(int c=0;c<3;c++){
          printf("soy el proceso:%d y mi elemento esss:%d\n",pid,fila_actual[c]);
        }*/
//1 envie al 0 y al 2
    //   MPI_Recv(&fila_arriba, 3, MPI_INT, arriba, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);//recibe de proceso 0/root      //  MPI_Send(&fila_actual,3,MPI_INT,arriba,0,MPI_COMM_WORLD);

        //envia al proceso anterior
    /*    MPI_Send(&fila_actual,3,MPI_INT,arriba,pid-1,MPI_COMM_WORLD);
        //recibe del proceso siguiente
        MPI_Recv(&fila_abajo,3,MPI_INT,abajo,pid+1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        //envia al proceso siguiente
        MPI_Send(&fila_actual,3,MPI_INT,abajo,pid+1,MPI_COMM_WORLD);
        //recibe del proceso anterior
        MPI_Recv(&fila_arriba,3,MPI_INT,arriba,pid-1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
*/
      //  MPI_Send(&fila_actual,3,MPI_INT,arriba,0,MPI_COMM_WORLD);//envia su fila actual del procesador


    //    MPI_Recv(&fila_abajo, 3, MPI_INT, abajo, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);


//  MPI_Recv(&fila_abajo,3,MPI_INT,vecino_abajo,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
//  MPI_Send(&fila_actual,3,MPI_INT,vecino_abajo,0,MPI_COMM_WORLD);
//  MPI_Recv(&fila_arriba,3,MPI_INT,vecino_arriba,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);




  // imprimir_tablero(matriz);
      //MPI_Barrier(MPI_COMM_WORLD);
        //MPI_Gather(&recibir, 10, MPI_INT, &regreso,10, MPI_INT, 0, MPI_COMM_WORLD);


            /*  for (int i = 0; i < 10; i++) {
                  printf("\n%d", regreso[i]);
              }
*/

    //  Ti=MPI_Wtime();
      //for(k=0;k<=5;k++){
        //SCATTER
       // printf("P0--> Enviando datos a P%d:",pid);

	//printf("buffercito..\n");
	//printf("%d\n",buffer1[pid]);
//}







//int a=MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
     //        MPI_STATUS_IGNORE);
	//printf("%d\n",buffer1[pid]);
	//printf("%d",number);
	//printf("%d\n",pid);
	//printf("soy difente de p0");

   //Creando tablero



/*


    Tf=MPI_Wtime();

   */
	//fin else
}
//printf("Tiempo de ejecucion: %f",Ti-Tf);
MPI_Finalize();
return 0;

}
