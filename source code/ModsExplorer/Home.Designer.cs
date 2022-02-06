namespace ModsExplorer
{
    partial class Home
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.picsGroupBox1 = new System.Windows.Forms.GroupBox();
            this.topPictureBox1 = new System.Windows.Forms.PictureBox();
            this.lastPage = new System.Windows.Forms.Button();
            this.nextPage = new System.Windows.Forms.Button();
            this.btmPanel1 = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.topPictureBox1)).BeginInit();
            this.btmPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // picsGroupBox1
            // 
            this.picsGroupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.picsGroupBox1.BackColor = System.Drawing.SystemColors.Control;
            this.picsGroupBox1.Location = new System.Drawing.Point(165, 49);
            this.picsGroupBox1.Margin = new System.Windows.Forms.Padding(3, 40, 3, 3);
            this.picsGroupBox1.Name = "picsGroupBox1";
            this.picsGroupBox1.Size = new System.Drawing.Size(423, 566);
            this.picsGroupBox1.TabIndex = 0;
            this.picsGroupBox1.TabStop = false;
            this.picsGroupBox1.Visible = false;
            // 
            // topPictureBox1
            // 
            this.topPictureBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.topPictureBox1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.topPictureBox1.Location = new System.Drawing.Point(0, 0);
            this.topPictureBox1.Name = "topPictureBox1";
            this.topPictureBox1.Size = new System.Drawing.Size(989, 48);
            this.topPictureBox1.TabIndex = 1;
            this.topPictureBox1.TabStop = false;
            // 
            // lastPage
            // 
            this.lastPage.Location = new System.Drawing.Point(28, 26);
            this.lastPage.Name = "lastPage";
            this.lastPage.Size = new System.Drawing.Size(99, 22);
            this.lastPage.TabIndex = 2;
            this.lastPage.Text = "上一页";
            this.lastPage.UseVisualStyleBackColor = true;
            this.lastPage.Click += new System.EventHandler(this.lastPage_Click);
            // 
            // nextPage
            // 
            this.nextPage.Location = new System.Drawing.Point(28, 54);
            this.nextPage.Name = "nextPage";
            this.nextPage.Size = new System.Drawing.Size(99, 22);
            this.nextPage.TabIndex = 3;
            this.nextPage.Text = "下一页";
            this.nextPage.UseVisualStyleBackColor = true;
            this.nextPage.Click += new System.EventHandler(this.nextPage_Click);
            // 
            // btmPanel1
            // 
            this.btmPanel1.Controls.Add(this.nextPage);
            this.btmPanel1.Controls.Add(this.lastPage);
            this.btmPanel1.Location = new System.Drawing.Point(0, 49);
            this.btmPanel1.Name = "btmPanel1";
            this.btmPanel1.Size = new System.Drawing.Size(159, 250);
            this.btmPanel1.TabIndex = 5;
            // 
            // Home
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.AutoScrollMargin = new System.Drawing.Size(0, 20);
            this.ClientSize = new System.Drawing.Size(988, 763);
            this.Controls.Add(this.btmPanel1);
            this.Controls.Add(this.topPictureBox1);
            this.Controls.Add(this.picsGroupBox1);
            this.Name = "Home";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Home_Load);
            this.Scroll += new System.Windows.Forms.ScrollEventHandler(this.Home_Scroll);
            this.SizeChanged += new System.EventHandler(this.Home_SizeChanged);

            this.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.Home_MouseWheel);
            ((System.ComponentModel.ISupportInitialize)(this.topPictureBox1)).EndInit();
            this.btmPanel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private PictureBox topPictureBox1;
        internal GroupBox picsGroupBox1;
        private Button lastPage;
        private Button nextPage;
        private Panel btmPanel1;

    }
}