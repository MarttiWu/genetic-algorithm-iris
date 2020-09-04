# Genetic Algorithm



# Iris Dataset



# Usage

Open terminal

    make
    
1. Run directly in the terminal by typing the following:

        #./main [algo] [runs] [iter] [filename] [population] [Pc] [Pm]
        ./main ga 30 1000 "" 20 0.08 0.78
    
2. Or if you want to run multiple times, just by opening the "search.sh" and add whatever you want and run by typing


        ./search.sh
    in the terminal.
    
    
# Customize

You can change the iteration block by modifying 

        const int block=100;
in "execute.hpp".

# Results

Best accuracy within 1000 generations of average of 30 runs: 0.760889

Best accuracy within 1000 generations: 0.833333



