namespace ClientSeaScrew
{
    partial class ProfileForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureBoxAvatar = new System.Windows.Forms.PictureBox();
            this.labelFirstName = new System.Windows.Forms.Label();
            this.labelLastname = new System.Windows.Forms.Label();
            this.buttonToChat = new System.Windows.Forms.Button();
            this.buttonExitToAuthorazation = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxAvatar)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBoxAvatar
            // 
            this.pictureBoxAvatar.Location = new System.Drawing.Point(90, 78);
            this.pictureBoxAvatar.Name = "pictureBoxAvatar";
            this.pictureBoxAvatar.Size = new System.Drawing.Size(313, 215);
            this.pictureBoxAvatar.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBoxAvatar.TabIndex = 0;
            this.pictureBoxAvatar.TabStop = false;
            // 
            // labelFirstName
            // 
            this.labelFirstName.AutoSize = true;
            this.labelFirstName.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelFirstName.Location = new System.Drawing.Point(186, 311);
            this.labelFirstName.Name = "labelFirstName";
            this.labelFirstName.Size = new System.Drawing.Size(51, 27);
            this.labelFirstName.TabIndex = 1;
            this.labelFirstName.Text = "Имя";
            // 
            // labelLastname
            // 
            this.labelLastname.AutoSize = true;
            this.labelLastname.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelLastname.Location = new System.Drawing.Point(186, 361);
            this.labelLastname.Name = "labelLastname";
            this.labelLastname.Size = new System.Drawing.Size(103, 27);
            this.labelLastname.TabIndex = 2;
            this.labelLastname.Text = "Фамилия";
            // 
            // buttonToChat
            // 
            this.buttonToChat.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.buttonToChat.Font = new System.Drawing.Font("Consolas", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonToChat.Location = new System.Drawing.Point(432, 12);
            this.buttonToChat.Name = "buttonToChat";
            this.buttonToChat.Size = new System.Drawing.Size(85, 48);
            this.buttonToChat.TabIndex = 3;
            this.buttonToChat.Text = "Чат";
            this.buttonToChat.UseVisualStyleBackColor = false;
            this.buttonToChat.Click += new System.EventHandler(this.buttonToChat_Click);
            // 
            // buttonExitToAuthorazation
            // 
            this.buttonExitToAuthorazation.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.buttonExitToAuthorazation.Font = new System.Drawing.Font("Consolas", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonExitToAuthorazation.Location = new System.Drawing.Point(432, 78);
            this.buttonExitToAuthorazation.Name = "buttonExitToAuthorazation";
            this.buttonExitToAuthorazation.Size = new System.Drawing.Size(85, 57);
            this.buttonExitToAuthorazation.TabIndex = 4;
            this.buttonExitToAuthorazation.Text = "Выйти";
            this.buttonExitToAuthorazation.UseVisualStyleBackColor = false;
            this.buttonExitToAuthorazation.Click += new System.EventHandler(this.buttonExitToAuthorization_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(176, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(155, 27);
            this.label1.TabIndex = 5;
            this.label1.Text = "Мой профиль";
            // 
            // ProfileForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(128)))), ((int)(((byte)(255)))));
            this.ClientSize = new System.Drawing.Size(529, 483);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonExitToAuthorazation);
            this.Controls.Add(this.buttonToChat);
            this.Controls.Add(this.labelLastname);
            this.Controls.Add(this.labelFirstName);
            this.Controls.Add(this.pictureBoxAvatar);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "ProfileForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "vk1000-7";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxAvatar)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.PictureBox pictureBoxAvatar;
        public System.Windows.Forms.Label labelFirstName;
        public System.Windows.Forms.Label labelLastname;
        public System.Windows.Forms.Button buttonToChat;
        public System.Windows.Forms.Button buttonExitToAuthorazation;
        public System.Windows.Forms.Label label1;
    }
}