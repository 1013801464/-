using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharpWindowsForms {
    public partial class Form1 : Form {
        private bool lastFlipHorizontal = false;
        private bool lastFlipVertical = false;
        private bool flipHorizontal;
        private bool flipVertical;
        MouseHook mouse = new MouseHook();
        private PictureBox[,] pictureBox = new PictureBox[2, 2];
        private Point p = new Point(0, 0);
        private DateTime lastTime = DateTime.Now;
        private TimeSpan span = new TimeSpan(0, 0, 0, 0, 20);

        public Form1() {
            InitializeComponent();
            pictureBox[0, 0] = pictureBox1;
            pictureBox[0, 1] = pictureBox2;
            pictureBox[1, 0] = pictureBox3;
            pictureBox[1, 1] = pictureBox4;
            Bitmap image = Properties.Resources.arrow_l;
            MaximumSize = image.Size;
            pictureBox[0, 0].Size = image.Size;
            pictureBox[0, 1].Size = image.Size;
            pictureBox[1, 0].Size = image.Size;
            pictureBox[1, 1].Size = image.Size;
            pictureBox[0, 1].Image = Reverse(image, false, true);
            pictureBox[1, 0].Image = Reverse(image, true, false);
            pictureBox[1, 1].Image = Reverse(image, true, true);
            pictureBox[0, 1].Visible = false;
            pictureBox[1, 0].Visible = false;
            pictureBox[1, 1].Visible = false;
            pictureBox[1, 1].Visible = false;

            mouse.OnMouseActivity += mouse_OnMouseActivity;
            mouse.Start();
        }

        private Bitmap Reverse(Bitmap bitmap, bool horizontal, bool vertical) {
            if (!horizontal && !vertical) return bitmap;
            int width = bitmap.Width;
            int height = bitmap.Height;
            Bitmap bm = new Bitmap(width, height);//初始化一个记录经过处理后的图片对象
            int x, y, z;//x,y是循环次数,z是用来记录像素点的x坐标的变化的
            Color pixel;

            if (horizontal && !vertical) {
                for (y = height - 1; y >= 0; y--) {
                    for (x = width - 1, z = 0; x >= 0; x--) {
                        pixel = bitmap.GetPixel(x, y);//获取当前像素的值
                        bm.SetPixel(z++, y, Color.FromArgb(pixel.A, pixel.R, pixel.G, pixel.B));//绘图
                    }
                }
            } else if (!horizontal && vertical) {
                for (x = 0; x < width; x++) {
                    for (y = height - 1, z = 0; y >= 0; y--) {
                        pixel = bitmap.GetPixel(x, y);//获取当前像素的值
                        bm.SetPixel(x, z++, Color.FromArgb(pixel.A, pixel.R, pixel.G, pixel.B));//绘图
                    }
                }
            } else {
                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                        pixel = bitmap.GetPixel(x, y);//获取当前像素的值
                        bm.SetPixel(width - 1 - x, height - 1 - y, Color.FromArgb(pixel.A, pixel.R, pixel.G, pixel.B));//绘图
                    }
                }

            }
            return bm;
        }

        private void mouse_OnMouseActivity(object sender, MouseEventArgs e) {
            DateTime now = DateTime.Now;
            // Console.WriteLine(lastTime);
            if (now - lastTime < span) return;
            lastTime = now;
            flipHorizontal = false;
            flipVertical = false;
            BringToFront();

            int screenWidth = Screen.PrimaryScreen.Bounds.Width;
            int screenHeight = Screen.PrimaryScreen.Bounds.Height;
            if (e.Location.Y + Size.Height > screenHeight) {
                flipVertical = true;
                if (e.Location.X > Size.Width) {
                    flipHorizontal = true;
                }
            } else {
                if (e.Location.X + Size.Width > screenWidth) {
                    flipHorizontal = true;
                }
            }
            if (flipHorizontal != lastFlipHorizontal || flipVertical != lastFlipVertical) {
                flipCursorImage();
                lastFlipHorizontal = flipHorizontal;
                lastFlipVertical = flipVertical;
            }
            if (flipHorizontal) {
                p.X = e.Location.X - Size.Width;
            } else {
                p.X = e.Location.X + 1;
            }
            if (flipVertical) {
                p.Y = e.Location.Y - Size.Height;
            } else {
                p.Y = e.Location.Y + 1;
            }
            Location = p;
        }

        private void flipCursorImage() {
            Console.WriteLine(Size);
            // Size = size;
            pictureBox[0, 1].Visible = false;
            pictureBox[1, 0].Visible = false;
            pictureBox[1, 1].Visible = false;
            pictureBox[1, 1].Visible = false;
            pictureBox[flipHorizontal ? 1 : 0, flipVertical ? 1 : 0].Visible = true;
        }
    }
}
