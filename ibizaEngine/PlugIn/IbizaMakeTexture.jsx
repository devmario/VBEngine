#target photoshop

var isWin = (File.fs == "Windows");

for(var docI = 0; docI < app.documents.length; docI++) {
    var document = app.documents[docI];
    
    var i = 0;
    var j = 0;

    function getFileNameSubFileType(filePath) {
        var returnName = "";
        for(var m = filePath.length - 5; m >= 0; m--) {
            if(filePath[m] == (isWin ? '\\' : '/')) {
                break;
            } else {
                returnName = filePath[m] + returnName;
            }
        }
        return returnName;
    }

    Folder.current = File(document.fullName).parent;
    
    var txrName = getFileNameSubFileType(document.fullName.fsName);
    
    if(isWin)
    {
        document.saveAs(new File(Folder.current + "\\" + txrName + ".png"), new PNGSaveOptions, true);
    } else {
        document.saveAs(new File(Folder.current + "/" + txrName + ".png"), new PNGSaveOptions, true);
    }

    var uvPath;
    if(isWin)
    {
        uvPath = Folder.current.fsName + "\\" + txrName + ".uv";
    } else {
        uvPath = Folder.current.fsName + "/" + txrName + ".uv";
    }

    var uvExtension = new ExternalObject("lib:VBExternalForPhotoshop.framework");
    uvExtension.OpenUVFile(uvPath);

    Folder.current = File(document.fullName).parent;
    var slice_folder_path;
    if(isWin)
    {
        slice_folder_path = Folder.current.fsName + "\\" + txrName + "_slice";
    } else {
        slice_folder_path = Folder.current.fsName + "/" + txrName + "_slice";
    }
    var slice_folder = new Folder(slice_folder_path);
    if(slice_folder.created) {
        var fileList = slice_folder.getFiles()
        for (i = 0; i < fileList.length; i++) {
            if(fileList[i] instanceof File) {
                fileList[i].remove();
            }
        }
    } else {
        slice_folder.create();
    }

    function cropAndWriteTXR()
    {
        uvExtension.WriteUVName(document.layers[i].name);
        
        document.layers[i].bounds[0].type = Units.PIXELS;
        document.layers[i].bounds[1].type = Units.PIXELS;
        document.layers[i].bounds[2].type = Units.PIXELS;
        document.layers[i].bounds[3].type = Units.PIXELS;
        var x = document.layers[i].bounds[0].value;
        var y = document.layers[i].bounds[1].value;
        var w = document.layers[i].bounds[2].value - document.layers[i].bounds[0].value;
        var h = document.layers[i].bounds[3].value - document.layers[i].bounds[1].value;
        
        uvExtension.WriteUVInt(x);
        uvExtension.WriteUVInt(y);
        uvExtension.WriteUVInt(w);
        uvExtension.WriteUVInt(h);
        
        document.crop(document.layers[i].bounds);
        if(isWin)
        {
            document.saveAs(new File(slice_folder_path + "\\" + document.layers[i].name + ".png"), new PNGSaveOptions, true);
        } else {
            document.saveAs(new File(slice_folder_path + "/" + document.layers[i].name + ".png"), new PNGSaveOptions, true);
        }
    }

    for(i = 0; i < document.layers.length; i++)
    {
        document.suspendHistory("mark", "cropAndWriteTXR()");
        executeAction(charIDToTypeID("undo"), undefined, DialogModes.NO);
    }

    uvExtension.CloseUVFile();

    uvExtension.unload();
}
alert("완료.");