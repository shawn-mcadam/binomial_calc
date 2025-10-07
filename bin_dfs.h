#ifndef DIST_FUNCT_H
#define DIST_FUNCT_H

/* 
 * Purpose:
 * 	 Recursively calculate the probability mass function for the 
 * 	 binomial dist. The benefit of doing it this was is that 
 * 	 large n, large k and skewed p are less likely to break the function.
 * Assumptions:
 * 	 If k>n then the probability function is being used improperly.
 * 	 The function returns 0 in that case.
 * Returns:
 * 	 (n_choose_k)*(p^k)*((1-p)^(n-k)) if k<=n, 0 otherwise
 */
long double pmf(uint64_t k, uint64_t n, long double p);


/*
 * Purpose:
 * 	 Recusively sum up the probabilities for each i<=n
 * Assumptions:
 * 	 k <= n
 * Returns:
 * 	 P(X<=k) where X~bin(n, p)
 * 	 ie, \sum_{j=0}^k pmf(j, n, p)
 */
long double cdf(uint64_t k, uint64_t n, long double p);

#endif // DIST_FUNCT_H

