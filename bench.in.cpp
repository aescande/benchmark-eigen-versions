#include "benchmark/benchmark.h"

#include "Eigen/Core"

static void BM_@NAME@_NormalProduct(benchmark::State & state)
{
  Eigen::MatrixXd T = Eigen::MatrixXd::Random(30, 40);
  Eigen::VectorXd u = Eigen::VectorXd::Random(30);
  Eigen::Matrix<double,1,Eigen::Dynamic> v = Eigen::Matrix<double, 1, Eigen::Dynamic>::Random(40);
  double t = 0.3;

  double d = 0;
  for(auto _ : state)
  {
    T.noalias() -= t * u * v;
    d = T.data()[0];
  }
}
BENCHMARK(BM_@NAME@_NormalProduct);

static void BM_@NAME@_LazyProduct(benchmark::State & state)
{
  Eigen::MatrixXd T = Eigen::MatrixXd::Random(30, 40);
  Eigen::VectorXd u = Eigen::VectorXd::Random(30);
  Eigen::Matrix<double,1,Eigen::Dynamic> v = Eigen::Matrix<double, 1, Eigen::Dynamic>::Random(40);
  double t = 0.3;

  double d = 0;
  for(auto _ : state)
  {
    T.noalias() -= t * u.lazyProduct(v);
    d = T.data()[0];
  }
}
BENCHMARK(BM_@NAME@_LazyProduct);

static void BM_@NAME@_GroupProduct(benchmark::State & state)
{
  Eigen::MatrixXd T = Eigen::MatrixXd::Random(30, 40);
  Eigen::VectorXd u = Eigen::VectorXd::Random(30);
  Eigen::Matrix<double,1,Eigen::Dynamic> v = Eigen::Matrix<double, 1, Eigen::Dynamic>::Random(40);
  double t = 0.3;

  double d = 0;
  for(auto _ : state)
  {
    T.noalias() -= (t*u) * v;
    d = T.data()[0];
  }
}
BENCHMARK(BM_@NAME@_GroupProduct);

static void BM_@NAME@_SeparatedProduct(benchmark::State & state)
{
  Eigen::MatrixXd T = Eigen::MatrixXd::Random(30, 40);
  Eigen::VectorXd u = Eigen::VectorXd::Random(30);
  Eigen::Matrix<double,1,Eigen::Dynamic> v = Eigen::Matrix<double, 1, Eigen::Dynamic>::Random(40);
  double t = 0.3;

  double d = 0;
  for(auto _ : state)
  {
    v *= -t;
    T.noalias() += u * v;
    d = T.data()[0];
  }
}
BENCHMARK(BM_@NAME@_SeparatedProduct);

BENCHMARK_MAIN()
