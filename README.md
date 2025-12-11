`nobutterfly.c` implements a pruning plugin for geng (nauty 2.9.1) that eliminates any graph containing a butterfly subgraph, so the generator outputs only non-isomorphic, butterfly-free  graphs.


connected butterfly-free graphs: 
- **8 vertices**: 1,769 butterfly-free graphs
- **9 vertices**: 14,836 butterfly-free graphs
- **10 vertices**: 174,111 butterfly-free graphs
- **11 vertices**: 2,810,354 butterfly-free graphs
- **12 vertices**: 62810605 graphs (generated in 530.89 sec)
- **13 vertices**: 1926350530 graphs (made in 24514.28 cpu-seconds, 2382.73 seconds real time)
