#include <algorithm>
#include <boost/math/special_functions/spherical_harmonic.hpp>
#include <fstream>
#include <gsl/gsl_sf_coupling.h>
#include <iostream>
#include <iterator>
#include <math.h>
#include <stdio.h>

class sh
{

public:
  void test();

  double a(int l_prime, int m_prime, int l1, int m1, int l2, int m2);
  double b(int m_prime, int l_prime, int m1, int l1, int m2, int l2, int m3,
           int l3, int num /*= 16*/);
  void print_a();
  void check_diff();
};
