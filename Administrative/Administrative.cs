using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using System.IO;
using System.Xml.Linq;

namespace Csharp
{
    public partial class Administrative : Form
    {
        [DllImport("user32.dll")]
        private static extern IntPtr FindWindow(string windowClass, string windowName);

        [DllImport("user32.dll")]
        private static extern bool SetWindowText(IntPtr hWnd, string text);

        [DllImport("TranspFuncs.dll", CharSet = CharSet.Ansi)]
        private static extern void PlayProcess(string name, string title);

        string[] legendHuman = { "1000-7",
                            "Артём",
                            "Гор Саныч",
                            "XapTMaH19",
                            "Скорпион",
                            "Cуб-Зэра",
                            "Смоук",
                            "Рейден",
                            "Джонни Кейдж",
                            "Соня",
                            "Фуджин",
                            "Китана",
                            "Шао Кан",
                            "Лю Кан",
                            "Шанг Цунг",
                            "Камарова",
                            "Ир Михална",
                            "Жанна Дарковна",
                            "Евгения Михайловна",
                            "Лера Ларченко",
                            "Академик Сеченов",
                            "Джим Рон",
                            "Антон Чигур",
                            "Тайвин Ланнистер",
                            "Санса Старк",
                            "Джон Сноу",
                            "Джон Генри Эдем",
                            "Никита Капустин",
                            "Маратик",
                            "Mister X"
                            };

        public Administrative()
        {
            InitializeComponent();
            comboBoxClients.Items.AddRange(legendHuman);
        }

        private bool conditionServer = false;
       

        private Process server = null;

        //private Dictionary<string, Process> Clients = new Dictionary<string, Process>();

        private void buttonOnServer_Click(object sender, EventArgs e)
        {
            if (server == null || server.HasExited)
            {
                server = Process.Start("Server.exe");
                conditionServer = true;
            }
        }

        private void buttonCreateClient_Click(object sender, EventArgs e)
        {
            if (conditionServer)
            {
                //if (!Clients.ContainsKey(textBox1.Text))
                //{
                    //comboBoxClients.Items.Add(textBox1.Text);
                    PlayProcess("ClientCrosses.exe", textBox1.Text);
                    //Clients.Add(textBox1.Text, Process.Start("ClientCrosses"));
                    //Thread.Sleep(2000);
                    //SetWindowText(Clients[textBox1.Text].MainWindowHandle, textBox1.Text);
                    Random rnd = new Random();

                    //this.textBox1.Text = legendHuman[rnd.Next(legendHuman.Length)];
                //}
            }
        }


        private void buttonCreateClientSeaScrew_Click(object sender, EventArgs e)
        {
            if (conditionServer)
            {
                Process p = Process.Start("ClientSeaScrew.exe");
                //Thread.Sleep(3000);
                //SetWindowText(p.MainWindowHandle, textBox1.Text);

            }
        }

        private void UpdateTextBox(object sender, EventArgs e)
        {

        }

        private void buttonCreateClientSatan_Click(object sender, EventArgs e)
        {
            if (conditionServer)
            {
                Process p = Process.Start("ClientGo.exe");

            }
        }
    }
}
