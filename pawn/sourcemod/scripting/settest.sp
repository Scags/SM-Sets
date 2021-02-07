#include <smset>

public void OnPluginStart()
{
	CellSet set = new CellSet(4, 5);
	CellSet set2 = new CellSet(4, 4);
	for (int i = 0; i < 10; ++i)
	{
		set.Insert(i, i+1);
		set2.Insert(i);
	}

	PrintToServer("Length %d %d", set.Size, set2.Size);
	set.Erase(10);
	PrintToServer("Equals %d", set.Equals(set2));
	PrintToServer("Find 4 %d", set.Find(4));
	set.Erase(4, 5);
	PrintToServer("Find 4 %d", set.Find(4));
	PrintToServer("Equals %d", set.Equals(set2));
	PrintToServer("Length %d %d", set.Size, set2.Size);
	set.Clear();
	PrintToServer("Empty %d", set.Empty);
	set.Swap(set2);
	PrintToServer("Length %d %d", set.Size, set2.Size);

	PrintToServer("");

	StringSet sset = new StringSet("ccc", "ccc");
	StringSet sset2 = new StringSet("ccc", "ccc");

	sset.Insert("abc");
	sset.Insert("bca");
	sset2.Insert("bca");
	sset2.Insert("abc");

	PrintToServer("Length %d %d", sset.Size, sset2.Size);
	PrintToServer("Equals %d", sset.Equals(sset2));
	PrintToServer("Find abc %d", sset.Find("abc"));
	sset.Erase("abc");
	PrintToServer("Find abc %d", sset.Find("abc"));
	PrintToServer("Equals %d", sset.Equals(sset2));
	PrintToServer("Length %d %d", sset.Size, sset2.Size);
	sset.Clear();
	PrintToServer("Empty %d", sset.Empty);
	sset.Swap(sset2);
	PrintToServer("Length %d %d", sset.Size, sset2.Size);

	CellSetIterator citer = set.Iterator();
	char buffer[128];
	while (citer.Next())
	{
		Format(buffer, sizeof(buffer), "%s %d", buffer, citer.Get());
	}

	PrintToServer("citer %s", buffer);
	buffer[0] = '\0';

	StringSetIterator siter = sset.Iterator();
	while (siter.Next())
	{
		char buffer2[32];
		siter.Get(buffer2, sizeof(buffer2));
		Format(buffer, sizeof(buffer), "%s %s", buffer, buffer2);
	}

	PrintToServer("siter %s", buffer);

	delete set;
	delete set2;
	delete sset;
	delete sset2;
	delete citer;
	delete siter;
}