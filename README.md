# SAT_problem
Satisfiability problem (SAT) - the problem is based on the question - Is there such a logical substitution for the variables X = {x1, x2,…, xn} so that the logical product of all implants is logical 1?

To solve the above problem, we can use the GSAT and WalkSAT algorithms, which are based on the local search technique. The starting point of both algorithms is the random assignment of logical values "0" or "1" to the variables. Completion of the algorithms' operation depends on finding a solution for which all implants assume the logical value "1", otherwise one logical variable is negated and the new solution is reconsidered. Algorithms run until the correct solution is reached, or they finish their work with a negative answer after exceeding the assumed execution time.




# GSAT and WalkSAT 
The above algorithms differ in the method of selecting a variable to negate. The WalkSAT algorithm selects a random implant whose boolean value is "0", and then randomizes the variable contained in the selected implant and negates it, thereby changing the value of the implicit to "1". Whereas the GSAT algorithm considers the negation of each variable in the current configuration separately and then selects the case in which the number of implants with the value "0" is the smallest.

# Search with a taboo list
- a search method that uses a taboo list to avoid loops or repeating results. The taboo list is a set of "forbidden movements", ie already proven solutions. In this way, the algorithm does not oscillate around the local optimum.

# Program
User enter the data manually. The program finds a solution to the SAT problem using the WalkSAT or GSAT algorithm and displays it on the screen. The taboo list for the GSAT algorithm is also included. The program starts with random values of logical variables, however, when testing and comparing the results obtained with different algorithms, they were set to the same in a given sample, so that the algorithms had the same starting point.
