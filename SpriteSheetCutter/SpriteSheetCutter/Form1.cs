using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SpriteSheetCutter
{
    public partial class Form1 : Form
    {
        Bitmap spriteSheet;
        Bitmap[] chunk;
        int image_count = 0;
        int object_width, object_height, no_of_objects, no_of_rows;
        int pict_rect_width;
        int pict_rect_height;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            spriteSheet = new Bitmap(openFileDialog1.FileName);
            pictureBox1.Image = spriteSheet;
            button1.Visible = false;
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            object_width = spriteSheet.Width / Convert.ToInt32(textBox1.Text);
            object_height = spriteSheet.Height / Convert.ToInt32(textBox2.Text);         
            no_of_objects = Convert.ToInt32(textBox1.Text);
            no_of_rows = Convert.ToInt32(textBox2.Text);
            pict_rect_width = pictureBox1.Width / no_of_objects;
            pict_rect_height = pictureBox1.Height / no_of_rows;
            chunk = new Bitmap[no_of_objects * no_of_rows];
            Color[,] colors = new Color[object_width , object_height];
            int width_count = 0;
            int height_count = 0;
            for (int l = 0; l < Convert.ToInt32(textBox2.Text); l++)
            {
                for (int k = 0; k < Convert.ToInt32(textBox1.Text); k++)
                {
                    //get pixel in colors
                    for (int i = width_count; i < width_count + object_width; i++)
                    {
                        for (int j = height_count; j < object_height + height_count; j++)
                        {
                            colors[i - width_count, (j - height_count)] = spriteSheet.GetPixel(i, j);
                        }
                    }
                    width_count += object_width;
                    Bitmap temp_pic = new Bitmap(object_width, object_height, PixelFormat.Format24bppRgb);
                    for (int i = 0; i < object_width; i++)
                    {
                        for (int j = 0; j < object_height; j++)
                        {
                            temp_pic.SetPixel(i, j, colors[i, j]);
                        }
                    }
                    chunk[image_count] = temp_pic;
                    image_count++;
                }
                height_count += object_height;
                width_count = 0;        //this thing wasted my 2 hours :) NOICE!!!
            }

            
            for (int i = 0; i < spriteSheet.Width; i += object_width)
            {
                for (int j = 0; j < spriteSheet.Height; j++)
                {
                    spriteSheet.SetPixel(i, j, Color.Black);
                }
            }
            for (int i = 0; i < spriteSheet.Height; i += object_height)
            {
                for (int j = 0; j < spriteSheet.Width; j++)
                {
                    spriteSheet.SetPixel(j, i, Color.Black);
                }
            }
            pictureBox1.Refresh();

            //for (int i = 0; i < chunk.Length; i++)
            //{
            //    chunk[i].Save(@"hello" + i + ".bmp", ImageFormat.Bmp);
            //}
        }

        private void TextBox1_TextChanged(object sender, EventArgs e)
        {
           
        }

        private void TextBox2_TextChanged(object sender, EventArgs e)
        {
            button2.Enabled = true;
        }


        private void Button3_Click(object sender, EventArgs e)
        {
            int count = 0;
            int x =0 , y =0;
            drawRect(x, y);
            for (int i = 0; i < chunk.Length; i++)
            {
                if (count  < no_of_objects)
                {
                    count++;
                    x += pict_rect_width;
                }
                else
                {
                    count = 0;
                    y += pict_rect_height;
                    x = 0;
                }
                pictureBox2.Image = chunk[i];
                drawRect(x, y);
                pictureBox2.Refresh();
            }

        }

        private void drawRect(int x, int y)
        {
            Pen p = new Pen(Color.Red, 3);
            Rectangle rec = new Rectangle(x, y, pict_rect_width, pict_rect_height);
            pictureBox1.CreateGraphics().DrawRectangle(p, rec);
            System.Threading.Thread.Sleep(100);
            pictureBox1.Refresh();
        }
    }
}
