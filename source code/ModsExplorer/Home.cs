using MySql.Data.MySqlClient;
namespace ModsExplorer
{
    public partial class Home : Form
    {
        ModsPreviewPics modsPreviewPics;

        public Home()
        {
            InitializeComponent();
            
            modsPreviewPics=new ModsPreviewPics(this);            
            //
            /*
            CallMySQL callMySQL=new CallMySQL();
            callMySQL.SelectPicsPath();
            MessageBox.Show(callMySQL.GetPicPath());
            MessageBox.Show(callMySQL.GetPicPath());
            MessageBox.Show(callMySQL.GetPicPath());
            */
        }       

        private void Home_SizeChanged(object sender, EventArgs e)
        {
            modsPreviewPics.AlterMultPicBox();
            FixControler();
            //pictureBox1
            this.Text=String.Format("{0},{1},{2}",this.Width,this.Height, this.AutoScrollPosition.Y);
        }



        private void Home_Load(object sender, EventArgs e)
        {

        }

        private void lastPage_Click(object sender, EventArgs e)
        {   //上一页
            modsPreviewPics.UpdateMultPicBox(ModsPreviewPics.Operate.LAST);
        }

        private void nextPage_Click(object sender, EventArgs e)
        {   //下一页
            modsPreviewPics.UpdateMultPicBox(ModsPreviewPics.Operate.NEXT);
        }

        private void Home_MouseWheel(object sender, MouseEventArgs e)
        {   //鼠标滚动事件
            FixControler();
            this.Text = String.Format("{0},{1},{2}", btmPanel1.Top, btmPanel1.Location.Y.ToString(), this.AutoScrollPosition.Y);
        }

        private void Home_Scroll(object sender, ScrollEventArgs e)
        {
            FixControler();
        }

        void FixControler()
        {
            this.btmPanel1.Top = 49;
            this.topPictureBox1.Top = 0;
        }
    }



}