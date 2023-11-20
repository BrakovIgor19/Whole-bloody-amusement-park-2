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
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ClientSeaScrew
{
    public partial class AuthorizationForm : Form
    {
        private int id;


        private ChatForm chatForm;
        private RegistrationForm registrationForm;

        Socket sockIn;
        Socket sockOut;

        private CancellationTokenSource _cancelationTokenSourceOut;
        private CancellationToken _tokenOut;
        private CancellationTokenSource _cancelationTokenSourceIn;
        private CancellationToken _tokenIn;

        private bool isValid = false;

        public AutoResetEvent closeEvent;
        public AutoResetEvent lastCloseEvent;

        public AuthorizationForm()
        {
            closeEvent = new AutoResetEvent(false);
            lastCloseEvent = new AutoResetEvent(false);
            chatForm = new ChatForm(this);
            registrationForm = new RegistrationForm(this);
            InitializeComponent();
            int nPort = 1000 - 7;
            IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), nPort);

            _cancelationTokenSourceIn = new CancellationTokenSource();
            _tokenIn = _cancelationTokenSourceIn.Token;
            Task.Run(() =>
            {
                sockIn = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                sockIn.Connect(endPoint);
                if (!sockIn.Connected)
                {
                    throw new Exception("Connection error");
                }
                closeEvent.WaitOne();
                _cancelationTokenSourceOut.Cancel();
                closeEvent.WaitOne();
                _cancelationTokenSourceOut.Dispose();
                sockIn.Close();
                lastCloseEvent.Set();
            });

            // Модные таски по советам Марата
            _cancelationTokenSourceOut = new CancellationTokenSource();
            _tokenOut = _cancelationTokenSourceOut.Token;
            Task.Run(() =>
            {
                sockOut = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                sockOut.Connect(endPoint);
                if (!sockIn.Connected)
                {
                    throw new Exception("Connection error");
                }
                while (!_tokenOut.IsCancellationRequested)
                {
                    Message m = ReceiveMessage(sockOut);
                }
                sockOut.Close();
                closeEvent.Set();
            });
        }
        public void SendMessage(Socket s, Message m)
        {
            s.Send(m.toBytes(m.header), Marshal.SizeOf(m.header), SocketFlags.None);
            if (m.header.size != 0)
            {
                s.Send(m.get866().GetBytes(m.data), m.header.size, SocketFlags.None);
            }
        }

        public Message ReceiveMessage(Socket s)
        {
            Message m = new Message();
            byte[] buff = new byte[Marshal.SizeOf(m.header)];
            if (s.Receive(buff, Marshal.SizeOf(m.header), SocketFlags.None) != 0)
            {

                m.header = m.fromBytes<MessageHeader>(buff);
                if (m.header.size > 0)
                {
                    byte[] b = new byte[m.header.size];
                    s.Receive(b, m.header.size, SocketFlags.None);
                    m.data = m.get866().GetString(b, 0, m.header.size);

                }
            }
            else
            {
                throw new Exception("error receive message");
            }
            return m;
        }

        public void CloseAll()
        {
            //Message m = Message(id, 0, MessageTypes.MT_EXIT, "");
            //Send(sockIn, Message(id, 0, MessageTypes.MT_EXIT, ""));
            closeEvent.Set();
            lastCloseEvent.WaitOne();
            Application.Exit();
            /*chatForm.Show();
            chatForm.Close();
            registrationForm.Show();
            registrationForm.Close();
            this.Show();
            this.Close();*/
        }
        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
            chatForm.Show();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            this.Hide();
            registrationForm.Show();
        }

        private void AuthorizationForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            CloseAll();
        }
    }
}
