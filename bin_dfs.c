#include <inttypes.h> // uint64_t
#include "bin_dfs.h"

// private helper functions
long double cdf_helper(uint64_t k, uint64_t n, long double p, long double sum, long double error);
long double one_minus_cdf_helper(uint64_t k, uint64_t n, long double p, long double sum, long double error);
long double pmf_helper(uint64_t k, uint64_t n, long double p);


// declarations of public driver functions
long double pmf(uint64_t k, uint64_t n, long double p){
	if(k > n)
		return 0.0; // the function is being used improperly so return 0.0.
	if(2*k>n && p > 0.5)
		return pmf_helper(n-k, n, 1-p); // honestly don't really know if this helps
	return pmf_helper(k, n, p);
}

long double cdf(uint64_t k, uint64_t n, long double p){
	if(2*k>n)
		return 1-one_minus_cdf_helper(k+1, n, p, 0.0, 0.0);
	return cdf_helper(k, n, p, 0.0, 0.0);
}


// Can't do tail recursion here because the intermediate products can get
// far larger than LDBL_MAX
long double pmf_helper(uint64_t k, uint64_t n, long double p){
	// work through our k's then work through our n's.
	if(n == 0)
		return 1.0;
	if(k == 0)
		return (1-p)*pmf_helper(0, n-1, p);
	return n*p*pmf_helper(k-1, n-1, p)/k;
}

// accumulate a sum and error using tail recursion. Call with sum = error = 0.0
long double cdf_helper(uint64_t k, uint64_t n, long double p, long double sum, long double error){
	// sum until k == 0
	if(k == 0)
		return sum + pmf(0, n, p) + error; // add error back to sum to get 

	// perform a compensated addition on sum
	long double temp = pmf(k, n, p);
	long double next = sum + temp;
	return cdf_helper(k-1, n, p, next, error+((sum-next)+temp));
}

// calculates 1-cdf(k). Can result in fewer steps to find a solution to 1-cdf(k) if 2*k>n.
long double one_minus_cdf_helper(uint64_t k, uint64_t n, long double p, long double sum, long double error){
	// sum until k == n
	if(k > n)
		return sum + error; // add error back to sum to get 

	// perform a compensated addition on sum
	long double temp = pmf(k, n, p);
	long double next = sum + temp;
	return one_minus_cdf_helper(k+1, n, p, next, error+((sum-next)+temp));
}
