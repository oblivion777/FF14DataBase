using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ModsExplorer
{
    internal class CallMySQL
    {
        MySqlConnection conn;

        public CallMySQL()
        {
            conn = new MySqlConnection(GetLoginStr());
        }

        public CallMySQL(String conStr)
        {
            conn = new MySqlConnection(conStr);
        }

        public void ConnectMySQL()
        {          
            try
            {
                conn.Open();
                MessageBox.Show("已经建立连接");
            }
            catch (Exception)
            {
                MessageBox.Show("连接失败");
            }
            conn.Close();
        }

        static String GetLoginStr()
        {
#pragma warning disable CS8600 // 将 null 字面量或可能为 null 的值转换为非 null 类型。
            String reStr;
            System.IO.StreamReader file = new System.IO.StreamReader(@"D:/FF14DataBase/_log/login_info_cs.txt");
            reStr = file.ReadLine();
            if(reStr == null)
            {
                throw new Exception("读不出东西!");
            }
            return reStr;
        }
    }
}
