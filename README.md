# byte-store

## What is byte-store?

We have a set of *n* regions of the whole genome — say, a master list of summary DHS elements called over *m* samples or cell types. We also have signal that is specific to those regions — DNaseI cleavage counts (chromatin accessibility), chromatin state, motif model presence/absence, kmer composition, etc. — over the same *m* samples of interest. The ``byte-store`` tool creates a container to efficiently store all *n* x *n* pairwise comparisons of these signals, and offer very fast lookups of regions of interest from said container.

Because containers are efficient in disk storage and offer fast querying, we can ask some large-scale questions about pairwise relationships from multiple types of signals on a whole-genome scale, such as:

  1. Are there patterns of sequence content in my regions of interest? 
  2. What does chromatin accessibility look like over a set of locations? 
  3. Are some regions enriched for the same motif models?
  4. How do these patterns interrelate and with those from other experiments, such as Hi-C datasets? 