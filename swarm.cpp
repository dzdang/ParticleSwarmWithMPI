#include <random>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "swarm.h"
#include "cost_function.h"
#include "constants.h"

swarm::swarm(const int input_num_particles, const int input_num_dim, 
   int input_max_iter, cost_func_base *input_ptr, const bounds &input_bnds)
{
   max_iter = input_max_iter;
   num_particles = input_num_particles;
   particle_instance.resize(input_num_particles, particle(input_num_dim));
   best_soln.resize(input_num_dim,0.0);
   // best_soln = input_best_soln;
   ptr_2_cost_func = input_ptr;       //do we need to destroy this?
   bnds = input_bnds;
   num_dim = input_num_dim;
}

void swarm::init_swarm()
{
   std::mt19937 generator;
   std::vector<std::uniform_real_distribution<double> > distribution_pos;
   std::uniform_real_distribution<double> distribution_vel(0.0,bnds.upper_bnds[0]*0.001);  
   std::vector<double> rand_pos(best_soln.size(),0.0);
   std::vector<double> rand_vel(best_soln.size(),0.0);

   if(verbose)
   {
      std::cout << "Initializing Swarm's Particles..." << std::endl;
   }

   distribution_pos.reserve(num_dim);
   for(int i = 0; i < num_dim; i++)
   {
      distribution_pos.emplace_back(bnds.lower_bnds[i],bnds.upper_bnds[i]);
   }

   for(auto it = particle_instance.begin(); it != particle_instance.end(); it++)
   {
      int i = 0;
      std::generate(rand_pos.begin(), rand_pos.end(), [&]() {
         i++;
         return distribution_pos[i-1](generator);
      });

      it->set_position(rand_pos);
      it->set_best_position(rand_pos);

      //check if particle's current position gives a smaller objective than 
      //the swarm's current best position
      if(cost_function(rand_pos,ptr_2_cost_func) < cost_function(best_soln,ptr_2_cost_func)) 
      {
         set_best_soln(rand_pos);
      }

      std::generate(rand_vel.begin(), rand_vel.end(), [&]() {
         return distribution_vel(generator);
      });
      it->set_position(rand_pos);
      it->set_best_position(rand_pos);      
      it->set_velocity(rand_vel);
   }

   if(verbose)
   {
      std::cout << "Completed Swarm Initialization." << std::endl;
   }   
}

void swarm::set_best_soln(const std::vector<double> &input_best)
{
   best_soln = input_best;
}

void swarm::update_swarm()
{
   std::default_random_engine generator;
   std::uniform_real_distribution<double> distribution(0.0,1.0);
   std::vector<double> part_pos; //var for storing particle position

   for(auto it = particle_instance.begin(); it != particle_instance.end(); it++)
   {
      it->update_velocity(best_soln);
      it->update_position();
      part_pos = it->get_position();

      if(cost_function(part_pos,ptr_2_cost_func) < 
         cost_function(it->get_best_position(),ptr_2_cost_func))
      {

         it->set_best_position(part_pos);

         if(cost_function(part_pos,ptr_2_cost_func) < 
            cost_function(best_soln,ptr_2_cost_func))
         {
            best_soln = part_pos;
         }
      }
   }
}

void swarm::iterate()
{
   int iter = 0;

   while(iter < max_iter)
   {
      if(verbose)
      {
         std::cout << "Iteration number: " << iter << std::endl;
      }

      update_swarm();

      if(verbose)
      {
         for(auto it = best_soln.begin(); it != best_soln.end(); it++)
         {
            std::cout << "Best Solution: " << std::setprecision(10) << *it << std::endl;
         }
      }

      iter++;
   }
}