using MySql.Data.MySqlClient;
namespace ModsExplorer
{
    public partial class Home : Form
    {
        ModsPreviewPics modsPreviewPics;

        public Home()
        {
            CheckForIllegalCrossThreadCalls = false;
            InitializeComponent();           
            modsPreviewPics=new ModsPreviewPics(this);
            
            
        }

        private void Home_Load(object sender, EventArgs e)
        {
            modsPreviewPics.AlterMultPicBox();
            modsPreviewPics.UpdateControls(ModsPreviewPics.Operate.LAST);
            SetLabelTest();
        }

        private void Home_SizeChanged(object sender, EventArgs e)
        {
            modsPreviewPics.AlterMultPicBox();
            //this.labelTest.Text = String.Format("{0}", this.panelPicsBox1.AutoScrollPosition.Y);


            //FixLeftSideControler();
            //pictureBox1         
        }

        private void lastPage_Click(object sender, EventArgs e)
        {   //上一页
            modsPreviewPics.UpdateControls(ModsPreviewPics.Operate.LAST);
            panelPicsBox1.AutoScrollPosition = new Point(0, 0);
            SetLabelTest();
        }

        private void nextPage_Click(object sender, EventArgs e)
        {   //下一页
            if (modsPreviewPics.readerModsInfo.GetPicsIndex() == modsPreviewPics.readerModsInfo.GetCountRow())
            {
                return;
            }
            modsPreviewPics.UpdateControls(ModsPreviewPics.Operate.NEXT);
            panelPicsBox1.AutoScrollPosition = new Point(0, 0);
            SetLabelTest();
        }

        private void Home_MouseWheel(object sender, MouseEventArgs e)
        {   //鼠标滚动事件
            //FixLeftSideControler();           
        }

        private void Home_Scroll(object sender, ScrollEventArgs e)
        {
            //FixLeftSideControler();
        }

        void SetLabelTest()
        {
            labelTest.Text = modsPreviewPics.readerModsInfo.GetPicsIndex().ToString() + '/' +
                modsPreviewPics.readerModsInfo.GetCountRow().ToString();
        }
    }



}