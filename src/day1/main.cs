using System;
using System.Collections.Generic;
using System.IO;

public class Day1
{
	public static void Main(string[] args)
	{
		List<int> ll = new List<int>();
		string[] lines = File.ReadAllLines(@"input.txt");
		foreach(string line in lines)
		{
			int v = Int32.Parse(line);
			ll.Add(v);
		}
		part1(ll);
		part2(ll);
	}
	
	static void part1(List<int> ll)
	{
		int cnt = ll.Count - 1;
		int incr = 0;
		for(int i = 0; i < cnt; i++)
		{
			int i1 = ll[i];
			int i2 = ll[i+1];
			if(i2 > i1) incr++;
		}
		Console.WriteLine("PART 1 incr = {0}", incr);
	}
	
	static void part2(List<int> ll)
	{
		int incr = 0;
		while(ll.Count >= 4)
		{
			int i1 = ll[0] + ll[1] + ll[2];
			int i2 = ll[1] + ll[2] + ll[3];
			if(i2 > i1) incr++;
			ll.RemoveAt(0);
		}
		Console.WriteLine("PART 2 incr = {0}", incr);
	}
}
