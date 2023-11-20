using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ClientSeaScrew
{
    public partial class ChatForm : Form
    {
        private AuthorizationForm authorizationForm;

        public ChatForm(AuthorizationForm authorizationForm)
        {
            this.authorizationForm = authorizationForm;
            InitializeComponent();
            ClientBox.Items.Add("Общий чат");
        }

        public void Send(Socket s, Message m)
        {

        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            this.Hide();
            authorizationForm.Show();
        }

        private void ChatForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.authorizationForm.CloseAll();
        }
    }
}
