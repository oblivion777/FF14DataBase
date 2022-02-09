using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ModsExplorer
{
    internal class CallMySQL
    {   /*查询图片前调用SelectLastPicsPath() OR SelectNextPicsPath()
         * 使用GetPicPath()获取完图片路径后需要关掉reader(执行CloseReader)
         */
        int countRow = 0;//mod数量
        MySqlConnection conn;
        MySqlCommand selectPicsPath;
        MySqlDataReader reader;
        int picsIndex = 0;//用于查询图片
#pragma warning disable CS8618 // 在退出构造函数时，不可为 null 的字段必须包含非 null 值。请考虑声明为可以为 null。
        public CallMySQL():this(GetLoginStr())
        {
            
        }
        public CallMySQL(String conStr)
        {
            conn = new MySqlConnection(conStr);
            ConnectMySQL();
            //用于执行MySQL查询语句的对象
            selectPicsPath = new MySqlCommand(null, conn);
            selectPicsPath.CommandText = "SELECT COUNT(mods.filename)" +
                "FROM mods INNER JOIN preview_pics ON mods.md5 = preview_pics.mod_md5";
            reader = selectPicsPath.ExecuteReader();
            if (!reader.Read())
            {
                throw new Exception("???");
            }
            countRow=reader.GetInt32(0);
            reader.Close();
        }
#pragma warning restore CS8618 // 在退出构造函数时，不可为 null 的字段必须包含非 null 值。请考虑声明为可以为 null。
 
        public void SelectLastPicsPath(int mode = -1)
        {
            String sql = String.Format("SELECT mods.filename,mods.path,preview_pics.filename AS 'pic_name',preview_pics.path AS 'pic_path'" +
                "FROM mods INNER JOIN preview_pics ON mods.md5 = preview_pics.mod_md5 LIMIT {0},{1}",
                setPicsIndex(mode), ModsPreviewPics.GetPreviewImagesCount());
            selectPicsPath.CommandText = sql;
            reader = selectPicsPath.ExecuteReader();
        }

        public void SelectNextPicsPath()
        {
            String sql = String.Format("SELECT mods.filename,mods.path,preview_pics.filename AS 'pic_name',preview_pics.path AS 'pic_path'" +
                "FROM mods INNER JOIN preview_pics ON mods.md5 = preview_pics.mod_md5 LIMIT {0},{1}", 
                setPicsIndex(1), ModsPreviewPics.GetPreviewImagesCount());
            selectPicsPath.CommandText = sql;
            reader = selectPicsPath.ExecuteReader();
        }

        public struct ModInfo
        {
            public string? name = null;
            public string? path = null;
            public string? picPath = null;
        }
        public ModInfo GetModInfo()
        {
            ModInfo modInfo = new();
            if (!reader.Read())
            {
                return modInfo;
            }           
            modInfo.picPath = reader.GetString("pic_path") + reader.GetString("pic_name");
            modInfo.name = reader.GetString("filename");
            modInfo.path = reader.GetString("path");

            return modInfo;
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

        private int setPicsIndex(int mode = 0, int increment = 100)
        {   /*设定从MySQL取回图片路径检索数据的范围,图片路径用于上一页和下一页按钮事件
             * "SELECT filename,path FROM preview_pics LIMIT {0},{1}", setPicsIndex(-1), 100
             */
            switch (mode)
            {
                case 0:
                    {
                        return picsIndex;
                    }
                case 1://向前检索
                    {
                        picsIndex += increment;
                        return picsIndex;
                    }
                case -1://向后检索
                    {
                        picsIndex -= increment;
                        picsIndex = Math.Max(picsIndex, 0);
                        return picsIndex;
                    }
                default:
                    {
                        return picsIndex;
                        //throw (new Exception("别乱搞!"));
                    }
            }
        }

        public void Close()
        {
            conn.Close();
        }

        public void CloseReader()
        {
            try
            {
                reader.Close();
            }
            catch (Exception)
            {
                MessageBox.Show("重复关闭Reader");
            }
            
        }

        public int GetCountRow()
        {
            return countRow;
        }

        public void SetPicsIndex(int index)
        {
            picsIndex = Math.Max(index, 0);
        }

        public int GetPicsIndex()
        {
            return Math.Min(picsIndex + 100, countRow);
        }
    }
}
