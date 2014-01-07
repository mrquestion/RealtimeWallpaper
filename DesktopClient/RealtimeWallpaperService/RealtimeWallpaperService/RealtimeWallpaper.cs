using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Net.Sockets;

namespace RealtimeWallpaperService
{
    public partial class RealtimeWallpaper : ServiceBase
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

        public RealtimeWallpaper()
        {
            InitializeComponent();
        }
        protected override void OnStart(string[] args)
        {
            //thread = new Thread(new ThreadStart(Run));
            //thread.Start();

            /*
            Image pngImage = Image.FromFile("R:\\latest.png");
            String tempFile = "R:\\latest.bmp";
            pngImage.Save(tempFile, ImageFormat.Bmp);
            int result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, tempFile, SPIF_UPDATEINIFILE);

            StreamWriter sw = new StreamWriter("R:\\abc.txt");
            sw.WriteLine(result);
            sw.Close();*/

            Process.Start(@"R:\\RealtimeWallpaper.exe");
        }
        protected override void OnStop()
        {
            run = false;
            if (thread != null) thread.Join();

            StreamWriter sw = new StreamWriter("R:\\b.txt");
            sw.WriteLine("bye");
            sw.Close();
        }

        private void Run()
        {
            run = true;
            while (run)
            {
                TcpClient tc = null;
                NetworkStream ns = null;
                try
                {
                    tc = new TcpClient(HOST, PORT);
                    ns = tc.GetStream();

                    ns.WriteByte(FLAG);
                    ns.Flush();

                    byte[] buffer = new byte[sizeof(int)];
                    for (int i = 0, max = buffer.Length; i < max; i++) buffer[i] = (byte)ns.ReadByte();
                    int size = BitConverter.ToInt32(buffer, 0);

                    buffer = new byte[size];
                    int r = 0, count = 0;
                    while (true)
                    {
                        r = ns.Read(buffer, count, buffer.Length - count);
                        count += r;
                        if (r < 0 || count >= size) break;
                    }

                    ns.WriteByte(SUCCESS);
                    ns.Flush();

                    String tempFile1 = System.IO.Path.GetTempFileName();
                    FileStream fs = File.OpenWrite(tempFile1);
                    fs.Write(buffer, 0, buffer.Length);
                    fs.Close();

                    Image pngImage = Image.FromFile(tempFile1);
                    String tempFile2 = System.IO.Path.GetTempFileName();
                    pngImage.Save(tempFile2, ImageFormat.Bmp);

                    int result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, tempFile2, SPIF_UPDATEINIFILE);

                    StreamWriter sw = new StreamWriter("R:\\a.txt", true);
                    sw.WriteLine(DateTime.Now.ToLongDateString());
                    sw.WriteLine(DateTime.Now.ToLongTimeString());
                    sw.WriteLine(tempFile1);
                    sw.WriteLine(tempFile2);
                    sw.WriteLine(result);
                    sw.WriteLine();
                    sw.Close();

                    Thread.Sleep(30000);
                }
                catch (Exception e)
                {
                    if (ns != null) ns.WriteByte(FAILURE);

                    StreamWriter sw = new StreamWriter("R:\\b.txt", true);
                    sw.WriteLine(DateTime.Now.ToLongDateString());
                    sw.WriteLine(DateTime.Now.ToLongTimeString());
                    sw.WriteLine(e.Message);
                    sw.WriteLine(e.ToString());
                    sw.WriteLine();
                    sw.Close();
                }
                finally
                {
                    if (ns != null) ns.Close();
                    if (tc != null) tc.Close();
                }
            }
        }
    }
}