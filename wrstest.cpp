#include "random_selector.hpp"
#include "sys/time.h"
#include <iostream>
#include <random>

using namespace dense::stochastic;
const int iter = 1000000;

int main() {
  std::default_random_engine generator;
  std::vector<float> weights = {4, 3, 2, 1};

  nonuniform_int_distribution<int> selector(weights);
  std::cout << "Constructed" << std::endl;
  std::vector<unsigned int> counts(weights.size());

  struct timeval start, end;
 
  double totalelapse = 0;
  for (int j = 0; j < 100; j++) {  

  gettimeofday(&start, NULL);
  int weightSize = weights.size();
  for (int i = 1; i < iter; i++) {
    int index = selector(generator);
    if (index < 0 || index >= weightSize) {
      std::cout << "Error, index out of range" << std::endl;
    } else {
      counts[index]++;
    }
  }

  gettimeofday(&end, NULL);
  
  double elapsedtime_sec = double(end.tv_sec - start.tv_sec)+
	  		  double(end.tv_usec - start.tv_usec)/1000000.0;
  
  totalelapse += elapsedtime_sec;
  }
  std::cout << "Average elapsed time for " << iter << " iterations: " << totalelapse/100 << std::endl;
  for (auto c : counts) {
    std::cout << c << ' ';
  }
  std::cout << std::endl;
}
