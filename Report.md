# Report
Fill out these report questions. 


1. What is the difference between a directed and undirected graph?

| Feature | Directed Graph | Undirected Graph |
|---------|----------------|------------------|
| Edge type | One-way arrow | Two-way line |
| Direction | Specific, one-way flow | Non-specific, two-way flow |
| Edge representation | (u,v) is not the same as (v,u) | (u,v) is the same as (v,u) |
| Common use | Dependencies, following, one-way systems | Mutual relationships, road networks |

2. What is the Big O of Dijkstra's algorithm.... 
   * Assuming you used an array (or list) to store the vertices.
   
   $O(V^2)$ - Finding the minimum distance vertex requires scanning all $V$ vertices, and we do this $V$ times in the main loop. This is what our implementation uses.[1]

   * Assuming you used a heap / priority queue to store the vertices.
   
   $O((V + E) \log V)$ - The heap makes finding the minimum vertex much faster ($O(\log V)$ instead of $O(V)$), and we update distances efficiently. For sparse graphs where edges are much less than $V^2$, this is significantly better.[1]


3. Explain in your own words what that means for larger graphs when trying to find the shortest distance. 
      > For small graphs with only a few dozen vertices, both implementations are fast enough and the choice does not matter much.

      > As graphs grow, the difference becomes huge. With 10,000 vertices:

      >- Array version: about $V^2 = 100,000,000$ operations  
      >- Heap version: roughly $(V + E) \log V$, which for a sparse graph is on the order of a few hundred thousand operations.[1]

      > That is around two orders of magnitude faster. The key idea is that $O(V^2)$ grows quadratically. Doubling the number of vertices roughly quadruples the work.


## Deeper Thinking
4. For this assignment, you didn't need the most "efficient" set of data structures (for example, a heap wasn't required). However, think on the scale of google/apple maps - they have to deal with millions of vertices and edges. What data structures would you use to store the graph? Why? Somethings to consider - would you be able to store the entire graph at a time? Could you break it up into smaller pieces? How would you do that? Would there be advantages to caching/memoization of paths? You are free to explore your thoughts on this subject/reflect on various ideas. Other than a realization of some scalability of problems, there isn't a wrong answer. 

   > For something as large as Google Maps with millions of locations, I would use compressed adjacency lists to store the graph efficiently. The entire world's graph cannot fit in memory on one machine, so I would partition it geographically into tiles or regions that load on-demand. Only loading the relevant area for each query plus a small buffer. [2]

   > Within each region, I would use a priority queue for efficient pathfinding. Caching would be crucial for storing popular routes like "airport to downtown" or pre-computing distances between major cities saves massive computation since many users request similar routes.[2]

   > I would also use a hierarchical approach where highways and major roads have pre-computed shortcuts, so long-distance queries use the simplified highway network instead of examining millions of local streets.

   > Breaking the graph into smaller pieces by geography or using natural boundaries like state lines would help distribute the workload across servers.



## Future Understanding
5. Related to shortest distance, is a problem called the "messenger" or "traveling sales person" problem commonly abbreviated to TSP. This problem is to find the shortest path that visits **every** vertex in a graph. Another way to look at it, is you are an delivery driver, and you have a series of packages to deliver. Can you find an optimal path for your deliveries that minimizes the total distance traveled? Imagine if you had 5 stops. How many different paths are there?  There are 120 possible paths to look at! (assuming fully connected routes). 
   * How many possible paths are there if you have 6 stops?
         
      $6! = 720$ possible paths

   * How many possible paths are there if you have 10 stops?
         
      $10! = 3,628,800$ possible paths

6. What type of growth is this problem? 

      >  Factorial growth: $O(n!)$
      > It grows extremely fast. Each additional stop multiplies the number of possible routes by the new number of stops. By 20 stops, there are on the order of $2.4 \times 10^{18}$ possible tours, which makes brute force enumeration completely unrealistic.[3]


7. Take some time to research TSP problems. It falls under a certain classification of problems? What is it? 

      > Traveling Salesperson Problem (TSP) is **NP-Complete**. The "NP" stands for non-deterministic polynomial time.[3,4]
      > This means no known polynomial-time algorithm can solve it exactly, and it's among the hardest problems in computer science.

8. Provide some examples of fields / problems that use TSP.

      - **Logistics and delivery**: Optimizing routes for parcel delivery companies to reduce distance, fuel, and time.[3,4]
      - **Airlines and transportation**: Crew and aircraft rotation planning and route scheduling to increase utilization and lower cost.[3,4]
      - **Telecommunications and networking**: Designing routes and cable layouts to minimize total distance.     [3,4]
      - **Robotics**: Planning efficient motion for robotic arms that must visit multiple points.  [3,4]
 

> [!TIP]
> We are having you explore TSP, so you can see the terms used for problem classification that are often the foundation of computer science theory. You will not be asked to know about TSP outside of this assignment or even problem classification. Computer Science is often about dealing with problems considered "too hard" or "impossible", and finding ways to make them possible! As such, knowing topics such as N, NP, NP-Complete, etc. is important to understand the limits (to break).


## Technical Interview Practice Questions
For both these questions, are you are free to use what you did as the last section on the team activities/answered as a group, or you can use a different question.

1. Select one technical interview question (this module or previous) from the [technical interview list](https://github.com/CS5008-khoury/Resources/blob/main/TechInterviewQuestions.md) below and answer it in a few sentences. You can use any resource you like to answer the question.

   > What are some types of graph representation? When would you prefer to use one over the other?
         > -  Adjacency list
         > -  Adjacency matrix
         > -  Edge list
         > -  Incidence matrix

         > For large, sparse graphs such as most real world networks, maps, or social graphs, an adjacency list is usually the best choice. If the graph is dense, or you need constant time edge lookups and the number of vertices is small, an adjacency matrix is preferable.
         



2. Select one coding question (this module or previous) from the [coding practice repository](https://github.com/CS5008-khoury/Resources/blob/main/LeetCodePractice.md) and include a c file with that code with your submission. Make sure to add comments on what you learned, and if you compared your solution with others.


# References

[1] R. Sedgewick and K. Wayne. 2011. Algorithms (4th ed.). Addison Wesley, Reading, MA.

[2] Sachin. 2017. The Algorithms Behind the Working of Google Maps. Medium. Retrieved November 24, 2025 from https://medium.com/@sachin28/the-algorithms-behind-the-working-of-google-maps-73c379bcc9b9

[3] V. Joshi. 2017. The Trials and Tribulations of the Traveling Salesman. basecs, Medium. Retrieved November 24, 2025 from https://medium.com/basecs/the-trials-and-tribulations-of-the-traveling-salesman-56048d6709d

[4] W3Schools.com. n.d. DSA The Traveling Salesman Problem. W3Schools DSA Reference. Retrieved November 24, 2025 from https://www.w3schools.com/dsa/dsa_ref_traveling_salesman.php