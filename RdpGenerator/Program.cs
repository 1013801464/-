using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace RdpGenerator {

    /// <summary>
    /// 代码来自：https://www.lmlphp.com/user/56/article/item/4511/
    /// </summary>
    class Program {

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        internal struct DATA_BLOB {
            public int cbData;

            public IntPtr pbData;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        internal struct CRYPTPROTECT_PROMPTSTRUCT {
            public int cbSize;

            public int dwPromptFlags;

            public IntPtr hwndApp;

            public string szPrompt;
        }
        [DllImport("crypt32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        private static extern bool CryptProtectData(ref DATA_BLOB pDataIn, string szDataDescr, ref DATA_BLOB pOptionalEntropy, IntPtr pvReserved, ref CRYPTPROTECT_PROMPTSTRUCT pPromptStruct, int dwFlags, ref DATA_BLOB pDataOut);

        static void Main(string[] args) {
            rdpProfile("D:\\微云同步助手\\1013801464\\同步的文件\\2020春季-实验室\\远程桌面\\99-root-tr.rdp", "10.10.108.99", "root", "w^mSUgrT12@Oxs%e", 1280, 1024);
        }
        private static void rdpProfile(string filename, string address, string username, string password, int screenWidth, int screenHeight) {
            if (File.Exists(filename)) {
                File.Delete(filename);
            }
            using (StreamWriter streamWriter = new StreamWriter(filename, true)) {

                streamWriter.WriteLine("use multimon:i:0");        // 使用多个显示器
                if (screenWidth != 0 && screenHeight != 0) {
                    streamWriter.WriteLine("desktopwidth:i:" + screenWidth);
                    streamWriter.WriteLine("desktopheight:i:" + screenHeight);
                    streamWriter.WriteLine("screen mode id:i:1");  // 窗口化
                    streamWriter.WriteLine("winposstr:s:0,3,0,0," + (screenWidth + 40) + "," + (screenHeight + 40));
                } else {
                    streamWriter.WriteLine("screen mode id:i:2");  // 全屏
                }
                streamWriter.WriteLine("session bpp:i:32");    // 颜色深度 32位/24位/16位/15位
                streamWriter.WriteLine("compression:i:1");
                streamWriter.WriteLine("keyboardhook:i:2");
                streamWriter.WriteLine("audiocapturemode:i:0");
                streamWriter.WriteLine("videoplaybackmode:i:1");
                streamWriter.WriteLine("connection type:i:6");
                streamWriter.WriteLine("networkautodetect:i:1");
                streamWriter.WriteLine("bandwidthautodetect:i:1");
                streamWriter.WriteLine("displayconnectionbar:i:1");
                streamWriter.WriteLine("enableworkspacereconnect:i:0");
                streamWriter.WriteLine("disable wallpaper:i:0");
                streamWriter.WriteLine("allow font smoothing:i:1");  // 字体平滑(需打开桌面合成)
                streamWriter.WriteLine("allow desktop composition:i:1");  // 桌面合成
                streamWriter.WriteLine("disable full window drag:i:1");
                streamWriter.WriteLine("disable menu anims:i:1");
                streamWriter.WriteLine("disable themes:i:0");
                streamWriter.WriteLine("disable cursor setting:i:0");
                streamWriter.WriteLine("bitmapcachepersistenable:i:1");
                streamWriter.WriteLine("full address:s:" + address);
                streamWriter.WriteLine("audiomode:i:0");
                streamWriter.WriteLine("redirectprinters:i:0");
                streamWriter.WriteLine("redirectcomports:i:0");
                streamWriter.WriteLine("redirectsmartcards:i:0");
                streamWriter.WriteLine("redirectclipboard:i:1");
                streamWriter.WriteLine("redirectposdevices:i:0");
                streamWriter.WriteLine("autoreconnection enabled:i:1");
                streamWriter.WriteLine("authentication level:i:0");  // 0是不显示任何警告, 2是显示提示, 1是拒绝连接
                streamWriter.WriteLine("prompt for credentials:i:0");
                streamWriter.WriteLine("negotiate security layer:i:1");
                streamWriter.WriteLine("remoteapplicationmode:i:0");
                streamWriter.WriteLine("alternate shell:s:");
                streamWriter.WriteLine("shell working directory:s:");
                streamWriter.WriteLine("gatewayhostname:s:");
                streamWriter.WriteLine("gatewayusagemethod:i:4");
                streamWriter.WriteLine("gatewaycredentialssource:i:4");
                streamWriter.WriteLine("gatewayprofileusagemethod:i:0");
                streamWriter.WriteLine("promptcredentialonce:i:0");
                streamWriter.WriteLine("gatewaybrokeringtype:i:0");
                streamWriter.WriteLine("use redirection server name:i:0");
                streamWriter.WriteLine("rdgiskdcproxy:i:0");
                streamWriter.WriteLine("kdcproxyname:s:");
                streamWriter.WriteLine("drivestoredirect:s:F:\\;");
                if (!string.IsNullOrEmpty(username)) {
                    streamWriter.WriteLine("username:s:" + username);
                }
                if (!string.IsNullOrEmpty(password)) {
                    streamWriter.WriteLine("password 51:b:" + Encrypt(password));
                }
            }
        }


        private static string Encrypt(string password) {
            byte[] bytes = Encoding.Unicode.GetBytes(password);
            DATA_BLOB dATA_BLOB = default(DATA_BLOB);
            DATA_BLOB dATA_BLOB2 = default(DATA_BLOB);
            DATA_BLOB dATA_BLOB3 = default(DATA_BLOB);
            dATA_BLOB.cbData = bytes.Length;
            dATA_BLOB.pbData = Marshal.AllocHGlobal(bytes.Length);
            Marshal.Copy(bytes, 0, dATA_BLOB.pbData, bytes.Length);
            dATA_BLOB3.cbData = 0;
            dATA_BLOB3.pbData = IntPtr.Zero;
            dATA_BLOB2.cbData = 0;
            dATA_BLOB2.pbData = IntPtr.Zero;
            CRYPTPROTECT_PROMPTSTRUCT cRYPTPROTECT_PROMPTSTRUCT = new CRYPTPROTECT_PROMPTSTRUCT {
                cbSize = Marshal.SizeOf(typeof(CRYPTPROTECT_PROMPTSTRUCT)),
                dwPromptFlags = 0,
                hwndApp = IntPtr.Zero,
                szPrompt = null
            };
            if (CryptProtectData(ref dATA_BLOB, "psw", ref dATA_BLOB3, IntPtr.Zero, ref cRYPTPROTECT_PROMPTSTRUCT, 1, ref dATA_BLOB2)) {
                if (IntPtr.Zero != dATA_BLOB.pbData) {
                    Marshal.FreeHGlobal(dATA_BLOB.pbData);
                }
                if (IntPtr.Zero != dATA_BLOB3.pbData) {
                    Marshal.FreeHGlobal(dATA_BLOB3.pbData);
                }
                byte[] array = new byte[dATA_BLOB2.cbData];
                Marshal.Copy(dATA_BLOB2.pbData, array, 0, dATA_BLOB2.cbData);
                return BitConverter.ToString(array).Replace("-", string.Empty);
            }
            return string.Empty;

        }
    }
}
