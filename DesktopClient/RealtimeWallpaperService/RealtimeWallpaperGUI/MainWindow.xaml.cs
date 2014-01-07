using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using System.Threading;
using System.Net.Sockets;
using System.IO;
using System.Drawing.Imaging;
using System.Drawing;
using System.Windows.Threading;

namespace RealtimeWallpaperGUI
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        private static readonly String HOST = "192.168.0.100";
        private static readonly int PORT = 9123;
        private static readonly byte FLAG = 2;
        private static readonly byte SUCCESS = 0;
        private static readonly byte FAILURE = 1;
        private static readonly int DELAY = 1;

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern Int32 SystemParametersInfo(UInt32 uiAction, UInt32 uiParam, String pvParam, UInt32 fWinIni);
        private static UInt32 SPI_SETDESKWALLPAPER = 20;
        private static UInt32 SPIF_UPDATEINIFILE = 0x01;
        private static UInt32 SPIF_SENDWININICHANGE = 0x02;

        private Thread thread = null;
        private volatile bool run = false;
        private String host = null;

        public MainWindow()
        {
            InitializeComponent();
        }
        private void Window_Unloaded(object sender, RoutedEventArgs e)
        {
            run = false;
            if (thread != null) thread.Join();
        }
        private void Start_Click(object sender, RoutedEventArgs e)
        {
            host = Host.Text.Trim();
            if (host == null || host.Length == 0) host = HOST;

            thread = new Thread(new ThreadStart(Run));
            thread.Start();
        }
        private void Stop_Click(object sender, RoutedEventArgs e)
        {
            run = false;
            if (thread != null) thread.Join();
        }

        private void Run()
        {
            String tempFile = null;
            int delay = DELAY;
            run = true;
            while (run)
            {
                delay++;
                if (delay > DELAY)
                {
                    delay = 0;
                    TcpClient tc = null;
                    NetworkStream ns = null;
                    try
                    {
                        tc = new TcpClient(host, PORT);
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

                        Dispatcher.BeginInvoke(DispatcherPriority.Normal, new DispatcherOperationCallback(delegate
                        {
                            Log.Text = String.Format("{0}{1}{2}", tempFile1, Environment.NewLine, tempFile2);
                            return null;
                        }), null);

                        /*
                        if (tempFile != null) File.Delete(tempFile);
                        tempFile = tempFile2;
                        File.Delete(tempFile1);*/

                        int result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, tempFile2, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);

/*

                        StreamWriter sw = new StreamWriter("R:\\a.txt", true);
                        sw.WriteLine(DateTime.Now.ToLongDateString());
                        sw.WriteLine(DateTime.Now.ToLongTimeString());
                        sw.WriteLine(tempFile1);
                        sw.WriteLine(tempFile2);
                        sw.WriteLine(result);
                        sw.WriteLine();
                        sw.Close();*/
                    }
                    catch (Exception e)
                    {
                        if (ns != null) ns.WriteByte(FAILURE);

                        Dispatcher.BeginInvoke(DispatcherPriority.Normal, new DispatcherOperationCallback(delegate
                        {
                            Log.Text = String.Format("{0}{1}{2}", e.Message, Environment.NewLine, e.ToString());
                            return null;
                        }), null);
/*

                        StreamWriter sw = new StreamWriter("R:\\b.txt", true);
                        sw.WriteLine(DateTime.Now.ToLongDateString());
                        sw.WriteLine(DateTime.Now.ToLongTimeString());
                        sw.WriteLine(e.Message);
                        sw.WriteLine(e.ToString());
                        sw.WriteLine();
                        sw.Close();*/
                    }
                    finally
                    {
                        if (ns != null) ns.Close();
                        if (tc != null) tc.Close();
                    }
                }

                Thread.Sleep(1000);
            }
        }
    }
}
