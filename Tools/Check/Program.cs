using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Check
{
    class Program
    {
        static void Main(string[] args)
        {
            StringBuilder sb = new StringBuilder();
            string line;
            while ((line = Console.ReadLine()) != null)
            {
                line = line.Trim();
                if (!line.StartsWith("Week"))
                {
                    sb.AppendLine(line.Replace("+10 LeetCoin", Environment.NewLine));
                }
            }
            List<string> left = new List<string>();
            List<bool> right = new List<bool>();
            foreach (var problem in sb.ToString().Split("\n", StringSplitOptions.RemoveEmptyEntries).Select(t => t.Trim()))
            {
                if (problem.Length > 0 && !problem.Contains("35"))
                {
                    string filename = string.Format(@"c:\dev\Competition\Competition\LEET_{0}.cpp", problem.ToUpper().Replace(" ", "_"));
                    bool exists = File.Exists(filename);
                    left.Add(problem);
                    right.Add(exists);
                }
            }
            int max = left.Select(t => t.Length).Max();
            for (int i = 0; i < left.Count; i++)
            {
                Console.WriteLine(left[i] + new string(' ', max + 2 - left[i].Length) + right[i]);
            }
        }
    }
}
