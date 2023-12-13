using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace ClientSeaScrew
{
    public enum MessageTypes : byte
    {
        MT_AUTHORIZATION,
        MT_AUTHORIZATION_FAILED,
        MT_AUTHORIZATION_SUCCESS,
        MT_EXIT,
        MT_GETDATA,
        MT_DATA,
        MT_USERS,
        MT_NODATA,
        MT_CONFIRM,
        MT_UPDATE_USER_LIST,
        MT_MESSAGE,
        MT_MESSAGE_ALL,
        MT_GET_ID_RECIPIENT
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct MessageHeader
    {
        [MarshalAs(UnmanagedType.I8)]
        public ulong to;
        [MarshalAs(UnmanagedType.I8)]
        public ulong from;
        [MarshalAs(UnmanagedType.I8)]
        public ulong type;
        [MarshalAs(UnmanagedType.I8)]
        public ulong size;
    };

    public class Message
    {
        public MessageHeader header;
        public string data;
        static Encoding cp866 = null;

        public Encoding get866()
        {
            if (cp866 is null)
            {
                Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);
                cp866 = Encoding.GetEncoding(1251);
            }
            return cp866;
        }


        public Message(uint to, uint from, MessageTypes type, string data)
        {
            this.data = data;
            header = new MessageHeader() { to = to, from = from, type = (ulong)type, size = (ulong)data.Length };
        }
        public Message()
        {
            this.data = string.Empty;
            this.header = new MessageHeader();
        }

        public byte[] toBytes(object obj)
        {
            int size = Marshal.SizeOf(obj);
            byte[] buff = new byte[size];
            IntPtr ptr = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(obj, ptr, true);
            Marshal.Copy(ptr, buff, 0, size);
            Marshal.FreeHGlobal(ptr);
            return buff;
        }

        public T fromBytes<T>(byte[] buff) where T : struct
        {
            T data = default(T);
            int size = Marshal.SizeOf(data);
            IntPtr i = Marshal.AllocHGlobal(size);
            Marshal.Copy(buff, 0, i, size);
            var d = Marshal.PtrToStructure(i, data.GetType());
            if (d != null)
            {
                data = (T)d;
            }
            Marshal.FreeHGlobal(i);
            return data;
        }

        //void send(Socket s)
        //{
        //    s.Send(toBytes(header), Marshal.SizeOf(header), SocketFlags.None);
        //    if (header.size != 0)
        //    {
        //        s.Send(get866().GetBytes(data), header.size, SocketFlags.None);
        //    }
        //}

        //MessageTypes receive(Socket s)
        //{
        //    byte[] buff = new byte[Marshal.SizeOf(header)];
        //    if (s.Receive(buff, Marshal.SizeOf(header), SocketFlags.None) == 0)
        //    {
        //        return MessageTypes.MT_NODATA;
        //    }
        //    header = fromBytes<MessageHeader>(buff);
        //    if (header.size > 0)
        //    {
        //        byte[] b = new byte[header.size];
        //        s.Receive(b, header.size, SocketFlags.None);
        //        data = get866().GetString(b, 0, header.size);

        //    }
        //    return header.type;
        //}

        //public static void send(Socket s, MessageRecipients to, MessageRecipients from, MessageTypes type = MessageTypes.MT_DATA, string data = "")
        //{
        //    new Message(to, from, type, data).send(s);

        //}
        //public static Message send(MessageRecipients to, MessageTypes type = MessageTypes.MT_DATA, string data = "")
        //{
        //    int nPort = 12345;
        //    IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), nPort);
        //    Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        //    s.Connect(endPoint);
        //    if (!s.Connected)
        //    {
        //        throw new Exception("Connection error");
        //    }
        //    var m = new Message(to, clientID, type, data);
        //    m.send(s);
        //    if (m.receive(s) == MessageTypes.MT_INIT)
        //    {
        //        clientID = m.header.to;
        //    }
        //    return m;
        //}
    }
}
