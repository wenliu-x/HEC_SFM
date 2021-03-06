// Copyright (C) 2014  Victor Fragoso <vfragoso@cs.ucsb.edu>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//
//     * Neither the name of the University of California, Santa Barbara nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL VICTOR FRAGOSO BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#ifndef STATX_DISTRIBUTIONS_EVD_GEV_CERES_H_
#define STATX_DISTRIBUTIONS_EVD_GEV_CERES_H_

#include <cmath>
#include <vector>
#include <ceres/ceres.h>

namespace statx
{
namespace distributions
{
namespace evd
{
// GEV fit using the quantile least-squares method
bool gevfit_ceres(const std::vector<double>& data, double* mu, double* sigma, double* xi);

// CERES CostFunction using analytical derivatives
class GEVCostFunctionAnalytic : public ceres::SizedCostFunction<1,  // Number of residuals
                                                                1,  // Size of first param
                                                                1,  // Size of second param
                                                                1 /* Size of third param */>
{
public:
  // Constructor
  // z: quantile
  // p: percentile
  GEVCostFunctionAnalytic(double z, double p) : z_(z), p_(p)
  {
  }

  // Evaluate method
  virtual bool Evaluate(double const* const* parameters, double* residuals, double** jacobians) const;

private:
  const double z_;  // quantile
  const double p_;  // percentile
};
}  // evd
}  // distributions
}  // statx
#endif  // STATX_DISTRIBUTIONS_EVD_GEV_CERES_H_
