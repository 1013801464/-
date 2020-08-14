using System;
using System.Text.RegularExpressions;

namespace 正则表达式 {
    class Program {
        static void Main(string[] args) {
            string input = "我\n爱\n你\n中\n国\nchina万\n岁";
            string pattern = @"(?<str>.(?=[\u4e00-\u9fa5]))";
            string replacement = "${str}\n";
            var val = Regex.Replace(input, pattern, replacement);
            Console.WriteLine(val);
        }
    }
}
