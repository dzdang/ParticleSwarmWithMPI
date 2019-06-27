#ifndef _cost_func_h_
#define _cost_func_h_

#include <math.h>
#include <vector>

//Implementation of a functor class; base class is abstract -> can't be instantiated
//

class cost_func_base
{
   public:
      cost_func_base() = default;
      virtual std::vector<double> operator() (std::vector<double> val) const = 0; //pure virtual
};   

class x_sq : public cost_func_base
{
   static inline double calc_sq(double x) {return (x-3)*(x-3);}

   public:
      x_sq() = default;
      virtual std::vector<double> operator()(std::vector<double> vec) const 
      {
         std::transform(vec.begin(), vec.end(), vec.begin(), calc_sq);

         return vec;
      }
};         

inline std::vector<double> cost_function(const std::vector<double> &vec, const cost_func_base * const user_cost)
{
   return(*user_cost)(vec);
}

#endif //_cost_func_h_