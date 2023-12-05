# CSC-212-Term-Project
Topic: String Search I  
Made By: Parker Holland (WParkerHolland), Caleb Cady (c4ddyshack), Jad Alsassa (carpspet), and Owen Cunnie (owenc740)  

## Purpose of our Project
It has been known that U.S. legislators do not read every bill that they must vote on. This is understandable when bills can be dozens of pages long and legislators are often busy. However, it does not mean that legislators should not do anything to inform themselves about bills they vote on. To help the legislators learn more about what they vote on, we aim to develop two different string searching algorithms and find which is more efficient. These algorithms will allow legislators to search for phrases in lengthy bills that pertain to their constituents. The efficiency of the algorithm is important because as stated earlier, legislators are busy and have no time for inefficient algorithms.  
This program will read data from a text file, which contains active legislation found on the U.S. Senate's official website (https://www.senate.gov/legislative/active_leg_page.htm). Depending on the user's input, this program can perform a Rabin-Karp search, Boyer-Moore search, or both of them and compare their benchmarks graphically.

## Who does what
Jad Alsassa - Designs main.cpp, which combines all other algorithms and shows output to the user (Everyone contributed minor changes to main whenever they changed a function they were working on)  
Caleb Cady - Develops the Boyer-Moore string search algorithm and anything else needed for it  
Parker Holland - Develops the Rabin-Karp string search algorithm and writes the readme file  
Owen Cunnie - Designs the files for the benchmarking and graphed the results for each search algorithm's benchmark  

## How to use
1. Copy the text from the text tab of legislation found on https://www.senate.gov/legislative/active_leg_page.htm into a text file.  
2. In the text file, replace all right leaning and left leaning quotation marks with ", all em dashes with -, and all left leaning and right leaning apostrophes with '.  
3. Compile with the command "g++ main.cpp bench.cpp boyer_moore.cpp rabin_karp.cpp"  
4. Run the executable with "./a.exe textFileName.txt".  
