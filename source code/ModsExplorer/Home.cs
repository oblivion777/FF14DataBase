using MySql.Data.MySqlClient;
namespace ModsExplorer
{
    public partial class Home : Form
    {
  
        
        public Home()
        {
            InitializeComponent();
            multPicBoxes = CreateMultPicBox();
            ModsPreviewPics conn = new ModsPreviewPics();            
            //conn.ConnectMySQL();
        }       

        private void Home_SizeChanged(object sender, EventArgs e)
        {
            AlterMultPicBox();
            //pictureBox1
            this.Text=String.Format("{0},{1},{2}",this.Width,this.Height, this.AutoScrollPosition.Y);
        }




        private PictureBox[] multPicBoxes;
        int picSizeX = 200;
        int picSizeY = 100;
        int previewImagesCount = 100;//显示图片总数

        PictureBox[] CreateMultPicBox()
        {
            int x = (this.Width - 200) / picSizeX;//列
            string picPath = "F:/FF14PrintScreen/wheat field_002.jpg";

            PictureBox[] picBoxes = new PictureBox[previewImagesCount];
            for (int i = 0; i < previewImagesCount; i++)
            {
                picBoxes[i] = new System.Windows.Forms.PictureBox()
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
                    Parent = this,
                };
                picBoxes[i].Image = Image.FromFile(picPath);
            }
            return picBoxes;
        }

        void AlterMultPicBox()
        {
            
            for (int i = 0; i < multPicBoxes.GetLength(0); i++)
            {
                multPicBoxes[i].Left = picLocationX(i);
                multPicBoxes[i].Top = picLocationY(i) + this.picsGroupBox1.Location.Y;
            }           
        }
        
        int picLocationX(int i)
        {   /*横向图片位置*/
            int x = (this.Width - 200) / picSizeX;//列       
            if(x <= 1)
            {
                x = 1;
            }
            return (picSizeX + 5) * (i % x) + this.picsGroupBox1.Location.X;
        }
        
        int picLocationY(int i)
        {   /*纵向图片位置*/
            int x = (this.Width - 200) / picSizeX;//列          
            if (x <= 1)
            {
                x = 1;
            }
            //return (20 + (i / x) * (picSizeY + 7)) - picsBoxScrollBar.Value * (previewImagesCount / x);
            return (20 + (i / x) * (picSizeY + 7));
        }

        private void Home_Load(object sender, EventArgs e)
        {

        }

    }



}