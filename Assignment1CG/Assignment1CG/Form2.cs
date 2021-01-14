using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Assignment1CG
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "Files|*.jpg;*.jpeg;";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                System.Drawing.Image img = System.Drawing.Image.FromFile(openFileDialog1.FileName);
                FileInfo fi = new FileInfo(openFileDialog1.FileName);
                textBox1.Text += "Image Width: " + img.Width + System.Environment.NewLine + System.Environment.NewLine;
                textBox1.Text += "Image Height: " + img.Height + System.Environment.NewLine+ System.Environment.NewLine;
                textBox1.Text += "Image Size: " + fi.Length + " Bytes" + System.Environment.NewLine + System.Environment.NewLine;
                textBox1.Text += "Image Extension: " + fi.Extension + System.Environment.NewLine + System.Environment.NewLine;

            }
            else
            {
            }
        }
    }
}
