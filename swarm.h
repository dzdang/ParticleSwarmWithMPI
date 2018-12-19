#ifndef _swarm_pso_h_
#define _swarm_pso_h_

#include <vector>
#include "particle.h"
#include "cost_function.h"

struct bounds
{
   std::vector<double> lower_bnds;
   std::vector<double> upper_bnds;

   bounds() = default;

   bounds(int num_dim, const std::vector<double> &input_lower_bnds, 
      const std::vector<double> &input_upper_bnds)
   {
      lower_bnds.resize(num_dim);
      upper_bnds.resize(num_dim);

      set_bounds(input_lower_bnds, input_upper_bnds);
   }

   void set_bounds(const std::vector<double> &input_lower_bnds, 
      const std::vector<double> &input_upper_bnds)
   {
      lower_bnds = input_lower_bnds;
      upper_bnds = input_upper_bnds;
   }
};

class swarm
{
   public:
      swarm() = default;

      swarm(const int input_num_particles, const int num_dim, 
         int input_max_iter, cost_func_base *input_ptr, const bounds &input_bnds);

      //Member function for initializing all swarm particle velocities and positions
      //based on uniform random distributions
      void init_swarm();  

      //Setter function for the best (most optimal) solution at the current iteration
      void set_best_soln(const std::vector<double> &input_best);  

      //Member function for updating the swarm particles' velocity and position
      //Called during swarm::iterate()
      void update_swarm();

      //Iterate until some convergence criteria is reached
      void iterate();

   private:
      int num_particles;
      int max_iter;
      int num_dim;
      std::vector<particle> particle_instance;
      std::vector<double> best_soln;
      cost_func_base *ptr_2_cost_func;
      bounds bnds;
};

#endif //_swarm_pso_h_