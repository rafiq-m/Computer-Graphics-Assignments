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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            double[] size = new double[4];
            string[] names = new string[4];
            int i = 0;
            string root = @"E:\practice";
            string[] subdirectoryEntries = Directory.GetDirectories(root);
            foreach (var folder in subdirectoryEntries)
            {           
                DirectoryInfo info = new DirectoryInfo(folder);
                FileInfo[] dirFiles = info.GetFiles();
                foreach (FileInfo file in dirFiles)
                {
                    size[i] += file.Length;
                }
                size[i] = size[i] / 1000000;
                names[i] = folder.ToString().Substring(12, folder.Length - 12);
                i += 1;
            }

            for (int j = 0; j < size.Length; j++)
            {
                this.chart1.Series["Str Comp"].Points.AddXY(names[j], size[j]);
            }


        }

        private void Button2_Click(object sender, EventArgs e)
        {
            Form2 form = new Form2();
            form.Show();
        }
    }
}
