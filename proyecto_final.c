#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char **argv){
  int i,j,np,pid,iteraciones,k,n=3,vecinoDerecho,vecinoIzquierdo,VVivos;
  int filas=15;
  int columnas=15;



int matrizA[filas][columnas];
int matrizB[filas][columnas];


  MPI_Status stat;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&pid);
  MPI_Comm_size(MPI_COMM_WORLD,&np);
  int fila_actual[columnas-1],fila_actualizada[columnas-1],fila_abajo[columnas-1],fila_arriba[columnas-1],abajo=pid+1,arriba=pid-1;
//iniciando tablero
if(pid==0){
  double start = MPI_Wtime();
  printf("numero de procesos totales:%d\n",np );
 printf("PROCESO MASTER.. HACIENDO MATRIZ\n");

  //CREANDO MATRIZ tablero

   printf("\n");
        	for(i=0;i<filas;++i){
        		for(j=0; j<columnas;++j){
        			matrizA[i][j]=0+rand()%2;
        		    }
        	     }
            //IMPRIMIR MATRIZ tablero

            printf("tablero orginal\n");
            for(i=0;i<filas;i++){
                  for(j=0;j<columnas;j++){
                     printf("|%d|",matrizA[i][j]);
                  }
               printf("\n");

             }

    MPI_Scatter(&matrizA,columnas,MPI_INT,&fila_actual,columnas,MPI_INT,0,MPI_COMM_WORLD);//podria el buffer ir sin &

  /*  for(int c=0;c<3;c++){
        printf("soy el proceso:%d y mi elemento es:%d\n",pid,fila_actual[c]);

        }
*/
  

      //COMUNICACIÓN DE PROCESOS
      MPI_Sendrecv(&fila_actual, columnas , MPI_INT,abajo, 0 ,&fila_abajo, columnas , MPI_INT,abajo, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Sendrecv(&fila_actual, columnas , MPI_INT,np-1, 0 ,&fila_arriba, columnas , MPI_INT,arriba, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int k;
    /*    for(k=0;k<columnas;k++){
          printf("ROOT recibi...%d\n",fila_abajo[k]);
     }
     for(k=0;k<columnas;k++){
       printf("ROOT recibi...%d\n",fila_arriba[k]);
  }*/

  //Vecindad usada=Moore




for(i=0;i<columnas;i++){
  vecinoDerecho=i+1;
    vecinoIzquierdo=i-1;
    //revisa a su derecha (borde)
      if (vecinoDerecho>=columnas){
        vecinoDerecho=0;
      }
    //revisa a su izquierda (borde)
      if (vecinoDerecho<0){
        vecinoDerecho=columnas-1;
      }
    //Contador de vecinos
      int VVivos=0;
      int Vmuertos=0;
      if(fila_arriba[vecinoIzquierdo]==1){
        VVivos++;
      }
      else{Vmuertos++;
      }
      if(fila_arriba[i]==1){
        VVivos++;
      }else{Vmuertos++;
      }
      if(fila_arriba[vecinoDerecho]==1){
        VVivos++;
      }
      else{Vmuertos++;
      }
      if(fila_actual[vecinoIzquierdo]==1){
        VVivos++;
      }
      else{Vmuertos++;
      }
      if(fila_actual[vecinoDerecho]==1){
        VVivos++;
      }
      else{Vmuertos++;
      }
      if(fila_abajo[vecinoIzquierdo]==1){
        VVivos++;
      }
      else{Vmuertos++;
      }
      if(fila_abajo[i]==1){
        VVivos++;
      }
      else{Vmuertos++;
      }
      if(fila_abajo[vecinoDerecho]==1){
        VVivos++;
      }
      else{Vmuertos++;
      }
     printf("\n");
    /*  printf("PID:%d y VIVOS:%d\n",pid,VVivos);
      printf("PID:%d y MUERTOS:%d\n",pid,Vmuertos);
      printf("\n");
*/
      if(fila_actual[i]==1){
          if(VVivos<2){
            fila_actualizada[i]=0;//muere de soledad

          }else{
            fila_actualizada[i]=1;

          }
          if(VVivos==2 || VVivos==3){
            fila_actualizada[i]=0;//muere de soledad

          }else{
            fila_actualizada[i]=1;

          }

          if(VVivos>3){
            fila_actualizada[i]=0;//muere de sobrepoblación

          }else{
            fila_actualizada[i]=1;

          }

      }
      if(fila_actual[i]==0){
        if(VVivos>=3){
          fila_actualizada[i]=1;//revive
        }else{
          fila_actualizada[i]=0;

        }

      }



}


for(k=0;k<columnas;k++){
//  printf("ROOT matriz actualizada...%d\n",fila_actualizada[k]);
}

MPI_Gather(&fila_actualizada,columnas,MPI_INT,&matrizB,columnas,MPI_INT,0,MPI_COMM_WORLD);

double end  = MPI_Wtime();

double tiempo_fila=end-start;
printf("TIEMPO TOTAL proceso pid %d----->%f[s]\n",pid,tiempo_fila);
printf("Tablero actualizado\n");
for(i=0;i<filas;i++){
      for(j=0;j<columnas;j++){
         printf("|%d|",matrizB[i][j]);
      }
   printf("\n");

 }

}else{
  double start  = MPI_Wtime();
      MPI_Scatter(&matrizA,columnas,MPI_INT,&fila_actual,columnas,MPI_INT,0,MPI_COMM_WORLD);//podria el buffer ir sin &
      int a;
      int fila_abajo[columnas],fila_arriba[columnas];
    /*  for(int a=0;a<3;a++){
          printf("soy el proceso:%d y mi elemento es:%d\n",pid,fila_actual[a]);
          }
*/
      if(pid!=np-1){
        printf("\n");
        MPI_Sendrecv(&fila_actual, columnas , MPI_INT,arriba, 0 ,&fila_arriba, columnas , MPI_INT,arriba, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Sendrecv(&fila_actual, columnas , MPI_INT,abajo, 0 ,&fila_abajo, columnas , MPI_INT,abajo, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);


  /*     for(a=0;a<columnas;a++){

        printf("SOY EL PROCESO :%d y recibi la fila de arriba:%d\n",pid,fila_arriba[a]);
                        }

      for(a=0;a<columnas;a++){

      printf("SOY EL PROCESO :%d y recibi la fila de abajo:%d\n",pid,fila_abajo[a]);


    }*/
for(int i=0;i<columnas;i++){
    vecinoDerecho=i+1;
      vecinoIzquierdo=i-1;
      //revisa a su derecha (borde)
        if (vecinoDerecho>=columnas){
          vecinoDerecho=0;
        }
      //revisa a su izquierda (borde)
        if (vecinoDerecho<0){
          vecinoDerecho=columnas-1;
        }
      //Contador de vecinos
        int VVivos=0;
        int Vmuertos=0;
        if(fila_arriba[vecinoIzquierdo]==1){
          VVivos++;
        }
        else{Vmuertos++;
        }
        if(fila_arriba[i]==1){
          VVivos++;
        }else{Vmuertos++;
        }
        if(fila_arriba[vecinoDerecho]==1){
          VVivos++;
        }
        else{Vmuertos++;
        }
        if(fila_actual[vecinoIzquierdo]==1){
          VVivos++;
        }
        else{Vmuertos++;
        }
        if(fila_actual[vecinoDerecho]==1){
          VVivos++;
        }
        else{Vmuertos++;
        }
        if(fila_abajo[vecinoIzquierdo]==1){
          VVivos++;
        }
        else{Vmuertos++;
        }
        if(fila_abajo[i]==1){
          VVivos++;
        }
        else{Vmuertos++;
        }
        if(fila_abajo[vecinoDerecho]==1){
          VVivos++;
        }
        else{Vmuertos++;
        }
    /*    printf("\n");
        printf("PID:%d y VIVOS:%d\n",pid,VVivos);
        printf("PID:%d y MUERTOS:%d\n",pid,Vmuertos);
        printf("\n");*/

        if(fila_actual[i]==1){
            if(VVivos<2){
              fila_actualizada[i]=0;//muere de soledad

            }else{
              fila_actualizada[i]=1;

            }
            if(VVivos==2 || VVivos==3){
              fila_actualizada[i]=0;//muere de soledad

            }else{
              fila_actualizada[i]=1;

            }

            if(VVivos>3){
              fila_actualizada[i]=0;//muere de sobrepoblación

            }else{
              fila_actualizada[i]=1;

            }

        }
        if(fila_actual[i]==0){
          if(VVivos>=3){
            fila_actualizada[i]=1;//revive
          }else{
            fila_actualizada[i]=0;

          }

        }





}

for(int k=0;k<columnas;k++){
//  printf("pid:%d matriz actualizada...%d\n",pid,fila_actualizada[k]);
}
MPI_Gather(&fila_actualizada,columnas,MPI_INT,&matrizB,columnas,MPI_INT,0,MPI_COMM_WORLD);

double end  = MPI_Wtime();

double tiempo_fila=end-start;
printf("TIEMPO TOTAL proceso pid %d----->%f[s]\n",pid,tiempo_fila);
      }

      if(pid==np-1){
        printf("\n");
        MPI_Sendrecv(&fila_actual, columnas , MPI_INT,0, 0 ,&fila_arriba, columnas , MPI_INT,0, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Sendrecv(&fila_actual, columnas, MPI_INT,arriba, 0 ,&fila_abajo, columnas , MPI_INT,arriba, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  /*   for(a=0;a<columnas;a++){

        printf("SOY EL PROCESO :%d y recibi la fila de abajo:%d\n",pid,fila_arriba[a]);

    }
    for(a=0;a<columnas;a++){

    printf("SOY EL PROCESO :%d y recibi la fila de arriba:%d\n",pid,fila_abajo[a]);

}*/


for(int i=0;i<columnas;i++){
vecinoDerecho=i+1;
  vecinoIzquierdo=i-1;
  //revisa a su derecha (borde)
    if (vecinoDerecho>=columnas){
      vecinoDerecho=0;
    }
  //revisa a su izquierda (borde)
    if (vecinoDerecho<0){
      vecinoDerecho=columnas-1;
    }
  //Contador de vecinos
    int VVivos=0;
    int Vmuertos=0;

    if(fila_arriba[vecinoIzquierdo]==1){
      VVivos++;
    }
    else{Vmuertos++;
    }
    if(fila_arriba[i]==1){
      VVivos++;
    }else{Vmuertos++;
    }
    if(fila_arriba[vecinoDerecho]==1){
      VVivos++;
    }
    else{Vmuertos++;
    }
    if(fila_actual[vecinoIzquierdo]==1){
      VVivos++;
    }
    else{Vmuertos++;
    }
    if(fila_actual[vecinoDerecho]==1){
      VVivos++;
    }
    else{Vmuertos++;
    }
    if(fila_abajo[vecinoIzquierdo]==1){
      VVivos++;
    }
    else{Vmuertos++;
    }
    if(fila_abajo[i]==1){
      VVivos++;
    }
    else{Vmuertos++;
    }
    if(fila_abajo[vecinoDerecho]==1){
      VVivos++;
    }
    else{Vmuertos++;
    }
/*    printf("\n");
    printf("PID:%d y VIVOS:%d\n",pid,VVivos);
    printf("PID:%d y MUERTOS:%d\n",pid,Vmuertos);
    printf("\n");*/

  if(fila_actual[i]==1){
        if(VVivos<2){
          fila_actualizada[i]=0;//muere de soledad

        }

        if(VVivos==2 || VVivos==3){
          fila_actualizada[i]=0;//muere de soledad

        }

        if(VVivos>3){
          fila_actualizada[i]=0;//muere de sobrepoblación

        }

    }
    if(fila_actual[i]==0){
      if(VVivos>=3){
        fila_actualizada[i]=1;//revive
      }

    }




}
for(int k=0;k<columnas;k++){
  //printf("pid:%d matriz actualizada...%d\n",pid,fila_actualizada[k]);
}
MPI_Gather(&fila_actualizada,columnas,MPI_INT,&matrizB,columnas,MPI_INT,0,MPI_COMM_WORLD);
double end=MPI_Wtime();
double tiempo_fila=end-start;
printf("TIEMPO TOTAL proceso pid %d----->%f[s]\n",pid,tiempo_fila);
}
//printf("Tiempo de ejecucion: %f",Ti-Tf);

}



MPI_Finalize();
//imprimir matriz actualizada
//IMPRIMIR MATRIZ tablero

return 0;

}
