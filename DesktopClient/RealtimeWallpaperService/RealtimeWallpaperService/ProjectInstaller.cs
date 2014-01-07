using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration.Install;
using System.Linq;
using System.ServiceProcess;
using Microsoft.Win32;

namespace RealtimeWallpaperService
{
    [RunInstaller(true)]
    public partial class ProjectInstaller : System.Configuration.Install.Installer
    {
        public ProjectInstaller()
        {
            InitializeComponent();

            ServiceInstaller si = serviceInstaller;
            ServiceProcessInstaller spi = serviceProcessInstaller;

            /*
            RegistryKey rk = Registry.LocalMachine.OpenSubKey(String.Format(@"System\CurrentControlSet\Services\{0}", si.ServiceName), true);
            try
            {
                ServiceType stOld = (ServiceType)(int)rk.GetValue("type");
                ServiceType stNew = stOld | ServiceType.InteractiveProcess;
                rk.SetValue("type", (int)stNew);
            }
            catch (Exception e)
            {

            }
            finally
            {
                rk.Close();
            }*/
            /*
            RegistryKey rk = Registry.LocalMachine.OpenSubKey(@"SYSTEM\CurrentControlSet\Services\RealtimeWallpaper", true);
            if (rk != null)
            {
                object value = rk.GetValue("Type");
                if (value != null)
                {
                    rk.SetValue("Type", (int)value | 256);
                }
            }*/
        }
    }
}