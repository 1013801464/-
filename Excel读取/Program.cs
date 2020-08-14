using System;
using System.Collections.Generic;
using System.Data;
using System.Data.OleDb;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Excel读取 {
    class Program {
        static void Main(string[] args) {
            Regex reg = new Regex("(\\d+)");
            Match match = reg.Match("TE_0301A");
            string num = match.Value;
            string value = match.Groups[1].Value;
            Console.WriteLine("value的值为：{0}", value);
            DataSet ds = ExcelToDS(@"D:\Excel\给郝部长氟化铝点表.xls");
            Console.WriteLine("Test");
            // ds.Tables[0].Rows[0]
        }
        
        public static DataSet ExcelToDS(string Path)  {
            // 版本警告: Provider=Microsoft.Jet.OLEDB.4.0只支持Office97-2003，不支持2007。如果需要支持2007，使用 Provider='Microsoft.Ace.OLEDB.12.0
            string strConn = "Provider=Microsoft.Jet.OLEDB.4.0;" + "Data Source=" + Path + ";" + "Extended Properties=Excel 8.0;";
            OleDbConnection conn = new OleDbConnection(strConn);
            conn.Open();
            string strExcel = "";
            OleDbDataAdapter myCommand = null;
            DataSet ds = null;
            // 查询数据: OLEDB会自动生成列名F1,F2……Fn 
            strExcel = "select * from [sheet1$]";
            myCommand = new OleDbDataAdapter(strExcel, strConn);
            ds = new DataSet();
            myCommand.Fill(ds, "table1");
            return ds;
        }
    }
}
