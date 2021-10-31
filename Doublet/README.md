This program use A* algorithm to find the shortest path to transform the starting word to the ending word. A valid transformation is considered as changing only one letter and become aother valid word (the user should provide a list of valid words).

To compile, type "make doublet", and an executable called doublet will be generated.

To run, type "./doublet start end words.txt", where start is the starting word, end is the ending word, and words.txt is a list of valid words.

The output contains <steps> and <expansions>, where <steps> is the fewest number of transformations to get from the start word to the end word, and <expansions> is the number of words that the algorithm considers, ie. the number of times it removes the min-value word from its MinHeap.