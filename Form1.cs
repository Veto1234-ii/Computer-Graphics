using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace myfirst_projekt
{
    public partial class Form1 : Form
    {
        Bitmap image;
        public Form1()
        {
            InitializeComponent();
        }

        private void открытьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //создаем диалог для открытия файла
            OpenFileDialog dialog = new OpenFileDialog();
            
            //фильтр для открытия только изображений
            dialog.Filter = "Image files | *.png; *.jpg; *.bmp | All Files (*.*) | *.*";

            // проверка выбрал ли пользователь файл
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                //инициализация переменной image выбранным изображением
                image = new Bitmap(dialog.FileName);

                //визализация на форме 
                pictureBox1.Image = image;

                //обновление pictureBox
                pictureBox1.Refresh();
            }
        }

        private void инверсияToolStripMenuItem_Click(object sender, EventArgs e)
        {
            /*
            //создаем объект класса InvertFilter
            InvertFilter filter = new InvertFilter();

            //создаем новый экземпляр класса Bitmap, присваиваем ему результат ф-ии processImage
            Bitmap resultImage = filter.processImage(image);

            pictureBox1.Image = resultImage;
            pictureBox1.Refresh();
            */

            Filters filter = new InvertFilter();
            backgroundWorker1.RunWorkerAsync(filter);
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            Bitmap newImage = ((Filters)e.Argument).processImage(image, backgroundWorker1);
            if (backgroundWorker1.CancellationPending != true)
                image = newImage;
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            progressBar1.Value = e.ProgressPercentage;
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (!e.Cancelled)
            {
                pictureBox1.Image = image;
                pictureBox1.Refresh();
            }

            progressBar1.Value = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            backgroundWorker1.CancelAsync();
        }

        private void размытиеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Filters filter = new BlurFilter();

            backgroundWorker1.RunWorkerAsync(filter);


        }

        private void гауссаToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Filters filter = new GaussianFilter();

            backgroundWorker1.RunWorkerAsync(filter);
        }

        private void черноБелоеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Filters filter = new GrayScaleFilter();

            backgroundWorker1.RunWorkerAsync(filter);
        }
    }
}
