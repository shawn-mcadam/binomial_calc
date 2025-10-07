// just a really large main function and a usage function
#include <stdio.h>    // printf(), scanf()
#include <stdlib.h>   // atoi(), strtold(), EXIT_FAILURE/SUCCESS
#include <string.h>   // strncat() and strlen()
#include <inttypes.h> // uint64_t
#include <ctype.h>    // isnumber()

#include "bin_dfs.h" // pdf(), cdf()

// Remember the program name for the usage function
char * program_name;

/*
 * Purpose:
 * 	 Display information about what went wrong and how to use the program
 * 	 then quit out of the program.
 * Assumptions:
 * 	 program_name is a global variable and is initialized to argv[0]
 * Returns:
 * 	 Exits the program.
 */
void usage(int exit_type, char* reason){
	if(exit_type!=EXIT_SUCCESS)
		fprintf(stderr, "Error: %s\n", reason);
	fprintf(stderr, "Usage: %s [-h] [-i] [-a <N> <P>] [-k <K>] "
			"where 0<=N, 0<=P<=1, and 0<=K\n", program_name);
	exit(exit_type);
}


/*
 * Purpose:
 *	 Main function. Behaves like a typical shell script
 */
int main(int argc, char *argv[]){
	int n = 0, k = -1;
	long double prob = -1.0; 
	int interactive=0, bare=0; // assume all special modes are not in use
	int cumulative=1, pdf_out=1; // assume all outputs are wanted
	program_name = argv[0]; // init the global var program name for usage()

	// process each argument passed to the program
	int walker=1; // skip argv[0] b/c it's the name of the program
	while(walker != argc){
		char* current_arg = argv[walker];
		// We'll only process options if everything goes well
		if(current_arg[0]=='-'){
			// walk through each char in the argument
			int char_walker=1;
			char current_char=current_arg[char_walker];
			while(current_char != '\0'){
				if(current_char == 'h')
					usage(EXIT_SUCCESS, "");
				else if(current_char == 'a'){
					//if(!isnumber(argv[walker+1]) || !isnumber(argv[walker+2]))
					//	usage(EXIT_FAILURE, "The sample size/ "
					//			"probability must be a number");
					// get the probability of success
					prob=strtold(argv[++walker], NULL);
					// if prob>1 then it should be n
					if(prob>1){
						n=(int)prob;
						prob=strtold(argv[++walker], NULL);
					}
					else
						n = atoi(argv[++walker]);
				}
				else if(current_char == 'k')
					// find where to evaluate the pmf
					k = atoi(argv[++walker]);
				else if(current_char == 'b')
					// use the program in bare mode
					bare=1;
				else if(current_char == 'c')
					// only output the cumulative dist function
					pdf_out=0;
				else if(current_char == 'p')
					// only output the single probability
					cumulative=0;
				else if(current_char == 'i')
					// force interactive mode
					interactive=1;
				else{
					// display the invalid option
					char str[25] = "Invalid option: ";
					strncat(str, current_arg, 24-strlen(str));
					usage(EXIT_FAILURE, str);
				}
				current_char=current_arg[++char_walker];
			}
		}else{
			// display the invalid argument
			char str[31] = "Entered invalid arguement: ";
			strncat(str, argv[walker], 30-strlen(str));
			usage(EXIT_FAILURE, str);
		}
		walker++;
	}


	// if the user didn't supply n and p earlier, use the program interactively
	if(prob==-1.0){
		interactive=1;
		n=0;
		prob=0;
		printf("Sample size N = ");
		if((scanf("%d", &n))!=1)
			usage(EXIT_FAILURE, "Invalid sample size");
		printf("For 0<=P<=1, P = ");
		if((scanf("%Lf", &prob))!=1)
			usage(EXIT_FAILURE, "Invalid sample size");
	}
	if(k<0){
		printf("For pmf p(k), k = ");
		if((scanf("%i", &k)) != 1)
			usage(EXIT_FAILURE, "PMF undefined");
	}
	
	// check to see if the user behaved themself
	if(n<0)
		usage(EXIT_FAILURE, "N cannot be negative");

	if(prob>1 || prob<0)
		usage(EXIT_FAILURE, "P>1 or P<0");

	if(interactive){
		long double p_k_ = 0.0;
		long double P_xlesk_ = 0.0;
		// continue calculating probabilities until the user enters a letter
		do{
			// check to make sure k isn't negative each time through the loop
			if(k<0)
				usage(EXIT_FAILURE, "K cannot be negative");
			p_k_= pmf((uint64_t)k, (uint64_t)n, prob);
			P_xlesk_ = cdf((uint64_t)k, (uint64_t)n, prob);
			printf("p(%d) = %.16Lf\n", k, p_k_);
			printf("P(X<=%d) = %.16Lf\n", k, P_xlesk_);
			k = 0;
			p_k_ = 0.0;
			P_xlesk_ = 0.0;
			printf("k = ");
		}while((scanf("%d", &k)) == 1);
	}else{
		if(cumulative){
			if(!bare)
				printf("P(X<=%d) = ", k);
			printf("%.16Lf\n", cdf((uint64_t)k, (uint64_t)n, prob));
		}
		if(pdf_out){
			if(!bare)
				printf("p(%d) = ", k);
			printf("%.16Lf\n", pmf((uint64_t)k, (uint64_t)n, prob));
		}
	}
	return EXIT_SUCCESS;
}
