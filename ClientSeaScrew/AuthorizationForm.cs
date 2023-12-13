using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ClientSeaScrew
{
    public partial class AuthorizationForm : Form
    {
        public ChatForm chatForm;
        public RegistrationForm registrationForm;
        public ProfileForm profileForm;
        public Client client;
        public AutoResetEvent ev;

        public Regex rgxMail = new Regex(@"^[-\w.]+@([A-Za-z0-9][-A-Za-z0-9]+\.)+[A-Za-z]{2,4}$"); // само регулярное выражение

        public AuthorizationForm()
        {
            ev = new AutoResetEvent(false);
            chatForm = new ChatForm(this);
            registrationForm = new RegistrationForm(this);
            profileForm = new ProfileForm(this);
            InitializeComponent();
            InitializeControls();
            
        }

        public void ExitToAthorization()
        {
            if (client != null && client.isValid) {
            
                Task t = Task.Run(() =>
                {
                    client.Close();
                });
                t.Wait();
            }
        }
        private void InitializeControls()
        {
            // Set to no text.
            textBoxPassword.Text = "";
            // The password character is an asterisk.
            textBoxPassword.PasswordChar = '*';
            // The control will allow no more than 32 characters.
            textBoxPassword.MaxLength = 32;

            textBoxMail.Text = "";
            textBoxMail.MaxLength = 64;
        }
        public void CloseAll()
        {
            //Message m = Message(id, 0, MessageTypes.MT_EXIT, "");
            //Send(sockIn, Message(id, 0, MessageTypes.MT_EXIT, ""));
            if (client != null)
            {
                //CancellationTokenSource bufTok = new CancellationTokenSource();
                //CancellationToken canBuf = bufTok.Token;
                ExitToAthorization();
                Application.Exit();
                
            }
            /*chatForm.Show();
            chatForm.Close();
            registrationForm.Show();
            registrationForm.Close();
            this.Show();
            this.Close();*/
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            this.Hide();
            registrationForm.Show();
        }

        private void AuthorizationForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            // CloseAll();
            //registrationForm.Close();
            // chatForm.Close();
            //Close();
            //this.Cancel
            //Environment.Exit(0);
            if (client != null && client.isValid)
            {
                CloseAll();
            }
        }

        private void buttonEnter_Click(object sender, EventArgs e)
        {
            //client = new Client(this, chatForm, registrationForm);
            if (rgxMail.IsMatch(textBoxMail.Text))
            {
                if (textBoxPassword.Text != string.Empty)
                { 
                    client = new Client(this, chatForm, registrationForm);
                    client.eventType = EventTypes.ET_AUTHORIZATION;
                    client.ev.Set();
                    ev.WaitOne();
                    if (client.isValid)
                    {
                        textBoxMail.Text = string.Empty;
                        textBoxPassword.Text = string.Empty;
                        labelErrorAuthorization.Text = string.Empty;
                        profileForm.labelLastname.Text = client.lastName;
                        profileForm.labelFirstName.Text = client.firstName;
                        profileForm.pictureBoxAvatar.Image = Image.FromFile("../../../Resource/Avatars/" + client.nameAvatar);
                        this.Hide();
                        client.isValid = false;
                        chatForm.Show();
                        ev.WaitOne();
                        client.isValid = true;
                        //chatForm.PlayUpdate();
                    }
                    else
                    {
                        labelErrorAuthorization.Text = "Неверная почта или пароль!";
                    }
                }
                else
                {
                    labelErrorAuthorization.Text = "Введите пароль!";
                }
            }
            else
            {
                labelErrorAuthorization.Text = "Неверный формат почты!";
            }
        }

    }
}
