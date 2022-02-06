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
            //pictureBox1
            this.Text=String.Format("{0},{1},{2}",this.Width,this.Height, this.AutoScrollPosition.Y);
        }



        private void Home_Load(object sender, EventArgs e)
        {

        }

    }



}