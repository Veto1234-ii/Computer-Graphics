using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.ComponentModel;

namespace myfirst_projekt
{
    abstract class Filters
    {
        //уникальная для каждого из фильтров, вычисляет значение пикселя
        protected abstract Color calculateNewPixelColor(Bitmap sourceImage, int x, int y);


        //ф-я приводит значение пикселя к допустимому диапазону
        public int Clamp(int value, int min, int max)
        {
            if (value < min)
                return min;
            if (value > max)
                return max;

            return value;
        }

        
        public Bitmap processImage(Bitmap sourceImage, BackgroundWorker worker)
        {
            // общая для всех фильтров часть
            Bitmap resultImage = new Bitmap(sourceImage.Width, sourceImage.Height);

            for (int i = 0; i < sourceImage.Width; i++)
            {
                worker.ReportProgress((int)((float)i / resultImage.Width * 100));
                if (worker.CancellationPending)
                    return null;

                for (int j = 0; j < sourceImage.Height; j++)
                {
                    resultImage.SetPixel(i, j, calculateNewPixelColor(sourceImage, i, j));
                }
            }

                
            return resultImage;
        }
    }

    class InvertFilter: Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            // получили цвет исходного пикселя
            Color sourceColor = sourceImage.GetPixel(x, y);
            
            //вычислили инверсию этого цвета
            Color resultColor = Color.FromArgb(255 - sourceColor.R,
                                                255 - sourceColor.G,
                                                255 - sourceColor.B);

            return resultColor;
        }
    }

    class GrayScaleFilter: Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color sourceColor = sourceImage.GetPixel(x, y);

            Color resultColor = Color.FromArgb((int) (0.36 * sourceColor.R + 0.53* sourceColor.G + 0.11*sourceColor.B),
                                               (int)(0.36 * sourceColor.R + 0.53 * sourceColor.G + 0.11 * sourceColor.B),
                                               (int)(0.36 * sourceColor.R + 0.53 * sourceColor.G + 0.11 * sourceColor.B));
            
            return resultColor;
        }

        }

    class MatrixFilter: Filters
    {
        protected float[,] kernel = null;
        protected MatrixFilter() { }

        public MatrixFilter(float[,] kernel)
        {
            this.kernel = kernel;
        }

        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            //радиусы фильтра
            int radiusX = kernel.GetLength(0) / 2;
            int radiusY = kernel.GetLength(1) / 2;

            // цветовые компоненты результирующего цвета
            float resultR = 0;
            float resultG = 0;
            float resultB = 0;

            // перебираем окрестность цикла
            // предполагается что ядро фильтра, поступающее на вход, явл нормированным
            for(int l = -radiusY; l<= radiusY; l++)
                for(int k = -radiusX; k<= radiusX; k++)
                {
                    // l, k - положение элемента в матрице фильтра(ядре)
                    int idX = Clamp(x + k, 0, sourceImage.Width - 1);
                    int idY = Clamp(y + l, 0, sourceImage.Height - 1);

                    Color neighborColor = sourceImage.GetPixel(idX, idY);

                    resultR += neighborColor.R * kernel[k + radiusX, l + radiusY];
                    resultG += neighborColor.G * kernel[k + radiusX, l + radiusY];
                    resultB += neighborColor.B * kernel[k + radiusX, l + radiusY];

                }
            return Color.FromArgb(
                Clamp((int)resultR, 0, 255),
                Clamp((int)resultG, 0, 255),
                Clamp((int)resultB, 0, 255)
                );
        }

        

    }

    class BlurFilter : MatrixFilter
    {
        public BlurFilter()
        {
            int sizeX = 3;
            int sizeY = 3;

            kernel = new float[sizeX, sizeY];

            for (int i = 0; i < sizeX; i++)
                for (int j = 0; j < sizeY; j++)
                    kernel[i, j] = 1.0f / (float)(sizeX * sizeY);
        }
    }

    class GaussianFilter: MatrixFilter
    {
        public void createGaussianKernel(int radius, float sigma)
        {
            //определяем размер ядра
            int size = 2 * radius + 1;
            //создаем ядро фильтра
            kernel = new float[size, size];
            //коэффициент нормировки ядра
            float norm = 0;
            //расчитываем ядро линейного фильтра

            for(int i = -radius; i<=radius; i++)
                for(int j = -radius; j<=radius; j++)
                {
                    kernel[i + radius, j + radius] = (float)(Math.Exp(-(i * i + j * j) / (sigma * sigma)));
                    norm += kernel[i + radius, j + radius];
                }

            //нормируем ядро
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    kernel[i, j] /= norm;
        }

        public GaussianFilter()
        {
            createGaussianKernel(3, 2);
        }
    }

    class linear_stretch : Filters
    {
        public int get_maxBrightness(Bitmap sourceImage)
        {
            Color sourceColor = sourceImage.GetPixel((int)sourceImage.Width / 2, (int)sourceImage.Height / 2);
            int mx = sourceColor.ToArgb();

            for (int i = 0; i < sourceImage.Width; i++)
                for (int j = 0; j < sourceImage.Height; j++)
                {
                    int t = sourceImage.GetPixel(i, j).ToArgb();

                    if (t >= mx) mx = t;
                    
                    
                }

            return mx;
        }

        public int get_minBrightness(Bitmap sourceImage)
        {
            Color sourceColor = sourceImage.GetPixel((int)sourceImage.Width / 2, (int)sourceImage.Height / 2);
            int mn = sourceColor.ToArgb();

            for (int i = 0; i < sourceImage.Width; i++)
                for (int j = 0; j < sourceImage.Height; j++)
                {
                    int t = sourceImage.GetPixel(i, j).ToArgb();

                    if (t <= mn) mn = t;


                }

            return mn;
        }


    }


}
