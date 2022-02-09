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
            CheckForIllegalCrossThreadCalls = false;
                       
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
            this.labelTest.Text = String.Format("{0}", this.panelPicsBox1.AutoScrollPosition.Y);
            
            //FixLeftSideControler();
            //pictureBox1         
        }



        private void Home_Load(object sender, EventArgs e)
        {
            modsPreviewPics.AlterMultPicBox();
            modsPreviewPics.UpdateMultPicBox(ModsPreviewPics.Operate.LAST);
        }

        private void lastPage_Click(object sender, EventArgs e)
        {   //上一页
            modsPreviewPics.UpdateMultPicBox(ModsPreviewPics.Operate.LAST);
            panelPicsBox1.AutoScrollPosition = new Point(0, 0);
        }

        private void nextPage_Click(object sender, EventArgs e)
        {   //下一页
            modsPreviewPics.UpdateMultPicBox(ModsPreviewPics.Operate.NEXT);
            panelPicsBox1.AutoScrollPosition = new Point(0, 0);
        }

        private void Home_MouseWheel(object sender, MouseEventArgs e)
        {   //鼠标滚动事件
            //FixLeftSideControler();           
        }

        private void Home_Scroll(object sender, ScrollEventArgs e)
        {
            //FixLeftSideControler();
        }

        void FixLeftSideControler()
        {
            this.btmPanel1.Top = 49;
            this.topPictureBox1.Top = 0;
        }
    }



}