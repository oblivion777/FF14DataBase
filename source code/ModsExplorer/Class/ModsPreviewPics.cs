using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;
namespace ModsExplorer
{
    internal class ModsPreviewPics
    {

        Home homeWinForn;                       //主窗体对象
        private PictureBox[] multPicBoxes;      //图片框对象数组
        int picSizeX = 200;                     //单张图片横轴像素
        int picSizeY = 100;                     //单张图片纵轴像素
        static int previewImagesCount = 100;    //显示图片总数
        int picsRow;                            //列
        private Label[] modsNameLabels;         //Label
        CallMySQL readerModsInfo = new CallMySQL();
        public enum Operate
        {
            NONE,LAST,NEXT
        }
        public ModsPreviewPics(Home hObj)
        {
            homeWinForn = hObj;
            multPicBoxes = new PictureBox[previewImagesCount];
            modsNameLabels=new Label[previewImagesCount];
            calcRow();
            readerModsInfo.SelectLastPicsPath();

            CreateMultPicBox();
            CreateModsNameLabels();
        }
        //批量生成图片框
        private void CreateMultPicBox()
        {
            for (int i = 0; i < previewImagesCount; i++)
            {

                multPicBoxes[i] = new System.Windows.Forms.PictureBox()
                {
                    //Anchor = AnchorStyles.Left | AnchorStyles.Top,
                    BackgroundImageLayout = ImageLayout.None,
                    BorderStyle = BorderStyle.FixedSingle,
                    Location = new Point(picLocationX(i), picLocationY(i)),
                    Name = ("pictureBoxes" + i.ToString()),
                    Size = new Size(picSizeX, picSizeY),
                    SizeMode = PictureBoxSizeMode.Zoom,
                    TabIndex = 0,
                    TabStop = false,
                    Parent = homeWinForn.panelPicsBox1,
                };
            }
            readerModsInfo.CloseReader();
        }

        //批量更新图片和mod文件名
        public void UpdateMultPicBox(Operate action)
        {
            CallMySQL.ModInfo modInfo;
            switch (action)
            {
                case Operate.LAST:
                    {
                        readerModsInfo.SelectLastPicsPath();
                        break;
                    }
                case Operate.NEXT:
                    {
                        readerModsInfo.SelectNextPicsPath();
                        break;
                    }
                default: throw (new Exception("别搞事!"));
            }
            for (int i = 0; i < previewImagesCount; i++)
            {
#pragma warning disable CS8600 // 将 null 字面量或可能为 null 的值转换为非 null 类型。
                modInfo = readerModsInfo.GetModInfo();
                if (modInfo.picPath == null)
#pragma warning restore CS8600 // 将 null 字面量或可能为 null 的值转换为非 null 类型。
                {
                    multPicBoxes[i].Image = null;
                    continue;
                }
                else
                {
                    multPicBoxes[i].Image = Image.FromFile(modInfo.picPath);//更新图片对象
                    modsNameLabels[i].Text = modInfo.name;//更新mod名
                }               
            }
            readerModsInfo.CloseReader();
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }

        //用于改变窗体时调整图片框位置
        public void AlterMultPicBox()
        {
            calcRow();
            for (int i = 0; i < multPicBoxes.GetLength(0); i++)
            {   //调整图片框
                multPicBoxes[i].Left = picLocationX(i);
                multPicBoxes[i].Top = picLocationY(i);
                //调整label
                modsNameLabels[i].Left = multPicBoxes[i].Location.X;
                modsNameLabels[i].Top = multPicBoxes[i].Location.Y + picSizeY;
            }
        }

        /*图片横坐标*/
        int picLocationX(int i)
        {        
            if (picsRow <= 1)
            {
                picsRow = 1;
            }
            return (picSizeX + 5) * (i % picsRow);
        }
        /*图片纵坐标*/
        const int INTERVAL = 60;     //间距
        int picLocationY(int i)
        {
            if (picsRow <= 1)
            {
                picsRow = 1;
            }
            /*行数=i÷列数的商(舍去余数)*/
            return (20 + (i / picsRow) * (picSizeY + INTERVAL)) + homeWinForn.panelPicsBox1.AutoScrollPosition.Y;
        }
        //计算列数
        int calcRow()
        {
            picsRow = (homeWinForn.panelPicsBox1.Width - 30) / picSizeX;//列
            return picsRow;
        }

        public static int GetPreviewImagesCount()
        {
            return previewImagesCount;
        }

        /*=====================================================================*/
        void CreateModsNameLabels()
        {
            for (int i = 0; i < previewImagesCount; i++)
            {
                modsNameLabels[i] = new Label()
                {
                    Location = new System.Drawing.Point(0, 0),
                    Name = ("modsNameLabel" + i.ToString()),
                    Size = new System.Drawing.Size(picSizeX, INTERVAL),
                    TabIndex = 0,
                    TabStop = false,
                    TextAlign = System.Drawing.ContentAlignment.TopCenter,
                    Parent = homeWinForn.panelPicsBox1,
                };            
            }
            readerModsInfo.CloseReader();
        }

    }
}
