using MySql.Data.MySqlClient;
namespace ModsExplorer
{
    public partial class Home : Form
    {
  
        
        public Home()
        {
            InitializeComponent();
            multPicBoxes = CreateMultPicBox();
        }       

        private void Home_SizeChanged(object sender, EventArgs e)
        {
            AlterMultPicBox();
            this.Text=String.Format("{0},{1}",this.Width,this.Height); 
        }


        private PictureBox[] multPicBoxes;
        int picSizeX = 200;
        int picSizeY = 100;
        PictureBox[] CreateMultPicBox()
        {
            int l = 100;//图片总数
            int x = this.Width / picSizeX;//列
            string picPath = "F:/FF14PrintScreen/wheat field_002.jpg";

            PictureBox[] picBoxes = new PictureBox[l];
            for (int i = 0; i < l; i++)
            {
                picBoxes[i] = new System.Windows.Forms.PictureBox()
                {
                    Anchor = AnchorStyles.Right | AnchorStyles.Top,
                    BackgroundImageLayout = ImageLayout.None,
                    BorderStyle = BorderStyle.FixedSingle,
                    Location = new Point(this.Width - 40 - x * picSizeX + (picSizeX + 5) * (i % x), (60 + (i / x) * (picSizeY + 7))),
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
            int x = (this.Width - 150) / picSizeX ;      //列
            for (int i = 0; i < multPicBoxes.GetLength(0); i++)
            {
                multPicBoxes[i].Left = this.Width - 70 - x * picSizeX + (picSizeX + 5) * (i % x);
                multPicBoxes[i].Top = ((60 + (i / x) * (picSizeY + 7)));
            }
        }
    }



}