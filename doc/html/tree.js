foldersTree = gFld("<b>Root</b>", "", "")
     insDoc(foldersTree, gLnk("Main Page", "", "main.html"))
aux1 = insFld(foldersTree, gFld("File List", "", "files.html"))
       insDoc(aux1, gLnk("wxMozillaBrowser.cpp", "", ""))
       insDoc(aux1, gLnk("wxMozillaBrowser.h", "", ""))
       insDoc(aux1, gLnk("wxMozillaBrowserChrome.cpp", "", ""))
       insDoc(aux1, gLnk("wxMozillaBrowserChrome.h", "", ""))
       insDoc(aux1, gLnk("wxMozillaChrome.cpp", "", ""))
       insDoc(aux1, gLnk("wxMozillaStream.cpp", "", ""))
       insDoc(aux1, gLnk("wxMozillaStream.h", "", ""))
aux1 = insFld(foldersTree, gFld("Compound List", "", "annotated.html"))
       insDoc(aux1, gLnk("wxMozillaBrowser", "", "classwxMozillaBrowser.html"))
       insDoc(aux1, gLnk("wxMozillaBrowserChrome", "", "classwxMozillaBrowserChrome.html"))
       insDoc(aux1, gLnk("wxMozillaStream", "", "classwxMozillaStream.html"))
aux1 = insFld(foldersTree, gFld("Class Hierarchy", "", "hierarchy.html"))
  aux2 = insFld(aux1, gFld("nsIEmbeddingSiteWindow", "", ""))
         insDoc(aux2, gLnk("wxMozillaBrowserChrome", "", "classwxMozillaBrowserChrome.html"))
  aux2 = insFld(aux1, gFld("nsIInputStream", "", ""))
         insDoc(aux2, gLnk("wxMozillaStream", "", "classwxMozillaStream.html"))
  aux2 = insFld(aux1, gFld("nsIInterfaceRequestor", "", ""))
         insDoc(aux2, gLnk("wxMozillaBrowserChrome", "", "classwxMozillaBrowserChrome.html"))
  aux2 = insFld(aux1, gFld("nsIWebBrowserChrome", "", ""))
         insDoc(aux2, gLnk("wxMozillaBrowserChrome", "", "classwxMozillaBrowserChrome.html"))
  aux2 = insFld(aux1, gFld("nsIWebBrowserChromeFocus", "", ""))
         insDoc(aux2, gLnk("wxMozillaBrowserChrome", "", "classwxMozillaBrowserChrome.html"))
  aux2 = insFld(aux1, gFld("nsIWebProgressListener", "", ""))
         insDoc(aux2, gLnk("wxMozillaBrowserChrome", "", "classwxMozillaBrowserChrome.html"))
  aux2 = insFld(aux1, gFld("wxWindow", "", ""))
         insDoc(aux2, gLnk("wxMozillaBrowser", "", "classwxMozillaBrowser.html"))
     insDoc(foldersTree, gLnk("Compound Members", "", "functions.html"))