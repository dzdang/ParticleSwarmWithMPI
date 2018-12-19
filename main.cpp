#include <iostream>
#include "cost_function.h"
#include "swarm.h"


int main(int argc, char const *argv[])
{
   int max_iter = 10000;
   int num_dim = 1;
   int num_particles = 10;
   auto cost_func_ptr = new x_sq();
   std::vector<double> lower_bnds = {-10};
   std::vector<double> upper_bnds = {10};
   bounds bnds(num_dim, lower_bnds,upper_bnds);

   swarm swarm_obj(num_particles, num_dim, max_iter, cost_func_ptr, bnds);

   swarm_obj.init_swarm();
   swarm_obj.iterate();

   // std::cout << cost_function(4,ptr) << std::endl;

   delete cost_func_ptr;
}