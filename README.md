# SM-Sets
 Implements std::unordered_set into SourcePawn
 
# Purpose
Instead of abusing StringMaps for O(1) duplicate value protection and lookup, this extension exposes std::unordered_set so that there is a fitting type for these cases.