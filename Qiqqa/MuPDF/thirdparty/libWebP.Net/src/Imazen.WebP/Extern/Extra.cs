using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace Imazen.WebP.Extern {
    public partial class NativeMethods {
        
        public static void WebPSafeFree(IntPtr toDeallocate)
        {
            WebPFree(toDeallocate);
        }


        [DllImportAttribute("MuPDFLib", EntryPoint = "WebPFree", CallingConvention = CallingConvention.Cdecl)]
        public static extern void WebPFree(IntPtr toDeallocate);
    }
}