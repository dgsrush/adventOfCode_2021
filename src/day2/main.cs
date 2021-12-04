using System;
using System.Collections.Generic;
using System.IO;

public class Row
{
	public string cmd;
	public int val;
	
	public Row(string c, int v)
	{
		cmd = c;
		val = v;
	}
	
	public void print()
	{
		Console.WriteLine("{0} = {1}", cmd, val);
	}
}

public class Day1
{
	public static void Main(string[] args)
	{
		List<Row> ll = new List<Row>();
		string[] lines = File.ReadAllLines(@"input.txt");
		foreach(string line in lines)
		{
			if(line.Length > 0)
			{
				string[] vv = line.Split(null, 2);
				int v = Int32.Parse(vv[1]);
				Row r = new Row(vv[0], v);
				ll.Add(r);
			}
		}
		part1(ll);
		part2(ll);
	}
	
	static void part1(List<Row> ll)
	{
		int horiz = 0;
		int depth = 0;
		
		for(int i = 0; i < ll.Count; i++)
		{
			if(ll[i].cmd == "forward")
				horiz += ll[i].val;
			else if(ll[i].cmd == "up")
				depth -= ll[i].val;
			else if(ll[i].cmd == "down")
				depth += ll[i].val;
		}
		
		Console.WriteLine("PART 1 horiz = {0}", horiz);
		Console.WriteLine("PART 1 depth = {0}", depth);
		Console.WriteLine("PART 1 answer = {0}", horiz * depth);
	}
	
	static void part2(List<Row> ll)
	{
		int horiz = 0;
		int depth = 0;
		int aim = 0;

		for(int i = 0; i < ll.Count; i++)
		{
			if(ll[i].cmd == "forward")
			{
				horiz += ll[i].val;
				depth += aim * ll[i].val;
			}
			else if(ll[i].cmd == "up")
			{
				aim -= ll[i].val;
			}
			else if(ll[i].cmd == "down")
			{
				aim += ll[i].val;
			}
		}

		Console.WriteLine("PART 2 horiz = {0}", horiz);
		Console.WriteLine("PART 2 depth = {0}", depth);
		Console.WriteLine("PART 2 answer = {0}", horiz * depth);
	}
}
