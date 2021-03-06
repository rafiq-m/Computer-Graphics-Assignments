using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TwoImageArithemetic
{
    public partial class Form1 : Form
    {
        Color[,] color1;
        Bitmap picture1;
        Color[,] color2;
        Bitmap picture2;
        public Form1()
        {
            InitializeComponent();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            //Add two Images
            Color[,] color3 = new Color[picture2.Width, picture2.Height];
            float t = 0.0f;
            for (int k = 0; t <= 1.0; k++)
            {
                for (int i = 0; i < picture2.Width; i++)
                {
                    for (int j = 0; j < picture2.Height; j++)
                    {
                        byte r = (byte)(((1-t)*color1[i, j].R + t*color2[i, j].R));
                        byte g = (byte)(((1-t)*color1[i, j].G + t*color2[i, j].G));
                        byte b = (byte)(((1-t)*color1[i, j].B + t*color2[i, j].B));
                        color3[i, j] = Color.FromArgb(r, g, b);
                    }
                }
                t += 0.05f;
                System.Threading.Thread.Sleep(200);
                pictureBox3.Refresh();
                showImage(color3);
            }
        }

        private void Button5_Click(object sender, EventArgs e)
        {
            MessageBox.Show("select your 1st image");
            openFileDialog1.ShowDialog();
            pictureBox1.Image = new Bitmap(openFileDialog1.FileName);


            MessageBox.Show("select your 2nd image");
            openFileDialog1.ShowDialog();
            pictureBox2.Image = new Bitmap(openFileDialog1.FileName);

            button5.Enabled = false;

            //Get image 1 pixels from the image

            picture1 = new Bitmap(pictureBox1.Image);
            picture1 = ResizeImage(picture1, 300, 300);
            color1 = new Color[picture1.Width, picture1.Height];
            picture2 = new Bitmap(pictureBox2.Image);
            picture2 = ResizeImage(picture2, 300, 300);
            color2 = new Color[picture2.Width, picture2.Height];

            for (int i = 0; i < picture1.Width; i++)
            {
                for (int j = 0; j < picture1.Height; j++)
                {
                    color1[i, j] = picture1.GetPixel(i, j);
                }
            }

            //Get image 2 pixels from the image
            
            for (int i = 0; i < picture2.Width; i++)
            {
                for (int j = 0; j < picture2.Height; j++)
                {
                    color2[i, j] = picture2.GetPixel(i, j);
                }
            }

        }

       

        private void Button2_Click(object sender, EventArgs e)
        {
            //Subtract two Images
            Color[,] color3 = new Color[picture2.Width, picture2.Height];
            for (int i = 0; i < picture2.Width; i++)
            {
                for (int j = 0; j < picture2.Height; j++)
                {
                    byte r = (byte)(color1[i, j].R - color2[i, j].R);
                    byte g = (byte)(color1[i, j].G - color2[i, j].G);
                    byte b = (byte)(color1[i, j].B - color2[i, j].B);
                    color3[i, j] = Color.FromArgb(r, g, b);
                }
            }


            showImage(color3);
        }

        private void Button3_Click(object sender, EventArgs e)
        {
            //Multiply two Images
            Color[,] color3 = new Color[picture2.Width, picture2.Height];
            for (int i = 0; i < picture2.Width; i++)
            {
                for (int j = 0; j < picture2.Height; j++)
                {
                    byte r = (byte)(color1[i, j].R * color2[i, j].R);
                    byte g = (byte)(color1[i, j].G * color2[i, j].G);
                    byte b = (byte)(color1[i, j].B * color2[i, j].B);
                    color3[i, j] = Color.FromArgb(r, g, b);
                }
            }


            showImage(color3);
            
        }





        private void showImage(Color[,] color)
        {
            Bitmap new_image = new Bitmap(picture2.Width, picture2.Height);
            for (int i = 0; i < picture2.Width; i++)
            {
                for (int j = 0; j < picture2.Height; j++)
                {
                    new_image.SetPixel(i, j, color[i, j]);
                }
            }
            pictureBox3.Image = new_image;
        }
        private Bitmap ResizeImage(Image image, int width, int height)
        {
            var destRect = new Rectangle(0, 0, width, height);
            var destImage = new Bitmap(width, height);

            destImage.SetResolution(image.HorizontalResolution, image.VerticalResolution);

            using (var graphics = Graphics.FromImage(destImage))
            {
                graphics.CompositingMode = CompositingMode.SourceCopy;
                graphics.CompositingQuality = CompositingQuality.HighQuality;
                graphics.InterpolationMode = InterpolationMode.HighQualityBicubic;
                graphics.SmoothingMode = SmoothingMode.HighQuality;
                graphics.PixelOffsetMode = PixelOffsetMode.HighQuality;

                using (var wrapMode = new ImageAttributes())
                {
                    wrapMode.SetWrapMode(WrapMode.TileFlipXY);
                    graphics.DrawImage(image, destRect, 0, 0, image.Width, image.Height, GraphicsUnit.Pixel, wrapMode);
                }
            }

            return destImage;
        }

        private void Button4_Click(object sender, EventArgs e)
        {
            //Divide Two Images
            Color[,] color3 = new Color[picture2.Width, picture2.Height];
            for (int i = 0; i < picture2.Width; i++)
            {
                for (int j = 0; j < picture2.Height; j++)
                {
                    if (color2[i, j].R != 0 && color2[i, j].G != 0 && color2[i, j].B != 0)
                    {
                        byte r = (byte)(color1[i, j].R / color2[i, j].R);
                        byte g = (byte)(color1[i, j].G / color2[i, j].G);
                        byte b = (byte)(color1[i, j].B / color2[i, j].B);
                        color3[i, j] = Color.FromArgb(r, g, b);
                    }
                    else
                    {
                        color3[i, j] = Color.FromArgb(255, 255, 255);
                    }
                }
            }


            showImage(color3);
        }
    }
}
