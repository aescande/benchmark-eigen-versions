#include "benchmark/benchmark.h"

#include "Eigen/Core"

typedef Eigen::Matrix<double,1,Eigen::Dynamic> RowVector;

static void BM_@NAME@_NormalProduct(benchmark::State & state)
{
  Eigen::MatrixXd M = Eigen::MatrixXd::Random(30, 40);
  RowVector m = RowVector::Random(40);
  Eigen::VectorXd u = Eigen::VectorXd::Random(30);
  RowVector v0 = RowVector::Random(40);
  RowVector v(40);
  double tau = 0.3;
  
  for(auto _ : state)
  {
    v = v0;
    v += m;
    m -= tau*v;
    M.noalias() -= tau * u * v;
  }
}
BENCHMARK(BM_@NAME@_NormalProduct);

static void BM_@NAME@_LazyProduct(benchmark::State & state)
{
  Eigen::MatrixXd M = Eigen::MatrixXd::Random(30, 40);
  RowVector m = RowVector::Random(40);
  Eigen::VectorXd u = Eigen::VectorXd::Random(30);
  RowVector v0 = RowVector::Random(40);
  RowVector v(40);
  double tau = 0.3;

  for(auto _ : state)
  {
    v = v0;
    v += m;
    m -= tau*v;
    M.noalias() -= tau * u.lazyProduct(v);
  }
}
BENCHMARK(BM_@NAME@_LazyProduct);

static void BM_@NAME@_GroupProduct(benchmark::State & state)
{
  Eigen::MatrixXd M = Eigen::MatrixXd::Random(30, 40);
  RowVector m = RowVector::Random(40);
  Eigen::VectorXd u = Eigen::VectorXd::Random(30);
  RowVector v0 = RowVector::Random(40);
  RowVector v(40);
  double tau = 0.3;

  for(auto _ : state)
  {
    v = v0;
    v += m;
    m -= tau*v;
    M.noalias() -= (tau*u) * v;
  }
}
BENCHMARK(BM_@NAME@_GroupProduct);

static void BM_@NAME@_SeparatedProduct(benchmark::State & state)
{
  Eigen::MatrixXd M = Eigen::MatrixXd::Random(30, 40);
  RowVector m = RowVector::Random(40);
  Eigen::VectorXd u = Eigen::VectorXd::Random(30);
  RowVector v0 = RowVector::Random(40);
  RowVector v(40);
  double tau = 0.3;

  for(auto _ : state)
  {
    v = v0;
    v += m;
    v *= -tau;
    m += v;
    M.noalias() += u * v;
  }
}
BENCHMARK(BM_@NAME@_SeparatedProduct);

BENCHMARK_MAIN()
