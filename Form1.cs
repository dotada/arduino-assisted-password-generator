using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Drawing.Text;
using System.Diagnostics;

namespace arduinopasswordmanager
{
    public partial class Form1 : Form
    {
        public Random rng = new Random();
        delegate void SetTextCallback(string text);
        public string txt = "";
        public char[] alphacap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ".ToCharArray();
        public char[] alpha = "abcdefghijklmnopqrstuvwxyz".ToCharArray();
        public char[] specsymb = "*!@#$%^&".ToCharArray();
        public char[] numbers = "1234567890".ToCharArray();
        public char[] touse;
        public StringBuilder sb = new StringBuilder();
        public string passwd;
        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            // Show all the incoming data in the port's buffer
            txt = serport.ReadExisting();
            //Console.WriteLine(serport.ReadExisting());
            Console.WriteLine(txt);
            //SetText(txt);
            txt.Replace("\n", "");
            checkBox1.Invoke((Action)delegate
            {
                checkBox1.Checked = true;
            });
            button1.Invoke((Action)delegate
            {
                button1.Enabled = false;
            });
        }
        private SerialPort serport = new SerialPort("COM3", 74880, Parity.None, 8, StopBits.One);
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serport.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);
            serport.Open();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            int.TryParse(txt, out int seed);
            rng = new Random(seed);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            passwd = "";
            textBox2.Text = "Password length: " + trackBar1.Value.ToString();
            sb.Clear();
            if (checkBox1.Checked)
            {
                sb.Append(alpha);
                if (checkBox3.Checked)
                {
                    sb.Append(specsymb);
                }
                if (checkBox4.Checked)
                {
                    sb.Append(alphacap);
                }
                if (checkBox2.Checked)
                {
                    sb.Append(numbers);
                }
                for (int i=0; i < trackBar1.Value; i++)
                {
                    string sbstr = sb.ToString();
                    char rndpick = sbstr[rng.Next(maxValue: sb.Length)];
                    passwd += rndpick;
                }
                textBox1.Text = passwd;
            }
        }
    }
}
