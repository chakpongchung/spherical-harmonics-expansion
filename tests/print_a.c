#include <algorithm>
#include <boost/math/special_functions/spherical_harmonic.hpp>
#include <fstream>
#include <gsl/gsl_sf_coupling.h>
#include <iostream>
#include <iterator>
#include <math.h>
#include <stdio.h>

//#define pi 3.1415926
using namespace std;
using namespace boost::math;

double a(int l_prime, int m_prime, int l1, int m1, int l2, int m2)
{

  // printf("m_prime:   %d  ", m_prime);
  // printf(",l_prime:  %d\n", l_prime);

  double temp = (2 * l1 + 1) * (2 * l2 + 1) * (2 * l_prime + 1) /
                (4.0 * M_PI); // printf("temp is: %f\n", temp);
  double first = gsl_sf_coupling_3j(2 * l1, 2 * l2, 2 * l_prime, 2 * 0, 2 * 0,
                                    2 * 0); // printf("first is: %f\n", first);
  double second =
      gsl_sf_coupling_3j(2 * l1, 2 * l2, 2 * l_prime, 2 * m1, 2 * m2,
                         -2 * m_prime); // printf("second is: %f\n", second);
  // printf("a is: %.18f \n", pow(-1, m_prime)*pow(temp, 0.5)*first*second);
  // printf("a is: %20.4f pow(-1, m_prime)*pow(temp, 0.5)*first*second \n");

  return pow(-1, m_prime) * pow(temp, 0.5) * first * second;
}

double b(int m_prime, int l_prime, int m1, int l1, int m2, int l2, int m3,
         int l3, int num /*= 16*/)
{

  double sum = 0;
  for (int l = 0; l <= num; l++)
    for (int m = -l; m <= l; m++)
    {
      double temp = (2 * l + 1) * (2 * l3 + 1) * (2 * l_prime + 1) / 4 * M_PI;
      int first =
          gsl_sf_coupling_3j(2 * l, 2 * l3, 2 * l_prime, 2 * 0, 2 * 0, 2 * 0);
      int second = gsl_sf_coupling_3j(2 * l, 2 * l3, 2 * l_prime, 2 * m, 2 * m3,
                                      -2 * m_prime);
      sum = sum +
            a(m, l, m1, l1, m2, l2) * pow(-1, m_prime) * temp * first * second;
    }

  return sum;
}

int main()
{

  printf(
      "*******************************************************************\n");
  printf(
      "cofficients for spherical-harmonic expansion test program  -cpchung\n");
  printf(
      "*******************************************************************\n");

  int l1 = 8, m1 = -3, l2 = 21, m2 = -1; //  l1 ,l2 >=0, |m1|<=l1, |m2|<=l2;
  assert(l1 >= 0 && l2 >= 0);
  assert(abs(m1) <= l1 && abs(m2) <= l2);

  double theta = M_PI * 0, phi = M_PI * 0; // theta θ in [0, π], phi φ in
                                           // [0,2π);
  assert(theta <= M_PI && 0 <= theta);
  assert(0 <= phi && phi <= 2 * M_PI);
  cout << "theta is now: " << theta << " phi is now: " << phi << endl;

  ofstream datafile;
  datafile.open("data.csv");

  int lmax = 2;
  for (int l = 0; l <= lmax; l++)
    for (int m = -l; m <= l; m++)
      for (int j = 0; j <= lmax; j++)
        for (int p = -j; p <= j; p++)
          for (int n = max(abs(l - j), 0); n <= min((l + j), lmax); n++)
          {
            if (abs(m + p) <= n)
              datafile << l << "," << m << "," << j << "," << p << "," << n
                       << "," << setprecision(17) << a(n, m + p, j, p, l, m)
                       << endl;
          }

  datafile.close();

  return 0;
}
