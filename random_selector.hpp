#ifndef RANDOM_SELECTOR
#define RANDOM_SELECTOR
#include "completetree.hpp"
#include "weightsum_tree.hpp"
#include "numerics.hpp"
#include <limits>
#include <utility>
#include <random>

namespace dense {
namespace stochastic {


//Class to randomly select an index where each index's probability of being 
//  selected is weighted by a given vector.  
template <class IntType = int, size_t precision = std::numeric_limits<Real>::digits>
class nonuniform_int_distribution : protected complete_tree<IntType, std::pair<Real, Real> >,  
                                    public weightsum_tree<nonuniform_int_distribution<IntType, precision>, IntType, precision> {
 public:
  using This = nonuniform_int_distribution<IntType, precision>;
  using BaseTree = complete_tree<IntType, std::pair<Real, Real> >;
  using WeightSum = weightsum_tree<This, IntType, precision>;
  friend WeightSum;
  using PosType = typename BaseTree::position_type;
  static constexpr PosType left_of(PosType i) { return 2 * i + 1;}
  static constexpr PosType right_of(PosType i) { return 2 * i + 2;}
  static constexpr PosType parent_of(PosType i) { return (i - 1) / 2;}

  //Weights can be of any type, but most be convertable to Real values
  nonuniform_int_distribution() = delete;
  nonuniform_int_distribution(PosType p) : BaseTree(p), WeightSum(*this) {};

  template<typename T>
  nonuniform_int_distribution(std::vector<T>& weights) :
    BaseTree(weights.size()),
    WeightSum(*this)
  {
    for (const auto& w : weights) {
      BaseTree::emplace_entry(std::move(w), 0.0);
    }
    WeightSum::compute_weights();
  }

  
  Real& weight_of(PosType p) {
    return BaseTree::value_of(p).first;
  }

  Real& weightsum_of(PosType p) {
    return BaseTree::value_of(p).second;
  }

  const Real& weightsum_of(PosType p) const {
    return const_cast<This*>(this)->weightsum_of(p);
  }

  PosType id_of(PosType p) { return p; }

};

}
}
#endif
