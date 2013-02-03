CoreLink
========

CoreLink was conceived as a mashup of the games Core War and Uplink.
Players write "viruses" to compete in the game. Unlike Core War, the 
game takes place across a network of connected nodes. 

The objective of CoreLink programs is currently undefined. Ideally, 
there could be different challenging victory conditions. A few 
ideas include:
 - Elimination 
 - Distributed computation towards a specific goal (e.g., protein 
   folding)
 - Distributed computation towards a distributed goal (e.g., 
   bitcoin mining)

I'd also like to include some NPC programs like firewalls and virus 
scanners. 

It might also be interesting to have a mode where players act as 
sysadmins, with the objective of defending some set of nodes from 
the viruses.

Currently, programs are implemented in C++. I'd also like to support
writing programs in Python and C, but ultimately an extension of 
Redcode or maybe some other simple stack machine would be a more
practical solution.


