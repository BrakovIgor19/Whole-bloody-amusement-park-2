using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Security.Permissions;
using System.Windows.Forms;
using System.Diagnostics.Eventing.Reader;
using System.Numerics;

namespace ClientSeaScrew
{
    public enum EventTypes : byte
    {
        ET_AUTHORIZATION,
        ET_FAILED_AUTHORIZATION,
        ET_SEND_MESSAGE,
        ET_EXIT
    };
    public class Client
    {
        public uint id;
        public string firstName;
        public string lastName;
        public string nameAvatar;

        public Dictionary<uint, string> cacheConversations = new Dictionary<uint, string>();
        public Dictionary<uint, uint> selectItemToIdConv = new Dictionary<uint, uint>();
        public Dictionary<uint, List<string>> history = new Dictionary<uint, List<string>>();

        private Socket sockIn;
        private Socket sockOut;

        private CancellationTokenSource _cancelationTokenSourceOut;
        private CancellationToken _tokenOut;
        private Task tOut;
        private CancellationTokenSource _cancelationTokenSourceIn;
        private CancellationToken _tokenIn;
        private Task tIn;

        public AutoResetEvent ev;
        public AutoResetEvent evStart;
        public bool isValid = false;

        public EventTypes eventType;
        public uint bufSendId;
        public string bufSendStr;

        //public string codeError;

        private AuthorizationForm authorizationForm;

        public Client(AuthorizationForm authorizationForm, ChatForm chatForm, RegistrationForm registrationForm)
        {
            this.authorizationForm = authorizationForm;

            isValid = false;
            ev = new AutoResetEvent(false);
            evStart = new AutoResetEvent(false);

            history = new Dictionary<uint, List<string>>();

            int nPort = 1000 - 7;
            IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), nPort);

            // Модные таски по советам Марата
            _cancelationTokenSourceOut = new CancellationTokenSource();
            _tokenOut = _cancelationTokenSourceOut.Token;
            tOut = Task.Run(() =>
            {
            sockOut = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            sockOut.Connect(endPoint);
            if (!sockOut.Connected)
            {
                throw new Exception("Connection error");
            }
            else
            {
                evStart.Set();
            }
            while (!_tokenOut.IsCancellationRequested)
            {
                ev.WaitOne();
                switch (eventType)
                {
                    case EventTypes.ET_AUTHORIZATION:
                    {
                        string bufStr = authorizationForm.textBoxMail.Text + ";" + authorizationForm.textBoxPassword.Text;
                        SendMessage(sockOut, new Message(0, 0, MessageTypes.MT_AUTHORIZATION, bufStr));
                        Message m = ReceiveMessage(sockOut);
                        if ((MessageTypes)m.header.type == MessageTypes.MT_AUTHORIZATION_SUCCESS)
                        {
                            isValid = true;
                            string[] bufArrStr = m.data.Split(';');
                            id = uint.Parse(bufArrStr[0]);
                            firstName = bufArrStr[1];
                            lastName = bufArrStr[2];
                            nameAvatar = bufArrStr[3];
                        }
                        else
                        {
                            eventType = EventTypes.ET_FAILED_AUTHORIZATION;
                            ev.Set();
                        }
                        break;

                    }
                    case EventTypes.ET_SEND_MESSAGE:
                    {                       
                        SendMessage(sockOut, new Message(bufSendId, id, MessageTypes.MT_MESSAGE,bufSendStr));
                        Message m = ReceiveMessage(sockOut);
                        authorizationForm.chatForm.ev.Set();
                        break;
                    }
                    case EventTypes.ET_FAILED_AUTHORIZATION:
                    {
                        _cancelationTokenSourceOut.Cancel();
                        ev.Set();
                        _cancelationTokenSourceIn.Cancel();
                        tIn.Wait();
                        _cancelationTokenSourceOut.Dispose();
                        _cancelationTokenSourceIn.Dispose();
                        sockOut.Close();
                        sockIn.Close();
                        evStart.Dispose();
                        ev.Dispose();
                        break;
                    }
                    case EventTypes.ET_EXIT:
                    {
                        SendMessage(sockOut, new Message(0, 0, MessageTypes.MT_EXIT, ""));
                        Message m = ReceiveMessage(sockOut);
                        break;
                    }
                    }
                    authorizationForm.ev.Set();                   
                }
                authorizationForm.ev.Reset();
            });

            // Модные таски по советам Марата
            _cancelationTokenSourceIn = new CancellationTokenSource();
            _tokenIn = _cancelationTokenSourceIn.Token;
            tIn = Task.Run(() =>
            {
                evStart.WaitOne();
                sockIn = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                sockIn.Connect(endPoint);
                if (!sockIn.Connected)
                {
                    throw new Exception("Connection error");
                }
                while (!_tokenIn.IsCancellationRequested)
                {
                    Message m = ReceiveMessage(sockIn);
                    MessageTypes mt = (MessageTypes)m.header.type;
                    switch (mt)
                    {
                        case MessageTypes.MT_UPDATE_USER_LIST:
                        {
                            UpdateCacheConversations(m.data);
                            authorizationForm.chatForm.ev.Set();
                            break;
                        }
                        case MessageTypes.MT_MESSAGE:
                        {
                            if (!history.ContainsKey((uint)m.header.to))
                            {
                                history.Add((uint)m.header.to, new List<string>());    
                            }
                            history[(uint)m.header.to].Add(m.data);
                            authorizationForm.chatForm.bufIdConv = (int)m.header.to;
                            authorizationForm.chatForm.ev.Set();
                            break;
                        }
                        case MessageTypes.MT_EXIT: //MessageTypes.MT_EXIT
                        {
                            _cancelationTokenSourceIn.Cancel();
                            break;
                        }
                    }
                }
            });
            

        }
        public void SendMessage(Socket s, Message m)
        {
            s.Send(m.toBytes(m.header), Marshal.SizeOf(m.header), SocketFlags.None);
            if (m.header.size != 0)
            {
                s.Send(m.get866().GetBytes(m.data), (int)m.header.size, SocketFlags.None);
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
                    s.Receive(b, (int)m.header.size, SocketFlags.None);
                    m.data = m.get866().GetString(b, 0, (int)m.header.size);
                }
            }
            else
            {
                throw new Exception("error receive message");
            }
            return m;
        }
        public void Close()
        {
            isValid = false;
            /*SendMessage(sockOut, new Message(0, 0, MessageTypes.MT_EXIT, ""));
            Message m = ReceiveMessage(sockOut);*/
            _cancelationTokenSourceOut.Cancel();
            eventType = EventTypes.ET_EXIT;
            ev.Set();
            
            //sockIn.Shutdown(SocketShutdown.Both);
            //sockIn.Disconnect(true);
            _cancelationTokenSourceIn.Cancel();
            tOut.Wait();
            tIn.Wait();

            authorizationForm.chatForm.isValid = false;
            authorizationForm.chatForm._cancelationTokenSourceUp.Cancel();
            authorizationForm.chatForm.ev.Set();
            authorizationForm.chatForm.tUpdate.Wait();
            _cancelationTokenSourceOut.Dispose();
            _cancelationTokenSourceIn.Dispose();
            authorizationForm.chatForm._cancelationTokenSourceUp.Dispose();
            sockOut.Close();
            sockIn.Close();
            evStart.Dispose();
            ev.Dispose();
            authorizationForm.chatForm.ev.Dispose();

            //Thread.Sleep(2000);
        }
        void UpdateCacheConversations(string upStr)
        {
            string[] stringsBuf = upStr.Split(';');
            Dictionary<uint, string> bufDict = new Dictionary<uint, string>();
            Dictionary<uint, uint> bufDict2 = new Dictionary<uint, uint>();
            
            for (int i = 0, j = 0; i < stringsBuf.Length - 1; i += 2, j++)
            {
                bufDict.Add(uint.Parse(stringsBuf[i]), stringsBuf[i + 1]);
                bufDict2.Add((uint)j, uint.Parse(stringsBuf[i]));
            }

            cacheConversations = bufDict;
            selectItemToIdConv = bufDict2;
        }
    }
}
