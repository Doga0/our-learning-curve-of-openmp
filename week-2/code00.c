#include<stdio.h>
#include<mpi.h>
#include<sys/resource.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]) 
{
 
  int rank,nproc;
  MPI_Status status;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&nproc);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  unsigned long int i,j,num;
  char *pEnd;
  //unsigned long int 4 bayt 0...4294967295 
  double sumseq;
  struct rusage ru;
  double tseci,tsecf;
  long int who=0;
  unsigned long int remaining,length,datalength;
  unsigned long  int *data;
  double sum=0.0;

  //  printf("The nproc and rank  is  %d %d \n",nproc,rank);


if (nproc==1) 
{ 
      //      printf("********************************************************\n");
      //unsigned long int data[num];
      //      printf("arg[1] is %s \n",argv[1]);
      num=strtoul(argv[1],&pEnd,0);
      data =(unsigned long  int *) malloc(sizeof(unsigned long int)*num);
      //      printf("The numercial value of arg[1] is %ld\n",num);
      //      printf("By experience, num should not be greater than 8 digits\n");

      //      getrusage(who,&ru);
      //      tseci=(ru.ru_utime.tv_sec + 10e-6* ru.ru_utime.tv_usec);
      //      tseci+=(ru.ru_stime.tv_sec + 10e-6 * ru.ru_stime.tv_usec);
      tseci=MPI_Wtime();
      //      printf("The initial time is %f\n",tseci);
      FILE * outfile;
      if ((outfile = fopen("0outputfile.dat", "wb")) == NULL) 
	{
	  fprintf(stderr, "can't open outputfile.dat \n");
	  exit(1);
	}
      sumseq = 0.0;
      for (i=0;i<num;i++)
	{
	  *(data+i)=i+1;
	  sumseq=sumseq+(i+1);
	  fprintf(outfile, "Loop value, array value and sum are %ld %ld %e \n",i,data[i],sumseq);
	}
      fclose(outfile);
      //      getrusage(who,&ru);
      //      tsecf=(ru.ru_utime.tv_sec + 10e-6* ru.ru_utime.tv_usec);
      //     tsecf+=(ru.ru_stime.tv_sec + 10e-6 * ru.ru_stime.tv_usec);
      tsecf=MPI_Wtime();
      //      printf("The final time is %f\n",tsecf);
      //      printf("******The sequential elapsed time  is %f\n",(tsecf-tseci)/100000);
      printf("********************************************************\n");
      printf("******The sequential sum is %e\n",sumseq);
      printf("******The sequential elapsed time  is %f\n",tsecf-tseci);
      printf("********************************************************\n");
MPI_Finalize();
exit(0);
}





  if (rank==0)
    {


      //      printf("********************************************************\n");
      //unsigned long int data[num];
      //      printf("arg[1] is %s \n",argv[1]);
      num=strtoul(argv[1],&pEnd,0);
      data =(unsigned long  int *) malloc(sizeof(unsigned long int)*num);
      for (i=0;i<num;i++)
	{
	  *(data+i)=i+1;
	}


      remaining =( num % nproc );
      length=num/nproc;
      datalength=length;
      //      printf("length is %ld \n",length);
      //      printf("The remaining  is  %ld\n",num % (unsigned long int)nproc);
      //      printf("The num, nproc and rank  is %ld %d %d \n",num,nproc,rank);
      //      printf("The remaining  is  %ld\n",remaining);
      //      printf("********************************************************\n");
      //    }
      //  if (rank==0)
      //    {

      tseci=MPI_Wtime();
      //      printf("The initial time is %f\n",tseci);
      for ( i = 0 ; i <length ; i++ )
	{
	  sum=sum+data[i];
	}
      printf("Proc is %d, the partial sum is %e \n",rank,sum);

      for ( i = 1 ; i < nproc ; i++ )
	{
	  if(i==(nproc-1))  length=length+remaining;
	  MPI_Send( &length, 1 ,MPI_UNSIGNED_LONG,i, 10, MPI_COMM_WORLD );
	  //  for ( j = i*datalength ; j <= (i+1)*datalength-1 ; j++ )
	  //   printf("Proc is %d, %d th element sent  %ld \n",rank,j,data[j]);
	  MPI_Send( &data[ i*datalength] , length ,MPI_UNSIGNED_LONG ,i, 10, MPI_COMM_WORLD );
	  //printf("Part for proc %d is  sent \n",i);
	  //  printf("********************************************************\n");
	}
      double partialsum=0.0;
      for ( i = 1 ; i < nproc ; i++ )
	{
	  MPI_Recv( &partialsum, 1, MPI_DOUBLE, i, 20, MPI_COMM_WORLD, &status);
	  //  printf("Proc is %d, the sent partial sum is %f \n",i,partialsum);
	  sum=sum+partialsum;
	}
    }
  else
    {
      MPI_Recv( &length, 1, MPI_UNSIGNED_LONG, 0, 10, MPI_COMM_WORLD, &status);
      unsigned long  int *dataproc;
      dataproc =(unsigned long  int *) malloc(sizeof(unsigned long int)*length);
      MPI_Recv( dataproc, length, MPI_UNSIGNED_LONG, 0, 10, MPI_COMM_WORLD, &status);
      char buf[50];
      char buf1[50]="outputfile.dat";
      snprintf(buf, 50, "%d", rank);
      // printf("Inverted form integer to string  %s \n",buf);
      strcat(buf, buf1);
      // printf("Filename is  %s \n",buf);
      FILE * outfile;
      if ((outfile = fopen(buf, "wb")) == NULL)
        {
          fprintf(stderr, "can't open %s \n",buf);
          exit(1);
        }

      double sum=0.0; 
      for ( i = 0 ; i <length ; i++ )
	{
	  sum=sum+dataproc[i];
          fprintf(outfile, "Loop value, array value and sum are %ld %ld %e \n",i,dataproc[i],sum);
	  //   printf("Proc is %d, %d th element recieved  %ld \n",rank,i,dataproc[i]);
	}
      fclose(outfile);
      printf("Proc is %d, the partial sum is %e \n",rank,sum);
      //      printf("********************************************************\n");
      MPI_Send( &sum, 1 ,MPI_DOUBLE,0, 20, MPI_COMM_WORLD );
    }

  if (rank==0)  
    {
      printf("********************************************************\n");
      printf("******The parallel total sum is %e \n",sum);
      tsecf=MPI_Wtime();
      //      printf("The final  time is %f\n",tsecf);
      //      printf("******The parallel elapsed time  is %f\n",(tsecf-tseci)/100000);
      printf("******The parallel elapsed time  is %f\n",tsecf-tseci);
      printf("********************************************************\n");
    }
MPI_Finalize();
}
