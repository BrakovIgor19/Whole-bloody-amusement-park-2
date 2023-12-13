namespace Csharp
{
    partial class Administrative
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
            this.buttonOnServer = new System.Windows.Forms.Button();
            this.buttonCreateClientCross = new System.Windows.Forms.Button();
            this.buttonCreateClientSeaScrew = new System.Windows.Forms.Button();
            this.buttonCreateClientLizard = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.comboBoxClients = new System.Windows.Forms.ComboBox();
            this.buttonCreateClientSatan = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonOnServer
            // 
            this.buttonOnServer.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.buttonOnServer.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonOnServer.Location = new System.Drawing.Point(16, 13);
            this.buttonOnServer.Margin = new System.Windows.Forms.Padding(4);
            this.buttonOnServer.Name = "buttonOnServer";
            this.buttonOnServer.Size = new System.Drawing.Size(169, 117);
            this.buttonOnServer.TabIndex = 0;
            this.buttonOnServer.Text = "Включить сервер";
            this.buttonOnServer.UseVisualStyleBackColor = false;
            this.buttonOnServer.Click += new System.EventHandler(this.buttonOnServer_Click);
            // 
            // buttonCreateClientCross
            // 
            this.buttonCreateClientCross.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.buttonCreateClientCross.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonCreateClientCross.Location = new System.Drawing.Point(232, 19);
            this.buttonCreateClientCross.Margin = new System.Windows.Forms.Padding(4);
            this.buttonCreateClientCross.Name = "buttonCreateClientCross";
            this.buttonCreateClientCross.Size = new System.Drawing.Size(169, 117);
            this.buttonCreateClientCross.TabIndex = 7;
            this.buttonCreateClientCross.Text = "Сотворить крестового клиента";
            this.buttonCreateClientCross.UseVisualStyleBackColor = false;
            this.buttonCreateClientCross.Click += new System.EventHandler(this.buttonCreateClient_Click);
            // 
            // buttonCreateClientSeaScrew
            // 
            this.buttonCreateClientSeaScrew.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.buttonCreateClientSeaScrew.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonCreateClientSeaScrew.Location = new System.Drawing.Point(16, 143);
            this.buttonCreateClientSeaScrew.Name = "buttonCreateClientSeaScrew";
            this.buttonCreateClientSeaScrew.Size = new System.Drawing.Size(169, 117);
            this.buttonCreateClientSeaScrew.TabIndex = 12;
            this.buttonCreateClientSeaScrew.Text = "Сотворить клиента на Си шурупе";
            this.buttonCreateClientSeaScrew.UseVisualStyleBackColor = false;
            this.buttonCreateClientSeaScrew.Click += new System.EventHandler(this.buttonCreateClientSeaScrew_Click);
            // 
            // buttonCreateClientLizard
            // 
            this.buttonCreateClientLizard.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.buttonCreateClientLizard.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonCreateClientLizard.Location = new System.Drawing.Point(232, 143);
            this.buttonCreateClientLizard.Name = "buttonCreateClientLizard";
            this.buttonCreateClientLizard.Size = new System.Drawing.Size(169, 117);
            this.buttonCreateClientLizard.TabIndex = 13;
            this.buttonCreateClientLizard.Text = "Сотворить Ящера";
            this.buttonCreateClientLizard.UseVisualStyleBackColor = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(35, 361);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(389, 27);
            this.label1.TabIndex = 11;
            this.label1.Text = "Популярные имена для клиентов";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(121, 263);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(220, 28);
            this.label5.TabIndex = 9;
            this.label5.Text = "Выбранный клиент";
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("Consolas", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox1.Location = new System.Drawing.Point(64, 308);
            this.textBox1.Margin = new System.Windows.Forms.Padding(4);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(337, 37);
            this.textBox1.TabIndex = 4;
            this.textBox1.Text = "1000-7";
            this.textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // comboBoxClients
            // 
            this.comboBoxClients.FormattingEnabled = true;
            this.comboBoxClients.Location = new System.Drawing.Point(64, 405);
            this.comboBoxClients.Name = "comboBoxClients";
            this.comboBoxClients.Size = new System.Drawing.Size(337, 24);
            this.comboBoxClients.TabIndex = 10;
            this.comboBoxClients.SelectedIndexChanged += new System.EventHandler(this.UpdateTextBox);
            // 
            // buttonCreateClientSatan
            // 
            this.buttonCreateClientSatan.Font = new System.Drawing.Font("Consolas", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonCreateClientSatan.Location = new System.Drawing.Point(436, 19);
            this.buttonCreateClientSatan.Name = "buttonCreateClientSatan";
            this.buttonCreateClientSatan.Size = new System.Drawing.Size(207, 241);
            this.buttonCreateClientSatan.TabIndex = 15;
            this.buttonCreateClientSatan.Text = "Сотвороть клиента на языке САТАНЫ";
            this.buttonCreateClientSatan.UseVisualStyleBackColor = true;
            this.buttonCreateClientSatan.Click += new System.EventHandler(this.buttonCreateClientSatan_Click);
            // 
            // Administrative
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(655, 442);
            this.Controls.Add(this.buttonCreateClientSatan);
            this.Controls.Add(this.buttonCreateClientLizard);
            this.Controls.Add(this.buttonCreateClientSeaScrew);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBoxClients);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.buttonCreateClientCross);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.buttonOnServer);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Administrative";
            this.Text = "Парк кровавых атракционов";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonOnServer;
        private System.Windows.Forms.Button buttonCreateClientCross;
        private System.Windows.Forms.Button buttonCreateClientSeaScrew;
        private System.Windows.Forms.Button buttonCreateClientLizard;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.ComboBox comboBoxClients;
        private System.Windows.Forms.Button buttonCreateClientSatan;
    }
}