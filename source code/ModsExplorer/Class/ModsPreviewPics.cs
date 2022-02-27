using System;
using System.Collections.Generic;
using System.Diagnostics;
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

        const int PX_RATE = 15;
        const int picSizeX = 16 * PX_RATE;                     //单张图片横轴像素
        const int picSizeY = 9 * PX_RATE;                  //单张图片纵轴像素
        
        static int imagesTotal = 100;    //显示图片总数
        int picsRow;                            //列
        private Label[] modsNameLabels;         //Label
        internal CallMySQL readerModsInfo = new CallMySQL();

        Thread[] threads = new Thread[imagesTotal];//线程数组
        //Task[] tasks = new Task[imagesTotal];
        public enum Operate
        {
            NONE,LAST,NEXT
        }
        public ModsPreviewPics(Home hObj)
        {
            homeWinForn = hObj;
            multPicBoxes = new PictureBox[imagesTotal];
            modsNameLabels=new Label[imagesTotal];
            calcRow();
            readerModsInfo.SelectLastPicsPath();

            CreateMultPicBox();
            CreateModsNameLabels();
        }
        //批量生成图片框
        private void CreateMultPicBox()
        {
            for (int i = 0; i < imagesTotal; i++)
            {

                multPicBoxes[i] = new System.Windows.Forms.PictureBox()
                {
                    //Anchor = AnchorStyles.Left | AnchorStyles.Top,
                    BackgroundImageLayout = ImageLayout.None,
                    BorderStyle = BorderStyle.None,
                    Location = new Point(0, 0),
                    Name = ("pictureBoxes" + i.ToString()),
                    Size = new Size(picSizeX, picSizeY),
                    SizeMode = PictureBoxSizeMode.Zoom,
                    TabIndex = 0,
                    TabStop = false,
                    Cursor= Cursors.Hand,
                    Parent = homeWinForn.panelPicsBox1,
                };
#pragma warning disable CS8622 // 参数类型中引用类型的为 Null 性与目标委托不匹配(可能是由于为 Null 性特性)。
                multPicBoxes[i].MouseEnter += new System.EventHandler(MultPicBoxesMouseEnter);
                multPicBoxes[i].MouseLeave += new System.EventHandler(MultPicBoxesMouseLeave);
                multPicBoxes[i].MouseDoubleClick += new MouseEventHandler(MultPicBoxesMouseDoubleClick);
#pragma warning restore CS8622 // 参数类型中引用类型的为 Null 性与目标委托不匹配(可能是由于为 Null 性特性)。
            }

            readerModsInfo.CloseReader();
        }

        //批量更新图片和mod文件名
        public void UpdateControls(Operate action)
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
                default: throw new Exception("别搞事!");
            }

            for (int i = 0; i < multPicBoxes.GetLength(0); i++)
            {   //开启多线程              
                modInfo = readerModsInfo.GetModInfo();
                threads[i] = new Thread(
                    new UpdatePicsThread(multPicBoxes[i], modsNameLabels[i], modInfo).RunThread);
                threads[i].Start();
            }
            for (int i = 0;i < threads.Length; i++)
            {   //等待多线程执行完毕
                threads[i].Join();
            }
            readerModsInfo.CloseReader();
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }
        
        /*用于改变窗体时调整图片框位置*/
        const int INTERVAL_X = 10;//间距
        //delegate void AlterBox(object state);
        public void AlterMultPicBox()
        {
            calcRow();
            int picW = Math.Max(homeWinForn.panelPicsBox1.Width / picsRow - INTERVAL_X - 5, picSizeX);
            int picH = (int)((double)picW / picSizeX * picSizeY);
            object Lock = new();
            //ThreadPool.SetMinThreads(120, 120);
            //ThreadPool.SetMaxThreads(5000, 5000);

            for (int i = 0; i < multPicBoxes.GetLength(0); i++)
            {
                Monitor.Enter(Lock);
                int index = i;
                Monitor.Exit(Lock);
                threads[i] = new Thread(() =>
                {
                    //调整图片框
                    multPicBoxes[index].Left = picLocationX(index, picW);
                    multPicBoxes[index].Top = picLocationY(index, picH);
                    multPicBoxes[index].Width = picW;
                    multPicBoxes[index].Height = picH;
                    //调整label
                    modsNameLabels[index].Left = multPicBoxes[index].Location.X;
                    modsNameLabels[index].Top = multPicBoxes[index].Location.Y + picH;
                });
                threads[i].Start();
            }
            for (int i = 0; i < multPicBoxes.GetLength(0); i++)threads[i].Join();
            //Task.WaitAll();          
        }
        //计算列数
        int calcRow()
        {
            picsRow = (homeWinForn.panelPicsBox1.Width - 40) / picSizeX;//列
            picsRow = Math.Max(picsRow, 1);
            return picsRow;
        }
        /*图片横坐标*/
        int picLocationX(int i, int picW = picSizeX)
        {
            /*
            if (picsRow <= 1)
            {
                picsRow = 1;
            }*/
            return (picW + INTERVAL_X) * (i % picsRow);
        }
        /*图片纵坐标*/
        const int INTERVAL_Y = 60;     //间距
        int picLocationY(int i, int picH = picSizeY)
        {/*
            if (picsRow <= 1)
            {
                picsRow = 1;
            }*/
            /*行数=i÷列数的商(舍去余数)*/
            return (20 + (i / picsRow) * (picH + INTERVAL_Y)) + homeWinForn.panelPicsBox1.AutoScrollPosition.Y;
        }

        public static int GetPreviewImagesCount()
        {
            return imagesTotal;
        }

        /*=====================================================================*/
        void CreateModsNameLabels()
        {
            for (int i = 0; i < imagesTotal; i++)
            {
                modsNameLabels[i] = new Label()
                {
                    Location = new System.Drawing.Point(0, 0),
                    Name = ("modsNameLabel" + i.ToString()),
                    Size = new System.Drawing.Size(picSizeX, INTERVAL_Y),
                    TabIndex = 0,
                    TabStop = false,
                    TextAlign = System.Drawing.ContentAlignment.TopCenter,
                    Parent = homeWinForn.panelPicsBox1,                  
                };                
            }           
            readerModsInfo.CloseReader();
        }

        void MultPicBoxesMouseEnter(object sender, EventArgs e)
        {   //图片框鼠标进入事件
            PictureBox picBox = (PictureBox)sender;
            picBox.BorderStyle = BorderStyle.Fixed3D;
        }

        void MultPicBoxesMouseLeave(object sender, EventArgs e)
        {   //图片框鼠标离开事件
            PictureBox picBox = (PictureBox)sender;
            picBox.BorderStyle = BorderStyle.None;
        }

        void MultPicBoxesMouseDoubleClick(object sender, MouseEventArgs e)
        {
            PictureBox picBox = (PictureBox)sender;
            CallMySQL.ModInfo modInfo = (CallMySQL.ModInfo)picBox.Tag;

            //调用资源管理器
            Process proc = new Process();
            proc.StartInfo.FileName = "explorer";
#pragma warning disable CS8602 // 解引用可能出现空引用。
            string modPath = modInfo.path + modInfo.name;
            proc.StartInfo.Arguments = "/e,/select," + modPath.Replace('/','\\');
#pragma warning restore CS8602 // 解引用可能出现空引用。
            proc.Start();
        }

    }

    internal class UpdatePicsThread
    {
        PictureBox multPicBoxes;
        Label modsNameLabels;
        CallMySQL.ModInfo modInfo;
        double picW = 400;//缩略图横向分辨率
        public UpdatePicsThread(PictureBox pictureBox, Label label, CallMySQL.ModInfo modInfo)
        {
            multPicBoxes = pictureBox;
            modsNameLabels = label;
            this.modInfo = modInfo;
        }

        public void RunThread()
        {
            Image? image;
#pragma warning disable CS8604 // 引用类型参数可能为 null。
            try
            {
                image = Image.FromFile(modInfo.picPath);
                double y = image.Height * (picW / image.Width);
                image = image.GetThumbnailImage((int)picW, (int)y, null, IntPtr.Zero);
            }
            catch (Exception)
            {
                image = null;
            }
#pragma warning restore CS8604 // 引用类型参数可能为 null。
            multPicBoxes.Image = image; //更新图片对象

            if (modInfo.name == null)
            {
                modsNameLabels.Text = null;
            }
            else
            {
                multPicBoxes.Tag = modInfo;
                modInfo.name = modInfo.name.Substring(0, modInfo.name.LastIndexOf('.'));
                modsNameLabels.Text = modInfo.name;//更新mod名
            }
            //GC.Collect();
            //GC.WaitForPendingFinalizers();
        }
    }
}

