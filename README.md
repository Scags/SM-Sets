# SM-Sets
 Implements std::unordered_set into SourcePawn
 
# Purpose
Instead of abusing StringMaps for O(1) duplicate value protection and lookup, this extension exposes std::unordered_set so that there is a fitting type for these cases.

# TODO
- Expose set iterators for plugins to use.
- Expand constructors to allow sets to be initialized with argumented values. Possibly the same thing with `.Insert` functions.
