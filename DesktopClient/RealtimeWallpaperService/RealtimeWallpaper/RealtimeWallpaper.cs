using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Net.Sockets;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;

namespace RealtimeWallpaper
{
    public class RealtimeWallpaper
    {
        private static readonly String HOST = "192.168.0.100";
        private static readonly int PORT = 9123;
        private static readonly byte FLAG = 2;
        private static readonly byte SUCCESS = 0;
        private static readonly byte FAILURE = 1;

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern Int32 SystemParametersInfo(UInt32 uiAction, UInt32 uiParam, String pvParam, UInt32 fWinIni);
        private static UInt32 SPI_SETDESKWALLPAPER = 20;
        private static UInt32 SPIF_UPDATEINIFILE = 0x01;
        private static UInt32 SPIF_SENDWININICHANGE = 0x02;

        private Thread thread = null;
        private bool run = false;

        public static void Main(String[] args)
        {
            /*
            Image pngImage = Image.FromFile("R:\\latest.png");
            String tempFile = "R:\\latest.bmp";
            pngImage.Save(tempFile, ImageFormat.Bmp);
            int result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, tempFile, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);

            StreamWriter sw = new StreamWriter("R:\\zxcv.txt");
            sw.WriteLine(result);
            sw.Close();*/

            RealtimeWallpaper rw = new RealtimeWallpaper();
        }

        public RealtimeWallpaper()
        {
            thread = new Thread(new ThreadStart(Run));
            thread.Start();
            run = false;
            if (thread != null) thread.Join();
        }
    }
}