#if defined _smset_included_
  #endinput
#endif
#define _smset_included_

// Forward declared iterators
enum CellSetIterator{}
enum StringSetIterator{}

methodmap CellSet < Handle
{
	// Initialize a CellSet object.
	// CellSets are identical to std::unordered_set<cell_t>.
	// Insertion and lookup are O(1).
	//
	// @param ... 			Var-arg values to automatically insert
	// 						during creation.
	public native CellSet(any ...);

	// Insert a value into a set. O(1n) per n items.
	// Note that behavior is bit-oriented!
	// A float value that has the same binary value
	// as an integer value will result in a collision,
	// and thus not insert itself into the set.
	//
	// @param ... 			Value(s) to insert.
	public native void Insert(any ...);

	// Erase a value from a set. O(1n) per n items.
	//
	// @param ... 			Value(s) to remove. Silently fails if none found.
	public native void Erase(any ...);

	// Detect if a value lies in a set. O(1).
	//
	// @param val 			Cell to search for.
	//
	// @return 				True if val exists, false otherwise.
	public native bool Find(any val);

	// Retrieve the number of items in a set.
	property int Size
	{
		public native get();
	}

	// Detect if set is empty.
	property bool Empty
	{
		public native get();
	}

	// Swap a set's values with another.
	//
	// @param other 		Set to swap with.
	public native void Swap(CellSet other);

	// Detect if a set has the same values as another.
	//
	// @param other 		Set to compare to.
	//
	// @return 				True if sets are equal, false otherwise.
	public native bool Equals(CellSet other);

	// Clear all values from a set.
	public native void Clear();

	// Create an cell set iterator. Note that this must be closed
	// with delete or CloseHandle().
	//
	// @return 				Handle to new CellSetIterator.
	public native CellSetIterator Iterator();
};

methodmap StringSet < Handle
{
	// Initialize a StringSet object.
	// StringSets are identical to std::unordered_set<std::string>.
	// Insertion and lookup are O(1).
	//
	// @param ... 			Var-arg values to automatically insert
	// 						during creation.
	public native StringSet(const char[] ...);

	// Insert a value into a set. O(1n) per n items.
	//
	// @param ... 			String(s) to insert.
	public native void Insert(const char[] ...);

	// Erase a value from a set. O(1n) per n items.
	//
	// @param ... 			String(s) to remove. Silently fails if none found.
	public native void Erase(const char[] ...);

	// Detect if a value lies in a set. O(1).
	//
	// @param val 			String to search for.
	//
	// @return 				True if val exists, false otherwise.
	public native bool Find(const char[] val);

	// Retrieve the number of items in a set.
	property int Size
	{
		public native get();
	}

	// Detect if set is empty.
	property bool Empty
	{
		public native get();
	}

	// Swap a set's values with another.
	//
	// @param other 		Set to swap with.
	public native void Swap(StringSet other);

	// Detect if a set has the same values as another.
	//
	// @param other 		Set to compare to.
	//
	// @return 				True if sets are equal, false otherwise.
	public native bool Equals(StringSet other);

	// Clear all values from a set.
	public native void Clear();

	// Create an string set iterator. Note that this must be closed
	// with delete or CloseHandle().
	//
	// @return 				Handle to new StringSetIterator.
	public native StringSetIterator Iterator();
};

// So overloading the == operators with handle values is probably a bad idea.

//stock bool operator==(CellSet set1, CellSet set2)
//{
//	return set1.Equals(set2);
//}
//
//stock bool operator!=(CellSet set1, CellSet set2)
//{
//	return !set1.Equals(set2);
//}
//
//stock bool operator==(StringSet set1, StringSet set2)
//{
//	return set1.Equals(set2);
//}
//
//stock bool operator!=(StringSet set1, StringSet set2)
//{
//	return !set1.Equals(set2);
//}

methodmap CellSetIterator < Handle
{
	// Move up along the iterator.
	//
	// @return 				True if the iteration is successful, false
	// 						if at the end of the iterator.
	public native bool Next();

	// Retrieve a value at the current point of the iterator.
	//
	// @return 				Value at the current point of the iterator.
	public native any Get();
};

methodmap StringSetIterator < Handle
{
	// Move up along the iterator.
	//
	// @return 				True if the iteration is successful, false
	// 						if at the end of the iterator.
	public native bool Next();

	// Retrieve a value at the current point of the iterator.
	//
	// @param buffer 		Buffer to store value into.
	// @param maxlength 	Max length of the string to copy
	public native void Get(char[] buffer, int maxlength);
};


public Extension __ext_smset =
{
	name = "SMSets",
	file = "smsets.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};

#if !defined REQUIRE_EXTENSIONS
public void __ext_smset_SetNTVOptional()
{
	MarkNativeAsOptional("CellSet.CellSet");
	MarkNativeAsOptional("CellSet.Insert");
	MarkNativeAsOptional("CellSet.Erase");
	MarkNativeAsOptional("CellSet.Find");
	MarkNativeAsOptional("CellSet.Size.get");
	MarkNativeAsOptional("CellSet.Empty.get");
	MarkNativeAsOptional("CellSet.Swap");
	MarkNativeAsOptional("CellSet.Equals");
	MarkNativeAsOptional("CellSet.Clear");
	MarkNativeAsOptional("CellSet.Iterator");
	MarkNativeAsOptional("StringSet.StringSet");
	MarkNativeAsOptional("StringSet.Insert");
	MarkNativeAsOptional("StringSet.Find");
	MarkNativeAsOptional("StringSet.Erase");
	MarkNativeAsOptional("StringSet.Size.get");
	MarkNativeAsOptional("StringSet.Empty.get");
	MarkNativeAsOptional("StringSet.Swap");
	MarkNativeAsOptional("StringSet.Equals");
	MarkNativeAsOptional("StringSet.Clear");
	MarkNativeAsOptional("StringSet.Iterator");
	MarkNativeAsOptional("CellSetIterator.Next");
	MarkNativeAsOptional("CellSetIterator.Get");
	MarkNativeAsOptional("StringSetIterator.Next");
	MarkNativeAsOptional("StringSetIterator.Get");
}
#endif