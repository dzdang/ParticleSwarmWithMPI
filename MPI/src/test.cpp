#include <mpi.h>
#include <iostream>
#include <random>

int main()
{
   std::uniform_real_distribution<double> distribution_vel(0.0,1.0);


   MPI_Init(NULL,NULL);

   // Get the number of processes
   int world_size;
   MPI_Comm_size(MPI_COMM_WORLD, &world_size);


   // Get the rank of the process
   int world_rank;
   MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

   // Get the name of the processor
   char processor_name[MPI_MAX_PROCESSOR_NAME];
   int name_len;
   MPI_Get_processor_name(processor_name, &name_len);

   std::mt19937 generator;//(world_rank);

   generator.seed(world_rank);

   // Print off a hello world message
   std::cout << time(NULL) << std::endl;
   std::cout << "processor id: " << world_rank << " " << distribution_vel(generator) << std::endl;

   // Finalize the MPI environment. No more MPI calls can be made after this
   MPI_Finalize();

   return 0;
}