#include <smset>

public void OnPluginStart()
{
	CellSet set = new CellSet();
	CellSet set2 = new CellSet();
	for (int i = 0; i < 10; ++i)
	{
		set.Insert(i);
		set2.Insert(i);
	}

	PrintToServer("Length %d %d", set.Size, set2.Size);
	PrintToServer("Equals %d", set.EqualTo(set2));
	PrintToServer("Find 4 %d", set.Find(4));
	set.Erase(4);
	PrintToServer("Find 4 %d", set.Find(4));
	PrintToServer("Equals %d", set.EqualTo(set2));
	PrintToServer("Length %d %d", set.Size, set2.Size);
	set.Clear();
	PrintToServer("Empty %d", set.Empty);
	set.Swap(set2);
	PrintToServer("Length %d %d", set.Size, set2.Size);

	PrintToServer("");

	StringSet sset = new StringSet();
	StringSet sset2 = new StringSet();

	sset.Insert("abc");
	sset.Insert("bca");
	sset2.Insert("bca");
	sset2.Insert("abc");

	PrintToServer("Length %d %d", sset.Size, sset2.Size);
	PrintToServer("Equals %d", sset.EqualTo(sset2));
	PrintToServer("Find abc %d", sset.Find("abc"));
	sset.Erase("abc");
	PrintToServer("Find abc %d", sset.Find("abc"));
	PrintToServer("Equals %d", sset.EqualTo(sset2));
	PrintToServer("Length %d %d", sset.Size, sset2.Size);
	sset.Clear();
	PrintToServer("Empty %d", sset.Empty);
	sset.Swap(sset2);
	PrintToServer("Length %d %d", sset.Size, sset2.Size);

	delete set;
	delete set2;
	delete sset;
	delete sset2;
}