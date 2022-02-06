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

        Home homeWinForn;                   //主窗体对象
        private PictureBox[] multPicBoxes;  //图片框对象数组
        int picSizeX = 200;                 //单张图片横轴像素
        int picSizeY = 100;                 //单张图片纵轴像素
        int previewImagesCount = 100;       //显示图片总数
        int picsRow;                        //列
        CallMySQL readPicsPath = new CallMySQL();
        public ModsPreviewPics(Home hObj)
        {
            homeWinForn = hObj;
            multPicBoxes = new PictureBox[previewImagesCount];
            calcRow();
            readPicsPath.SelectPicsPath();

            CreateMultPicBox();
            
        }
        //批量生成图片框
        private void CreateMultPicBox()
        {

            //string picPath = "F:/FF14PrintScreen/wheat field_002.jpg";
            string picPath;
            for (int i = 0; i < previewImagesCount; i++)
            {
#pragma warning disable CS8600 // 将 null 字面量或可能为 null 的值转换为非 null 类型。
                if ((picPath = readPicsPath.GetPicPath()) == null)
#pragma warning restore CS8600 // 将 null 字面量或可能为 null 的值转换为非 null 类型。
                {
                    break;
                }
                multPicBoxes[i] = new System.Windows.Forms.PictureBox()
                {
                    Anchor = AnchorStyles.Right | AnchorStyles.Top,
                    BackgroundImageLayout = ImageLayout.None,
                    BorderStyle = BorderStyle.FixedSingle,
                    Location = new Point(picLocationX(i), picLocationY(i)),
                    Name = ("pictureBoxes" + i.ToString()),
                    Size = new Size(picSizeX, picSizeY),
                    SizeMode = PictureBoxSizeMode.Zoom,
                    TabIndex = 0,
                    TabStop = false,
                    Parent = homeWinForn,
                };

                multPicBoxes[i].Image = Image.FromFile(picPath);

            }
            //return multPicBoxes;
        }

        //用于改变窗体时调整图片框位置
        public void AlterMultPicBox()
        {
            calcRow();
            for (int i = 0; i < multPicBoxes.GetLength(0); i++)
            {
                multPicBoxes[i].Left = picLocationX(i);
                multPicBoxes[i].Top = picLocationY(i) + homeWinForn.picsGroupBox1.Location.Y;
            }
        }

        /*横向图片位置*/
        int picLocationX(int i)
        {        
            if (picsRow <= 1)
            {
                picsRow = 1;
            }
            return (picSizeX + 5) * (i % picsRow) + homeWinForn.picsGroupBox1.Location.X;
        }
        /*纵向图片位置*/
        int picLocationY(int i)
        {       
            if (picsRow <= 1)
            {
                picsRow = 1;
            }
            return (20 + (i / picsRow) * (picSizeY + 7));
        }

        int calcRow()
        {
            picsRow = (homeWinForn.Width - 200) / picSizeX;//列
            return picsRow;
        }
    }
}
