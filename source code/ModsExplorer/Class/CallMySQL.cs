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
        public MySqlCommand selectPicsPath;
        public MySqlDataReader reader;
        int picsIndex = 0;
#pragma warning disable CS8618 // 在退出构造函数时，不可为 null 的字段必须包含非 null 值。请考虑声明为可以为 null。
        public CallMySQL():this(GetLoginStr())
        {
            
        }

        public CallMySQL(String conStr)
        {
            conn = new MySqlConnection(conStr);
            ConnectMySQL();

            selectPicsPath = new MySqlCommand("SELECT filename,path FROM preview_pics LIMIT 100,100", conn);
        }
#pragma warning restore CS8618 // 在退出构造函数时，不可为 null 的字段必须包含非 null 值。请考虑声明为可以为 null。
        public void SelectLastPicsPath()
        {
            String sql = String.Format("SELECT filename,path FROM preview_pics LIMIT {0},{1}", setPicsIndex(-1), 100);
            selectPicsPath.CommandText = sql;
            reader = selectPicsPath.ExecuteReader();
        }

        public void SelectNextPicsPath()
        {
            String sql = String.Format("SELECT filename,path FROM preview_pics LIMIT {0},{1}", setPicsIndex(1), 100);
            selectPicsPath.CommandText = sql;
            reader = selectPicsPath.ExecuteReader();
        }
        public String? GetPicPath()
        {
            if (!reader.Read())
            {
                return null;
            }
            //String picPath = reader.GetString(1);
            //picPath += reader.GetString(0);
            return reader.GetString(1) + reader.GetString(0);
        }

        private void ConnectMySQL()
        {          
            try
            {
                conn.Open();
                //MessageBox.Show("已经建立连接");
            }
            catch (Exception)
            {
                MessageBox.Show("连接MySQL失败!");               
            }
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

        public int setPicsIndex(int mode = 0, int increment = 100)
        {
            switch (mode)
            {
                case 0:
                    {
                        return picsIndex;
                    }
                case 1:
                    {
                        picsIndex += increment;
                        return picsIndex;
                    }
                case -1:
                    {
                        picsIndex -= increment;
                        if (picsIndex < 0)
                        { picsIndex = 0; }
                        return picsIndex;
                    }
                default:
                    {
                        throw (new Exception("别乱搞!"));
                    }
            }
        }

        public void close()
        {
            conn.Close();
        }
    }
}
