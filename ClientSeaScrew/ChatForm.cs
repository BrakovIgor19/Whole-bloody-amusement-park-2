using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ClientSeaScrew
{
    public partial class ChatForm : Form
    {
        private AuthorizationForm authorizationForm;

        public CancellationTokenSource _cancelationTokenSourceUp;
        public CancellationToken _tokenUp;
        public Task tUpdate;

        public AutoResetEvent ev;
        public bool isValid = true;
        public int bufIdConv = -1;

        public ChatForm(AuthorizationForm authorizationForm)
        {
            this.authorizationForm = authorizationForm;

            ev = new AutoResetEvent(false);

            InitializeComponent();
        }

        public void PlayUpdate()
        {
            _cancelationTokenSourceUp = new CancellationTokenSource();
            _tokenUp = _cancelationTokenSourceUp.Token;
            tUpdate = Task.Run(() =>
            {
                while (!_tokenUp.IsCancellationRequested)
                {
                    ev.WaitOne();
                    if (isValid)
                    {
                        if (listBoxConversations.Items.Count != authorizationForm.client.cacheConversations.Count)
                        {
                            List<string> buf = new List<string>();
                            listBoxConversations.Invoke(new Action(() => listBoxConversations.Items.Clear()));
                            foreach (KeyValuePair<uint, string> entry in authorizationForm.client.cacheConversations)
                            {
                                buf.Add(entry.Value);
                            }
                            listBoxConversations.Invoke(new Action(() => listBoxConversations.Items.AddRange(buf.ToArray())));
                        }
                        int buf2 = -1;
                        listBoxConversations.Invoke(new Action(() => buf2 = listBoxConversations.SelectedIndex));
                        if (authorizationForm.client.selectItemToIdConv.ContainsKey((uint)buf2) && authorizationForm.client.selectItemToIdConv[(uint)buf2] == bufIdConv)
                        {
                            chatBox.Invoke(new Action(() => chatBox.AppendText(authorizationForm.client.history[(uint)bufIdConv].Last() + '\r' + '\n')));
                            bufIdConv = -1;
                        }
                    }
                }
            });
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            authorizationForm.ExitToAthorization();
            this.Hide();
            authorizationForm.Show();

        }

        private void ChatForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (authorizationForm.client.isValid)
            {
                this.authorizationForm.CloseAll();
            }
        }

        private void buttonToProfile_Click(object sender, EventArgs e)
        {
            this.Hide();
            authorizationForm.profileForm.Show();
        }

        private void ChatForm_VisibleChanged(object sender, EventArgs e)
        {
            if (Visible && authorizationForm.client.isValid == false)
            {
                PlayUpdate();
                authorizationForm.ev.Set();
            }
        }

        private void buttonSend_Click(object sender, EventArgs e)
        {
            if (textBoxInputMessage.Text != string.Empty)
            {
                int selectItem = -1;
                authorizationForm.chatForm.listBoxConversations.Invoke(new Action(() => selectItem = listBoxConversations.SelectedIndex));
                if (selectItem != -1)
                {
                    authorizationForm.client.bufSendId = authorizationForm.client.selectItemToIdConv[(uint)selectItem];
                    authorizationForm.client.bufSendStr = textBoxInputMessage.Text;
                    authorizationForm.client.eventType = EventTypes.ET_SEND_MESSAGE;
                    authorizationForm.client.ev.Set();
                    //this.ev.WaitOne();
                    uint buf = 0;
                    authorizationForm.chatForm.listBoxConversations.Invoke(new Action(() => buf = authorizationForm.client.selectItemToIdConv[(uint)listBoxConversations.SelectedIndex]));
                    if (!authorizationForm.client.history.ContainsKey(buf))
                    {
                        authorizationForm.client.history.Add(buf, new List<string>());
                    }
                    authorizationForm.client.history[buf].Add(authorizationForm.client.firstName + " " + authorizationForm.client.lastName + ": " + textBoxInputMessage.Text);
                    chatBox.AppendText(authorizationForm.client.firstName + " " + authorizationForm.client.lastName + ": " + textBoxInputMessage.Text + '\r' + '\n');
                    textBoxInputMessage.Clear();
                }
            }
        }

        private void listBoxConversations_SelectedIndexChanged(object sender, EventArgs e)
        {
            chatBox.Clear();
            if (authorizationForm.client.history.ContainsKey(authorizationForm.client.selectItemToIdConv[(uint)listBoxConversations.SelectedIndex]))
            {               
                foreach (string str in authorizationForm.client.history[authorizationForm.client.selectItemToIdConv[(uint)listBoxConversations.SelectedIndex]])
                {
                    chatBox.AppendText(str + '\r' + '\n');
                }
            }
        }
    }
}
