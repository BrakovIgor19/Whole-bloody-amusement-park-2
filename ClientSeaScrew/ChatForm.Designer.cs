namespace ClientSeaScrew
{
    partial class ChatForm
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.chatBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxInputMessage = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.listBoxConversations = new System.Windows.Forms.ListBox();
            this.buttonSend = new System.Windows.Forms.Button();
            this.buttonExit = new System.Windows.Forms.Button();
            this.buttonToProfile = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // chatBox
            // 
            this.chatBox.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.chatBox.Font = new System.Drawing.Font("Consolas", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chatBox.Location = new System.Drawing.Point(25, 48);
            this.chatBox.Multiline = true;
            this.chatBox.Name = "chatBox";
            this.chatBox.ReadOnly = true;
            this.chatBox.Size = new System.Drawing.Size(473, 277);
            this.chatBox.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(181, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(129, 27);
            this.label1.TabIndex = 1;
            this.label1.Text = "Окно чата";
            // 
            // textBoxInputMessage
            // 
            this.textBoxInputMessage.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBoxInputMessage.Location = new System.Drawing.Point(25, 370);
            this.textBoxInputMessage.Multiline = true;
            this.textBoxInputMessage.Name = "textBoxInputMessage";
            this.textBoxInputMessage.Size = new System.Drawing.Size(473, 32);
            this.textBoxInputMessage.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(20, 340);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(155, 27);
            this.label2.TabIndex = 3;
            this.label2.Text = "Введите SMS";
            // 
            // listBoxConversations
            // 
            this.listBoxConversations.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.listBoxConversations.FormattingEnabled = true;
            this.listBoxConversations.ItemHeight = 27;
            this.listBoxConversations.Location = new System.Drawing.Point(524, 48);
            this.listBoxConversations.Name = "listBoxConversations";
            this.listBoxConversations.Size = new System.Drawing.Size(264, 274);
            this.listBoxConversations.TabIndex = 4;
            this.listBoxConversations.SelectedIndexChanged += new System.EventHandler(this.listBoxConversations_SelectedIndexChanged);
            // 
            // buttonSend
            // 
            this.buttonSend.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.buttonSend.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonSend.ForeColor = System.Drawing.SystemColors.ControlText;
            this.buttonSend.Location = new System.Drawing.Point(524, 370);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Size = new System.Drawing.Size(264, 32);
            this.buttonSend.TabIndex = 5;
            this.buttonSend.Text = "Отправить";
            this.buttonSend.UseVisualStyleBackColor = false;
            this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // buttonExit
            // 
            this.buttonExit.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.buttonExit.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonExit.Location = new System.Drawing.Point(819, 111);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(120, 84);
            this.buttonExit.TabIndex = 6;
            this.buttonExit.Text = "Выйти";
            this.buttonExit.UseVisualStyleBackColor = false;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // buttonToProfile
            // 
            this.buttonToProfile.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.buttonToProfile.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonToProfile.Location = new System.Drawing.Point(819, 12);
            this.buttonToProfile.Name = "buttonToProfile";
            this.buttonToProfile.Size = new System.Drawing.Size(120, 84);
            this.buttonToProfile.TabIndex = 7;
            this.buttonToProfile.Text = "Мой профиль";
            this.buttonToProfile.UseVisualStyleBackColor = false;
            this.buttonToProfile.Click += new System.EventHandler(this.buttonToProfile_Click);
            // 
            // ChatForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(128)))), ((int)(((byte)(255)))));
            this.ClientSize = new System.Drawing.Size(951, 428);
            this.Controls.Add(this.buttonToProfile);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.buttonSend);
            this.Controls.Add(this.listBoxConversations);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBoxInputMessage);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.chatBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "ChatForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "vk1000-7";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ChatForm_FormClosing);
            this.VisibleChanged += new System.EventHandler(this.ChatForm_VisibleChanged);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.TextBox chatBox;
        public System.Windows.Forms.Label label1;
        public System.Windows.Forms.TextBox textBoxInputMessage;
        public System.Windows.Forms.Label label2;
        public System.Windows.Forms.ListBox listBoxConversations;
        public System.Windows.Forms.Button buttonSend;
        public System.Windows.Forms.Button buttonExit;
        public System.Windows.Forms.Button buttonToProfile;
    }
}

