#include <iostream>
#include <mpi.h>
#include "../include/cost_function.h"
#include "../include/swarm.h"

//function for distributing particles across the processors
void distribute_particles(const int num_particles, const int num_proc, const int proc_id, 
   int &particle_id_start, int &particles_per_proc)
{
  if (num_proc > num_particles) {
    // Don't worry about this special case. Assume the number of particles
    // is greater than the number of processors.
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  particle_id_start = num_particles / num_proc * proc_id;
  particles_per_proc = num_particles / num_proc;
  if (proc_id == num_proc - 1) {
    // Give remainder to last process
    particles_per_proc += num_particles % num_proc;
  }
}


int main(int argc, char const *argv[])
{
   int max_iter = 100;
   int num_dim = 1;
   int num_particles = 400;
   auto cost_func_ptr = new x_sq();
   std::vector<double> lower_bnds = {-10};
   std::vector<double> upper_bnds = {10};
   bounds bnds(num_dim, lower_bnds,upper_bnds);

   MPI_Init(NULL, NULL);
   int num_proc;  //number of processors
   int proc_id;   //processor id
   MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
   MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

   std::cout << "Rank size is: " << num_proc << std::endl;

   int particle_id_start = 0;
   int particles_per_proc = 0;
   //assigns a subset of num_particles to proc_id, the number of particles for proc_id is stored in
   //particles_per_proc
   distribute_particles(num_particles, num_proc, proc_id, particle_id_start, particles_per_proc);

   std::cout << "proc_id: " << proc_id  << std::endl;
   std::cout << "particle_id_start: " << particle_id_start << std::endl;
   std::cout << "particles_per_proc: " << particles_per_proc << std::endl;

   swarm swarm_obj(particles_per_proc, num_dim, max_iter, cost_func_ptr, bnds, num_proc, proc_id);

   swarm_obj.init_swarm();
   swarm_obj.iterate();

   MPI_Finalize();

   delete cost_func_ptr;
   cost_func_ptr = nullptr;
}