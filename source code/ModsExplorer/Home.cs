namespace ModsExplorer
{
    public partial class Home : Form
    {
        private PictureBox[] multPicBoxes;
        public Home()
        {
            InitializeComponent();
            multPicBoxes = CreateMultPicBox();
        }

        PictureBox[] CreateMultPicBox()
        {
            int x = 4;//ÁÐ
            int l = 48;//Í¼Æ¬×ÜÊý
            int sizeX = 200;
            int sizeY = 100;
            string picPath = "F:/FF14PrintScreen/2021-12-24_03-21-25-921_ReminOutDoor169.jpg";

            PictureBox[] picBoxes = new PictureBox[l];
            for (int i = 0; i < l; i++)
            {
                picBoxes[i] = new System.Windows.Forms.PictureBox()
                {
                    Anchor = AnchorStyles.Right | AnchorStyles.Top,
                    BackgroundImageLayout = ImageLayout.None,
                    //BorderStyle = BorderStyle.Fixed3D,
                    Location = new Point(this.Width - 40 - x * sizeX + (sizeX + 5) * (i % x), (60 + (i / x) * (sizeY + 10))),
                    Name = ("pictureBoxes" + i.ToString()),
                    Size = new Size(sizeX, sizeY),
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
            int x = this.Width;
            for (int i = 0; i < multPicBoxes.GetLength(0); i++)
            {
                multPicBoxes[i].Left = x - 400;
            }
        }
    }



}